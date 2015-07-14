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

ADD FILE ./cut-cn.py;

DROP TABLE IF EXISTS gezi_name_cn_count;
CREATE TABLE gezi_name_cn_count ROW FORMAT CHARSET "GBK" AS 
SELECT word, count(*) AS count 
FROM(
MAP uname
USING 'python.tar.gz/python ./cut-cn.py'
AS word
FROM
(
	SELECT DISTINCT uname 
	FROM default.pbdata
	WHERE day = ${hiveconf:date} 
)T
)T2
GROUP BY word;
