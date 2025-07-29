select d_next_o_id from district where d_w_id=5 and d_id=10;
select MAX(o_id) as max_o_id from orders where o_w_id=5 and o_d_id=10;
select MAX(no_o_id) as max_no_o_id from new_orders where no_w_id=5 and no_d_id=10;
select COUNT(no_o_id) as count_no_o_id from new_orders where no_w_id=5 and no_d_id=10;
select MAX(no_o_id) as max_no_o_id from new_orders where no_w_id=5 and no_d_id=10;
select MIN(no_o_id) as min_no_o_id from new_orders where no_w_id=5 and no_d_id=10;
select SUM(o_ol_cnt) as sum_ol_cnt from orders where o_w_id=5 and o_d_id=10;
select COUNT(ol_o_id) as count_ol_o_id from order_line where ol_w_id=5 and ol_d_id=10;