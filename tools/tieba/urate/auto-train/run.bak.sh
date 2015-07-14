./get-trate-corpus.sh 
./seg-trate-corpus.sh 
./gen-identifer.py ./title-content.segged.txt identifer.txt
./gen-feature.py ./title-content.segged.txt identifer.txt feature.txt
./identifer-text2bin -i ./identifer.txt -o ./identifer.bin 
mv ./ltrate.thread.model/ ltrate.thread.model.bak
./melt feature.txt -iter 500000 -c train -m ltrate.thread.model 
cp ./identifer.bin ./ltrate.thread.model/ 
mv ./roc.thread.model/ ./roc.thread.model.bak
./melt feature.txt -iter 1000000 -lt roc -lr 0.2 -c train -m roc.thread.model
