sh gen-py.sh $1
comake2 -P
make clean
time make -j12 2>&1 $1 | tee make-result.txt
grep --color=auto -B 1  error:  make-result.txt
