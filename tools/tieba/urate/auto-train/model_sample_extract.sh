cd ./corpus/ 
python ../get-ori-data.py 
cd ..
./gen-label.py ./corpus/thread_spampid.txt ./corpus/thread_normalpid.txt > pid.txt

sh ./get-trate-corpus.sh 
./gen-reply-trate-label.py ./corpus/reply_spampid.txt ./corpus/reply_normalpid.txt > pid.reply.trate.txt
