hive -f gen-user-grade-info.hql -hiveconf date=$1 table=gezi_ugrade2
hive -f reduce-features.hql -hiveconf itable=gezi_ugrade2 otable=gezi_ugrade_feature2
