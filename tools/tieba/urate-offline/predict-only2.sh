hive -f ./predict.hql -hiveconf itable=gezi_urate_behaviour_oldbehav_img_lou_ugrade_feature$1 otable=gezi_ubehaviour_predict_2_$1
hive -f ./print-info.hql -hiveconf date=$1 itable=gezi_ubehaviour_predict_2_$1 otable=gezi_uinfo_2_$1
#hive -e 'select uid, score, feature from queryPlatform.gezi_ubehaviour_predict'$1' ORDER BY score DESC' > predict.$1.txt
hive -e 'select * from queryPlatform.gezi_uinfo_2_'$1' WHERE score > 0.8 ORDER BY score DESC' > uinfo2.$1.txt
