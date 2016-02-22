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
fs.add("食堂\t百度大厦", 0);
fs.add("美女\t百度大厦", 0);
fs.add("食堂\t文思海辉", 1);
fs.add("班车\t文思海辉", 1);
#fs.method(CHI)
#fs.strategy(FeatureSelector.MAX);
fs.method(IG)
fs.strategy(FeatureSelector.SUM)
fs.calc()
fs.show()
fs.save('temp.txt')
