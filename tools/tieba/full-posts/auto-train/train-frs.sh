#cat ../../urate/auto-train/pid.txt ../../urate/auto-train/pid.pv.spam.500.txt > pid.withpv.txt
./pids2tids.py ../../urate/auto-train/pid.frs.txt tid.frs.txt
#./pids2tids.py pid.withpv.txt tid.txt
./fullposts_train -i ./tid.frs.txt -o feature.frs.txt
./fix-label.py feature.frs.txt feature.fixed.frs.txt 
#./add-weight.py feature.fixed.txt 4 > feature.fixed.weight.txt
python ./remove-files.py ./history 1000000
rm -rf ./model
./bin/melt ./feature.fixed.frs.txt -cl fr -c train --flagfile=./gbdt.gflags -excl plsa -m frs.model
#./bin/melt ./feature.fixed.weight.txt -cl fr -c train --flagfile=./gbdt.gflags --weight=2

merge-tlc.py ./feature.fixed.txt ./feature.fixed.frs.txt feature.merge.txt 
./bin/melt ./feature.merge.txt -cl fr -c train --flagfile=./gbdt.gflags -excl plsa -m merge.model
