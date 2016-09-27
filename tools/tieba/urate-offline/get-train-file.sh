hive -e 'select feature_names from queryPlatform.gezi_ubehaviour_label limit 1' > feature.header.txt
hive -e 'select feature from queryPlatform.gezi_ubehaviour_dense_feature limit 500000' > feature.body.txt
rm feature.origin.txt
cp feature.txt feature.origin.txt
./add-header.py feature.header.txt feature.body.txt > feature.txt
python  ./splitData_auto.py
b=$?
if [ $b -eq 0 ];then
    echo 'model use before!'
else 
	rm -rf ./model_origin
	cp  -rf ./model ./model_origin	
	./melt feature.train.txt -cl fr -vl 1 --flagfile=gbdt.500tree.gflags -c tt -test feature.model.test.txt -excl plsa>modelResult.txt
fi

python  ./evaludate-auto.py
a=$?
echo $a
if [ $a -eq 1 ];then
    echo 'model is right!'
else
    echo 'model is not right,use origin model!'
	rm -rf ./model
    cp -rf ./model_origin  ./model     
	rm feature.txt
    cp feature.origin.txt feature.txt 
fi


rm -rf feature.body.txt
