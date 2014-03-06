set mapred.job.name=chenghuige.upload; 
set hive.map.aggr=true; 
set hive.auto.convert.join=true; 
set mapred.job.map.capacity=6000; 
set mapred.job.reduce.capacity=500;

DROP TABLE gezi_ClassWords;
CREATE TABLE gezi_ClassWords(class STRING, words STRING);
LOAD DATA LOCAL INPATH './test.txt' OVERWRITE INTO TABLE gezi_ClassWords;
INSERT OVERWRITE LOCAL DIRECTORY './gezi_ClassWords' SELECT * FROM gezi_ClassWords;
