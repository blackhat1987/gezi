#!/usr/bin/env python
# -*- coding: gbk -*-
# ==============================================================================
#          \file   test_matchdict.py
#        \author   chenghuige  
#          \date   2016-11-04 22:26:12.336407
#   \Description  
# ==============================================================================

  
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import libmatchdict

from libmatch_dict import MatchDict

text = 'abc刘亦菲朴姬兰你是谁宫崎骏最新电影下载 nike刘亦菲妈妈刘亦菲小姨'

match_dict = MatchDict('./entities.md.fix.filtered')

vec = match_dict.search(text)

for item in vec:
  print(item.word, item.offset, item.length, item.property)

print(match_dict.search_count(text))

vec = match_dict.search(text, libmatch_dict.MATCH_DICT_SEARCH_ALL)

for item in vec:
  print(item.word, item.offset, item.length, item.property)
