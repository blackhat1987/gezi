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
ADD FILE ./gen-relation.py;

DROP TABLE IF EXISTS gezi_pb_relation;
CREATE TABLE gezi_pb_relation AS
REDUCE thread_id, uid, title
USING 'python.tar.gz/python ./gen-relation.py'
AS uid1, uid2, weight
FROM 
(
	SELECT thread_id, uid, get_json_object(title, "$.title") AS title
	FROM default.pbdata
	WHERE day = 20150225 and thread_id > 100
	CLUSTER BY thread_id 
)T;


