set mapred.job.name=chenghuige.coocur-info; 
set hive.map.aggr=true; 
set hive.auto.convert.join=true; 
set mapred.job.map.capacity=6000; 
set mapred.job.reduce.capacity=500;

DROP TABLE gezi_TotalTable;
CREATE TABLE gezi_TotalTable AS
	SELECT count FROM gezi_Coocur
	WHERE word1 IS  NULL AND  word2 IS NULL;
INSERT OVERWRITE LOCAL DIRECTORY './gezi_TotalTable' SELECT * FROM gezi_TotalTable;

DROP TABLE gezi_FirstTable;
CREATE TABLE gezi_FirstTable AS
	SELECT word1 AS word, count FROM gezi_Coocur
	WHERE word1 IS NOT NULL AND word2 IS NULL 
	DISTRIBUTE BY count 
	SORT BY count DESC;
INSERT OVERWRITE LOCAL DIRECTORY './gezi_FirstTable' SELECT * FROM gezi_FirstTable;

DROP TABLE gezi_SecondTable;
CREATE TABLE gezi_SecondTable AS
	SELECT word2 AS word, count FROM gezi_Coocur
	WHERE word1 IS NULL AND word2 IS NOT NULL 
	DISTRIBUTE BY count 
	SORT BY count DESC;
INSERT OVERWRITE LOCAL DIRECTORY './gezi_SecondTable' SELECT * FROM gezi_SecondTable;

DROP TABLE gezi_FirstCoocur;
CREATE TABLE gezi_FirstCoocur AS
	SELECT * FROM gezi_Coocur
	WHERE word1 IS NOT NULL AND word2 IS NOT NULL
	DISTRIBUTE BY word1
	SORT BY word1, count DESC;
INSERT OVERWRITE LOCAL DIRECTORY './gezi_FirstCoocur' SELECT * FROM gezi_FirstCoocur;

DROP TABLE gezi_SecondCoocur;
CREATE TABLE gezi_SecondCoocur AS
	SELECT * FROM gezi_Coocur
	WHERE word1 IS NOT NULL AND word2 IS NOT NULL
	DISTRIBUTE BY word2
	SORT BY word2, count DESC;
INSERT OVERWRITE LOCAL DIRECTORY './gezi_SecondCoocur' SELECT * FROM gezi_SecondCoocur;
