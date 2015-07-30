hive -f ./print-info.hql -hiveconf date=$1 itable=gezi_ubehaviour_predict$1 otable=gezi_uinfo$1
#hive -e 'select uid, score, feature from queryPlatform.gezi_ubehaviour_predict'$1' ORDER BY score DESC' > predict.$1.txt
hive -e 'select * from queryPlatform.gezi_uinfo'$1' WHERE score > 0.8 ORDER BY score DESC' > uinfo.$1.txt
