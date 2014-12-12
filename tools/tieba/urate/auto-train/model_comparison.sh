wget ftp://cq01-forum-urate01.cq01.baidu.com//home/forum/tieba-urate/log/tieba_urate.log.$1* .
#cat tieba_urate.log.$1* | perl -ane 'if($_=~/PID:\((.+?)\).*score\((.+?)\).*title:\((.+?)\).*content:\((.+?)\).*result:\((.+?)\)/) {print "$1\t$2\t$3\t$4\t$5\n";}' > for_evaluate.txt
cat tieba_urate.log.$1* | perl -ane 'if($_=~/PID:\((.+?)\).*title:\((.+?)\).*content:\((.+?)\).*result:\((.+?)\)/) {print "$1\t$2\t$3\t$4\t$5\n";}' > for_evaluate.txt
./split-thread-reply.py for_evaluate.txt 
./sort.py for_evaluate.thread.txt -1 > for_evaluate.thread.sorted.txt
./rand.py for_evaluate.thread.txt > for_evaluate.thread.rand.txt
head -n 15000 for_evaluate.thread.rand.txt > for_evaluate.thread.rand.15000.txt
./sort.py for_evaluate.thread.rand.15000.txt -1 > for_evaluate.thread.rand.15000.sorted.txt
./gen-evaluate-label.py for_evaluate.thread.rand.15000.txt > for_evaluate.thread.rand.15000.label.txt
./urate_train -i for_evaluate.thread.rand.15000.label.txt -o feature.evaluate.txt  
./melt feature.evaluate.txt -c test
./sort.py --header ./result/0.inst.txt -2 > evaluate.now.sorted.txt
./get-old-recall.py for_evaluate.thread.rand.15000.sorted.txt 0.974 > old.recall.txt
./get-new-recall.py old.recall.txt evaluate.now.sorted.txt > new.recall.txt
./merge-recall.py old.recall.txt new.recall.txt > all.reacll.txt
