set mapred.job.name=chenghuige.add; 
set hive.map.aggr=true; 
set hive.auto.convert.join=false; 
set mapred.job.map.capacity=6000; 
set mapred.job.reduce.capacity=5000;
set mapred.reduce.tasks=1000;
set stream.memory.limit=6000;
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

ADD FILE model;
ADD FILE ./merge-urate-behaviour-feature.py;

DROP TABLE IF EXISTS gezi_t;
CREATE TABLE gezi_t AS
			SELECT  /*+ mapjoin(R2)*/ L.uid, L.feature, L.feature_names, R.feature AS feature2, feature_names2
			FROM gezi_urate L
			LEFT OUTER JOIN 
			(SELECT * FROM gezi_user_behaviour_feature WHERE has_pc_commit = '1' or has_wap_commit = '1') R
			ON L.uid = R.uid
			JOIN 
			(SELECT feature_names AS feature_names2 FROM gezi_user_behaviour_feature LIMIT 1)R2;

