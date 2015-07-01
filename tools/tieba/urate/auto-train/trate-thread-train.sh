python seg-trate-corpus.py ./corpus/train_spam_title ./corpus/train_spam_content ./corpus/train_nonspam_title ./corpus/train_nonspam_content title-content.segged.txt identifer.1gram.txt 
python gen-identifer.py ./title-content.segged.txt identifer.txt
python gen-feature.py ./title-content.segged.txt identifer.txt feature.trate.txt 
python identifer-text2bin.py ./identifer.txt ./identifer.bin 
rm -rf ./ltrate.thread.model.bak/ 
mv ./ltrate.thread.model/ ./ltrate.thread.model.bak/ 
./bin/melt feature.trate.txt -iter 500000 -c train -m ltrate.thread.model -rs 12345 --mt=1 
cp ./identifer.bin ./ltrate.thread.model/ 
rm -rf ./roc.thread.model.bak
mv ./roc.thread.model/ ./roc.thread.model.bak
./bin/melt feature.trate.txt -iter 1000000 -lt roc -lr 0.2 -c train -m roc.thread.model -rs 12345 --mt=1 

rm -rf ./data/ltrate.thread.model/ 
rm -rf ./data/roc.thread.model/ 
cp -rf ./ltrate.thread.model/  ./data/ 
cp -rf ./roc.thread.model/ ./data/  
