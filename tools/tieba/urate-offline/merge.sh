#@TODO merge many features at one step ?
hive -f merge-features.hql -hiveconf ltable=gezi_urate rtable=gezi_user_behaviour_feature  sec_name=behaviour otable=gezi_user_urate_behaviour_feature
hive -f merge-features.hql -hiveconf ltable=gezi_user_urate_behaviour_feature rtable=pc_behaviour_feature_old   sec_name=oldbehav otable=gezi_urate_behaviour_oldbehav_feature
hive -f merge-features.hql -hiveconf ltable=gezi_urate_behaviour_oldbehav_feature rtable=gezi_user_img_feature sec_name=img otable=gezi_urate_behaviour_oldbehav_img_feature
hive -f merge-features.hql -hiveconf ltable=gezi_urate_behaviour_oldbehav_img_feature rtable=gezi_uid_tids_feature sec_name=lou otable=gezi_urate_behaviour_oldbehav_img_lou_feature
hive -f inner-merge-features.hql -hiveconf ltable=gezi_urate_behaviour_oldbehav_img_lou_feature rtable=gezi_ugrade_feature sec_name=ugrade otable=gezi_urate_behaviour_oldbehav_img_lou_ugrade_feature
