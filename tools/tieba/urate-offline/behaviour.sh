hive -f ./gen-behaviour-commands.hql -hiveconf date=$1 table=gezi_user_all_commands 
hive -f ./gen-behaviour-feature.hql -hiveconf itable=gezi_user_all_commands otable=gezi_user_behaviour_feature
