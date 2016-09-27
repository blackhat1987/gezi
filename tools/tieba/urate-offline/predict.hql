set mapred.job.name=chenghuige.add; 
set hive.map.aggr=true; 
set hive.auto.convert.join=true; 
set mapred.job.map.capacity=6000; 
set mapred.job.reduce.capacity=5000;
set stream.memory.limit=3048;

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

ADD FILE model;
ADD FILE ./predict.py;

DROP TABLE IF EXISTS ${hiveconf:otable};
CREATE TABLE ${hiveconf:otable} AS
MAP uid, feature_len, feature, feature_str
USING 'python.tar.gz/python ./predict.py'
AS (uid BIGINT, score FLOAT, feature_len INT, feature STRING, feature_str STRING)
FROM ${hiveconf:itable};
