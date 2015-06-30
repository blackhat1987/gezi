#!/bin/sh
FRSTYPE=0

THREADTYPE=2
MYSQLBIN="/home/forum/.jumbo/bin/mysql -h10.95.32.17 -P3306 -uroot -proot evaluation-pf -e"
ROOT_DIR="./"

DATE=$(date +%Y%m%d --date='12 month ago')
SELECT_SP="select post_id,pd.dict_id,t.name,end_time,d.name from epf_post_dict as pd inner join epf_task as t on pd.task_id=t.task_id inner join epf_dict as d on pd.dict_id=d.dict_id"
#WHERE_SP="where end_time > $DATE and record_status=0 and dict_id not in (0,1,37) and task_type"
WHERE_SP="where pd.dict_id not in (0,1) and t.task_type"
#SELECT_NO="select distinct post_id,max(pd.dict_id) as pd.dict_id,t.name,end_time,d.name from epf_post_dict as pd inner join epf_task as t on pd.task_id=t.task_id inner join epf_dict as d on pd.dict_id=d.dict_id"
SELECT_NO="select distinct post_id,pd.dict_id,t.name,end_time,d.name from epf_post_dict as pd inner join epf_task as t on pd.task_id=t.task_id inner join epf_dict as d on pd.dict_id=d.dict_id"
#WHERE_NO="where end_time > $DATE and record_status=0 and task_type"
WHERE_NO="where t.task_type"
GROUP="group by post_id having pd.dict_id=1"
ORDER="order by end_time desc"

$MYSQLBIN "set character_set_server = utf8;set character_set_database = utf8;set names utf8;$SELECT_SP $WHERE_SP=$FRSTYPE $ORDER" >${ROOT_DIR}/frs_spampid.txt
$MYSQLBIN "set character_set_server = utf8;set character_set_database = utf8;set names utf8;$SELECT_NO $WHERE_NO=$FRSTYPE $GROUP $ORDER" >${ROOT_DIR}/frs_normalpid.txt

$MYSQLBIN "set character_set_server = utf8;set character_set_database = utf8;set names utf8;$SELECT_SP $WHERE_SP=$THREADTYPE $ORDER" >${ROOT_DIR}/thread_spampid.txt
$MYSQLBIN "set character_set_server = utf8;set character_set_database = utf8;set names utf8;$SELECT_NO $WHERE_NO=$THREADTYPE $GROUP $ORDER" >${ROOT_DIR}/thread_normalpid.txt
