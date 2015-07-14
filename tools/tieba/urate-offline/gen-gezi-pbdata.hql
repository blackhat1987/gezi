set mapred.job.name=chenghuige.add; 
set hive.map.aggr=true; 
set hive.auto.convert.join=true; 
set mapred.job.map.capacity=6000; 
set mapred.job.reduce.capacity=5000;

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
ADD FILE ./urate_reducer;

DROP TABLE IF EXISTS gezi_pbdata;
CREATE TABLE gezi_pbdata AS
SELECT uid, post_id, get_json_object(title, '$.title') AS title, get_json_object(content, '$.content') AS content
FROM default.pbdata
WHERE day = 20150301 and (uid = 1076153393 or uid = 1476169251);

