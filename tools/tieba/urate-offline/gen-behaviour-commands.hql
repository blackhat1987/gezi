set mapred.job.name=chenghuige.gen-behaviour-commands; 
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
ADD FILE ./url-decode.py;

DROP TABLE IF EXISTS ueg_user_wap_commands;
CREATE TABLE ueg_user_wap_commands ROW FORMAT CHARSET "GBK" AS 
SELECT uid, collect_set(command) AS wap_commands FROM 
default.wap_user_behaviour
WHERE day = ${hiveconf:date} and mid != 'ueg' and uid > 10 
GROUP BY uid;

DROP TABLE IF EXISTS ueg_user_pc_commands;
CREATE TABLE ueg_user_pc_commands ROW FORMAT CHARSET "GBK" AS 
SELECT uid, collect_set(command) AS pc_commands FROM 
default.pc_user_behaviour
WHERE day = ${hiveconf:date} and mid != 'ueg' and uid > 10 
GROUP BY uid;

DROP TABLE IF EXISTS ${hiveconf:table};
CREATE TABLE ${hiveconf:table} ROW FORMAT CHARSET "GBK" AS 
MAP uid, pc_commands, wap_commands
USING 'python.tar.gz/python ./url-decode.py'
AS uid, pc_commands, wap_commands 
FROM(
		SELECT IF(L.uid is not null, L.uid, R.uid) as uid, pc_commands, wap_commands 
		FROM ueg_user_pc_commands L
		FULL OUTER JOIN 
		ueg_user_wap_commands R
		ON L.uid = R.uid)T;
