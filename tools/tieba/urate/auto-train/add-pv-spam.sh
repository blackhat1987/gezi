./filter-pv.py ./corpus/frs_spampid.txt > ./corpus/frs_spampid.filtered.txt
./label1.py ./corpus/frs_spampid.filtered.txt pid.pv.spam.txt
head -500 pid.pv.spam.txt > pid.pv.spam.500.txt
./urate_train -i pid.pv.spam.500.txt -o ./feature.pv.spam.txt  
./merge-tlc.py ./feature.fixed.txt ./feature.pv.spam.txt ./feature.fixed.addpv.txt 
#cat pid.pv.spam.txt >> pid.txt
