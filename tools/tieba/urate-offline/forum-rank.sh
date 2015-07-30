hive -f ./forum-rank.hql -hiveconf date=$1
cat ./forumRankUid/* > forumRankUid.txt
./gen-formRank.py forumRankUid.txt > forumRank.txt 
cp forumRank.txt ./data/
