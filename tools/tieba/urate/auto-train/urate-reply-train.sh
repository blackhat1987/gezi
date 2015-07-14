./bin/urate_train -i ./pid.reply.txt -o feature.reply.txt
./fix-label.py feature.reply.txt feature.reply.fixed.txt
python ./remove-files.py ./history 1000000

rm -rf ./reply.model.bak/ 
mv reply.model reply.model.bak
mlt feature.reply.fixed.txt -c train -cl fr -m reply.model -vl 1 -ri 1 -rs 1024 -ntree 2000 -nl 128 -mil 50 -lr 0.025 -ff 0.3 -nbag 6 -nbagfrac 1 --mf=1 -excl ^img_
#./bin/melt feature.reply.txt -cl fr --flagfile=./gbdt.gflags -vl 1 --excl history$ 

rm -rf ./data/reply.model 
cp -rf reply.model ./data/reply.model
