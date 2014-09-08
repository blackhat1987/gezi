gcc3
cp -rf ../include/* ../include.python/ 
pushd .
cd ../include.python/ 
gen-header-all.py
cd tools
gen-header-all.py
cd ..
cd tieba
gen-header-all.py 
cd .. 
cd Numeric
gen-header-all.py 
cd Vector
gen-header-all.py 
cd .. 
cd .. 
cd feature
gen-header-all.py 
cd .. 
cd PythonWrapper
gen-header-all.py 
cd .. 
cd tieba 
gen-header-all.py
cd info 
gen-header-all.py
cd ..
cd urate 
gen-header-all.py 
cd .. 
cd ..
popd
sh gen-py.sh $1
comake2 -P
make clean
time make -j12 2>&1 | tee make-result.txt
grep --color=auto -B 1  error:  make-result.txt
