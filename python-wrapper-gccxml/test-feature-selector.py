#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   test-feature-selector.py
#        \author   chenghuige  
#          \date   2014-03-02 18:22:38.491329
#   \Description  
# ==============================================================================

import sys,os
from libgezi import *

fs = FeatureSelector()
fs.clear();
fs.add("ʳ��\t�ٶȴ���", 0);
fs.add("��Ů\t�ٶȴ���", 0);
fs.add("ʳ��\t��˼����", 1);
fs.add("�೵\t��˼����", 1);
#fs.method(CHI)
#fs.strategy(FeatureSelector.MAX);
fs.method(IG)
fs.strategy(FeatureSelector.SUM)
fs.calc()
fs.show()
fs.save('temp.txt')
