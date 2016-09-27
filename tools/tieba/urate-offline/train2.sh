#sh ./gen-name-cn-freq.sh $1 &
#sh ./forum-rank.sh $1 &
#sh ./gen-label.sh $1 &

#sh ./urate.sh $1 &
#sh ./behaviour.sh $1 &
#sh ./pc-behav-old.sh $1 &
#sh ./img.sh $1 &
#sh ./tid.sh $1 &
#sh ./ugrade.sh $1 &
#wait

sh ./merge.sh $1

hive -f ./add-label.hql -hiveconf table=gezi_urate_behaviour_oldbehav_img_lou_ugrade_feature
hive -f ./gen-train-features.hql 
sh ./get-train-file.sh 
#sh ./get-train-sparse-file.sh

./melt feature.txt -cl fr -vl 1 --flagfile=gbdt.500tree.gflags -c train -excl plsa
