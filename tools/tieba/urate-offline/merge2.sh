#@TODO merge many features at one step ?
hive -f merge-features.hql -hiveconf ltable=gezi_urate2 rtable=gezi_user_behaviour_feature2  sec_name=behaviour otable=gezi_user_urate_behaviour_feature2
hive -f merge-features.hql -hiveconf ltable=gezi_user_urate_behaviour_feature2 rtable=pc_behaviour_feature_old2   sec_name=oldbehav otable=gezi_urate_behaviour_oldbehav_feature2
hive -f merge-features.hql -hiveconf ltable=gezi_urate_behaviour_oldbehav_feature2 rtable=gezi_user_img_feature2 sec_name=img otable=gezi_urate_behaviour_oldbehav_img_feature2
hive -f merge-features.hql -hiveconf ltable=gezi_urate_behaviour_oldbehav_img_feature2 rtable=gezi_uid_tids_feature2 sec_name=lou otable=gezi_urate_behaviour_oldbehav_img_lou_feature2
hive -f inner-merge-features.hql -hiveconf ltable=gezi_urate_behaviour_oldbehav_img_lou_feature2 rtable=gezi_ugrade_feature2 sec_name=ugrade otable=gezi_urate_behaviour_oldbehav_img_lou_ugrade_feature$1
