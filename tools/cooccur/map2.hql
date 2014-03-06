set mapred.job.name=chenghuige.coocur; 
set hive.map.aggr=true; 
set hive.auto.convert.join=true; 
set mapred.job.map.capacity=6000; 
set mapred.job.reduce.capacity=500;

DROP TABLE gezi_Coocur2;
CREATE TABLE gezi_Coocur2 AS 
	SELECT word1, word2, sum(count) AS count
		FROM gezi_Coocur
		GROUP BY word1, word2;

INSERT OVERWRITE LOCAL DIRECTORY './gezi_Coocur2' SELECT * FROM gezi_Coocur2;

