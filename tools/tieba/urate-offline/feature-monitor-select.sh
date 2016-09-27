sh ./predict.1.sh $1

echo 'begin merge'
sh ./merge2.sh $1



# hive -f ./add-label.hql -hiveconf table=gezi_urate_behaviour_oldbehav_img_lou_ugrade_feature
# hive -f ./gen-train-features.hql 
# sh ./get-train-file.sh 
#sh ./get-train-sparse-file.sh

#./melt feature.txt -cl fr -vl 1 --flagfile=gbdt.500tree.gflags -c train -excl plsa


# sh ./gen-name-cn-freq.sh $1 &
# sh ./forum-rank.sh $1 &
# sh ./gen-label.sh $1 &

# sh ./urate.sh $1 &
# sh ./behaviour.sh $1 &
# sh ./pc-behav-old.sh $1 &
# sh ./img.sh $1 &
# sh ./tid.sh $1 &
# sh ./ugrade.sh $1 &

# sh ./merge.sh $1


hive -f ./add-label-feature.hql -hiveconf table=gezi_urate_behaviour_oldbehav_img_lou_ugrade_feature$1
hive -f ./gen-train-features.hql 
hive -e 'select feature from queryPlatform.gezi_ubehaviour_dense_feature limit 500000' >  feature_monitor.body.txt
./add-header.py feature.header.txt feature_monitor.body.txt > feature.test.txt

#hive -f ./add-label-feature.hql -hiveconf table=gezi_urate_behaviour_oldbehav_img_lou_ugrade_feature$1
#hive -f ./gen-train-features.hql 
#hive -e 'select feature_names from queryPlatform.gezi_ubehaviour_label limit 1' > feature_monitor.header.txt
#hive -e 'select feature from queryPlatform.gezi_ubehaviour_dense_feature limit 500000' > feature_monitor.body.txt
#./add-header.py feature.header.txt feature_monitor.body.txt > feature.test.txt
#./histogram_auto.py
#sh ./get-train-sparse-file.sh

#./melt feature.txt -cl fr -vl 1 --flagfile=gbdt.500tree.gflags -c train -excl plsa
