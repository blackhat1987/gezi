d=`date -d last-day +%Y%m%d`
sh ./get-evaluate-corpus.sh $d
#cat tieba_urate.log.$1* | perl -ane 'if($_=~/PID:\((.+?)\).*score\((.+?)\).*title:\((.+?)\).*content:\((.+?)\).*result:\((.+?)\)/) {print "$1\t$2\t$3\t$4\t$5\n";}' > for_evaluate.txt
cat ./evaluate.corpus/tieba_urate.log.* | perl -ane 'if($_=~/PID:\((.+?)\).*title:\((.+?)\).*content:\((.+?)\).*result:\((.+?)\)/) {print "$1\t$2\t$3\t$4\t$5\n";}' > evaluate.txt
./split-thread-reply.py evaluate.txt evaluate.thread.txt evaluate.reply.txt
sh ./evaluate-thread.sh $1
sh ./evaluate-reply.sh $1
