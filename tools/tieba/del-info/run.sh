./gen-script.py 31 > run.hql
hive -f ./run.hql 
hive -e 'select * from queryPlatform.gezi_del_info' > result.txt
