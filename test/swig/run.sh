swig -python -c++ chg.i 
#~/.jumbo/comake/comake2 -P
make clean 
make -j8
mv ./libchg.so _libchg.so
