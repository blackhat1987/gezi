./seg-trate-only-content-corpus.py ./corpus/reply/train_spam_content ./corpus/reply/train_nonspam_content title-content.reply.segged.txt identifer.1gram.txt 
python ./gen-identifer.py ./title-content.reply.segged.txt identifer.reply.txt 
python ./gen-feature.py ./title-content.reply.segged.txt identifer.reply.txt feature.trate.reply.txt 
./bin/identifer-text2bin -i ./identifer.reply.txt -o ./identifer.reply.bin 
mv ./ltrate.reply.model/ ./ltrate.reply.model.bak
./bin/melt feature.trate.reply.txt -iter 500000 -c train -m ltrate.reply.model -rs 12345 --mt=1 
cp ./identifer.reply.bin ./ltrate.reply.model/identifer.bin
mv ./roc.reply.model ./roc.reply.model.bak 
./bin/melt feature.trate.reply.txt -iter 1000000 -lt roc -lr 0.2 -c train -m roc.reply.model -rs 123 --mt=1

rm -rf ./data/ltrate.reply.model
rm -rf ./data/roc.reply.model
cp -rf ./ltrate.reply.model/ ./data/ 
cp -rf ./roc.reply.model/ ./data/
