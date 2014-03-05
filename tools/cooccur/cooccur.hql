set mapred.job.name=chenghuige.coocur; 
set mapred.job.map.capacity=4; 
set mapred.job.reduce.capacity=1; 
set hive.map.aggr=true; 
set hive.auto.convert.join=true; 
set hive.exec.mode.local.auto=true; 
ADD FILE gen-coocur-classword.py;
DROP TABLE classwords_coocur;
CREATE TABLE classwords_coocur AS 
		SELECT TRANSFORM(class, words) 
			USING 'python gen-coocur-classword.py' 
			AS (class1, word1, count1) 
			FROM class_words; 

INSERT OVERWRITE LOCAL DIRECTORY './result2' SELECT * FROM classwords_coocur;
