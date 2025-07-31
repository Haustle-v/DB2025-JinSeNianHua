/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL
v2. You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include <netinet/in.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>

#include <atomic>
#include <future>

#include "analyze/analyze.h"
#include "errors.h"
#include "optimizer/optimizer.h"
#include "optimizer/plan.h"
#include "optimizer/planner.h"
#include "portal.h"
#include "recovery/log_recovery.h"
#include "config.h"

#define SOCK_PORT 8765
#define MAX_CONN_LIMIT 8

static bool should_exit = false;

// 构建全局所需的管理器对象
auto disk_manager = std::make_unique<DiskManager>();
auto buffer_pool_manager = std::make_unique<BufferPoolManager>(BUFFER_POOL_SIZE, disk_manager.get());
// auto index_buffer_pool_manager = std::make_unique<BufferPoolManager>(INDEX_BUFFER_POOL_SIZE, disk_manager.get());
auto rm_manager = std::make_unique<RmManager>(disk_manager.get(), buffer_pool_manager.get());
auto ix_manager = std::make_unique<IxManager>(disk_manager.get(), buffer_pool_manager.get());
auto sm_manager = std::make_unique<SmManager>(disk_manager.get(), buffer_pool_manager.get(), buffer_pool_manager.get(),
                                              rm_manager.get(), ix_manager.get());
auto lock_manager = std::make_unique<LockManager>();
auto txn_manager = std::make_unique<TransactionManager>(lock_manager.get(), sm_manager.get());
auto planner = std::make_unique<Planner>(sm_manager.get());
auto optimizer = std::make_unique<Optimizer>(sm_manager.get(), planner.get());
auto ql_manager = std::make_unique<QlManager>(sm_manager.get(), txn_manager.get(), nullptr);
auto log_manager = std::make_unique<LogManager>(disk_manager.get());
auto recovery = std::make_unique<RecoveryManager>(disk_manager.get(), buffer_pool_manager.get(), sm_manager.get());
auto portal = std::make_unique<Portal>(sm_manager.get());
auto analyze = std::make_unique<Analyze>(sm_manager.get());
// pthread_mutex_t *buffer_mutex;
pthread_mutex_t *sockfd_mutex;

// 多线程形式load data
std::deque<std::future<void> > futures;
std::mutex pool_mutex;

static jmp_buf jmpbuf;
void sigint_handler(int signo) {
  should_exit = true;
  log_manager->flush_log_to_disk();
  DEBUG_PRINT("The Server receive Crtl+C, will been closed\n");
  longjmp(jmpbuf, 1);
}

// 判断当前正在执行的是显式事务还是单条SQL语句的事务，并更新事务ID
void SetTransaction(txn_id_t *txn_id, Context *context) {
  context->txn_ = txn_manager->get_transaction(*txn_id);
  if (context->txn_ == nullptr || context->txn_->get_state() == TransactionState::COMMITTED ||
      context->txn_->get_state() == TransactionState::ABORTED) {
    context->txn_ = txn_manager->begin(nullptr, context->log_mgr_);
    *txn_id = context->txn_->get_transaction_id();
    context->txn_->set_txn_mode(false);
  }
}

