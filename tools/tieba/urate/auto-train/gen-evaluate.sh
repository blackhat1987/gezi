wget ftp://cq01-forum-urate01.cq01.baidu.com//home/forum/tieba-urate/log/tieba_urate.log.$1* .
#cat tieba_urate.log.$1* | perl -ane 'if($_=~/PID:\((.+?)\).*score\((.+?)\).*title:\((.+?)\).*content:\((.+?)\).*result:\((.+?)\)/) {print "$1\t$2\t$3\t$4\t$5\n";}' > for_evaluate.txt
cat tieba_urate.log.$1* | perl -ane 'if($_=~/PID:\((.+?)\).*title:\((.+?)\).*content:\((.+?)\).*result:\((.+?)\)/) {print "$1\t$2\t$3\t$4\t$5\n";}' > for_evaluate.txt
./split-thread-reply.py for_evaluate.txt
