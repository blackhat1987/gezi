set mapred.job.name=chenghuige.add; 
set hive.map.aggr=true; 
set hive.auto.convert.join=true; 
set mapred.job.map.capacity=6000; 
set mapred.job.reduce.capacity=500;
set mapred.reduce.tasks = 1000;
USE queryPlatform;

ADD CACHEARCHIVE python.tar.gz;
ADD FILE libpython2.7.so;
ADD FILE libpython2.7.so.1.0;
ADD FILE libboost_python.so;
ADD FILE libboost_python.so.1.53.0;
ADD FILE libgezi.so;
ADD FILE ./libencoding_convert.so;
ADD FILE ./gezi.py;
ADD FILE ./gezi_common.py;
ADD FILE ./is_thread.py

DROP TABLE IF EXISTS gezi_tid_uid;
CREATE TABLE gezi_tid_uid AS 
		MAP thread_id, uid, title
		USING 'python.tar.gz/python ./is_thread.py'
		AS thread_id, uid, title
		FROM(
		SELECT thread_id, uid, get_json_object(title, "$.title") AS title
		FROM default.pbdata 
		WHERE day = '${hiveconf:date}'
		)T;
