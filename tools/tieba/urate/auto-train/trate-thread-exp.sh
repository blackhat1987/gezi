python seg-trate-corpus.py ./corpus/train_spam_title ./corpus/train_spam_content ./corpus/train_nonspam_title ./corpus/train_nonspam_content title-content.segged.txt identifer.1gram.txt 
python gen-identifer.py ./title-content.segged.txt identifer.txt
python gen-feature.py ./title-content.segged.txt identifer.txt feature.trate.txt 
python identifer-text2bin.py ./identifer.txt ./identifer.bin 

lines=`cat ./feature.trate.txt | wc -l`
lines=$(($lines+$lines/2))
mlt feature.trate.txt -iter $lines
