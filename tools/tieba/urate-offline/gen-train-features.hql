set mapred.job.name=chenghuige.add; 
set hive.map.aggr=true; 
set hive.auto.convert.join=true; 
set mapred.job.map.capacity=6000; 
set mapred.job.reduce.capacity=5000;
set mapred.reduce.tasks=1000;
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
ADD FILE ./gen-dense-feature.mapper.py;

DROP TABLE IF EXISTS gezi_ubehaviour_dense_feature;
CREATE TABLE gezi_ubehaviour_dense_feature AS
MAP uid, label, feature_len, feature
USING 'python.tar.gz/python ./gen-dense-feature.mapper.py'
AS feature 
FROM gezi_ubehaviour_label;
