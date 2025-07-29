import random
from datetime import datetime
import os

consistency_checks = [
    "select d_next_o_id from district where d_w_id=5 and d_id=10;",
    "select MAX(o_id) as max_o_id from orders where o_w_id=5 and o_d_id=10;",
    "select MAX(no_o_id) as max_no_o_id from new_orders where no_w_id=5 and no_d_id=10;",
    "select COUNT(no_o_id) as count_no_o_id from new_orders where no_w_id=5 and no_d_id=10;",
    "select MAX(no_o_id) as max_no_o_id from new_orders where no_w_id=5 and no_d_id=10;",
    "select MIN(no_o_id) as min_no_o_id from new_orders where no_w_id=5 and no_d_id=10;",
    "select SUM(o_ol_cnt) as sum_ol_cnt from orders where o_w_id=5 and o_d_id=10;",
    "select COUNT(ol_o_id) as count_ol_o_id from order_line where ol_w_id=5 and ol_d_id=10;"
]


class TPCCSQLGenerator:
    def __init__(self, warehouse_count=1):
        self.warehouse_count = warehouse_count
        self.districts_per_warehouse = 10
        self.customers_per_district = 3000
        self.items_count = 100000

    def generate_new_order(self):
        w_id = random.randint(1, self.warehouse_count)
        d_id = random.randint(1, self.districts_per_warehouse)
        c_id = random.randint(1, self.customers_per_district)
        o_id = random.randint(1, 1000000)
        ol_cnt = random.randint(5, 15)  # 订单行数

        sqls = []

        # 查询客户和仓库信息
        sqls.append(f"SELECT c_discount, c_last, c_credit, w_tax FROM customer, warehouse "
                    f"WHERE w_id={w_id} AND c_w_id={w_id} AND c_d_id={d_id} AND c_id={c_id};")

        # 查询地区信息
        sqls.append(f"SELECT d_next_o_id, d_tax FROM district "
                    f"WHERE d_id={d_id} AND d_w_id={w_id};")

        # 更新地区订单ID
        next_o_id = o_id + 1
        sqls.append(f"UPDATE district SET d_next_o_id={next_o_id} "
                    f"WHERE d_id={d_id} AND d_w_id={w_id};")

        # 插入订单
        entry_date = datetime.now().strftime("'%Y-%m-%d %H:%M:%S'")
        sqls.append(f"INSERT INTO orders VALUES({o_id}, {d_id}, {w_id}, {c_id}, {entry_date}, "
                    f"1, {ol_cnt}, 1);")

        # 插入新订单
        sqls.append(f"INSERT INTO new_orders VALUES({o_id}, {d_id}, {w_id});")

        # 生成订单行
        for ol_number in range(1, ol_cnt + 1):
            ol_i_id = random.randint(1, self.items_count)
            ol_supply_w_id = w_id
            ol_quantity = random.randint(1, 10)
            ol_amount = round(random.uniform(1, 100), 2)
            ol_dist_info = f"'DIST_INFO_{random.randint(1, 100)}'"

            # 查询商品信息
            sqls.append(f"SELECT i_price, i_name, i_data FROM item WHERE i_id={ol_i_id};")

            # 查询库存信息
            sqls.append(f"SELECT s_quantity, s_data, s_dist_01, s_dist_02, s_dist_03, "
                        f"s_dist_04, s_dist_05, s_dist_06, s_dist_07, s_dist_08, s_dist_09, "
                        f"s_dist_10 FROM stock WHERE s_i_id={ol_i_id} AND s_w_id={ol_supply_w_id};")

            # 更新库存
            new_quantity = random.randint(1, 100)  # 简化处理
            sqls.append(f"UPDATE stock SET s_quantity={new_quantity} "
                        f"WHERE s_i_id={ol_i_id} AND s_w_id={ol_supply_w_id};")

            # 插入订单行
            delivery_date = "'NULL'"
            sqls.append(f"INSERT INTO order_line VALUES ({o_id}, {d_id}, {w_id}, {ol_number}, "
                        f"{ol_i_id}, {ol_supply_w_id}, {delivery_date}, {ol_quantity}, "
                        f"{ol_amount}, {ol_dist_info});")

        return sqls

    def generate_payment(self):
        w_id = random.randint(1, self.warehouse_count)
        d_id = random.randint(1, self.districts_per_warehouse)
        c_id = random.randint(1, self.customers_per_district)
        h_amount = round(random.uniform(1, 5000), 2)

        sqls = []

        # 更新仓库余额
        sqls.append(f"UPDATE warehouse SET w_ytd=w_ytd+{h_amount} WHERE w_id={w_id};")

        # 查询仓库信息
        sqls.append(f"SELECT w_street_1, w_street_2, w_city, w_state, w_zip, w_name "
                    f"FROM warehouse WHERE w_id={w_id};")

        # 更新地区余额
        sqls.append(f"UPDATE district SET d_ytd=d_ytd+{h_amount} "
                    f"WHERE d_w_id={w_id} AND d_id={d_id};")

        # 查询地区信息
        sqls.append(f"SELECT d_street_1, d_street_2, d_city, d_state, d_zip, d_name "
                    f"FROM district WHERE d_w_id={w_id} AND d_id={d_id};")

        # 查询客户信息
        sqls.append(f"SELECT c_first, c_middle, c_last, c_street_1, c_street_2, c_city, "
                    f"c_state, c_zip, c_phone, c_credit, c_credit_lim, c_discount, c_balance, "
                    f"c_since FROM customer WHERE c_w_id={w_id} AND c_d_id={d_id} AND c_id={c_id};")

        # 更新客户余额
        c_balance = round(random.uniform(-1000, 10000), 2)
        sqls.append(f"UPDATE customer SET c_balance={c_balance} "
                    f"WHERE c_w_id={w_id} AND c_d_id={d_id} AND c_id={c_id};")

        # 插入历史记录
        h_date = datetime.now().strftime("'%Y-%m-%d %H:%M:%S'")
        h_data = "'Payment transaction'"
        sqls.append(f"INSERT INTO history VALUES({c_id}, {d_id}, {w_id}, {d_id}, {w_id}, "
                    f"{h_date}, {h_amount}, {h_data});")

        return sqls

    def generate_delivery(self):
        w_id = random.randint(1, self.warehouse_count)
        d_id = random.randint(1, self.districts_per_warehouse)
        o_carrier_id = random.randint(1, 10)
        datetime_str = datetime.now().strftime("'%Y-%m-%d %H:%M:%S'")

        sqls = []

        # 查询最小订单ID
        sqls.append(f"SELECT min(no_o_id) as min_o_id FROM new_orders "
                    f"WHERE no_d_id={d_id} AND no_w_id={w_id};")

        # 假设获取的订单ID
        o_id = random.randint(1, 1000000)

        # 删除新订单
        sqls.append(f"DELETE FROM new_orders WHERE no_o_id={o_id} "
                    f"AND no_d_id={d_id} AND no_w_id={w_id};")

        # 查询订单客户ID
        sqls.append(f"SELECT o_c_id FROM orders WHERE o_id={o_id} "
                    f"AND o_d_id={d_id} AND o_w_id={w_id};")

        # 假设获取的客户ID
        c_id = random.randint(1, self.customers_per_district)

        # 更新订单承运商
        sqls.append(f"UPDATE orders SET o_carrier_id={o_carrier_id} "
                    f"WHERE o_id={o_id} AND o_d_id={d_id} AND o_w_id={w_id};")

        # 更新订单行交付日期
        sqls.append(f"UPDATE order_line SET ol_delivery_d={datetime_str} "
                    f"WHERE ol_o_id={o_id} AND ol_d_id={d_id} AND ol_w_id={w_id};")

        # 计算订单总金额
        sqls.append(f"SELECT sum(ol_amount) as sum_amount FROM order_line "
                    f"WHERE ol_o_id={o_id} AND ol_d_id={d_id};")

        # 假设获取的订单总金额
        sum_amount = round(random.uniform(50, 500), 2)

        # 更新客户余额和交付计数
        sqls.append(f"UPDATE customer SET c_balance=c_balance+{sum_amount}, "
                    f"c_delivery_cnt=c_delivery_cnt+1 WHERE c_id={c_id} "
                    f"AND c_d_id={d_id} AND c_w_id={w_id};")

        return sqls

    def generate_order_status(self):
        w_id = random.randint(1, self.warehouse_count)
        d_id = random.randint(1, self.districts_per_warehouse)

        # 60%按姓氏查询，40%按ID查询
        if random.random() < 0.6:
            c_last = f"'CUSTOMER{random.randint(1, 100)}'"
            sqls = [
                f"SELECT count(c_id) as count_c_id FROM customer "
                f"WHERE c_w_id={w_id} AND c_d_id={d_id} AND c_last={c_last};",

                f"SELECT c_balance, c_first, c_middle, c_last FROM customer "
                f"WHERE c_w_id={w_id} AND c_d_id={d_id} AND c_last={c_last} "
                f"ORDER BY c_first;"
            ]
        else:
            c_id = random.randint(1, self.customers_per_district)
            sqls = [
                f"SELECT c_balance, c_first, c_middle, c_last FROM customer "
                f"WHERE c_w_id={w_id} AND c_d_id={d_id} AND c_id={c_id};"
            ]

        # 查询订单信息
        o_id = random.randint(1, 1000000)
        sqls.append(f"SELECT o_id, o_entry_d, o_carrier_id FROM orders "
                    f"WHERE o_w_id={w_id} AND o_d_id={d_id} AND o_c_id={c_id} "
                    f"AND o_id={o_id};")

        # 查询订单行
        sqls.append(f"SELECT ol_i_id, ol_supply_w_id, ol_quantity, ol_amount, ol_delivery_d "
                    f"FROM order_line WHERE ol_w_id={w_id} AND ol_d_id={d_id} AND ol_o_id={o_id};")

        return sqls

    def generate_stock_level(self):
        w_id = random.randint(1, self.warehouse_count)
        d_id = random.randint(1, self.districts_per_warehouse)
        level = random.randint(10, 20)

        sqls = []

        # 查询地区下一个订单ID
        sqls.append(f"SELECT d_next_o_id FROM district "
                    f"WHERE d_id={d_id} AND d_w_id={w_id};")

        # 假设获取的下一个订单ID
        d_next_o_id = random.randint(1000, 2000)

        # 查询最近20个订单的商品ID
        sqls.append(f"SELECT ol_i_id FROM order_line "
                    f"WHERE ol_w_id={w_id} AND ol_d_id={d_id} "
                    f"AND ol_o_id<{d_next_o_id} AND ol_o_id>={d_next_o_id-20};")

        # 假设获取的商品ID
        ol_i_id = random.randint(1, self.items_count)

        # 查询低库存商品数量
        sqls.append(f"SELECT count(*) as count_stock FROM stock "
                    f"WHERE s_w_id={w_id} AND s_i_id={ol_i_id} AND s_quantity<{level};")

        return sqls

    def generate_transaction(self, transaction_type):
        if transaction_type == "new_order":
            return self.generate_new_order()
        elif transaction_type == "payment":
            return self.generate_payment()
        elif transaction_type == "delivery":
            return self.generate_delivery()
        elif transaction_type == "order_status":
            return self.generate_order_status()
        elif transaction_type == "stock_level":
            return self.generate_stock_level()
        else:
            raise ValueError(f"Unknown transaction type: {transaction_type}")


def generate_tpcc_workload(output_file, transaction_count=100):
    generator = TPCCSQLGenerator(warehouse_count=5)
    transaction_types = ["new_order", "payment", "delivery", "order_status", "stock_level"]

    with open(output_file, 'w') as f:
        for _ in range(transaction_count):
            # 按TPCC标准比例选择事务类型
            rand = random.random()
            if rand < 0.45:
                trans_type = "new_order"
            elif rand < 0.87:
                trans_type = "payment"
            elif rand < 0.92:
                trans_type = "order_status"
            elif rand < 0.97:
                trans_type = "delivery"
            else:
                trans_type = "stock_level"

            sqls = generator.generate_transaction(trans_type)
            sqls.insert(0, "begin;")
            sqls.append("commit;")
            for sql in sqls:
                f.write(sql + "\n")
        # for stmt in consistency_checks:
        #     f.write(stmt + '\n')


thread = 5
if __name__ == "__main__":
    os.makedirs("tpcc_sql")
    print("生成TPCC测试SQL文件...")
    for i in range(0, thread):
        generate_tpcc_workload(f"tpcc_sql/tpcc_txn_{i}.sql", transaction_count=10)
    print("生成完成，文件已保存")
