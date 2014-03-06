set mapred.job.name=chenghuige.seg; 
set hive.map.aggr=true; 
set hive.auto.convert.join=true; 
set mapred.job.map.capacity=6000; 
set mapred.job.reduce.capacity=500;

ADD CACHEARCHIVE python2.7.2.tar.gz;
ADD CACHEARCHIVE data.tar.gz;
ADD CACHEARCHIVE conf.tar.gz;
ADD FILE libboost_python.so;
ADD FILE libboost_python.so.1.53.0;
ADD FILE libboost_python.so;
ADD FILE libboost_python.so.1.53.0;
ADD FILE libgezi.so;
ADD FILE seg.py;
DROP TABLE gezi_SegedCorpus;
CREATE TABLE gezi_SegedCorpus AS 
	SELECT TRANSFORM(text) 
		USING 'LD_LIBRARY_PATH=./ python2.7.2.tar.gz/python/bin/python seg.py' 
		AS (class, words) 
		FROM gezi_Corpus;

INSERT OVERWRITE LOCAL DIRECTORY './gezi_SegedCorpus' SELECT * FROM gezi_SegedCorpus;
