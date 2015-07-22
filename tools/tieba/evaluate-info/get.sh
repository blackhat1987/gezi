#!/bin/sh
FRSTYPE=0
PBTYPE=1
THREADTYPE=2
REPLYTYPE=8

MYSQLBIN="/home/forum/.jumbo/bin/mysql -h10.95.32.17 -P3306 -uroot -proot evaluation-pf -N -e"

DATE=$(date +%Y%m%d --date='12 month ago')
SELECT_SP="select post_id,pd.dict_id,t.name,end_time,d.name from epf_post_dict as pd inner join epf_task as t on pd.task_id=t.task_id inner join epf_dict as d on pd.dict_id=d.dict_id"
WHERE_SP="where pd.dict_id not in (0,1,37) and t.task_status = 2 and t.task_type"
SELECT_NO="select distinct post_id, max(pd.dict_id) as dict_id,t.name,end_time,d.name from epf_post_dict as pd inner join epf_task as t on pd.task_id=t.task_id inner join epf_dict as d on pd.dict_id=d.dict_id"
WHERE_NO="where t.task_status = 2 and t.task_type"
GROUP="group by post_id having dict_id=1"
ORDER="order by end_time desc"

$MYSQLBIN "set character_set_server = utf8;set character_set_database = utf8;set names utf8;$SELECT_SP $WHERE_SP=$FRSTYPE $ORDER" > frs_spampid.txt
iconv -f utf8 -t gbk frs_spampid.txt > frs_spampid.txt.bak
mv frs_spampid.txt.bak frs_spampid.txt 
$MYSQLBIN "set character_set_server = utf8;set character_set_database = utf8;set names utf8;$SELECT_NO $WHERE_NO=$FRSTYPE $GROUP $ORDER" > frs_normalpid.txt
iconv -f utf8 -t gbk frs_normalpid.txt > frs_normalpid.txt.bak
mv frs_normalpid.txt.bak frs_normalpid.txt

$MYSQLBIN "set character_set_server = utf8;set character_set_database = utf8;set names utf8;$SELECT_SP $WHERE_SP=$THREADTYPE $ORDER" > thread_spampid.txt
iconv -f utf8 -t gbk thread_spampid.txt > thread_spampid.txt.bak
mv thread_spampid.txt.bak thread_spampid.txt
$MYSQLBIN "set character_set_server = utf8;set character_set_database = utf8;set names utf8;$SELECT_NO $WHERE_NO=$THREADTYPE $GROUP $ORDER" > thread_normalpid.txt
iconv -f utf8 -t gbk thread_normalpid.txt > thread_normalpid.txt.bak
mv thread_normalpid.txt.bak thread_normalpid.txt 


$MYSQLBIN "set character_set_server = utf8;set character_set_database = utf8;set names utf8;$SELECT_SP $WHERE_SP=$PBTYPE $ORDER" > pb_spampid.txt
iconv -f utf8 -t gbk pb_spampid.txt > pb_spampid.txt.bak
mv pb_spampid.txt.bak pb_spampid.txt 
$MYSQLBIN "set character_set_server = utf8;set character_set_database = utf8;set names utf8;$SELECT_NO $WHERE_NO=$PBTYPE $GROUP $ORDER" > pb_normalpid.txt
iconv -f utf8 -t gbk pb_normalpid.txt > pb_normalpid.txt.bak
mv pb_normalpid.txt.bak pb_normalpid.txt

$MYSQLBIN "set character_set_server = utf8;set character_set_database = utf8;set names utf8;$SELECT_SP $WHERE_SP=$REPLYTYPE $ORDER" > reply_spampid.txt
iconv -f utf8 -t gbk reply_spampid.txt > reply_spampid.txt.bak
mv reply_spampid.txt.bak reply_spampid.txt 
$MYSQLBIN "set character_set_server = utf8;set character_set_database = utf8;set names utf8;$SELECT_NO $WHERE_NO=$REPLYTYPE $GROUP $ORDER" > reply_normalpid.txt
iconv -f utf8 -t gbk reply_normalpid.txt > reply_normalpid.txt.bak
mv reply_normalpid.txt.bak reply_normalpid.txt 

