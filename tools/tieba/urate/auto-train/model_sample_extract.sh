cd ./corpus/ 
rm -rf *

python ../get-ori-data.py 

cd ..
#./gen-label.py ./corpus/thread_spampid.txt ./corpus/thread_normalpid.txt > pid.txt #urate thread
./gen-label-full.py ./evaluate-info/thread_spampid.txt ./evaluate-info/thread_normalpid.txt > pid.txt #urate thread

sh ./get-trate-corpus.sh  #trate thread corpus

#./gen-reply-trate-label.py ./corpus/pb_spampid.txt ./corpus/pb_normalpid.txt > pid.reply.trate.txt  #trate reply 
./gen-reply-trate-label.py ./evaluate-info/pb_spampid.txt ./evaluate-info/pb_normalpid.txt > pid.reply.trate.txt  #trate reply 

./gen-label.py ./corpus/reply_spampid.txt ./corpus/reply_normalpid.txt > pid.reply.txt  #urate reply 
