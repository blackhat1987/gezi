hive -f gen-user-grade-info.hql -hiveconf date=$1 table=gezi_ugrade
hive -f reduce-features.hql -hiveconf itable=gezi_ugrade otable=gezi_ugrade_feature
