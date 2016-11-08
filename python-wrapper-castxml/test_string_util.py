#!/usr/bin/env python
# -*- coding: gbk -*-
# ==============================================================================
#          \file   test_string_util.py
#        \author   chenghuige  
#          \date   2016-11-05 10:32:10.722281
#   \Description  
# ==============================================================================

  
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import gezi.nowarning 
import libstring_util as su

text = 'abc你好jordan今天天气不错'

print(text)
print(len(text))

print([x for x in su.gbk_offsets(text)])
