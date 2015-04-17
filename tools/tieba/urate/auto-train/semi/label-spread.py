#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   label-spread.py
#        \author   chenghuige  
#          \date   2015-04-10 12:14:34.325608
#   \Description  
# ==============================================================================

import sys,os
import numpy as np

data = np.loadtxt(sys.argv[1], skiprows=1)

X = data[:,2:]
y = data[:,1]

n_total_samples = len(y)
n_labeled_points = 1000

unlabeled_indices = np.arange(n_total_samples)[n_labeled_points:]

y[unlabeled_indices] = -1

from sklearn.decomposition import PCA
pca = PCA(n_components=10)
pca_result = pca.fit_transform(X)

from sklearn.semi_supervised import LabelSpreading
label_prop_model = LabelSpreading()
label_prop_model.fit(X, y)

n = 0
for line in open(sys.argv[2]):
	if n == 0:
		print '#' + line,
	else:
		l = line.rstrip().split('\t')
		l[0] = '_' + l[0]
		l[1] = str(label_prop_model.transduction_[n - 1])
		print '\t'.join(l)
	n += 1


