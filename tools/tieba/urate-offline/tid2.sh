hive -f gen-tid-lou-feature.hql -hiveconf date=$1 table=gezi_tid_feature2
hive -f reduce-features.hql -hiveconf itable=gezi_tid_feature2 otable=gezi_uid_tids_feature2
