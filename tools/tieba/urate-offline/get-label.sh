hive -e 'select feature_name from queryPlatform.gezi_ubehaviour_label limit 1' > feature.header.txt
hive -e 'select uid, label, feature_len, feature from queryPlatform.gezi_ubehaviour_label' > feature.body.txt
./add-header.py feature.header.txt feature.body.txt > feature.txt
rm -rf feature.body.txt
