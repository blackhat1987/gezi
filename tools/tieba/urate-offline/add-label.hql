set mapred.job.name=chenghuige.add; 
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
ADD FILE ./gen-behaviour-feature.py;

DROP TABLE IF EXISTS gezi_ubehaviour_label;
CREATE TABLE gezi_ubehaviour_label AS
SELECT /*+ mapjoin(R)*/ L.uid, IF(R.uid is null, 0, 1) AS label, feature_len, feature,feature_str, feature_names
FROM ${hiveconf:table} L
LEFT OUTER JOIN
(
	SELECT * FROM gezi_user_post_del_info
	WHERE del_ratio > 0.6
)R
ON L.uid = R.uid;
