#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   hist-feature.py
#        \author   chenghuige  
#          \date   2014-10-02 16:22:18.533077
#   \Description  
# ==============================================================================

from gezi import * 

input = sys.argv[1]

input1 = input.replace('.txt', '.pos.txt')
input2 = input.replace('.txt', '.neg.txt')
print input1, input2
col = sys.argv[2]
print col
bins_ = 10 
if len(sys.argv) > 3:
	bins_ = int(sys.argv[3])

if not os.path.exists(input1) or not os.path.exists(input2):
	cmd = 'melt %s -c sd -header 1 -label 1'%(input)
	print cmd
	os.system(cmd)


input12 = input1.replace('.txt', '.csv')

if not os.path.exists(input12):
	cmd = 'melt2csv.py %s > %s'%(input1, input12)
	print cmd
	os.system(cmd)

input22 = input2.replace('.txt', '.csv')
if not os.path.exists(input22):
	cmd = 'melt2csv.py %s > %s'%(input2, input22)
	print cmd
	os.system(cmd)

input1 = input12
input2 = input22

print input1,input2
print 'loading: ' + input1
tp = pd.read_table(input1)
print 'loading: ' + input2
tn = pd.read_table(input2)
print tp[col]
#cols = tp.columns()

cmd = 'mkdir -p ./hist'
print cmd
os.system(cmd)

prefix = input[:input.rindex('.txt')]

file_name = './hist/' + prefix + '.' + col + '.png'
plt.hist((tp[col], tn[col]), bins=bins_)
plt.savefig(file_name)
