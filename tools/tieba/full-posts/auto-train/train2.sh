#cat ../../urate/auto-train/pid.txt ../../urate/auto-train/pid.pv.spam.500.txt > pid.withpv.txt
#./pids2tids.py ../../urate/auto-train/pid.txt tid.txt
#./pids2tids.py pid.withpv.txt tid.txt
./fullposts_train -i ./tid.txt 
./fix-label.py feature.txt feature.fixed.txt 
#./add-weight.py feature.fixed.txt 4 > feature.fixed.weight.txt
python ./remove-files.py ./history 1000000
rm -rf ./model
./bin/melt ./feature.fixed.txt -cl fr -c train --flagfile=./gbdt.gflags
#./bin/melt ./feature.fixed.weight.txt -cl fr -c train --flagfile=./gbdt.gflags --weight=2
