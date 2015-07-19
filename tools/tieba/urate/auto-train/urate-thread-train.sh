./bin/urate_train -i ./pid.txt -o feature.txt
./fix-label.py feature.txt feature.fixed.txt 
#sh ./add-pv-spam.sh 
#./add-weight.py ./feature.fixed.addpv.txt 4 > ./feature.fixed.addpv.weight.txt
#./add-weight.py ./feature.fixed.txt 4 > ./feature.fixed.addpv.weight.txt
./add-weight.py ./feature.fixed.txt 4 > ./feature.fixed.weight.txt
#python ./remove-files.py ./history 10000000
rm -rf ./model.bak/ 
mv model model.bak
rm -rf ./result.bak/
mv result result.bak
#./bin/melt feature.fixed.addpv.weight.txt -c train -cl fr --flagfile=./gbdt.gflags -vl 1 --weight=2
#./bin/melt feature.fixed.weight.txt -c train -cl fr --flagfile=./gbdt.gflags -vl 1 --weight=2
mlt feature.fixed.weight.txt -c train -cl fr -rs 1024 -nl 128 -ntree 1500 -nl 128 -mil 50 -lr 0.025 -ff 0.3 -nbag 6 -bstrap=1 --mfeature=1 --mc=1 -excl ^img_ --weight=2
#./bin/melt feature.fixed.txt -c train -cl fr --flagfile=./gbdt.gflags -vl 1 
#./bin/melt feature.fixed.addpv.txt -c train -cl fr --flagfile=./gbdt.gflags -vl 1 
#./bin/melt feature.txt -cl fr --flagfile=./gbdt.gflags -vl 1 --excl history$ 

rm -rf ./data/thread.model 
cp -rf model ./data/thread.model 
