set mapred.job.name=chenghuige.add; 
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

DROP TABLE IF EXISTS pbdata_with_img;
CREATE TABLE pbdata_with_img AS 
SELECT *
FROM (
	SELECT * FROM default.pbdata
	WHERE day = ${hiveconf:date}
)L
LEFT OUTER JOIN
(
	SELECT pid, ocr, porn_score, similarity_score, color_score, gameporn_score, textbox_num, text_rate 
	FROM default.tieba_mds_ueg_img_fea_post_day
	WHERE event_day = ${hiveconf:date}
)R
ON L.post_id = R.pid;
