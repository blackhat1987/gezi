sed -i "s/\.\.\/include/\.\/include/g" $1
pushd .
cd ..
python ./python-wrapper/$1
popd 
o=${1/.py/_py.cc} 
sed -i "s/\"include/\"\.\.\/include/g" $o
python ./fix-pyplusplus.py $o > $o.bak
mv $o.bak $o
