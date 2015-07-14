d=`date -d last-day +%Y%m%d`
echo $d

a=`cat ./feature.trate.txt | wc -l`
b=2
a=$(($a+$a/2))
echo $a
