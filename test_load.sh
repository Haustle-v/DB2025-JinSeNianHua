#!/bin/bash
cd ./build

# 配置路径
SERVER_PATH="./bin/rmdb"
CLIENT_PATH="../rmdb_client/build/rmdb_client"
TEST_DB="test_load"
SQL_FILE="../load_data.sql"

# 清理旧的测试数据库
echo "🔄 清理旧测试环境..."
rm -rf "$TEST_DB"

# 启动服务端（前台运行，方便查看错误）
echo "🚀 启动数据库服务端..."
$SERVER_PATH "$TEST_DB" &
SERVER_PID=$!

# 增加等待时间并检查服务端是否运行
echo "⏳ 等待服务端初始化..."
sleep 3

if ! ps -p $SERVER_PID > /dev/null; then
    echo "❌ 服务端启动失败！"
    exit 1
fi

# 执行测试并计时
echo "⏱️ 开始测试..."
echo "----------------------------------------"
time "$CLIENT_PATH" < "$SQL_FILE"
echo "----------------------------------------"

# 清理并关闭服务端
echo "🧹 测试完成，清理环境..."
kill $SERVER_PID
wait $SERVER_PID 2>/dev/null

echo "✅ 加载测试完成"
echo "💡 提示：实际执行时间见上方输出"
