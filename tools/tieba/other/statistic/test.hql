set mapred.job.name=chenghuige.forum; 
set hive.map.aggr=true; 
set hive.auto.convert.join=true; 
set mapred.job.map.capacity=6000; 
set mapred.job.reduce.capacity=500;

ADD FILE libpython2.7.so;
ADD FILE libpython2.7.so.1.0;
ADD FILE libboost_python.so;
ADD FILE libboost_python.so.1.53.0;
ADD FILE libgezi.so;
ADD FILE ./libencoding_convert.so;
ADD FILE ./gezi.py;
ADD FILE ./gezi_common.py;
ADD CACHEARCHIVE python.tar.gz;
ADD FILE ./is_thread.utf8.py;
ADD FILE ./is_thread.py;

USE queryPlatform;

DROP TABLE IF EXISTS gezi_titles;
CREATE TABLE gezi_titles AS 
		SELECT post_id, title
		FROM default.pbdata 
		WHERE day = '20150211'
		LIMIT 100;
