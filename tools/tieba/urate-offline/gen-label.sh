hive -f ./gen-user-del-count.hql -hiveconf date=$1
hive -f ./gen-user-post-count.hql -hiveconf date=$1
hive -f ./gen-user-post-del-count.hql 
