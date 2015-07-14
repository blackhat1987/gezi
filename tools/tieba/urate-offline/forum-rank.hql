set mapred.job.name=chenghuige.forum; 
set hive.map.aggr=true; 
set hive.auto.convert.join=true; 
set mapred.job.map.capacity=6000; 
set mapred.job.reduce.capacity=500;
set mapred.reduce.tasks = 1000;
USE queryPlatform;

DROP TABLE IF EXISTS gezi_ForumRank;
CREATE TABLE gezi_ForumRank AS 
		SELECT * FROM(
			SELECT forum_name, COUNT(DISTINCT thread_id) as tid_count, 
			COUNT(DISTINCT post_id) as pid_count, 
			COUNT(DISTINCT uid) as uid_count, 
			COUNT(DISTINCT ip) as ip_count
		FROM default.pbdata 
		WHERE day = '${hiveconf:date}'
		GROUP BY forum_name)T;

INSERT OVERWRITE LOCAL DIRECTORY './forumRankUid' SELECT * FROM gezi_ForumRank ORDER BY uid_count DESC;
