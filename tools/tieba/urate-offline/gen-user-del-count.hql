set mapred.job.name=chenghuige.add; 
set hive.map.aggr=true; 
set hive.auto.convert.join=true; 
set mapred.job.map.capacity=6000; 
set mapred.job.reduce.capacity=5000;
set mapred.reduce.tasks = 1000;
USE queryPlatform;

ADD ARCHIVE python.tar.gz;
ADD FILE libpython2.7.so;
ADD FILE libpython2.7.so.1.0;
ADD FILE libboost_python.so;
ADD FILE libboost_python.so.1.53.0;
ADD FILE libgezi.so;
ADD FILE ./libencoding_convert.so;
ADD FILE ./gezi.py;
ADD FILE ./gezi_common.py;
ADD FILE ./op-filter.py;
ADD FILE ./user-del-count.py;

DROP TABLE IF EXISTS gezi_user_del_info;
CREATE TABLE gezi_user_del_info AS
REDUCE user_id, post_id, title, content, op_username 
USING 'python.tar.gz/python ./user-del-count.py'
AS user_id, count, thread_count, pic_count
FROM(
MAP user_id, post_id, title, content, op_username
USING 'python.tar.gz/python op-filter.py'
AS user_id, post_id, title, content, op_username
FROM (
SELECT *
FROM default.forum_ueg_anti_monitor
WHERE day = ${hiveconf:date})T
CLUSTER BY user_id)T2;

