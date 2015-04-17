#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   select-feature.py
#        \author   chenghuige  
#          \date   2015-04-14 15:41:05.995583
#   \Description  
# ==============================================================================

import sys,os

lines = open(sys.argv[1]).readlines()

for i in range(len(lines) - 1):
    if lines[i].startswith('0') and lines[i + 1].startswith('1'):
        for j in range(40):
            print lines[i + j].split()[0].split(':')[1]
        break

 