void *client_handler(void *sock_fd) {
  int fd = *((int *)sock_fd);
  pthread_mutex_unlock(sockfd_mutex);

  int i_recvBytes;
  // 接收客户端发送的请求
  char data_recv[BUFFER_LENGTH];
  // 需要返回给客户端的结果
  char *data_send = new char[BUFFER_LENGTH];
  // 需要返回给客户端的结果的长度
  int offset = 0;
  // 记录客户端当前正在执行的事务ID
  txn_id_t txn_id = INVALID_TXN_ID;

  // 为每个客户端单独分配一个词法解析器 sqb 7.9
  yyscan_t scanner;
  yylex_init(&scanner);

  DEBUG_PRINT("establish client connection, sockfd: " + std::to_string(fd) + "\n");

  while (true) {
    DEBUG_PRINT("Waiting for request...");
    memset(data_recv, 0, BUFFER_LENGTH);

    i_recvBytes = read(fd, data_recv, BUFFER_LENGTH);

    if (i_recvBytes == 0) {
      DEBUG_PRINT("Maybe the client has closed");
      break;
    }
    if (i_recvBytes == -1) {
      DEBUG_PRINT("Client read error!");
      break;
    }

    DEBUG_PRINT("i_recvBytes:" << i_recvBytes);

    if (strcmp(data_recv, "exit") == 0) {
      DEBUG_PRINT("Client exit.");
      break;
    }
    if (strcmp(data_recv, "crash") == 0) {
      DEBUG_PRINT("Server crash");
      exit(1);
    }

    // set output_file off
    if (strcmp(data_recv, "set output_file off") == 0) {
      sm_manager->io_enabled_ = false;
      if (write(fd, data_send, offset + 1) == -1) {
        break;
      }
      continue;
    }

    if (strcmp(data_recv, "set output_file on") == 0) {
      sm_manager->io_enabled_ = true;
      if (write(fd, data_send, offset + 1) == -1) {
        break;
      }
      continue;
    }

    if (strncmp(data_recv, "load", 4) == 0) {
      std::string load_stmt(data_recv);
      int csv_file_end = load_stmt.find(" into ");
      int tab_name_start = csv_file_end + 6;
      int tab_name_end = load_stmt.find(";");

      std::string csv_file = load_stmt.substr(5, csv_file_end - 5);
      std::string tab_name = load_stmt.substr(tab_name_start, tab_name_end - tab_name_start);

      futures.emplace_back(std::async(std::launch::async, [csv_file, tab_name] {
        sm_manager->load_csv_data(csv_file, tab_name);
        // buffer_pool_manager->flush_all_pages(sm_manager->fhs_.at(tab_name)->GetFd());
      }));
      //   sm_manager->load_csv_data(csv_file, tab_name);
      if (write(fd, data_send, offset + 1) == -1) {
        break;
      }
      continue;
    }

    // 使用锁保证数据全部加载
    pool_mutex.lock();
    for (auto &future : futures) {
      future.get();
    }
    // if(!futures.empty()){
    //     for(auto &entry:sm_manager->fhs_){
    //       buffer_pool_manager->flush_all_pages(entry.second->GetFd());
    //     }
    //     for(auto &entry:sm_manager->ihs_){
    //       index_buffer_pool_manager->flush_all_pages(entry.second->get_fd());
    //     }
    // }
    futures.clear();
    pool_mutex.unlock();

    DEBUG_PRINT("Read from client " << fd << ": " << data_recv);

    memset(data_send, '\0', BUFFER_LENGTH);
    offset = 0;

    // 开启事务，初始化系统所需的上下文信息（包括事务对象指针、锁管理器指针、日志管理器指针、存放结果的buffer、记录结果长度的变量）
    Context *context =
        new Context(lock_manager.get(), log_manager.get(), nullptr, data_send, &offset, txn_manager.get());
    // sqb :启用事务 6.4
    SetTransaction(&txn_id, context);

    // 用于判断是否已经调用了yy_delete_buffer来删除buf
    bool finish_analyze = false;
    // pthread_mutex_lock(buffer_mutex);
    // YY_BUFFER_STATE buf = yy_scan_string(data_recv);
    YY_BUFFER_STATE buf = yy_scan_string(data_recv, scanner);
    if (yyparse(scanner) == 0) {
      if (ast::parse_tree != nullptr) {
        try {
          // analyze and rewrite
          std::shared_ptr<Query> query = analyze->do_analyze(ast::parse_tree);  // 将语法树转换为plan树
          yy_delete_buffer(buf, scanner);
          finish_analyze = true;
          //   pthread_mutex_unlock(buffer_mutex);

          // 特判快速统计数据量
          if (query->tables.size() == 1 && query->cols.size() == 1 && query->cols[0].aggFuncType == ast::AGG_COUNT &&
              query->conds.empty()) {
            auto &col = query->cols[0];
            std::string &col_name = col.alias == "" ? col.col_name : col.alias;
            ql_manager->quick_count_table(query->tables[0], col_name, context);
          } else {
            // 优化器
            std::shared_ptr<Plan> plan = optimizer->plan_query(query, context);
            // portal
            std::shared_ptr<PortalStmt> portalStmt = portal->start(plan, context);
            portal->run(portalStmt, ql_manager.get(), &txn_id, context);  // 真正执行
            portal->drop();
          }

        } catch (TransactionAbortException &e) {
          // 事务需要回滚，需要把abort信息返回给客户端并写入output.txt文件中
          std::string str = "abort\n";
          memcpy(data_send, str.c_str(), str.length());
          data_send[str.length()] = '\0';
          offset = str.length();

          // 回滚事务
          txn_manager->abort(context->txn_, log_manager.get());
          DEBUG_PRINT(e.GetInfo());

          if (sm_manager->io_enabled_) {  // yfs 7.3
            std::fstream outfile;
            outfile.open("output.txt", std::ios::out | std::ios::app);
            outfile << str;
            outfile.close();
          }
        } catch (RMDBError &e) {
          // 遇到异常，需要打印failure到output.txt文件中，并发异常信息返回给客户端
          std::cerr << e.what() << std::endl;

          memcpy(data_send, e.what(), e.get_msg_len());
          data_send[e.get_msg_len()] = '\n';
          data_send[e.get_msg_len() + 1] = '\0';
          offset = e.get_msg_len() + 1;

          if (sm_manager->io_enabled_) {  // yfs 7.3
            // 将报错信息写入output.txt
            std::fstream outfile;
            outfile.open("output.txt", std::ios::out | std::ios::app);
            outfile << "failure\n";
            outfile.close();
          }
        }
      }
    } else {
      std::string ParseError = "parse error";
      std::memcpy(data_send, ParseError.c_str(), ParseError.length());
      data_send[ParseError.length()] = '\n';
      data_send[ParseError.length() + 1] = '\0';
      offset = ParseError.length() + 1;

      // 将报错信息写入output.txt
      if (sm_manager->io_enabled_) {
        std::fstream outfile;
        outfile.open("output.txt", std::ios::out | std::ios::app);
        outfile << "failure\n";
        outfile.close();
      }
    }
    if (finish_analyze == false) {
      yy_delete_buffer(buf, scanner);
      //   pthread_mutex_unlock(buffer_mutex);
    }
    // future TODO: 格式化 sql_handler.result, 传给客户端
    // send result with fixed format, use protobuf in the future
    if (write(fd, data_send, offset + 1) == -1) {
      break;
    }
    // 如果是单挑语句，需要按照一个完整的事务来执行，所以执行完当前语句后，自动提交事务
    // sqb :启用事务 6.4
    if (context->txn_->get_txn_mode() == false) {
      txn_manager->commit(context->txn_, context->log_mgr_);
    }
  }

  // Clear
  DEBUG_PRINT("Terminating current client_connection...");
  close(fd);           // close a file descriptor.
  pthread_exit(NULL);  // terminate calling thread!
}

