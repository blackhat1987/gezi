python $1
o=${1/.py/_py.cc} 
python ./fix-pyplusplus.py $o > $o.bak
mv $o.bak $o
