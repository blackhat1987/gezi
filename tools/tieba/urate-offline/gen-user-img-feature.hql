set mapred.job.name=chenghuige.gen-user-img-feature; 
set hive.map.aggr=true; 
set hive.auto.convert.join=false; 
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
ADD FILE ./url-decode.py;

ADD ARCHIVE python.tar.gz;
ADD FILE libpython2.7.so;
ADD FILE libpython2.7.so.1.0;
ADD FILE libboost_python.so;
ADD FILE libboost_python.so.1.53.0;
ADD FILE libgezi.so;
ADD FILE ./libencoding_convert.so;
ADD FILE ./gezi.py;
ADD FILE ./gezi_common.py;
ADD FILE ./img_reducer;

DROP TABLE IF EXISTS ${hiveconf:table};
CREATE TABLE ${hiveconf:table} AS
REDUCE uid, ocr, porn_score, similarity_score, color_score, gameporn_score, textbox_num, text_rate
USING 'chmod 777 ./img_reducer && ./img_reducer'
AS uid, feature_len, feature, feature_str, feature_names
FROM(
SELECT *
FROM default.tieba_mds_ueg_img_fea_post_day
WHERE event_day = ${hiveconf:date} 
CLUSTER BY uid)T
