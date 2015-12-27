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

FLAGS.port = 8004
FLAGS.debug = True
FLAGS.reply_path = './data/ltrate.reply.model'
FLAGS.thread_path = './data/ltrate.thread.model'

app = Flask(__name__)
app.secret_key = 's3cr3t'

@app.route('/')
def index():
	return 'This is demo of trate you may try /trate'

from flask.ext.wtf import Form
from wtforms import IntegerField
from wtforms import StringField
from wtforms.validators import Required,Length

class TrateForm(Form):
    post_id = IntegerField('post_id',validators = [Required()])
    title = StringField('title',validators = [Required()])
    content = StringField('content', validators = [Required()])
    score = 0

def validate_on_submit(form):
	if form.post_id.data == None or form.post_id.data <= 0:
		return False
	return True

from flask import request  

predictors = None
@app.route('/trate',methods = ['GET' , 'POST'])
def trate():
    form = TrateForm()
    
    global predictors
    models = (FLAGS.reply_path, FLAGS.thread_path)
    identifers = (FLAGS.reply_path + "/identifer.bin", FLAGS.thread_path + "/identifer.bin")

    if validate_on_submit(form):
        print('post_id:%d'%form.post_id.data)

        import nowarning
        import text_predictor as tp
        if predictors == None:
            reply_predictor = tp.TextPredictor(identifers[0], models[0])
            thread_predictor = tp.TextPredictor(identifers[1], models[1])
            predictors = (reply_predictor, thread_predictor)

        import libtieba as tieba

        pid = form.post_id.data
        info = tieba.get_post_info(pid)

        is_thread = info.IsThread()
        preidctor = predictors[is_thread]

        form.score, debug_info = preidctor.predict_debug(info.title, info.content)

        return render_template('index.html',form = form, info = info, debug_info = debug_info)
    elif form.title.data != None or form.content.data != None:
        info = libtieba.PostInfo()
        if form.title.data == None:
            info.title = ''
        elif form.content.data == None:
            info.content = '' 

        print info.title 
        print info.content

    return render_template('error.html', form = form)

if __name__ == '__main__':
	app.run(host='0.0.0.0', port=FLAGS.port, debug=FLAGS.debug)
