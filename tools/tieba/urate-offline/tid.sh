
hive -f gen-tid-lou-feature.hql -hiveconf date=$1 table=gezi_tid_feature
hive -f reduce-features.hql -hiveconf itable=gezi_tid_feature otable=gezi_uid_tids_feature
