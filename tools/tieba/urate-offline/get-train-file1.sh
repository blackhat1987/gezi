

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
    rm -rf 	./model_origin
else
    echo 'model is not right,use origin model!'
	rm -rf ./model
    cp -rf ./model_origin  ./model       
fi


rm -rf feature.body.txt
