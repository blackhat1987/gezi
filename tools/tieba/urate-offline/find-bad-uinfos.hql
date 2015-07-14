set mapred.job.name=chenghuige.merge-features; 
set hive.map.aggr=true; 
set hive.auto.convert.join=true; 
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

DROP TABLE IF EXISTS gezi_bad_uids;
CREATE TABLE gezi_bad_uids(uid STRING);
LOAD DATA LOCAL INPATH  './frs_spamuids.txt' OVERWRITE INTO TABLE gezi_bad_uids;

DROP TABLE IF EXISTS gezi_bad_uinfo;
CREATE TABLE gezi_bad_uinfo AS 
SELECT * FROM
gezi_uinfo L
LEFT SEMI JOIN 
gezi_bad_uids R
ON L.uid = R.uid;
