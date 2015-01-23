sed -i "s/\.\.\/include/\.\/include/g" $1
pushd .
cd ..
o=${1/.py/_py.cc} 
rm ./python-wrapper/$o
python ./python-wrapper/$1
popd 
sed -i "s/\"include/\"\.\.\/include/g" $o
python ./fix-pyplusplus.py $o > ./tmp/$o.bak1 
python ./add-static-def.py ./tmp/$o.bak1 > ./tmp/$o.bak2
python ./fix-constructor.py ./tmp/$o.bak2 > ./tmp/$o.bak3
python ./fix-pyplusplus-stl.py ./tmp/$o.bak3 > ./tmp/$o.bak4
python ./fix-pyplusplus-map.py ./tmp/$o.bak4 > ./tmp/$o.bak5
python ./fix-add-more-vector.py ./tmp/$o.bak5 > $o
