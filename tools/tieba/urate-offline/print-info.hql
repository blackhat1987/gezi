set mapred.job.name=chenghuige.print-info; 
set hive.map.aggr=true; 
set hive.auto.convert.join=true; 
set mapred.job.map.capacity=6000; 
set mapred.job.reduce.capacity=500;
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
ADD FILE ./print-info.py;

DROP TABLE IF EXISTS ${hiveconf:otable};
CREATE TABLE ${hiveconf:otable} AS 
REDUCE uid, uname, score, post_id, forum_name, title, content, feature_len, feature
USING 'python.tar.gz/python ./print-info.py'
AS uid, uname, score, post_id, fnames, titles, contents, feature_len, feature
FROM
(
SELECT L.uid, create_time, post_id, uname, score, forum_name, title, content, feature_len, feature
FROM 
${hiveconf:itable} L
JOIN 
(
	SELECT uid, create_time, post_id, uname, forum_name, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content
	FROM default.pbdata
	WHERE day = ${hiveconf:date}
)R
ON L.uid = R.uid
DISTRIBUTE BY uid 
SORT BY uid, create_time DESC)T;

