#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   evaluate-precision.py
#        \author   chenghuige  
#          \date   2014-12-15 10:37:27.407714
#   \Description  
# ==============================================================================

import sys,os

def evaluate_precision(label_list, predicts, precision):
    tp_list = [0] * (len(label_list) + 1)
    for i in range(len(label_list)):
        if (label_list[i] == 1):
            tp_list[i + 1] = tp_list[i] + 1
        else:
            tp_list[i + 1] = tp_list[i]
    
    tp = fp = tn = fn = 0
    for i in reversed(range(len(label_list))):
        if tp_list[i + 1] / float(i + 1) >= precision:
            tp = tp_list[i + 1]
            fp = i + 1 - tp 
            print "Choosing thre: %f"%predicts[i]
            break
        else:
            if label_list[i] == 1:
                fn += 1
            else:
                tn += 1

 