#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   test_urate.py
#        \author   chenghuige  
#          \date   2015-12-21 17:13:23.267851
#   \Description  
# ==============================================================================

import nowarning
import liburate as urate
import libmelt_predict as mp
import libtieba as tieba

#info = tieba.UrateInfo() #error... attemp to free invalid pointer why ?
info = urate.UrateInfo()
fe = urate.gen_urate_features(80728380434, info)

print info.nowPostInfo.postId

print fe.str()

pf = mp.PredictorFactory()
predictor = pf.LoadPredictor('./data/thread.model/')


print predictor.ToGainSummary(fe)

score = predictor.Predict(fe)
print score
