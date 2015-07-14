set mapred.job.name=chenghuige.add;
set hive.map.aggr=true;
set hive.auto.convert.join=true;
set mapred.job.map.capacity=6000;
set mapred.job.reduce.capacity=5000;
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
ADD FILE ./behave.reducer.py;

DROP TABLE IF EXISTS gezi_bad_behave_uids;
CREATE TABLE gezi_bad_behave_uids AS 
REDUCE uid, command
USING 'python.tar.gz/python ./behave.reducer.py'
AS uid, commands
FROM
(
	SELECT uid, command
	FROM default.pc_user_behaviour
	WHERE day = 20150311 and mid != 'ueg' and errno = 0  and uid > 0
	CLUSTER BY uid
)T;
