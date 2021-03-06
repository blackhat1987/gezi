set mapred.job.name=chenghuige.coocur; 
set hive.map.aggr=true; 
set hive.auto.convert.join=true; 
set mapred.job.map.capacity=6000; 
set mapred.job.reduce.capacity=500;

ADD CACHEARCHIVE python2.7.2.tar.gz;
ADD FILE gen-coocur-classword.py;
DROP TABLE gezi_Coocur;
CREATE TABLE gezi_Coocur AS 
	SELECT word1, word2, sum(count) AS count
		FROM
		(
			SELECT TRANSFORM(class, words) 
				USING 'python2.7.2.tar.gz/python/bin/python gen-coocur-classword.py' 
				AS (word1, word2, count) 
				FROM gezi_ClassWords
		) T
		GROUP BY word1, word2;

INSERT OVERWRITE LOCAL DIRECTORY './gezi_Coocur' SELECT * FROM gezi_Coocur;

