set mapred.job.name=chenghuige.add; 
set hive.map.aggr=true; 
set hive.auto.convert.join=true; 
set mapred.job.map.capacity=6000; 
set mapred.job.reduce.capacity=500;

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

DROP TABLE IF EXISTS gezi_baduids;
CREATE TABLE gezi_baduids(uid STRING);
LOAD DATA LOCAL INPATH './uids.txt' OVERWRITE INTO TABLE gezi_baduids;

DROP TABLE IF EXISTS ueg_pc_user_behavior;
CREATE TABLE ueg_pc_user_behavior ROW FORMAT CHARSET "GBK" AS 
MAP bduid, uid, uname, cur_time, mid, command, url, uip, refer, fid, fname, tid, pn, vip, is_new_user, user_start_time, nation, province, city, errno, ispv, cookieuid, email, mobilephone, agent, pro_type, qword, video_num, image_num, music_num, uip_str, quote_type, post_id, first_dir, second_dir, day 
USING 'python.tar.gz/python ./url-decode.py'
AS bduid, uid, uname, cur_time, mid, command, url, uip, refer, fid, fname, tid, pn, vip, is_new_user, user_start_time, nation, province, city, errno, ispv, cookieuid, email, mobilephone, agent, pro_type, qword, video_num, image_num, music_num, uip_str, quote_type, post_id, first_dir, second_dir, day 
FROM
(
SELECT bduid, uid, uname, cur_time, mid, command, url, uip, refer, fid, fname, tid, pn, vip, is_new_user, user_start_time, nation, province, city, errno, ispv, cookieuid, email, mobilephone, agent, pro_type, qword, video_num, image_num, music_num, uip_str, quote_type, post_id, first_dir, second_dir, day
FROM
(
	SELECT *
	FROM default.pc_user_behaviour
	WHERE day >= ${hiveconf:day1} and day <= ${hiveconf:day2} and mid != 'ueg'
)L
LEFT SEMI JOIN 
(
	SELECT uid as userid FROM gezi_baduids		
)R
ON L.uid = R.userid)T
DISTRIBUTE BY uid 
SORT BY uid, cur_time;

