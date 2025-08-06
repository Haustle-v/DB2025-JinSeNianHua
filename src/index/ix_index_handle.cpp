/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL
v2. You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "ix_index_handle.h"

#include "ix_scan.h"

/**
 * @brief 在当前node中查找第一个>=target的key_idx
 *
 * @return
 * key_idx，范围为[0,num_key)，如果返回的key_idx=num_key，则表示target大于最后一个key
 * @note 返回key index（同时也是rid index），作为slot no
 */
int IxNodeHandle::lower_bound(const char *target) const {
  // Todo:
  // 查找当前节点中第一个大于等于target的key，并返回key的位置给上层
  // 提示:
  // 可以采用多种查找方式，如顺序遍历、二分查找等；使用ix_compare()函数进行比较

  // sqb: 5.25 二分实现 相当于找左边界
  int l = 0, r = page_hdr->num_key - 1;
  while (l <= r) {
    int mid = (l + r) >> 1;
    char *cur_key = get_key(mid);
    int cmp = ix_compare(target, cur_key, file_hdr->col_types_, file_hdr->col_lens_);
    if (cmp <= 0) {
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  //   二分最终的l就是结果 没找到时为num_key 找到了就是对应下标
  //   补充没有键值的情况
  return page_hdr->num_key == 0 ? -1 : l;
}

/**
 * @brief 在当前node中查找第一个>target的key_idx
 *
 * @return
 * key_idx，范围为[1,num_key)，如果返回的key_idx=num_key，则表示target大于等于最后一个key
 * @note 注意此处的范围从1开始
 */
int IxNodeHandle::upper_bound(const char *target) const {
  // Todo:
  // 查找当前节点中第一个大于target的key，并返回key的位置给上层
  // 提示:
  // 可以采用多种查找方式：顺序遍历、二分查找等；使用ix_compare()函数进行比较

  // sqb: 5.25 二分实现 还是找左边界 改条件判断即可
  int l = 0, r = page_hdr->num_key - 1;
  while (l <= r) {
    int mid = (l + r) >> 1;
    char *cur_key = get_key(mid);
    int cmp = ix_compare(target, cur_key, file_hdr->col_types_, file_hdr->col_lens_);
    if (cmp < 0) {
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  //   二分最终的l就是结果 没找到时为num_key 找到了就是对应下标
  //   补充没有键值的情况
  return page_hdr->num_key == 0 ? -1 : l;
}

/**
 * @brief 用于叶子结点根据key来查找该结点中的键值对
 * 值value作为传出参数，函数返回是否查找成功
 *
 * @param key 目标key
 * @param[out] value 传出参数，目标key对应的Rid
 * @return 目标key是否存在
 */
bool IxNodeHandle::leaf_lookup(const char *key, Rid **value) {
  // Todo:
  // 1. 在叶子节点中获取目标key所在位置
  // 2. 判断目标key是否存在
  // 3. 如果存在，获取key对应的Rid，并赋值给传出参数value
  // 提示：可以调用lower_bound()和get_rid()函数。

  // sqb 5.25
  assert(is_leaf_page() && "index try to loopup in not leaf node!");
  int pos = lower_bound(key);
  //   确保位置合法 验证相等 注意叶子节点的键和值的位置是对应的
  if (pos >= 0 && pos < page_hdr->num_key &&
      (ix_compare(key, get_key(pos), file_hdr->col_types_, file_hdr->col_lens_) == 0)) {
    *value = get_rid(pos);
    return true;
  }

  return false;
}

/**
 * 用于内部结点（非叶子节点）查找目标key所在的孩子结点（子树）
 * @param key 目标key
 * @return page_id_t 目标key所在的孩子节点（子树）的存储页面编号
 */
page_id_t IxNodeHandle::internal_lookup(const char *key) {
  // Todo:
  // 1. 查找当前非叶子节点中目标key所在孩子节点（子树）的位置
  // 2. 获取该孩子节点（子树）所在页面的编号
  // 3. 返回页面编号

  // sqb 5.25
  assert(!is_leaf_page() && "index try to loopup in not internal node!");
  int pos = upper_bound(key);
  //  内部节点的值要比键多一个 这么规定 key_idx对应的val是小于key的孩子
  //  key_idx+1为大于key的孩子 因此除了-1,其它情况均返回pos-1的孩子
  if (pos <= 0) {
    // 内部节点为空时 或小于第一个key
    return value_at(0);
  }

  return value_at(pos - 1);
}

/**
 * @brief 在指定位置插入n个连续的键值对
 * 将key的前n位插入到原来keys中的pos位置；将rid的前n位插入到原来rids中的pos位置
 *
 * @param pos 要插入键值对的位置
 * @param (key, rid) 连续键值对的起始地址，也就是第一个键值对，可以通过(key,
 * rid)来获取n个键值对
 * @param n 键值对数量
 * @note [0,pos)           [pos,num_key)
 *                            key_slot
 *                            /      \
 *                           /        \
 *       [0,pos)     [pos,pos+n)   [pos+n,num_key+n)
 *                      key           key_slot
 */
void IxNodeHandle::insert_pairs(int pos, const char *key, const Rid *rid, int n) {
  // Todo:
  // 1. 判断pos的合法性
  // 2. 通过key获取n个连续键值对的key值，并把n个key值插入到pos位置
  // 3. 通过rid获取n个连续键值对的rid值，并把n个rid值插入到pos位置
  // 4. 更新当前节点的键数量

  // sqb 5.25
  int key_num = get_size();
  if (pos < 0 || pos > key_num) {
    throw InternalError("ixNode try to insert pair at invalid pos");
  }

  //   处理键
  char *cur_key = get_key(pos);
  int move_num = key_num - pos;  // 要移动键的数量
  int key_len = file_hdr->col_tot_len_;
  // 先挪n个键的空间 然后再复制
  memmove(cur_key + n * key_len, cur_key, move_num * key_len);
  memcpy(cur_key, key, n * key_len);

  //   处理记录
  Rid *cur_rid = get_rid(pos);
  memmove(cur_rid + n, cur_rid, move_num * sizeof(Rid));
  memcpy(cur_rid, rid, n * sizeof(Rid));

  //   更新数量
  set_size(get_size() + n);
}

/**
 * @brief 用于在结点中插入单个键值对。
 * 函数返回插入后的键值对数量
 *
 * @param (key, value) 要插入的键值对
 * @return int 键值对数量
 */
int IxNodeHandle::insert(const char *key, const Rid &value) {
  // Todo:
  // 1. 查找要插入的键值对应该插入到当前节点的哪个位置
  // 2. 如果key重复则不插入
  // 3. 如果key不重复则插入键值对
  // 4. 返回完成插入操作之后的键值对数量

  //   sqb 5.25
  int pos = lower_bound(key);
  int key_num = get_size();
  // 当前节点为空 可以插到位置0
  pos = pos == -1 ? 0 : pos;
  if (pos >= 0 && pos < key_num && (ix_compare(key, get_key(pos), file_hdr->col_types_, file_hdr->col_lens_) == 0)) {
    // 键值重复
    return key_num;
  }
  insert_pair(pos, key, value);

  return get_size();
}

/**
 * @brief 用于在结点中的指定位置删除单个键值对
 *
 * @param pos 要删除键值对的位置
 */
void IxNodeHandle::erase_pair(int pos) {
  // Todo:
  // 1. 删除该位置的key
  // 2. 删除该位置的rid
  // 3. 更新结点的键值对数量

  // sqb 5.25
  int key_num = get_size();
  if (pos < 0 || pos >= key_num) {
    throw InternalError("ixNode try to erase pair at invalid pos");
  }

  char *cur_key = get_key(pos);
  int move_num = key_num - pos - 1;  // 要移动键的数量
  int key_len = file_hdr->col_tot_len_;

  //  保险起见移动完清零
  memmove(cur_key, cur_key + key_len, move_num * key_len);
  memset(cur_key + move_num * key_len, 0, key_len);

  Rid *cur_rid = get_rid(pos);
  memmove(cur_rid, cur_rid + 1, move_num * sizeof(Rid));
  memset(cur_rid + move_num, 0, sizeof(Rid));

  set_size(get_size() - 1);
}

/**
 * @brief 用于在结点中删除指定key的键值对。函数返回删除后的键值对数量
 *
 * @param key 要删除的键值对key值
 * @return 完成删除操作后的键值对数量
 */
int IxNodeHandle::remove(const char *key) {
  // Todo:
  // 1. 查找要删除键值对的位置
  // 2. 如果要删除的键值对存在，删除键值对
  // 3. 返回完成删除操作后的键值对数量

  // sqb 5.25
  int pos = lower_bound(key);
  int key_num = get_size();
  //   相等才删除键
  if (pos >= 0 && pos < key_num && (ix_compare(key, get_key(pos), file_hdr->col_types_, file_hdr->col_lens_) == 0)) {
    erase_pair(pos);
    return get_size();
  }

  return key_num;
}

//   为latch_ crabbing定义
inline bool IxNodeHandle::is_safe(Operation op) {
  if (op == Operation::FIND) return true;

  if (op == Operation::INSERT) {
    return get_size() + 1 < get_max_size();
  }

  //   删除时，删到1时根节点要被叶子节点替换 所以根节点最小为2
  int mini_size = is_root_page() ? 2 : get_min_size();
  if (op == Operation::DELETE) {
    return get_size() > mini_size;
  }

  //   查找
  return true;
}

IxIndexHandle::IxIndexHandle(DiskManager *disk_manager, BufferPoolManager *buffer_pool_manager, int fd)
    : disk_manager_(disk_manager), index_buffer_pool_manager_(buffer_pool_manager), fd_(fd) {
  // init file_hdr_
  disk_manager_->read_page(fd, IX_FILE_HDR_PAGE, (char *)&file_hdr_, sizeof(file_hdr_));
  char *buf = new char[PAGE_SIZE];
  memset(buf, 0, PAGE_SIZE);
  disk_manager_->read_page(fd, IX_FILE_HDR_PAGE, buf, PAGE_SIZE);
  file_hdr_ = new IxFileHdr();
  file_hdr_->deserialize(buf);
  delete buf;

  // disk_manager管理的fd对应的文件中，设置从file_hdr_->num_pages开始分配page_no
  int now_page_no = disk_manager_->get_fd2pageno(fd);
  disk_manager_->set_fd2pageno(fd, now_page_no + 1);
}

/**
 * @brief 用于查找指定键所在的叶子结点
 * @param key 要查找的目标key值
 * @param operation 查找到目标键值对后要进行的操作类型
 * @param transaction 事务参数，如果不需要则默认传入nullptr
 * @return [leaf node] and [root_is_latched] 返回目标叶子结点以及根结点是否加锁
 * @note need to Unlatch and unpin the leaf node outside!
 * 注意：用了FindLeafPage之后一定要unlatch叶结点，否则下次latch该结点会堵塞！
 */
std::pair<IxNodeHandle *, bool> IxIndexHandle::find_leaf_page(const char *key, Operation operation,
                                                              Transaction *transaction, bool find_first) {
  // Todo:
  // 1. 获取根节点
  // 2. 从根节点开始不断向下查找目标key
  // 3. 找到包含该key值的叶子结点停止查找，并返回叶子节点

  // sqb 5.26
  root_latch_.lock();
  bool root_locked = true;
  assert(file_hdr_->root_page_ != IX_NO_PAGE && "index start with invalid root page");
  IxNodeHandle *node = fetch_node(file_hdr_->root_page_);

  // 根据操作类型决定如何对根节点加锁
  if (operation == Operation::FIND) {
    node->page->RLatch();
    root_latch_.unlock();
    root_locked = false;
  } else {
    node->page->WLatch();
    if (node->is_safe(operation)) {
      root_latch_.unlock();
      root_locked = false;
    }
  }

  while (!node->is_leaf_page()) {
    // 参考了maintain 父节点的部分 递归应该也要unpin
    page_id_t child_page_no = node->internal_lookup(key);
    IxNodeHandle *child_node = fetch_node(child_page_no);
    if (operation == Operation::FIND) {
      child_node->page->RLatch();
      node->page->RUnlatch();
      index_buffer_pool_manager_->unpin_page(node->get_page_id(), false);
    } else {
      // 插入和删除在这里必须有事务指针
      child_node->page->WLatch();
      transaction->append_index_latch_page_set(node->page);
      if (child_node->is_safe(operation)) {
        if (root_locked) {
          root_latch_.unlock();
          root_locked = false;
        }
        release_all_ancestors(transaction);
      }
    }

    delete node;
    node = child_node;
  }

  //   插入和删除都需要加锁
  return std::make_pair(node, root_locked);
}

/**
 * @brief 用于查找指定键在叶子结点中的对应的值result
 *
 * @param key 查找的目标key值
 * @param result 用于存放结果的容器
 * @param transaction 事务指针
 * @return bool 返回目标键值对是否存在
 */
bool IxIndexHandle::get_value(const char *key, std::vector<Rid> *result, Transaction *transaction) {
  // Todo:
  // 1. 获取目标key值所在的叶子结点
  // 2. 在叶子节点中查找目标key值的位置，并读取key对应的rid
  // 3. 把rid存入result参数中
  // 提示：使用完buffer_pool提供的page之后，记得unpin page；记得处理并发的上锁

  // sqb 5.26
  auto entry = find_leaf_page(key, Operation::FIND, transaction);
  if (entry.first == nullptr) {
    throw InternalError("try find valud one invalid leaf page");
  }
  IxNodeHandle *leaf_node = entry.first;
  Rid *value = nullptr;
  bool ret = false;
  if (leaf_node->leaf_lookup(key, &value)) {
    result->emplace_back(*value);
    ret = true;
  }
  leaf_node->page->RUnlatch();
  index_buffer_pool_manager_->unpin_page(leaf_node->get_page_id(), false);
  delete leaf_node;

  return ret;
}

/**
 * @brief  将传入的一个node拆分(Split)成两个结点，在node的右边生成一个新结点new
 * node
 * @param node 需要拆分的结点
 * @return 拆分得到的new_node
 * @note need to unpin the new node outside
 * 注意：本函数执行完毕后，原node和new node都需要在函数外面进行unpin
 */
IxNodeHandle *IxIndexHandle::split(IxNodeHandle *node) {
  // Todo:
  // 1. 将原结点的键值对平均分配，右半部分分裂为新的右兄弟结点
  //    需要初始化新节点的page_hdr内容
  // 2. 如果新的右兄弟结点是叶子结点，更新新旧节点的prev_leaf和next_leaf指针
  //    为新节点分配键值对，更新旧节点的键值对数记录
  // 3.
  // 如果新的右兄弟结点不是叶子结点，更新该结点的所有孩子结点的父节点信息(使用IxIndexHandle::maintain_child())

  // sqb 5.27
  int init_size = node->get_size();
  assert(init_size == node->get_max_size() && "b+ tree split error");
  IxNodeHandle *right_node = create_node();
  right_node->page->WLatch();

  // 均分键值 b+的阶可能无法均分
  int left_num = init_size / 2;
  int right_num = init_size - left_num;
  node->set_size(left_num);
  right_node->set_size(right_num);

  char *left_key = node->get_key(left_num);
  Rid *left_rid = node->get_rid(left_num);
  int key_len = node->file_hdr->col_tot_len_;
  memmove(right_node->get_key(0), left_key, key_len * right_num);
  memset(left_key, 0, right_num * key_len);
  memmove(right_node->get_rid(0), left_rid, right_num * sizeof(Rid));
  memset(left_rid, 0, right_num * sizeof(Rid));

  //   初始化page_hdr
  right_node->page_hdr->next_free_page_no = IX_NO_PAGE;
  right_node->page_hdr->parent = node->get_parent_page_no();
  bool is_leaf = node->is_leaf_page();
  right_node->page_hdr->is_leaf = is_leaf;

  if (is_leaf) {
    // 参考erase leaf更新前后叶子
    page_id_t init_next_page_no = node->get_next_leaf();
    page_id_t right_page_no = right_node->get_page_no();
    node->set_next_leaf(right_page_no);

    right_node->set_prev_leaf(node->get_page_no());
    right_node->set_next_leaf(init_next_page_no);

    IxNodeHandle *init_next = fetch_node(init_next_page_no);
    init_next->page->WLatch();
    init_next->set_prev_leaf(right_page_no);
    init_next->page->WUnlatch();
    index_buffer_pool_manager_->unpin_page(init_next->get_page_id(), true);
    delete init_next;
  } else {
    // 若为内部节点 更新子节点的parent
    for (int child_idx = 0; child_idx < right_num; ++child_idx) {
      maintain_child(right_node, child_idx);
    }
  }

  return right_node;
}

/**
 * @brief Insert key & value pair into internal page after split
 * 拆分(Split)后，向上找到old_node的父结点
 * 将new_node的第一个key插入到父结点，其位置在 父结点指向old_node的孩子指针 之后
 * 如果插入后>=maxsize，则必须继续拆分父结点，然后在其父结点的父结点再插入，即需要递归
 * 直到找到的old_node为根结点时，结束递归（此时将会新建一个根R，关键字为key，old_node和new_node为其孩子）
 *
 * @param (old_node, new_node)
 * 原结点为old_node，old_node被分裂之后产生了新的右兄弟结点new_node
 * @param key 要插入parent的key
 * @note
 * 一个结点插入了键值对之后需要分裂，分裂后左半部分的键值对保留在原结点，在参数中称为old_node，
 * 右半部分的键值对分裂为新的右兄弟节点，在参数中称为new_node（参考Split函数来理解old_node和new_node）
 * @note 本函数执行完毕后，new node和old node都需要在函数外面进行unpin
 */
void IxIndexHandle::insert_into_parent(IxNodeHandle *old_node, const char *key, IxNodeHandle *new_node,
                                       Transaction *transaction) {
  // Todo:
  // 1. 分裂前的结点（原结点,
  // old_node）是否为根结点，如果为根结点需要分配新的root
  // 2. 获取原结点（old_node）的父亲结点
  // 3. 获取key对应的rid，并将(key, rid)插入到父亲结点
  // 4. 如果父亲结点仍需要继续分裂，则进行递归插入
  // 提示：记得unpin page

  // sqb 5.27
  if (old_node->is_root_page()) {
    // 原根节点分裂 创建新的 初始化
    IxNodeHandle *root_node = create_node();
    page_id_t root_page_no = root_node->get_page_no();
    root_node->page_hdr->next_free_page_no = IX_NO_PAGE;
    root_node->page_hdr->parent = old_node->get_parent_page_no();
    root_node->page_hdr->is_leaf = false;
    root_node->set_size(0);

    // 让两个节点指向它 现在节点是已经定住的 后面unpin即可
    old_node->set_parent_page_no(root_page_no);
    new_node->set_parent_page_no(root_page_no);

    // 当前根插入
    root_node->insert_pair(0, old_node->get_key(0), {old_node->get_page_no(), -1});
    root_node->insert_pair(1, new_node->get_key(0), {new_node->get_page_no(), -1});

    file_hdr_->root_page_ = root_page_no;
    // 释放资源
    root_latch_.unlock();
    release_all_ancestors(transaction);
    index_buffer_pool_manager_->unpin_page(root_node->get_page_id(), true);
    delete root_node;
  } else {
    // 直接找爹
    IxNodeHandle *parent_node = fetch_node(old_node->get_parent_page_no());

    //   将右侧节点的第一个插入
    int key_num = parent_node->insert(key, {new_node->get_page_no(), -1});
    if (key_num > file_hdr_->btree_order_) {
      // 还得分裂
      IxNodeHandle *new_split_right_node = split(parent_node);
      insert_into_parent(parent_node, new_split_right_node->get_key(0), new_split_right_node, transaction);
      new_split_right_node->page->WUnlatch();
      index_buffer_pool_manager_->unpin_page(new_split_right_node->get_page_id(), true);
      delete new_split_right_node;
    }
    release_all_ancestors(transaction);
    index_buffer_pool_manager_->unpin_page(parent_node->get_page_id(), true);
    delete parent_node;
  }
}

//   load专用
void IxIndexHandle::insert_entry_for_loader(const char *key, const Rid &value) {
  last_node_->insert_pair(last_node_->get_size(), key, value);
  //   先插入 在看情况分裂
  if (last_node_->get_size() > file_hdr_->btree_order_) {
    IxNodeHandle *new_right_split_node = split(last_node_);
    insert_into_parent(last_node_, new_right_split_node->get_key(0), new_right_split_node, nullptr);
    file_hdr_->last_leaf_ = new_right_split_node->get_page_no();
    new_right_split_node->page->WUnlatch();
    index_buffer_pool_manager_->unpin_page(last_node_->get_page_id(), true);
    delete last_node_;
    last_node_ = new_right_split_node;
  }
}

/**
 * @brief 将指定键值对插入到B+树中
 * @param (key, value) 要插入的键值对
 * @param transaction 事务指针
 * @return page_id_t 插入到的叶结点的page_no
 */
page_id_t IxIndexHandle::insert_entry(const char *key, const Rid &value, Transaction *transaction) {
  // Todo:
  // 1. 查找key值应该插入到哪个叶子节点
  // 2. 在该叶子节点中插入键值对
  // 3. 如果结点已满，分裂结点，并把新结点的相关信息插入父节点
  // 提示：记得unpin
  // page；若当前叶子节点是最右叶子节点，则需要更新file_hdr_.last_leaf；记得处理并发的上锁

  // sqb   5.28
  auto [leaf_node, root_locked] = find_leaf_page(key, Operation::INSERT, transaction);

  //   IxNodeHandle *leaf_node = entry.first;
  if (leaf_node == nullptr) {
    throw InternalError("insert entry at invalid leaf node");
  }
  char pre_first_key[file_hdr_->col_tot_len_];
  memcpy(pre_first_key, leaf_node->get_key(0), file_hdr_->col_tot_len_);
  int ket_num_before = leaf_node->get_size();
  int key_num_after = leaf_node->insert(key, value);
  char *cur_first_key = leaf_node->get_key(0);
  bool is_repeat = ket_num_before == key_num_after;

  //   //   处理并发情况下插入重复键值的问题
  //   if (is_repeat && transaction != nullptr) {
  //     throw TransactionAbortException(transaction->get_transaction_id(), AbortReason::WRITE_CONFLICT);
  //   }

  if (!is_repeat && key_num_after > file_hdr_->btree_order_) {
    // 如果没重复会直接插入 超过上限才分裂 更新父节点
    IxNodeHandle *new_right_split_node = split(leaf_node);
    //    更新最后叶子
    if (leaf_node->get_page_no() == file_hdr_->last_leaf_) {
      file_hdr_->last_leaf_ = new_right_split_node->get_page_no();
    }
    insert_into_parent(leaf_node, new_right_split_node->get_key(0), new_right_split_node, transaction);
    new_right_split_node->page->WUnlatch();
    index_buffer_pool_manager_->unpin_page(new_right_split_node->get_page_id(), true);
    delete new_right_split_node;
    root_locked = false;  // 这个会在insert_into_parent中释放锁，避免重复释放
  } else if (!is_repeat && memcmp(pre_first_key, cur_first_key, file_hdr_->col_tot_len_) != 0) {
    // 如果更新了第一个节点，那么维护父节点的对应key
    maintain_parent(leaf_node);
  }

  // 普通的插入或重复键值，处理锁资源
  if (root_locked) {
    root_latch_.unlock();
  }
  release_all_ancestors(transaction);

  //   重复则为读-false 不重复为写-true
  leaf_node->page->WUnlatch();
  page_id_t ret = leaf_node->get_page_no();
  index_buffer_pool_manager_->unpin_page(leaf_node->get_page_id(), !is_repeat);
  delete leaf_node;
  return ret;  // 返回值不重要
}

/**
 * @brief 用于删除B+树中含有指定key的键值对
 * @param key 要删除的key值
 * @param transaction 事务指针
 */
bool IxIndexHandle::delete_entry(const char *key, Transaction *transaction) {
  // Todo:
  // 1. 获取该键值对所在的叶子结点
  // 2. 在该叶子结点中删除键值对
  // 3.
  // 如果删除成功需要调用CoalesceOrRedistribute来进行合并或重分配操作，并根据函数返回结果判断是否有结点需要删除
  // 4.
  // 如果需要并发，并且需要删除叶子结点，则需要在事务的delete_page_set中添加删除结点的对应页面；记得处理并发的上锁

  //   sqb 5.28
  auto [leaf_node, root_locked] = find_leaf_page(key, Operation::DELETE, transaction);
  if (leaf_node == nullptr) {
    throw InternalError("delete at invalid leaf node");
  }
  //   IxNodeHandle *leaf_node = entry.first;
  //   bool root_locked = entry.second;

  int key_num_before = leaf_node->get_size();
  int key_num_after = leaf_node->remove(key);
  bool success = key_num_before != key_num_after;
  if (success) {
    // 成功删除才调整节点
    coalesce_or_redistribute(leaf_node, transaction, &root_locked);
  }
  //   处理锁资源
  if (root_locked) {
    root_latch_.unlock();
  }
  release_all_ancestors(transaction);

  //   仍根据success来unpin
  leaf_node->page->WUnlatch();
  index_buffer_pool_manager_->unpin_page(leaf_node->get_page_id(), success);
  delete leaf_node;
  return success;
}

/**
 * @brief 用于处理合并和重分配的逻辑，用于删除键值对后调用
 *
 * @param node 执行完删除操作的结点
 * @param transaction 事务指针
 * @param root_is_latched 传出参数：根节点是否上锁，用于并发操作
 * @return 是否需要删除结点
 * @note User needs to first find the sibling of input page.
 * If sibling's size + input page's size >= 2 * page's minsize, then
 * redistribute. Otherwise, merge(Coalesce).
 */
bool IxIndexHandle::coalesce_or_redistribute(IxNodeHandle *node, Transaction *transaction, bool *root_is_latched) {
  // Todo:
  // 1. 判断node结点是否为根节点
  //    1.1 如果是根节点，需要调用AdjustRoot()
  //    函数来进行处理，返回根节点是否需要被删除 1.2
  //    如果不是根节点，并且不需要执行合并或重分配操作，则直接返回false，否则执行2
  // 2. 获取node结点的父亲结点
  // 3. 寻找node结点的兄弟结点（优先选取前驱结点）
  // 4.
  // 如果node结点和兄弟结点的键值对数量之和，能够支撑两个B+树结点（即node.size+neighbor.size
  // >= NodeMinSize*2)，则只需要重新分配键值对（调用Redistribute函数）
  // 5.
  // 如果不满足上述条件，则需要合并两个结点，将右边的结点合并到左边的结点（调用Coalesce函数）

  // sqb 5.28
  int mini_size = node->get_min_size();

  if (node->is_root_page()) {
    // 根节点直接调整 调整根节点指向后放锁
    bool ret = adjust_root(node);
    if (*root_is_latched) {
      root_latch_.unlock();
      *root_is_latched = false;
    }
    // 根节点已经处理完，可以释放所有锁
    release_all_ancestors(transaction);
    return ret;
  } else if (node->get_size() >= mini_size) {
    // 叶子节点大小符合要求 该节点必定安全，根锁必然释放 同时释放所有锁
    maintain_parent(node);
    release_all_ancestors(transaction);
    return false;
  }

  //   叶子节点大小不符合要求 移动借或合并 这个时候必定有父节点的锁
  IxNodeHandle *parent_node = fetch_node(node->get_parent_page_no());
  bool need_remove = true;
  int node_idx = parent_node->find_child(node);
  IxNodeHandle *sibling_node = fetch_node(parent_node->value_at(node_idx == 0 ? node_idx + 1 : node_idx - 1));
  sibling_node->page->WLatch();

  if (node->get_size() + sibling_node->get_size() >= 2 * mini_size) {
    // 两节点仍可存在 重新分配键值
    if (*root_is_latched) {
      // 重分配不影响根 放锁
      root_latch_.unlock();
      *root_is_latched = false;
    }
    redistribute(sibling_node, node, parent_node, node_idx);
    release_all_ancestors(transaction);
    need_remove = false;
  } else {
    // 两节点需合并
    coalesce(&sibling_node, &node, &parent_node, node_idx, transaction, root_is_latched);
  }

  sibling_node->page->WUnlatch();
  index_buffer_pool_manager_->unpin_page(parent_node->get_page_id(), true);
  index_buffer_pool_manager_->unpin_page(sibling_node->get_page_id(), true);
  delete parent_node;
  delete sibling_node;

  return need_remove;
}

/**
 * @brief 用于当根结点被删除了一个键值对之后的处理
 * @param old_root_node 原根节点
 * @return bool 根结点是否需要被删除
 * @note size of root page can be less than min size and this method is only
 * called within coalesce_or_redistribute()
 */
bool IxIndexHandle::adjust_root(IxNodeHandle *old_root_node) {
  // Todo:
  // 1.
  // 如果old_root_node是内部结点，并且大小为1，则直接把它的孩子更新成新的根结点
  // 2. 如果old_root_node是叶结点，且大小为0，则直接更新root page
  // 3. 除了上述两种情况，不需要进行操作

  //   sqb 5.28
  int key_num = old_root_node->get_size();
  bool is_leaf = old_root_node->is_leaf_page();
  if (!is_leaf && key_num == 1) {
    // 内部节点删除时 让叶子做根
    IxNodeHandle *leaf_node = fetch_node(old_root_node->value_at(0));
    update_root_page_no(leaf_node->get_page_no());
    leaf_node->set_parent_page_no(IX_NO_PAGE);
    index_buffer_pool_manager_->unpin_page(leaf_node->get_page_id(), true);
    delete leaf_node;
    release_node_handle(*old_root_node);
    return true;
  } else if (is_leaf && key_num == 0) {
    // 根节点是叶子且无键值的情况下 这个节点应该不需要删除
    release_node_handle(*old_root_node);
    update_root_page_no(IX_INIT_ROOT_PAGE);
    return false;
  }

  return false;
}

/**
 * @brief 重新分配node和兄弟结点neighbor_node的键值对
 * Redistribute key & value pairs from one page to its sibling page. If index ==
 * 0, move sibling page's first key & value pair into end of input "node",
 * otherwise move sibling page's last key & value pair into head of input
 * "node".
 *
 * @param neighbor_node sibling page of input "node"
 * @param node input from method coalesceOrRedistribute()
 * @param parent the parent of "node" and "neighbor_node"
 * @param index node在parent中的rid_idx
 * @note node是之前刚被删除过一个key的结点
 * index=0，则neighbor是node后继结点，表示：node(left)      neighbor(right)
 * index>0，则neighbor是node前驱结点，表示：neighbor(left)  node(right)
 * 注意更新parent结点的相关kv对
 */
void IxIndexHandle::redistribute(IxNodeHandle *neighbor_node, IxNodeHandle *node, IxNodeHandle *parent, int index) {
  // Todo:
  // 1. 通过index判断neighbor_node是否为node的前驱结点
  // 2. 从neighbor_node中移动一个键值对到node结点中
  // 3.
  // 更新父节点中的相关信息，并且修改移动键值对对应孩字结点的父结点信息（maintain_child函数）
  // 注意：neighbor_node的位置不同，需要移动的键值对不同，需要分类讨论

  // sqb 5.29

  //   index 为0 代表node在左边 否则在右边
  int remove_pos = index == 0 ? 0 : neighbor_node->get_size() - 1;
  int insert_pos = index == 0 ? node->get_size() : 0;
  node->insert_pair(insert_pos, neighbor_node->get_key(remove_pos), *neighbor_node->get_rid(remove_pos));
  neighbor_node->erase_pair(remove_pos);
  maintain_child(node, insert_pos);
  //   两个节点都维护一下 否则左边第一个若是被删将没有被维护
  maintain_parent(node);
  maintain_parent(neighbor_node);
}

/**
 * @brief
 * 合并(Coalesce)函数是将node和其直接前驱进行合并，也就是和它左边的neighbor_node进行合并；
 * 假设node一定在右边。如果上层传入的index=0，说明node在左边，那么交换node和neighbor_node，保证node在右边；合并到左结点，实际上就是删除了右结点；
 * Move all the key & value pairs from one page to its sibling page, and notify
 * buffer pool manager to delete this page. Parent page must be adjusted to take
 * info of deletion into account. Remember to deal with coalesce or redistribute
 * recursively if necessary.
 *
 * @param neighbor_node sibling page of input "node"
 * (neighbor_node是node的前结点)
 * @param node input from method coalesceOrRedistribute()
 * (node结点是需要被删除的)
 * @param parent parent page of input "node"
 * @param index node在parent中的rid_idx
 * @return true means parent node should be deleted, false means no deletion
 * happend
 * @note Assume that *neighbor_node is the left sibling of *node (neighbor ->
 * node)
 */
bool IxIndexHandle::coalesce(IxNodeHandle **neighbor_node, IxNodeHandle **node, IxNodeHandle **parent, int index,
                             Transaction *transaction, bool *root_is_latched) {
  // Todo:
  // 1.
  // 用index判断neighbor_node是否为node的前驱结点，若不是则交换两个结点，让neighbor_node作为左结点，node作为右结点
  // 2.
  // 把node结点的键值对移动到neighbor_node中，并更新node结点孩子结点的父节点信息（调用maintain_child函数）
  // 3.
  // 释放和删除node结点，并删除parent中node结点的信息，返回parent是否需要被删除
  // 提示：如果是叶子结点且为最右叶子结点，需要更新file_hdr_.last_leaf

  // sqb 5.29
  //   index 为0 node在左边 交换！ 注意交换后index变了
  if (index == 0) {
    std::swap(neighbor_node, node);
    ++index;
  }

  //   移动键值 因为右侧节点都比前一节点大 直接查到尾巴
  int key_num = (*node)->get_size();
  (*neighbor_node)->insert_pairs((*neighbor_node)->get_size(), (*node)->get_key(0), (*node)->get_rid(0), key_num);

  bool is_leaf = (*node)->is_leaf_page();

  //   维护新挪移的孩子 内部节点才需要维护
  if (!is_leaf) {
    int merge_key_size = (*neighbor_node)->get_size();
    for (int child_idx = merge_key_size - key_num; child_idx < merge_key_size; ++child_idx) {
      maintain_child(*neighbor_node, child_idx);
    }
  }

  //   更新最后叶子
  if (is_leaf && file_hdr_->last_leaf_ == (*node)->get_page_no()) {
    file_hdr_->last_leaf_ = (*neighbor_node)->get_page_no();
  }

  //   释放并删除node
  if (is_leaf) {
    erase_leaf(*node);
  }
  (*parent)->erase_pair(index);
  release_node_handle(**node);
  //   维护它爹
  return coalesce_or_redistribute(*parent, transaction, root_is_latched);
}

/**
 * @brief 这里把iid转换成了rid，即iid的slot_no作为node的rid_idx(key_idx)
 * node其实就是把slot_no作为键值对数组的下标
 * 换而言之，每个iid对应的索引槽存了一对(key,rid)，指向了(要建立索引的属性首地址,插入/删除记录的位置)
 *
 * @param iid
 * @return Rid
 * @note
 * iid和rid存的不是一个东西，rid是上层传过来的记录位置，iid是索引内部生成的索引槽位置
 */
Rid IxIndexHandle::get_rid(const Iid &iid) const {
  IxNodeHandle *node = fetch_node(iid.page_no);
  node->page->RLatch();
  if (iid.slot_no >= node->get_size()) {
    node->page->RUnlatch();
    throw IndexEntryNotFoundError();
  }
  Rid ret = *node->get_rid(iid.slot_no);
  node->page->RUnlatch();
  index_buffer_pool_manager_->unpin_page(node->get_page_id(), false);  // unpin it!
  delete node;
  return ret;
}

/**
 * @brief FindLeafPage + lower_bound
 *
 * @param key
 * @return Iid
 * @note 上层传入的key本来是int类型，通过(const char *)&key进行了转换
 * 可用*(int *)key转换回去
 */
Iid IxIndexHandle::lower_bound(const char *key) {
  // sqb 5.29
  IxNodeHandle *leaf_node = find_leaf_page(key, Operation::FIND, nullptr).first;
  int key_idx = leaf_node->lower_bound(key);
  Iid ret{-1, -1};
  if (key_idx == leaf_node->get_size()) {
    if (leaf_node->get_next_leaf() == IX_LEAF_HEADER_PAGE) {
      ret = leaf_end();
    } else {
      ret.page_no = leaf_node->get_next_leaf();
      ret.slot_no = 0;
    }
  } else if (key_idx == -1) {
    ret = leaf_end();
  } else {
    ret.page_no = leaf_node->get_page_no();
    ret.slot_no = key_idx;
  }
  leaf_node->page->RUnlatch();
  index_buffer_pool_manager_->unpin_page(leaf_node->get_page_id(), false);
  delete leaf_node;
  return ret;
}

/**
 * @brief FindLeafPage + upper_bound
 *
 * @param key
 * @return Iid
 */
Iid IxIndexHandle::upper_bound(const char *key) {
  // sqb 5.29
  IxNodeHandle *leaf_node = find_leaf_page(key, Operation::FIND, nullptr).first;
  int key_idx = leaf_node->upper_bound(key);
  Iid ret{-1, -1};
  if (key_idx == -1) {
    ret = leaf_end();
  } else if (key_idx == leaf_node->get_size()) {
    if (leaf_node->get_next_leaf() == IX_LEAF_HEADER_PAGE) {
      ret = leaf_end();
    } else {
      ret.page_no = leaf_node->get_next_leaf();
      ret.slot_no = 0;
    }
  } else if (key_idx == -1) {
    ret = leaf_end();
  } else {
    ret.page_no = leaf_node->get_page_no();
    ret.slot_no = key_idx;
  }
  leaf_node->page->RUnlatch();
  index_buffer_pool_manager_->unpin_page(leaf_node->get_page_id(), false);
  delete leaf_node;
  return ret;
}

/**
 * @brief 指向最后一个叶子的最后一个结点的后一个
 * 用处在于可以作为IxScan的最后一个
 *
 * @return Iid
 */
Iid IxIndexHandle::leaf_end() const {
  IxNodeHandle *node = fetch_node(file_hdr_->last_leaf_);
  node->page->RLatch();
  Iid iid = {.page_no = file_hdr_->last_leaf_, .slot_no = node->get_size()};
  node->page->RUnlatch();
  index_buffer_pool_manager_->unpin_page(node->get_page_id(), false);  // unpin it!
  delete node;
  return iid;
}

/**
 * @brief 指向第一个叶子的第一个结点
 * 用处在于可以作为IxScan的第一个
 *
 * @return Iid
 */
Iid IxIndexHandle::leaf_begin() const {
  Iid iid = {.page_no = file_hdr_->first_leaf_, .slot_no = 0};
  return iid;
}

/**
 * @brief 获取一个指定结点
 *
 * @param page_no
 * @return IxNodeHandle*
 * @note pin the page, remember to unpin it outside!
 */
IxNodeHandle *IxIndexHandle::fetch_node(int page_no) const {
  Page *page = index_buffer_pool_manager_->fetch_page(PageId{fd_, page_no});
  IxNodeHandle *node = new IxNodeHandle(file_hdr_, page);

  return node;
}

/**
 * @brief 创建一个新结点
 *
 * @return IxNodeHandle*
 * @note pin the page, remember to unpin it outside!
 * 注意：对于Index的处理是，删除某个页面后，认为该被删除的页面是free_page
 * 而first_free_page实际上就是最新被删除的页面，初始为IX_NO_PAGE
 * 在最开始插入时，一直是create
 * node，那么first_page_no一直没变，一直是IX_NO_PAGE
 * 与Record的处理不同，Record将未插入满的记录页认为是free_page
 */
IxNodeHandle *IxIndexHandle::create_node() {
  IxNodeHandle *node;
  file_hdr_->num_pages_++;

  PageId new_page_id = {.fd = fd_, .page_no = INVALID_PAGE_ID};
  // 从3开始分配page_no，第一次分配之后，new_page_id.page_no=3，file_hdr_.num_pages=4
  Page *page = index_buffer_pool_manager_->new_page(&new_page_id);
  if (page == nullptr) {
    throw PageNotExistError(disk_manager_->get_file_name(fd_), new_page_id.page_no);
  }
  node = new IxNodeHandle(file_hdr_, page);
  return node;
}

/**
 * @brief 从node开始更新其父节点的第一个key，一直向上更新直到根节点
 *
 * @param node
 */
void IxIndexHandle::maintain_parent(IxNodeHandle *node) {
  IxNodeHandle *curr = node;
  while (curr->get_parent_page_no() != IX_NO_PAGE) {
    // Load its parent
    IxNodeHandle *parent = fetch_node(curr->get_parent_page_no());
    int rank = parent->find_child(curr);
    char *parent_key = parent->get_key(rank);
    char *child_first_key = curr->get_key(0);
    if (memcmp(parent_key, child_first_key, file_hdr_->col_tot_len_) == 0) {
      assert(index_buffer_pool_manager_->unpin_page(parent->get_page_id(), true));
      delete parent;
      break;
    }
    memcpy(parent_key, child_first_key,
           file_hdr_->col_tot_len_);  // 修改了parent node
    curr = parent;

    assert(index_buffer_pool_manager_->unpin_page(parent->get_page_id(), true));
    delete parent;
  }
}

/**
 * @brief
 * 要删除leaf之前调用此函数，更新leaf前驱结点的next指针和后继结点的prev指针
 *
 * @param leaf 要删除的leaf
 */
void IxIndexHandle::erase_leaf(IxNodeHandle *leaf) {
  // 这个函数只有合并时会被调 并且leaf是右侧的节点 所以只需为next加锁
  assert(leaf->is_leaf_page());

  IxNodeHandle *prev = fetch_node(leaf->get_prev_leaf());
  prev->set_next_leaf(leaf->get_next_leaf());
  index_buffer_pool_manager_->unpin_page(prev->get_page_id(), true);
  delete prev;

  IxNodeHandle *next = fetch_node(leaf->get_next_leaf());
  next->page->WLatch();
  next->set_prev_leaf(leaf->get_prev_leaf());  // 注意此处是SetPrevLeaf()
  next->page->WUnlatch();
  index_buffer_pool_manager_->unpin_page(next->get_page_id(), true);
  delete next;
}

/**
 * @brief 删除node时，更新file_hdr_.num_pages
 *
 * @param node
 */
void IxIndexHandle::release_node_handle(IxNodeHandle &node) { file_hdr_->num_pages_--; }

/**
 * @brief 将node的第child_idx个孩子结点的父节点置为node
 */
void IxIndexHandle::maintain_child(IxNodeHandle *node, int child_idx) {
  if (!node->is_leaf_page()) {
    //  Current node is inner node, load its child and set its parent to current
    //  node
    int child_page_no = node->value_at(child_idx);
    IxNodeHandle *child = fetch_node(child_page_no);
    child->set_parent_page_no(node->get_page_no());
    index_buffer_pool_manager_->unpin_page(child->get_page_id(), true);
    delete child;
  }
}

//   latch crabbing过程中，用于释放祖先节点
void IxIndexHandle::release_all_ancestors(Transaction *txn) {
  if (txn != nullptr) {
    auto &latch_pages = *txn->get_index_latch_page_set();
    for (auto &page : latch_pages) {
      page->WUnlatch();
      index_buffer_pool_manager_->unpin_page(page->get_page_id(), false);
    }
    txn->get_index_latch_page_set()->clear();
  }
}
