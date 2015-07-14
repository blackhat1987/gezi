set mapred.job.name=chenghuige.urate; 
set hive.map.aggr=true; 
set hive.auto.convert.join=true; 
set mapred.job.map.capacity=6000; 
set mapred.job.reduce.capacity=5000;
set stream.memory.limit=6000;
set mapred.reduce.tasks=1;

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
ADD FILE ./urate_reducer;
ADD FILE data;
ADD FILE conf;

DROP TABLE IF EXISTS ${hiveconf:table};
CREATE TABLE ${hiveconf:table} AS
REDUCE uid, uname, post_id, thread_id, create_time, title, content, ip, forum_id, forum_name, level1_name, level2_name, day, hour
USING 'chmod 777 ./urate_reducer && ./urate_reducer'
AS uid, uname, post_id, feature_len, feature, feature_str, feature_names, day, hour
FROM(
SELECT uid, uname, post_id, thread_id, create_time,
			 get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content,
			 ip, forum_id, forum_name, 
			 get_json_object(param, "$.first_dir") as level1_name,
			 get_json_object(param, "$.forum_dir_two") as level2_name, 
			 day, hour
FROM default.pbdata
WHERE day = ${hiveconf:date} and uid = 959148911
DISTRIBUTE BY uid
SORT BY uid, create_time DESC)T;

