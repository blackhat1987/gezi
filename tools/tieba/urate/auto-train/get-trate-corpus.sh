rm -rf ./corpus/train*
cd ./corpus/
wget cq01-forum-xdi03.cq01:/home/forum/trate_autorun/reply_title_model/reply_title/data/train* .
mkdir -p reply 
cd reply 
rm -rf train*
wget cq01-forum-xdi03.cq01:/home/forum/trate_autorun/huifu_model/huifu/data/train* .
cd .. 
cd ..
