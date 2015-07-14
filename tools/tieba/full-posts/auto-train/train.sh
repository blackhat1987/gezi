#cat ../../urate/auto-train/pid.txt ../../urate/auto-train/pid.pv.spam.500.txt > pid.withpv.txt
./pids2tids.py ../../urate/auto-train/pid.frs.txt tid.txt
#./pids2tids.py pid.withpv.txt tid.txt
./fullposts_train -i ./tid.txt 
./fix-label.py feature.txt feature.fixed.txt 
#./add-weight.py feature.fixed.txt 4 > feature.fixed.weight.txt
#python ./remove-files.py ./history 1000000
rm -rf ./model
mlt ./feature.fixed.txt -cl fr -c train -ntree 1500 -nl 128 -mil 50 -lr 0.025 -ff 0.3 -nbag 6 -nbagfrac 1 --bstrap=1 --m=frs.model
#./bin/melt ./feature.fixed.weight.txt -cl fr -c train --flagfile=./gbdt.gflags --weight=2
