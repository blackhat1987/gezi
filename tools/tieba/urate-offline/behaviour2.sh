hive -f ./gen-behaviour-commands.hql -hiveconf date=$1 table=gezi_user_all_commands2 
hive -f ./gen-behaviour-feature.hql -hiveconf itable=gezi_user_all_commands2 otable=gezi_user_behaviour_feature2
