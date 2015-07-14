set mapred.job.name=chenghuige.add; 
set hive.map.aggr=true; 
set hive.auto.convert.join=false; 
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

ADD FILE ./merge-pc-old-behaviour.py;

DROP TABLE IF EXISTS gezi_urate_behaviour_oldbhav_feature;
CREATE TABLE gezi_urate_behaviour_oldbhav_feature AS
MAP uid, feature, feature_names, feature2, feature_names2
USING 'python.tar.gz/python ./merge-pc-old-behaviour.py'
AS uid, feature_len, feature, feature_str, feature_names
FROM 
(
		SELECT /*+ mapjoin(R2)*/ L.uid, L.feature, L.feature_names, R.feature AS feature2, R2.feature_names AS feature_names2 
		FROM gezi_user_urate_behaviour_feature L
		LEFT OUTER JOIN 
		pc_behaviour_feature_old R
		ON L.uid = R.uid
		JOIN 
		(SELECT feature_names FROM pc_behaviour_feature_old LIMIT 1)R2
)T;
