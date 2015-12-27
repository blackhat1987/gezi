#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   demo.py
#        \author   chenghuige  
#          \date   2015-12-20 14:15:16.357504
#   \Description  
# ==============================================================================

from flask import Flask
from flask import render_template

class FLAGS:
	pass

FLAGS.port = 8003
FLAGS.debug = True

app = Flask(__name__)
app.secret_key = 's3cr3t'

@app.route('/')
def index():
	return 'This is demo of urate you may try /urate'

from flask.ext.wtf import Form
from wtforms import IntegerField
from wtforms.validators import Required,Length

class UrateForm(Form):
    post_id = IntegerField('post_id',validators = [Required()])
    tree_index = IntegerField('tree_index',validators = [Required()])
    info = None
    score = 0

 
def validate_on_submit(form):
	if form.post_id.data == None or form.post_id.data <= 0:
		return False
	return True


from flask import request  
predictors = None
@app.route('/urate',methods = ['GET' , 'POST'])
def urate():
    form = UrateForm()
    
    models = ('./data/reply.model/', './data/thread.model/')
    if 'submit' in request.form:
    	if request.form['submit'] == 'FeatureGainThread' or request.form['submit'] == 'FeatureGainReply':
    		index = (request.form['submit'] == 'FeatureGainThread')
    		file_ = models[index] + 'model.featureGain.txt'
    		pre_str = 'Feature importance of model: %s\n\n'%models[index]
    		gain_str = pre_str + open(file_).read() 
    		return render_template('content.html', form = form, content = gain_str)

    if validate_on_submit(form):
        print('post_id:%d'%form.post_id.data)

        import nowarning
        import libmelt_predict as mp

        global predictors
        if predictors == None:
            reply_predictor = mp.PredictorFactory.LoadPredictor('./data/reply.model')
            thread_predictor = mp.PredictorFactory.LoadPredictor('./data/thread.model')
            predictors = (reply_predictor, thread_predictor)

        import liburate as urate
        import libmelt_predict as mp
        import libtieba as tieba

        form.info = urate.UrateInfo()
        fe = urate.gen_urate_features(form.post_id.data, form.info, historyNum = 40)

        is_thread = form.info.nowPostInfo.IsThread()
        preidctor = predictors[is_thread]
        form.score = preidctor.Predict(fe)
        pid = form.post_id.data

        print request.form
        if 'submit' in request.form:
        	if request.form['submit'] == 'Json':
        		s = urate.get_urate_info_str(form.info)
        		json_str = s.decode('gbk', 'ignore')
        		return render_template('content.html', form = form, content = json_str) 

        	if request.form['submit'] == 'FeatureGainPerPredict':
        		summary = preidctor.ToGainSummary(fe)
        		summary = 'PerfeatureGain for post_id: %d\nscore:%.3f\n\n%s'%(pid, form.score, summary)
        		return render_template('content.html', form = form, content = summary) 

        	if request.form['submit'] == 'PrintTree':
    			index = 0
    			if form.tree_index.data != None:
    				index = form.tree_index.data
    			model = models[is_thread]

    			import os
    			command = 'rm -rf ./static/tree*.png'
    			os.system(command)
    			command = './print-gbdt-tree.py --m %s --tree %d --outfile ./static/tree.%d.%d.png --feature %s'%(model, index, pid, index, fe.str())
    			os.system(command)
    			return render_template('tree.html', form = form, pid = pid, index = index)


        from gezi import get_timestr
        return render_template('index.html',form = form, get_timestr = get_timestr)

    return render_template('error.html', form = form)

if __name__ == '__main__':
	app.run(host='0.0.0.0', port=FLAGS.port, debug=FLAGS.debug)
