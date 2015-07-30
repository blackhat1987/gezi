hive -e 'select feature_names from queryPlatform.gezi_ubehaviour_label limit 1' > feature.header.txt
hive -e 'select uid, label, feature_len,feature from queryPlatform.gezi_ubehaviour_label' > feature.body.txt
./add-header-sparse.py feature.header.txt feature.body.txt > feature.txt
rm -rf feature.body.txt
