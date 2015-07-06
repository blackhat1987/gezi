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
SELECT L20150626.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150626 and post_id % 31 == 0)L20150626
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150626 and post_id % 31 == 0)R20150626
ON L20150626.post_id == R20150626.post_id 
UNION ALL
SELECT L20150625.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150625 and post_id % 31 == 0)L20150625
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150625 and post_id % 31 == 0)R20150625
ON L20150625.post_id == R20150625.post_id 
UNION ALL
SELECT L20150624.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150624 and post_id % 31 == 0)L20150624
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150624 and post_id % 31 == 0)R20150624
ON L20150624.post_id == R20150624.post_id 
UNION ALL
SELECT L20150623.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150623 and post_id % 31 == 0)L20150623
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150623 and post_id % 31 == 0)R20150623
ON L20150623.post_id == R20150623.post_id 
UNION ALL
SELECT L20150622.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150622 and post_id % 31 == 0)L20150622
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150622 and post_id % 31 == 0)R20150622
ON L20150622.post_id == R20150622.post_id 
UNION ALL
SELECT L20150621.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150621 and post_id % 31 == 0)L20150621
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150621 and post_id % 31 == 0)R20150621
ON L20150621.post_id == R20150621.post_id 
UNION ALL
SELECT L20150620.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150620 and post_id % 31 == 0)L20150620
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150620 and post_id % 31 == 0)R20150620
ON L20150620.post_id == R20150620.post_id 
UNION ALL
SELECT L20150619.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150619 and post_id % 31 == 0)L20150619
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150619 and post_id % 31 == 0)R20150619
ON L20150619.post_id == R20150619.post_id 
UNION ALL
SELECT L20150618.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150618 and post_id % 31 == 0)L20150618
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150618 and post_id % 31 == 0)R20150618
ON L20150618.post_id == R20150618.post_id 
UNION ALL
SELECT L20150617.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150617 and post_id % 31 == 0)L20150617
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150617 and post_id % 31 == 0)R20150617
ON L20150617.post_id == R20150617.post_id 
UNION ALL
SELECT L20150616.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150616 and post_id % 31 == 0)L20150616
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150616 and post_id % 31 == 0)R20150616
ON L20150616.post_id == R20150616.post_id 
UNION ALL
SELECT L20150615.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150615 and post_id % 31 == 0)L20150615
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150615 and post_id % 31 == 0)R20150615
ON L20150615.post_id == R20150615.post_id 
UNION ALL
SELECT L20150614.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150614 and post_id % 31 == 0)L20150614
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150614 and post_id % 31 == 0)R20150614
ON L20150614.post_id == R20150614.post_id 
UNION ALL
SELECT L20150613.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150613 and post_id % 31 == 0)L20150613
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150613 and post_id % 31 == 0)R20150613
ON L20150613.post_id == R20150613.post_id 
UNION ALL
SELECT L20150612.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150612 and post_id % 31 == 0)L20150612
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150612 and post_id % 31 == 0)R20150612
ON L20150612.post_id == R20150612.post_id 
UNION ALL
SELECT L20150611.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150611 and post_id % 31 == 0)L20150611
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150611 and post_id % 31 == 0)R20150611
ON L20150611.post_id == R20150611.post_id 
UNION ALL
SELECT L20150610.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150610 and post_id % 31 == 0)L20150610
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150610 and post_id % 31 == 0)R20150610
ON L20150610.post_id == R20150610.post_id 
UNION ALL
SELECT L20150609.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150609 and post_id % 31 == 0)L20150609
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150609 and post_id % 31 == 0)R20150609
ON L20150609.post_id == R20150609.post_id 
UNION ALL
SELECT L20150608.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150608 and post_id % 31 == 0)L20150608
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150608 and post_id % 31 == 0)R20150608
ON L20150608.post_id == R20150608.post_id 
UNION ALL
SELECT L20150607.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150607 and post_id % 31 == 0)L20150607
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150607 and post_id % 31 == 0)R20150607
ON L20150607.post_id == R20150607.post_id 
UNION ALL
SELECT L20150606.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150606 and post_id % 31 == 0)L20150606
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150606 and post_id % 31 == 0)R20150606
ON L20150606.post_id == R20150606.post_id 
UNION ALL
SELECT L20150605.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150605 and post_id % 31 == 0)L20150605
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150605 and post_id % 31 == 0)R20150605
ON L20150605.post_id == R20150605.post_id 
UNION ALL
SELECT L20150604.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150604 and post_id % 31 == 0)L20150604
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150604 and post_id % 31 == 0)R20150604
ON L20150604.post_id == R20150604.post_id 
UNION ALL
SELECT L20150603.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150603 and post_id % 31 == 0)L20150603
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150603 and post_id % 31 == 0)R20150603
ON L20150603.post_id == R20150603.post_id 
UNION ALL
SELECT L20150602.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150602 and post_id % 31 == 0)L20150602
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150602 and post_id % 31 == 0)R20150602
ON L20150602.post_id == R20150602.post_id 
UNION ALL
SELECT L20150601.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150601 and post_id % 31 == 0)L20150601
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150601 and post_id % 31 == 0)R20150601
ON L20150601.post_id == R20150601.post_id 
UNION ALL
SELECT L20150531.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150531 and post_id % 31 == 0)L20150531
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150531 and post_id % 31 == 0)R20150531
ON L20150531.post_id == R20150531.post_id 
UNION ALL
SELECT L20150530.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150530 and post_id % 31 == 0)L20150530
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150530 and post_id % 31 == 0)R20150530
ON L20150530.post_id == R20150530.post_id 
UNION ALL
SELECT L20150529.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150529 and post_id % 31 == 0)L20150529
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150529 and post_id % 31 == 0)R20150529
ON L20150529.post_id == R20150529.post_id 
UNION ALL
SELECT L20150528.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150528 and post_id % 31 == 0)L20150528
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150528 and post_id % 31 == 0)R20150528
ON L20150528.post_id == R20150528.post_id 
UNION ALL
SELECT L20150527.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150527 and post_id % 31 == 0)L20150527
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150527 and post_id % 31 == 0)R20150527
ON L20150527.post_id == R20150527.post_id 
)T;

