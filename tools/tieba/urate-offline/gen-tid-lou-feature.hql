set mapred.job.name=chenghuige.gen-tid-lou-feature; 
set hive.map.aggr=true; 
set hive.auto.convert.join=false; 
set mapred.job.map.capacity=6000; 
set mapred.job.reduce.capacity=500;
set stream.memory.limit=6000;
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
ADD FILE ./lou_reducer;

ADD FILE data;
ADD FILE conf;


DROP TABLE IF EXISTS ${hiveconf:table};
CREATE TABLE ${hiveconf:table} AS
REDUCE thread_id, create_time, uid, uname, ip, title, content
USING 'chmod 777 ./lou_reducer && ./lou_reducer'
AS tid, uid, feature_len, feature, feature_str, feature_names
FROM(
SELECT thread_id, create_time, uid, uname, ip, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content
FROM default.pbdata
WHERE day = ${hiveconf:date} 
DISTRIBUTE BY thread_id
SORT BY thread_id, create_time
)T;
