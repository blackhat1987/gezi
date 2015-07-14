#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   text-score.py
#        \author   chenghuige  
#          \date   2014-04-25 14:17:57.490315
#   \Description  
# ==============================================================================
from gezi import *
import urllib, json
from collections import defaultdict

LogHelper.set_level(4)

identifer_path = './identifer.bin'
model_path = './model/'
model_text_path = './model/model.txt'

identifer = DoubleIdentifer()
identifer.Load(identifer_path)
word_num = identifer.size()
print 'identifer load done word_num: ' + str(word_num)

f = {}
num = 0;
for line in open(model_text_path):
	num += 1
	if (num < 3):
		continue
	l = line.strip().split()
	f[int(l[0])] = float(l[-1])

print 'model text load done'

Segmentor.init()
seg = Segmentor()

predictor = PredictorFactory.LoadPredictor(model_path)

ngram = 3
sep = '$#$'

print 'all load done, work!'

def deal(pid):
	url = "http://service.tieba.baidu.com/service/post?method=getPostInfo&post_ids=a:1:{i:0;i:%d;}&format=mcpackraw"%pid
	content = urllib.urlopen(url).readline().decode('gbk')	
	m = {}
	try:
	    m = json.loads(content)['output'][0]
	except Exception:
	    print "wrong [%s]"%pid
	    print content
	    print line
	    return
	
	title = m['title'].encode('gbk').replace('\n', ' ')
	content = m['content'].encode('gbk').replace('\n', ' ')
	title = get_real_title(title)
	print title
	print content
	content = strip_html(content)
	if len(content) > 100:
		content = gbk_substr(content, 0, 100)
	title = seg.segment(title, sep, SEG_BASIC)
	content = seg.segment(content, sep, SEG_BASIC)
	print title
	print content

	tmap = defaultdict(float)
	l1 = title.split(sep)
	li = get_words(l1, ngram)
	#print len(li)
	get_skip_bigram(l1, li, 2, sep)
	#print len(li)
	for word in li:
		#print word
		id_ = identifer.id(word)
		if id_ >= 0 :
			tmap[id_] += identifer.value(id_)

	l = content.split(sep)
	li = get_words(l, ngram)
	#print len(li)
	get_skip_bigram(l, li, 2, sep)
	#print len(li)
	for word in li:
		#print word
		id_ = identifer.id(word) 
		if id_ >= 0:
			id = id_ + word_num
			tmap[id] += identifer.value(id_)
	
	fe = Vector()
	for key,value in sorted(tmap.items()):
		fe.Add(key, value)
	fe2 = predictor.Normalize(fe)


	from prettytable import PrettyTable 
	#x = PrettyTable(["Id", "Key", "Value", "NormValue", "Weight"]) 
	print "show infos"	
	num = 0
	for id in fe.indices:
		value = fe.values[num]
		value2 = fe2.values[num]
		weight = 0
		if id in f:
			weight = f[id]
		if id < word_num:
			key = identifer.key(id)
		else:
			key = 'c:' + identifer.key(id - word_num)
		print '\t'.join([str(num), "Id:%d"%id, "Key:%s"%key, "Value:%f"%value, "NormValue:%f"%value2, "Weight:%f"%weight])
		#x.add_row([str(id), key, str(value), str(value2), str(weight)])
		num += 1

	#print x
	print "predict"
	print "Output: %f"%predictor.Output(fe)
	#print fe.str()
	print "Score: %f"%predictor.Predict(fe)
	print fe.str()

while True:
	input = raw_input()
	try:
		pid = int(input)
		deal(pid)
	except Exception:
		try:
			for line in open(input):
				try:
					pid = int(line.strip())
					deal(pid)
				except Exception:
					pass
		except Exception:
			pass
