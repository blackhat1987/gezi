echo $1 > pid.test.txt
./gen-title-content.test.py ./pid.test.txt > test.txt 
more test.txt
./seg-text.py test.txt test.segged.txt identifer.test.txt
./gen-feature.py test.segged.txt identifer.bin feature.test.txt
/home/users/chenghuige/rsc/app/search/sep/anti-spam/melt/tools3/melt feature.test.txt -c test 
more ./result/0.inst.txt 
