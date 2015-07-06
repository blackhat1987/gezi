set mapred.job.name=chenghuige.add; 
set hive.map.aggr=true; 
set hive.auto.convert.join=false; 
set mapred.job.map.capacity=6000; 
set mapred.job.reduce.capacity=5000;
set mapred.reduce.tasks = 1000;
USE queryPlatform;

DROP TABLE IF EXISTS gezi_del_info;
CREATE TABLE gezi_del_info AS 
SELECT * FROM (
SELECT L.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = ${hiveconf:date}) L
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = ${hiveconf:date}:) R
ON L.post_id == R.post_id and L.post_id % 31 == 0
UNION ALL

);
