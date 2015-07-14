set mapred.job.name=chenghuige.pc-behaviour-old; 
set hive.map.aggr=true; 
set hive.auto.convert.join=true; 
set mapred.job.map.capacity=6000; 
set mapred.job.reduce.capacity=500;
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
ADD FILE ./pc-behaviour.old.mapper.py;
ADD FILE ./pc-behaviour.old.reducer.py;
ADD FILE ./seq_feature;

DROP TABLE IF EXISTS ${hiveconf:table};
CREATE TABLE ${hiveconf:table} AS 
REDUCE uid, cookie, uname, time, open_id, pro, mid, command, url, uip, refer, fid, fname, tid, nation, province, city, error_no, is_pv, email, mobile, agent, qword, video_num, image_num, quote_type
USING 'python.tar.gz/python ./pc-behaviour.old.reducer.py'
AS uid, feature_len, feature, feature_str, feature_names
FROM(
MAP bduid,uid,uname,cur_time,optime,openid,pro,mid,command,url,uip,refer,fid,fname,tid,pn,iuid,iuname,vip,is_new_user,user_start_time,nation,province,city,errno,ispv,cookieuid,no_un,email,mobilephone,agent,pro_type,qword,icommand,followed_id,is_like,video_num,image_num,music_num,uip_str,quote_type,post_id,filterflag,uploadpicturecount,tousu_uid,tousu_uname,category_id,first_dir,second_dir,day 
USING 'python.tar.gz/python ./pc-behaviour.old.mapper.py'
AS uid, cookie, uname, time, open_id, pro, mid, command, url, uip, refer, fid, fname, tid, nation, province, city, error_no, is_pv, email, mobile, agent, qword, video_num, image_num, quote_type
FROM
(
	SELECT *
	FROM default.pc_user_behaviour
	WHERE day = ${hiveconf:date} and mid != 'ueg' and uid > 10 
)T
DISTRIBUTE BY uid 
SORT BY uid, time
)T2;

