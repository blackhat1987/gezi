hive -e 'select get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content from pbdata where day = 20150804' > 20150804.txt

