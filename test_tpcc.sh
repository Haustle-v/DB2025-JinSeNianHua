#!/bin/bash
cd ./build

# 配置路径
SERVER_PATH="./bin/rmdb"
CLIENT_PATH="../rmdb_client/build/rmdb_client"
TEST_DB="test_tpcc"
TXN_DIR="../tpcc_sql"
CHECK_SQL="../check_consistency.sql"
LOAD_SQL="../load_data.sql"
THREADS=8  # 可调整线程数

# 清理旧数据库
echo "🔄 清理旧测试环境..."
rm -rf "$TEST_DB"

# 启动服务端
echo "🚀 启动数据库服务端..."
$SERVER_PATH "$TEST_DB" &
SERVER_PID=$!

# 等待服务端启动
echo "⏳ 等待服务端初始化..."
sleep 5
if ! ps -p $SERVER_PID > /dev/null; then
    echo "❌ 服务端启动失败！"
    exit 1
fi

echo "⏳ 等待数据加载..."
time "$CLIENT_PATH" < "$LOAD_SQL"
echo "⏱️ 数据加载完毕"

# 执行并发事务
echo "⚙️ 并发执行事务脚本..."
echo "----------------------------------------"
start_time=$(date +%s)

# # 启动perf采样（后台运行）
# echo "🔍 开始性能采样..."
# sudo perf record -F 99 -g -p $SERVER_PID -o "$PERF_DATA" &
# PERF_PID=$!

PIDS=()
for ((i=0; i<$THREADS; i++)); do
    TXN_FILE="$TXN_DIR/tpcc_txn_$i.sql"
    "$CLIENT_PATH" < "$TXN_FILE" &
    PIDS+=($!)
done

# 等待所有子进程完成
for pid in "${PIDS[@]}"; do
    wait $pid
done

end_time=$(date +%s)
elapsed=$((end_time - start_time))
echo "----------------------------------------"
echo "⏱️ 所有事务完成，总耗时: ${elapsed} 秒"

# 执行一致性检查
echo "🔍 执行一致性检查..."
"$CLIENT_PATH" < "$CHECK_SQL"

# 停止服务端
echo "🧹 测试完成，关闭服务端..."
kill $SERVER_PID
wait $SERVER_PID 2>/dev/null

echo "✅ 并发测试完成"
