set mapred.job.name=chenghuige.merge-features; 
set hive.map.aggr=true; 
set hive.auto.convert.join=false; 
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

DROP TABLE IF EXISTS gezi_uinfo;
CREATE TABLE gezi_uinfo AS 
SELECT * FROM(
	SELECT * FROM gezi_uinfo${hiveconf:d1}
	UNION ALL 
	SELECT * FROM gezi_uinfo${hiveconf:d2}
	UNION ALL
	SELECT * FROM gezi_uinfo${hiveconf:d3}
	UNION ALL
	SELECT * FROM gezi_uinfo${hiveconf:d4}
	UNION ALL
	SELECT * FROM gezi_uinfo${hiveconf:d5}
	UNION ALL
	SELECT * FROM gezi_uinfo${hiveconf:d6}
	UNION ALL
	SELECT * FROM gezi_uinfo${hiveconf:d7}
)T;

DROP TABLE IF EXISTS gezi_uinfo${hiveconf:d8};

