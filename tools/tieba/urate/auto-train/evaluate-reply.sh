./sort.py evaluate.reply.txt -1 > evaluate.reply.sorted.txt
./rand.py evaluate.reply.txt > evaluate.reply.rand.txt
head -n 15000 evaluate.reply.rand.txt > evaluate.reply.rand.15000.txt
./sort.py evaluate.reply.rand.15000.txt -1 > evaluate.reply.rand.15000.sorted.txt
./gen-evaluate-label.py evaluate.reply.rand.15000.txt > evaluate.reply.rand.15000.label.txt
awk '{print $1}' evaluate.reply.rand.15000.txt > evaluate.reply.pid.txt
./urate_predicts_from_file -i evaluate.reply.pid.txt -o evaluate.reply.now.txt
./sort.py evaluate.reply.now.txt -1 > evaluate.reply.now.sorted.txt
./get-old-recall.py evaluate.reply.rand.15000.sorted.txt $1 > old.reply.recall.txt
./get-new-recall.py old.reply.recall.txt evaluate.reply.now.sorted.txt > new.reply.recall.txt
./merge-recall.py old.reply.recall.txt new.reply.recall.txt > all.reply.recall.txt
