sed -i "s/\.\.\/include/\.\/include/g" $1
pushd .
cd ..
o=${1/.py/_py.cc} 
rm ./python-wrapper/$o
python ./python-wrapper/$1
popd 
sed -i "s/\"include/\"\.\.\/include/g" $o
python ./fix-pyplusplus.py $o > $o.bak 
python ./add-static-def.py $o.bak > $o
python ./fix-constructor.py $o > $o.bak
python ./fix-pyplusplus-stl.py $o.bak > $o
python ./fix-pyplusplus-map.py $o > $o.bak
python ./fix-add-more-vector.py $o.bak > $o
#mv $o.bak $o
