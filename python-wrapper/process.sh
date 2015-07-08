i=$1
o=${i/.py/_py.cc} 
rm $o

python $i

sh fix-cc.sh $o

~/.jumbo/comake/comake2 -P
sh ~/tools/bin/make.sh
