#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   test_seg.py
#        \author   chenghuige  
#          \date   2016-08-27 12:59:59.700399
#   \Description  
# ==============================================================================

  
from __future__ import absolute_import
from __future__ import division
#from __future__ import print_function

import sys, os

import libsegment 
seg = libsegment.Segmentor 
seg.Init()

print seg.Segment('我是谁你是谁', '\t')
