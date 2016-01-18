python seg-trate-corpus.py ./corpus/train_spam_title ./corpus/train_spam_content ./corpus/train_nonspam_title ./corpus/train_nonspam_content title-content.segged.txt identifer.1gram.txt 
python gen-identifer.py ./title-content.segged.txt identifer.txt
python gen-feature.py ./title-content.segged.txt identifer.txt feature.trate.txt 
python identifer-text2bin.py ./identifer.txt ./identifer.bin 
rm -rf ./trate.thread.model.bak/ 
mv ./trate.thread.model/ ./trate.thread.model.bak/ 

mlt ./feature.trate.txt --attr 2 -rs 1024 -c sd -ci 4:1

#lines=`cat ./feature.trate.txt | wc -l`
#lines=$(($lines+$lines/2))
#mlt feature.trate.txt -iter $lines -c train -m trate.thread.model -rs 12345 --mt=1 
#cp ./identifer.bin ./trate.thread.model/ 
#rm -rf ./trate.roc.thread.model.bak
#mv ./trate.roc.thread.model/ ./roc.thread.model.bak
#mlt feature.trate.txt -iter 1000000 -lt roc -lr 0.2 -c train -m trate.roc.thread.model -rs 12345 --mt=1 

#rm -rf ./data/trate.thread.model/ 
#rm -rf ./data/trate.roc.thread.model/ 
#cp -rf ./trate.thread.model/  ./data/ 
#cp -rf ./trate.roc.thread.model/ ./data/  
