#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   trate_predictor.py
#        \author   chenghuige  
#          \date   2015-12-18 11:42:52.080763
#   \Description  
# ==============================================================================

import sys,os
import collections

#@TODO this is a bug as lib... which is generated using boost.python should import after tensorflow
#if not will core during seesion restore
from binary_classification import BinaryClassifier as DnnPredictor

import nowarning
import libtrate, libnormalizer
import libgezi 
from libsegment import *

from binary_classification import MlpOptions

class TextPredictor(object):
    def __init__(self, model_path, predictor_path):
        self.identifer = libtrate.DoubleIdentifer()
        self.identifer.Load(model_path + '/identifer.bin')

        #self.predictor = libtrate.LinearPredictor()
        #self.predictor.Load(predictor_path)

        self.predictor = libtrate.PredictorFactory.LoadPredictor(predictor_path)
        self.dnn_predictor = DnnPredictor()
        self.dnn_predictor.load(model_path)
        self.normalizer = None
        if self.predictor == None:
            self.normalizer = libnormalizer.NormalizerFactory().Load('./normalizer.bin')
        else:
            self.normalizer = self.predictor.GetNormalizer()
     
        from libcalibrator import CalibratorFactory
        self.calibrator = CalibratorFactory.Load(model_path + '/calibrator.bin')

        Segmentor.Init()

    def deal_title(self, title):
        return title + ' ' + libgezi.normalize_str(title)

    def deal_content(self, content):
        content = libgezi.strip_html(content)
        if len(content) > 100:
            content = libgezi.gbk_substr(content, 0, 100)
        content = content + ' ' + libgezi.normalize_str(content)
        return content


    def predict(self, title, content):
        Segmentor.Init()
        title = self.deal_title(title)
        content = self.deal_content(content)
        #return libtrate.TextPredictor.Predict(title, content, self.identifer, self.predictor)
        title_words = Segmentor.Segment(title, SEG_BASIC)
        content_words = Segmentor.Segment(content, SEG_BASIC)
        #return libtrate.TextPredictor.Predict(title_words, content_words, self.identifer, self.predictor
        #score1 = libtrate.TextPredictor.Predict(title_words, content_words, self.identifer, self.predictor)
        id_val_map =  libtrate.id_map()
        num_words = self.identifer.size()
        libtrate.TextPredictor.Prase(title_words, id_val_map, self.identifer, 0)
        libtrate.TextPredictor.Prase(content_words, id_val_map, self.identifer, num_words)
        #print id_val_map.size()
        fe = libtrate.Vector(id_val_map)
        #print fe.indices.size() 
        score = self.predictor.Predict(fe) 
        #print 'begin dnn predict'
        #fe = self.normalizer.NormalizeCopy(fe)
        dnn_score = float(self.dnn_predictor.Predict(fe))
        adjusted_dnn_score = self.calibrator.PredictProbability(dnn_score)
        #print score1, ' ', score2, ' ', score3
        #print 'linear: ',score1,' ','dnn: ', score3, 'adjusted: ', self.calibrator.PredictProbability(score3)
        #return self.predictor.Predict(fe)
        return (score, dnn_score, adjusted_dnn_score)


    def id2key_map(self, id_val_map):
        fe = libtrate.Vector(id_val_map)
        self.predictor.GetNormalizer().Normalize(fe);
        key_val_map = collections.defaultdict(float)
        weights = self.predictor.weights()
        total = 0
        for i in xrange(fe.indices.size()):
            index = fe.indices[i]
            val = fe.values[i]

            if weights[index] == 0:
                continue

            key = ''
            if index < self.identifer.size():
                key = 't:' + self.identifer.key(index)
            else:
                key = 'c:' + self.identifer.key(index - self.identifer.size())

            key_val_map[key] += weights[index]

            total += val * weights[index]
        total += self.predictor.bias()
        return key_val_map, total 
        
    def predict_debug(self, title, content):
        id_val_map =  libtrate.id_map()
        title = self.deal_title(title)
        content = self.deal_content(content)
        #score = libtrate.TextPredictor.Predict(title, content, self.identifer, self.predictor, id_val_map)

        title_words = Segmentor.Segment(title, SEG_BASIC)
        sep = '/'
        import gezi
        title_seg_result = sep.join(gezi.vec2list(title_words))
        content_words = Segmentor.Segment(content, SEG_BASIC)
        content_seg_result = sep.join(gezi.vec2list(content_words))
        score = libtrate.TextPredictor.Predict(title_words, content_words, self.identifer, self.predictor, id_val_map)

        key_val_map, total = self.id2key_map(id_val_map)
        import cStringIO
        map_info = cStringIO.StringIO()
        map_info.write('Per ngram weight sort by spam prob\n\n')

        sorted_items = sorted(key_val_map.items(), key=lambda x: x[1], reverse = True)
        for key, val in sorted_items:
            map_info.write('{}|{:40f}\n'.format(key.replace('\x01', '/'), val))

        map_info.write('\n\nPer ngram weight sort by impportance\n\n')
        sorted_items = sorted(key_val_map.items(), key=lambda x: abs(x[1]), reverse = True)
        for key, val in sorted_items:
            map_info.write('{}|{:40f}\n'.format(key.replace('\x01', '/'), val))

        class DebugInfo(object):
            title_seg_result = ''
            content_seg_result = ''

        debug_info = DebugInfo()
        debug_info.title_seg_result = title_seg_result
        debug_info.content_seg_result = content_seg_result
        debug_info.map_info = map_info.getvalue()
        debug_info.title = title 
        debug_info.content = content

        debug_info.total = total 
        debug_info.output = self.predictor.Output(id_val_map)
        debug_info.score = self.predictor.Predict(id_val_map)

        return score, debug_info

