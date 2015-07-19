./pids2tids.py ../urate/pid.frs.txt tid.txt
./fullposts_train -i ./tid.txt 
./fix-label.py feature.txt feature.fixed.txt 
./add-weight.py feature.fixed.txt 10 > feature.fixed.weight.txt
cp -rf frs.model frs.model.bak
rm -rf ./frs.model/
mlt ./feature.fixed.weight.txt -cl fr -c train -ntree 1500 -nl 128 -mil 50 -lr 0.025 -ff 0.3 -nbag 6 -nbagfrac 1 --bstrap=1 --m=frs.model --weight=2 --mfeature=1 --mc=1 --excl ^img_
