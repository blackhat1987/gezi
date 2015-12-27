#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   test_class.py
#        \author   chenghuige  
#          \date   2015-12-24 15:54:02.422854
#   \Description  
# ==============================================================================

import sys,os

class Test:
	#def predict(self, a):
	#	print a
	def predict(self, a, b):
		print a, b

def preidct(a):
	print a

def predict(a, b):
	print a, b

t = Test()

#t.predict('haha')

t.predict('haha', 'hehe')
 
predict('haha')

predict('haha', 'hehe')
