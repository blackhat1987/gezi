set mapred.job.name=chenghuige.upload.coocur; 
set hive.map.aggr=true; 
set hive.auto.convert.join=true; 
set mapred.job.map.capacity=12; 
set mapred.job.reduce.capacity=1;
set hive.exec.mode.local.auto=true; 
set hive.exec.mode.local.auto.inputbytes.max=16000000000;
set hive.exec.mode.local.auto.tasks.max=12; 

USE queryPlatform;

ADD FILE gen-coocur-classword.py;
DROP TABLE gezi_Coocur;
CREATE TABLE gezi_Coocur AS 
	SELECT word1, word2, sum(count) AS count
		FROM
		(
			SELECT TRANSFORM(class, words) 
				USING 'gen-coocur-classword.py' 
				AS (word1, word2, count) 
				FROM gezi_ClassWords
		) T
		GROUP BY word1, word2;

INSERT OVERWRITE LOCAL DIRECTORY './gezi_Coocur' SELECT * FROM gezi_Coocur;

