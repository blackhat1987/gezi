set mapred.job.name=chenghuige.add; 
set hive.map.aggr=true; 
set hive.auto.convert.join=true; 
set mapred.job.map.capacity=6000; 
set mapred.job.reduce.capacity=500;

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

DROP TABLE IF EXISTS gezi_baduids;
CREATE TABLE gezi_baduids(uid STRING);
LOAD DATA LOCAL INPATH './uids.txt' OVERWRITE INTO TABLE gezi_baduids;

DROP TABLE IF EXISTS ueg_wap_user_behavior;
CREATE TABLE ueg_wap_user_behavior ROW FORMAT CHARSET "GBK" AS 
MAP bduid, uid, uname, cur_time, optime, mid, command, url, uip, refer, fid, fname, tid, pn, is_new_user, errno, ispv, first_dir, second_dir, day 
USING 'python.tar.gz/python ./url-decode.py'
AS bduid, uid, uname, cur_time, optime, mid, command, url, uip, refer, fid, fname, tid, pn, is_new_user,  errno, ispv, first_dir, second_dir, day 
FROM default.wap_user_behaviour
WHERE day = 20150303
LIMIT 1000;

