rand.py ./corpus/frs_normalpid.txt > ./corpus/frs_normalpid.rand.txt
./gen-label2.py ./corpus/frs_spampid.txt ./corpus/frs_normalpid.rand.txt > pid.frs.txt #urate thread
./bin/urate_train -i ./pid.frs.txt -o feature.frs.txt
./fix-label.py feature.frs.txt feature.frs.fixed.txt
python ./remove-files.py ./history 1000000

rm -rf ./frs.model.bak/ 
mv frs.model frs.model.bak
./bin/melt feature.frs.fixed.txt -c train -cl fr -m frs.model --flagfile=./gbdt.gflags -vl 1 -ri 1 -excl plsa -ff 0.3 
#./bin/melt feature.reply.txt -cl fr --flagfile=./gbdt.gflags -vl 1 --excl history$  

#rm -rf ./data/frs.model 
#cp -rf frs.model ./data/frs.model
