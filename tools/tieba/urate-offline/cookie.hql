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


DROP TABLE IF EXISTS ueg_pc_user_behavior;
CREATE TABLE ueg_pc_user_behavior ROW FORMAT CHARSET "GBK" AS 
MAP bduid, uid, uname, cur_time, mid, command, url, uip, refer, fid, fname, tid, post_id, pn, is_new_user, errno, ispv, first_dir, second_dir, day 
USING 'python.tar.gz/python ./url-decode.py'
AS bduid, uid, uname, cur_time, mid, command, url, uip, refer, fid, fname, tid, post_id, pn, is_new_user,  errno, ispv, first_dir, second_dir, day 
FROM default.pc_user_behaviour
WHERE day = 20150304 and mid != 'ueg' and uid > 10
DISTRIBUTE BY uid 
SORT BY uid, cur_time;

