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
ADD FILE ./url-decode.py;


DROP TABLE IF EXISTS gezi_user_all_commands;
CREATE TABLE gezi_user_all_commands ROW FORMAT CHARSET "GBK" AS 
MAP uid, commands, wap_commands
USING 'python.tar.gz/python ./url-decode.py'
AS uid, commands, wap_commands 
FROM(
		SELECT IF(L.uid is not null, L.uid, R.uid) as uid, commands, wap_commands 
		FROM
		(
			SELECT * FROM ueg_user_commands
		)L
		FULL OUTER JOIN 
		(
			SELECT * FROM ueg_user_wap_commands
		)R
		ON L.uid = R.uid)T;
