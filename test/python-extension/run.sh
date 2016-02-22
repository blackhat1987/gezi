python ./chg.py 
mv ./chg_py.cc ./chg_py.cc.bak 
cat ./readme ./chg_py.cc.bak > ./chg_py.cc 

/home/users/chenghuige/.jumbo/comake/comake2 -P 
make clean
make -j12
