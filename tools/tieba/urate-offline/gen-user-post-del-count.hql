set mapred.job.name=chenghuige.add; 
set hive.map.aggr=true; 
set hive.auto.convert.join=true; 
set mapred.job.map.capacity=6000; 
set mapred.job.reduce.capacity=5000;
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
ADD FILE ./user-post-count.py;

DROP TABLE IF EXISTS gezi_user_post_del_info;
CREATE TABLE gezi_user_post_del_info AS
SELECT uid,count, thread_count, pic_count, del_count, del_thread_count, del_pic_count, del_count / count AS del_ratio
FROM
(
SELECT L.uid, L.count, L.thread_count, L.pic_count,  
			 IF(R.count IS NULL, 0, R.count) AS del_count, 
			 IF(R.thread_count IS NULL, 0, R.thread_count) AS del_thread_count, 
			 IF(R.pic_count IS NULL, 0, R.pic_count) AS del_pic_count
FROM 
(
	SELECT * FROM gezi_user_post_info
)L
LEFT OUTER JOIN
(
	SELECT * FROM gezi_user_del_info
)R
ON L.uid == R.user_id)T;

