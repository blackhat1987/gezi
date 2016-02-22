#sh ./prepare-header.sh 
sh ./prepare-all-header.sh
sh ./process.sh $1
#/home/users/chenghuige/.jumbo/comake/comake2 -P 
make clean 
time make -j12
