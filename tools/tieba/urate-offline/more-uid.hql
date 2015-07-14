set mapred.job.name=chenghuige.add; 
set hive.map.aggr=true; 
set hive.auto.convert.join=true; 
set mapred.job.map.capacity=6000; 
set mapred.job.reduce.capacity=500;
set mapred.reduce.tasks=1000;

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
ADD FILE ./url-decode.py;

DROP TABLE IF EXISTS ueg_more_uids;
CREATE TABLE ueg_more_uids ROW FORMAT CHARSET "GBK" AS 
SELECT cuid, count(DISTINCT uid) AS count, collect_set(uid) AS uids
FROM default.wap_user_behaviour
WHERE day = 20150301 
GROUP BY cuid
HAVING count > 10;
