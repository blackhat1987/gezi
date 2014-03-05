set mapred.job.name=chenghuige.upload.coocur; 
set hive.map.aggr=true; 
set hive.auto.convert.join=true; 
set mapred.job.map.capacity=12; 
set mapred.job.reduce.capacity=1;
set hive.exec.mode.local.auto=true; 
set hive.exec.mode.local.auto.inputbytes.max=16000000000;
set hive.exec.mode.local.auto.tasks.max=12; 

USE queryPlatform;

DROP TABLE gezi_ClassWords;
CREATE TABLE gezi_ClassWords(class STRING, words STRING);
LOAD DATA LOCAL INPATH './test.txt' OVERWRITE INTO TABLE gezi_ClassWords;
INSERT OVERWRITE LOCAL DIRECTORY './gezi_ClassWords' SELECT * FROM gezi_ClassWords;
