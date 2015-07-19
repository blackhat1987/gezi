cd ./corpus/ 
rm -rf *

cd ./evaluate-info/
rm -rf *
python ../get-ori-data.py  evaluate-info 

cd .. 
cd ./evaluate-info-recent/ 
rm -rf *
python ../get-ori-data.py evaluate-info-recent
cd ..

#./rand.py ./evaluate-info/frs_normalpid.txt > ./evaluate-info/frs_normalpid.rand.txt
#./gen-frs-label.py ./evaluate-info/frs_spampid.txt ./evaluate-info/frs_normalpid.rand.txt > pid.frs.txt
#./gen-frs-label.py ./evaluate-info/frs_spampid.txt ./evaluate-info/frs_normalpid.txt > pid.frs.txt
./rand.py ./evaluate-info-recent/frs_normalpid.txt > ./evaluate-info-recent/frs_normalpid.rand.txt
#./gen-frs-label.py ./evaluate-info-recent/frs_spampid.txt ./evaluate-info-recent/frs_normalpid.txt > pid.frs.txt
./gen-frs-label.py ./evaluate-info-recent/frs_spampid.txt ./evaluate-info-recent/frs_normalpid.rand.txt > pid.frs.txt
./gen-label-full.py ./evaluate-info/thread_spampid.txt ./evaluate-info/thread_normalpid.txt > pid.txt #urate thread

sh ./get-trate-corpus.sh  #trate thread corpus

./gen-reply-trate-label.py ./evaluate-info/pb_spampid.txt ./evaluate-info/pb_normalpid.txt > pid.reply.trate.txt  #trate reply 

./gen-label.py ./corpus/reply_spampid.txt ./corpus/reply_normalpid.txt > pid.reply.txt  #urate reply 
