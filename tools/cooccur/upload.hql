set mapred.job.name=chenghuige.upload.coocur; 
set hive.map.aggr=true; 
set hive.auto.convert.join=true; 
set mapred.job.map.capacity=12; 
set mapred.job.reduce.capacity=1;
set hive.exec.mode.local.auto=true; 
set hive.exec.mode.local.auto.inputbytes.max=16000000000;
set hive.exec.mode.local.auto.tasks.max=12; 

USE queryPlatform;
-- DROP TABLE class_words;
-- CREATE TABLE class_words(class STRING, words STRING);
-- LOAD DATA LOCAL INPATH './test.txt' OVERWRITE INTO TABLE class_words;
-- INSERT OVERWRITE LOCAL DIRECTORY './result' SELECT * FROM class_words;

ADD FILE gen-coocur-classword.py;
DROP TABLE classwords_coocur;
CREATE TABLE classwords_coocur AS 
		SELECT TRANSFORM(class, words) 
			USING 'python gen-coocur-classword.py' 
			AS (class1, word1, count1) 
			FROM class_words; 

INSERT OVERWRITE LOCAL DIRECTORY './result2' SELECT * FROM classwords_coocur;