set mapred.job.name=chenghuige.gen-user-grade-info; 
set hive.map.aggr=true; 
set hive.auto.convert.join=false; 
set mapred.job.map.capacity=6000; 
set mapred.job.reduce.capacity=5000;
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
ADD FILE ./gen-user-grade-info.py;

DROP TABLE IF EXISTS ${hiveconf:table};
CREATE TABLE ${hiveconf:table} AS
MAP uid, flag, level, score
USING 'python.tar.gz/python ./gen-user-grade-info.py'
AS uid, feature_len, feature, feature_str, feature_names
FROM 
(
SELECT L.uid AS uid, IF(flag is null, 0, flag) AS flag, IF(level is null, 0, level) AS level,
			IF(score is null, 0, score) AS score
FROM(
	SELECT uid, forum_id
	FROM default.pbdata
	WHERE day = ${hiveconf:date} 
)L
LEFT OUTER JOIN 
(
	SELECT uid, fid, flag, level, score 
	FROM default.tb_grade_info
	WHERE day = ${hiveconf:date}
)R
ON L.uid = R.uid and L.forum_id = R.fid)T;

