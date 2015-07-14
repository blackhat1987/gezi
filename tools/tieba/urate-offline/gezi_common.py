import time
import warnings
warnings.simplefilter("ignore", RuntimeWarning) 
import sys, os
from collections import defaultdict

import json
from libgezi import *

def get_timestr(stamp):
	ttime = stamp
	try:
		ttime = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(stamp))
	except Exception:
		pass
	return ttime

def get_datestr(stamp):
	ttime = stamp
	try:
		ttime = time.strftime('%Y-%m-%d 00:00:00', time.localtime(stamp))
	except Exception:
		pass
	return ttime

def get_ngram_words(l, ngram, sep = '$#$'):
	li = []
	for i in range(len(l)):
		for j in range(ngram):
			if (i + j >= len(l)):
				continue 
			li.append(sep.join(l[i : i + j + 1]))
	return li 


#@TODO generalized skip n now only skip-n bigram
#skip 1 2 3 4
def get_skipn_bigram(l, n, sep = '$#$'):
	li = []
	l2 = ['0', '0']
	for i in range(len(l) - 1 - n):
		l2[0] = l[i]
		l2[1] = l[i + 1 + n]
		li.append(sep.join(l2))
	return li 

def get_skipn_bigram(l, li, n, sep = '$#$'):
	l2 = ['0', '0']
	for i in range(len(l) - 1 - n):
		l2[0] = l[i]
		l2[1] = l[i + 1 + n]
		li.append(sep.join(l2))

def get_skip_bigram(l, li, n, sep = '$#$'):
	for skip in range(1, n):
		get_skipn_bigram(l, li, skip, sep)

def h2o(x):
	if isinstance(x, dict):
		return type('jo', (), {k: h2o(v) for k, v in x.iteritems()})
	elif isinstance(x, list):
		return [h2o(item) for item in x]
	else:
		return x

def h2o2(x):
	if isinstance(x, dict):
		return type('jo', (), {k: h2o2(v) for k, v in x.iteritems()})
	elif isinstance(x, list):
		return type('jo', (), {"value" + str(idx): h2o2(val) for idx, val in enumerate(x)})
	else:
		return x

def json2obj(s):
	import json
	a = h2o(json.loads(s))
	if hasattr(a, 'data'):
		return a.data
	return a

def json2obj2(s):
	import json
	a = h2o2(json.loads(s))
	if hasattr(a, 'data'):
		return a.data
	return a

def jsonfile2obj(path):
	return json2obj(open(path).read().decode('gbk', 'ignore'))

def jsonfile2obj2(path):
	return json2obj2(open(path).read().decode('gbk','ignore'))

def xmlfile2obj(path):
	import xmltodict
	doc = xmltodict.parse(open(path), process_namespaces=True)
	a = h2o2(doc)
	if hasattr(a, 'cereal'):
		return a.cereal.data
	return a

def xmlfile2obj2(path):
	import xmltodict
	doc = xmltodict.parse(open(path), process_namespaces=True)
	a = h2o2(doc)
	if hasattr(a, 'cereal'):
		return a.cereal.data
	return a

def dict2map(dict_, map_):
	for key,value in dict_.items():
		map_[key] = value 

def map2dict(map_):
	dict_ = {}
	for item in map_:
		dict_[item.key] = item.data 
	return dict_

def list2vec(list_, vec_):
	for item in list_:
		vec_.append(item)

def list2vector(list_, vec_):
	for item in list_:
		vec_.push_back(item)

def vec2list(vec_):
	list_ = []
	for item in vec_:
		list_.append(item)
	return list_

def vector2list(vec_):
	list_ = []
	for i in xrange(vec_.size()):
		list_.append(vec_[i])
	return list_

def list2gbk(l, strategy = 'ignore'):
	for i in range(len(l)):
		l[i] = l[i].decode('utf8').encode('gbk', strategy)

def merge_feature(feature, feature_names, feature2, feature_names2):
		fe = FeatureVector()
		feature = [x for x in feature.split(',') if x]
		feature2 = [x for x in feature.split(',') if x]
		feature_names = feature_names.split(',')
		feature_names2 = feature_names2.split(',')
		values = [0] * (len(feature_names) + len(feature_names2))
		for item in feature:
			l = item.split(':')
			values[int(l[0])] = float(l[1])
		for item in feature2:
			l = item.split(':')
			values[int(l[0]) + len(feature_names)] = float(l[1])

		feature_names += feature_names2
		for i in range(len(values)):
			fe.add(values[i], feature_names[i])
		return fe

def merge_feature(feature, feature_names, sec_name, feature2, feature_names2):
		fe = FeatureVector()
		feature = [x for x in feature.split(',') if x]
		has_feature2 = True
		if feature2 == '\N' or feature2 == 'NULL':
			feature2 = ''
			has_feature2 = False

		feature2 = [x for x in feature2.split(',') if x]
		feature_names = feature_names.split(',')
		feature_names2 = feature_names2.split(',')
		values = [0] * (len(feature_names) + len(feature_names2) + 1)
		for item in feature:
			l = item.split(':')
			values[int(l[0])] = float(l[1])

		values[len(feature_names)] = float(has_feature2)
		
		for item in feature2:
			l = item.split(':')
			values[int(l[0]) + len(feature_names) + 1] = float(l[1])

		feature_names.append('fhas_' + sec_name)
		feature_names += feature_names2 
		for i in range(len(values)):
			fe.add(values[i], feature_names[i])
		return fe
