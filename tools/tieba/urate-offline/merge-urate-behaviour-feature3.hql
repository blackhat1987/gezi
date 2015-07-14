set mapred.job.name=chenghuige.add; 
set hive.map.aggr=true; 
set mapred.job.map.capacity=6000; 
set mapred.job.reduce.capacity=5000;
set mapred.reduce.tasks=1000;
set stream.memory.limit=6000;
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

ADD FILE ./merge-urate-behaviour-feature.py;

DROP TABLE IF EXISTS gezi_user_urate_behaviour_feature;
CREATE TABLE gezi_user_urate_behaviour_feature AS
MAP uid, feature, feature_names, feature2, feature_names2
USING 'python.tar.gz/python ./merge-urate-behaviour-feature.py'
AS uid, feature_len, feature, feature_str, feature_names
FROM gezi_t;
