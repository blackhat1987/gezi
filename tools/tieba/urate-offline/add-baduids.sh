pushd .
cd ../urate/auto-train/ 
sh ./model_sample_extract.sh 
./frspids2uids.py ./corpus/frs_spampid.txt > ./corpus/frs_spamuids.txt 
cp ./corpus/frs_spamuids.txt ../../urate-offline/ 
popd
echo '-----------merge uinfos'
./merge-uinfos.py 
echo '----------find bad uinfos'
hive -f ./find-bad-uinfos.hql 
echo '---------gen baduid features'
hive -f gen-baduid-features.hql

echo '------------select to feature2'
hive -e 'select feature from queryPlatform.gezi_baduids_feature' > feature.baduids.txt

echo '------------add body'
./add-body.py feature.txt feature.baduids.txt > feature2.txt

echo '-----------------train model'
rm -rf model.bak
cp -rf model model.bak
mlt feature2.txt -cl fr -vl 1 --flagfile=/home/users/chenghuige/tools/melt/gbdt.500tree.2.gflags -c train -excl plsa 