void start_server() {
  // init mutex
  //   buffer_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
  sockfd_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
  //   pthread_mutex_init(buffer_mutex, nullptr);
  pthread_mutex_init(sockfd_mutex, nullptr);

  int sockfd_server;
  int fd_temp;
  struct sockaddr_in s_addr_in{};

  // 初始化连接
  sockfd_server = socket(AF_INET, SOCK_STREAM, 0);  // ipv4,TCP
  assert(sockfd_server != -1);
  int val = 1;
  setsockopt(sockfd_server, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

  // before bind(), set the attr of structure sockaddr.
  memset(&s_addr_in, 0, sizeof(s_addr_in));
  s_addr_in.sin_family = AF_INET;
  s_addr_in.sin_addr.s_addr = htonl(INADDR_ANY);
  s_addr_in.sin_port = htons(SOCK_PORT);
  fd_temp = bind(sockfd_server, (struct sockaddr *)(&s_addr_in), sizeof(s_addr_in));
  if (fd_temp == -1) {
    DEBUG_PRINT("Bind error!");
    exit(1);
  }

  fd_temp = listen(sockfd_server, MAX_CONN_LIMIT);
  if (fd_temp == -1) {
    DEBUG_PRINT("Listen error!");
    exit(1);
  }

  while (!should_exit) {
    DEBUG_PRINT("Waiting for new connection...");
    pthread_t thread_id;
    struct sockaddr_in s_addr_client{};
    int client_length = sizeof(s_addr_client);

    if (setjmp(jmpbuf)) {
      DEBUG_PRINT("Break from Server Listen Loop\n");
      break;
    }

    // Block here. Until server accepts a new connection.
    pthread_mutex_lock(sockfd_mutex);
    int sockfd = accept(sockfd_server, (struct sockaddr *)(&s_addr_client), (socklen_t *)(&client_length));
    if (sockfd == -1) {
      DEBUG_PRINT("Accept error!");
      continue;  // ignore current socket ,continue while loop.
    }

    // 和客户端建立连接，并开启一个线程负责处理客户端请求
    if (pthread_create(&thread_id, nullptr, &client_handler, (void *)(&sockfd)) != 0) {
      DEBUG_PRINT("Create thread fail!");
      break;  // break while loop
    }
  }

  // Clear
  DEBUG_PRINT(" Try to close all client-connection.\n");
  int ret = shutdown(sockfd_server,
                     SHUT_WR);  // shut down the all or part of a full-duplex connection.
  if (ret == -1) {
    DEBUG_PRINT(strerror(errno));
  }
  //    assert(ret != -1);
  sm_manager->close_db();
  DEBUG_PRINT(" DB has been closed.\n");
  DEBUG_PRINT("Server shuts down.");
}

int main(int argc, char **argv) {
  if (argc != 2) {
    // 需要指定数据库名称
    std::cerr << "Usage: " << argv[0] << " <database>" << std::endl;
    exit(1);
  }

  signal(SIGINT, sigint_handler);
  try {
    DEBUG_PRINT("\n"
                 "  _____  __  __ _____  ____  \n"
                 " |  __ \\|  \\/  |  __ \\|  _ \\ \n"
                 " | |__) | \\  / | |  | | |_) |\n"
                 " |  _  /| |\\/| | |  | |  _ < \n"
                 " | | \\ \\| |  | | |__| | |_) |\n"
                 " |_|  \\_\\_|  |_|_____/|____/ \n"
                 "\n"
                 "Welcome to RMDB!\n"
                 "Type 'help;' for help.\n"
                 "\n");
    // Database name is passed by args
    std::string db_name = argv[1];
    if (!sm_manager->is_dir(db_name)) {
      // Database not found, create a new one
      sm_manager->create_db(db_name);
    }
    // Open database
    sm_manager->open_db(db_name);

    // recovery database
    recovery->analyze();
    recovery->redo();
    recovery->undo();

    // sqb 恢复后重新设置lsn 6.11
    log_manager->set_global_lsn(recovery->get_max_lsn() + 1);

    // 开启服务端，开始接受客户端连接
    start_server();
  } catch (RMDBError &e) {
    std::cerr << e.what() << std::endl;
    exit(1);
  }
  return 0;
}
