sh ./trate-train.sh 
rm -rf ./data/ltrate.thread.model/ 
rm -rf ./data/roc.thread.model/ 
cp -rf ./ltrate.thread.model/  ./data/ 
cp -rf ./roc.thread.model/ ./data/  
rm -rf ./data/ltrate.reply.model/ 
rm -rf ./data/ltrate.thread.model/ 
cp -rf ./ltrate.reply.model/ ./data/ 
cp -rf ./roc.reply.model/ ./data/


./bin/urate_train -i ./pid.txt -o feature.txt
python ./remove-files.py ./history 1000000
mv model model.bak
mv result result.bak
./bin/melt feature.txt -c train -cl fr --flagfile=./gbdt.gflags -vl 1 --excl history$
./bin/melt feature.txt -cl fr --flagfile=./gbdt.gflags -vl 1 --excl history$ 
