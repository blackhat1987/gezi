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
SELECT L20151007.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20151007 and post_id % 31 == 0)L20151007
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20151007 and post_id % 31 == 0)R20151007
ON L20151007.post_id == R20151007.post_id 
UNION ALL
SELECT L20151006.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20151006 and post_id % 31 == 0)L20151006
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20151006 and post_id % 31 == 0)R20151006
ON L20151006.post_id == R20151006.post_id 
UNION ALL
SELECT L20151005.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20151005 and post_id % 31 == 0)L20151005
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20151005 and post_id % 31 == 0)R20151005
ON L20151005.post_id == R20151005.post_id 
UNION ALL
SELECT L20151004.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20151004 and post_id % 31 == 0)L20151004
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20151004 and post_id % 31 == 0)R20151004
ON L20151004.post_id == R20151004.post_id 
UNION ALL
SELECT L20151003.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20151003 and post_id % 31 == 0)L20151003
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20151003 and post_id % 31 == 0)R20151003
ON L20151003.post_id == R20151003.post_id 
UNION ALL
SELECT L20151002.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20151002 and post_id % 31 == 0)L20151002
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20151002 and post_id % 31 == 0)R20151002
ON L20151002.post_id == R20151002.post_id 
UNION ALL
SELECT L20151001.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20151001 and post_id % 31 == 0)L20151001
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20151001 and post_id % 31 == 0)R20151001
ON L20151001.post_id == R20151001.post_id 
UNION ALL
SELECT L20150930.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150930 and post_id % 31 == 0)L20150930
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150930 and post_id % 31 == 0)R20150930
ON L20150930.post_id == R20150930.post_id 
UNION ALL
SELECT L20150929.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150929 and post_id % 31 == 0)L20150929
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150929 and post_id % 31 == 0)R20150929
ON L20150929.post_id == R20150929.post_id 
UNION ALL
SELECT L20150928.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150928 and post_id % 31 == 0)L20150928
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150928 and post_id % 31 == 0)R20150928
ON L20150928.post_id == R20150928.post_id 
UNION ALL
SELECT L20150927.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150927 and post_id % 31 == 0)L20150927
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150927 and post_id % 31 == 0)R20150927
ON L20150927.post_id == R20150927.post_id 
UNION ALL
SELECT L20150926.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150926 and post_id % 31 == 0)L20150926
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150926 and post_id % 31 == 0)R20150926
ON L20150926.post_id == R20150926.post_id 
UNION ALL
SELECT L20150925.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150925 and post_id % 31 == 0)L20150925
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150925 and post_id % 31 == 0)R20150925
ON L20150925.post_id == R20150925.post_id 
UNION ALL
SELECT L20150924.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150924 and post_id % 31 == 0)L20150924
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150924 and post_id % 31 == 0)R20150924
ON L20150924.post_id == R20150924.post_id 
UNION ALL
SELECT L20150923.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150923 and post_id % 31 == 0)L20150923
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150923 and post_id % 31 == 0)R20150923
ON L20150923.post_id == R20150923.post_id 
UNION ALL
SELECT L20150922.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150922 and post_id % 31 == 0)L20150922
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150922 and post_id % 31 == 0)R20150922
ON L20150922.post_id == R20150922.post_id 
UNION ALL
SELECT L20150921.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150921 and post_id % 31 == 0)L20150921
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150921 and post_id % 31 == 0)R20150921
ON L20150921.post_id == R20150921.post_id 
UNION ALL
SELECT L20150920.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150920 and post_id % 31 == 0)L20150920
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150920 and post_id % 31 == 0)R20150920
ON L20150920.post_id == R20150920.post_id 
UNION ALL
SELECT L20150919.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150919 and post_id % 31 == 0)L20150919
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150919 and post_id % 31 == 0)R20150919
ON L20150919.post_id == R20150919.post_id 
UNION ALL
SELECT L20150918.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150918 and post_id % 31 == 0)L20150918
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150918 and post_id % 31 == 0)R20150918
ON L20150918.post_id == R20150918.post_id 
UNION ALL
SELECT L20150917.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150917 and post_id % 31 == 0)L20150917
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150917 and post_id % 31 == 0)R20150917
ON L20150917.post_id == R20150917.post_id 
UNION ALL
SELECT L20150916.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150916 and post_id % 31 == 0)L20150916
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150916 and post_id % 31 == 0)R20150916
ON L20150916.post_id == R20150916.post_id 
UNION ALL
SELECT L20150915.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150915 and post_id % 31 == 0)L20150915
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150915 and post_id % 31 == 0)R20150915
ON L20150915.post_id == R20150915.post_id 
UNION ALL
SELECT L20150914.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150914 and post_id % 31 == 0)L20150914
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150914 and post_id % 31 == 0)R20150914
ON L20150914.post_id == R20150914.post_id 
UNION ALL
SELECT L20150913.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150913 and post_id % 31 == 0)L20150913
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150913 and post_id % 31 == 0)R20150913
ON L20150913.post_id == R20150913.post_id 
UNION ALL
SELECT L20150912.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150912 and post_id % 31 == 0)L20150912
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150912 and post_id % 31 == 0)R20150912
ON L20150912.post_id == R20150912.post_id 
UNION ALL
SELECT L20150911.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150911 and post_id % 31 == 0)L20150911
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150911 and post_id % 31 == 0)R20150911
ON L20150911.post_id == R20150911.post_id 
UNION ALL
SELECT L20150910.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150910 and post_id % 31 == 0)L20150910
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150910 and post_id % 31 == 0)R20150910
ON L20150910.post_id == R20150910.post_id 
UNION ALL
SELECT L20150909.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150909 and post_id % 31 == 0)L20150909
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150909 and post_id % 31 == 0)R20150909
ON L20150909.post_id == R20150909.post_id 
UNION ALL
SELECT L20150908.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150908 and post_id % 31 == 0)L20150908
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150908 and post_id % 31 == 0)R20150908
ON L20150908.post_id == R20150908.post_id 
UNION ALL
SELECT L20150907.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = 20150907 and post_id % 31 == 0)L20150907
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = 20150907 and post_id % 31 == 0)R20150907
ON L20150907.post_id == R20150907.post_id 
)T;

