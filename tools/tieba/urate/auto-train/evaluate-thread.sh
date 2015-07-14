./sort.py evaluate.thread.txt -1 > evaluate.thread.sorted.txt
./rand.py evaluate.thread.txt > evaluate.thread.rand.txt
head -n 15000 evaluate.thread.rand.txt > evaluate.thread.rand.15000.txt
./sort.py evaluate.thread.rand.15000.txt -1 > evaluate.thread.rand.15000.sorted.txt
./gen-evaluate-label.py evaluate.thread.rand.15000.txt > evaluate.thread.rand.15000.label.txt
awk '{print $1}' evaluate.thread.rand.15000.txt > evaluate.pid.txt
./urate_predicts_from_file -i evaluate.pid.txt -o evaluate.now.txt
./sort.py evaluate.now.txt -1 > evaluate.now.sorted.txt
./get-old-recall.py evaluate.thread.rand.15000.sorted.txt $1 > old.recall.txt
./get-new-recall.py old.recall.txt evaluate.now.sorted.txt > new.recall.txt
./merge-recall.py old.recall.txt new.recall.txt > all.recall.txt
