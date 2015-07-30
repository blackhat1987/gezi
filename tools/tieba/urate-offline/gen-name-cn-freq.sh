hive -f ./count-name-cn.hql -hiveconf date=$1
hive -e 'select * from queryplatform.gezi_name_cn_count order by count desc' > word_count.txt
iconv -f utf8 -t gbk word_count.txt > word_count.gbk.txt
./convertCnCount2Ratio.py word_count.gbk.txt > ./nameCnFreq.txt 
cp ./nameCnFreq.txt ./data/
