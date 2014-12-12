sh ./seg-trate-corpus.sh 
python gen-identifer.py ./title-content.segged.txt identifer.txt
python gen-feature.py ./title-content.segged.txt identifer.txt feature.trate.txt 
./bin/identifer-text2bin -i ./identifer.txt -o ./identifer.bin 
mv ./ltrate.thread.model/ ./ltrate.thread.model.bak/ 
./bin/melt feature.trate.txt -iter 500000 -c train -m ltrate.thread.model -rs 12345 --mt=1 
cp ./identifer.bin ./ltrate.thread.model/ 
mv ./roc.thread.model/ ./roc.thread.model.bak
./bin/melt feature.trate.txt -iter 1000000 -lt roc -lr 0.2 -c train -m roc.thread.model -rs 12345 --mt=1
