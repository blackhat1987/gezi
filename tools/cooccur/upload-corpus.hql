set mapred.job.name=chenghuige.upload-corpus; 
set hive.map.aggr=true; 
set hive.auto.convert.join=true; 
set mapred.job.map.capacity=6000; 
set mapred.job.reduce.capacity=500;
set hive.exec.mode.local.auto=false; 
set hive.exec.mode.local.auto.inputbytes.max=16000000000;
set hive.exec.mode.local.auto.tasks.max=12; 

DROP TABLE gezi_Corpus;
CREATE TABLE gezi_Corpus(text STRING);
LOAD DATA LOCAL INPATH './result.txt' OVERWRITE INTO TABLE gezi_Corpus;
