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

app = Flask(__name__)
app.secret_key = 's3cr3t'

@app.route('/')
def index():
	return 'this is root index'

@app.route('/hello/')
@app.route('/hello/<name>')
def hello(name=None):
    return render_template('hello.html', name=name)

@app.route('/user/<username>')
def show_user_profile(username):
    # show the user profile for that user
    return 'User %s' % username

@app.route('/post/<int:post_id>')
def show_post(post_id):
    # show the post with the given id, the id is an integer
    return 'Post %d' % post_id

from flask.ext.wtf import Form
from wtforms import TextField,PasswordField
from wtforms.validators import Required,Length
class LoginForm(Form):
    username= TextField('username',validators = [Required()])
    password = PasswordField('username',validators = [Required()])
    

def validate_on_submit(form):
	if form.username.data == None or form.username.data == '' or form.password.data == None or form.password.data == '':
		return False
	return True

@app.route('/login',methods = ['GET' , 'POST'])
def login():
    form = LoginForm()
    #if form.validate_on_submit():
    if validate_on_submit(form):
    		print('username:' + form.username.data + ',password:' + form.password.data)
    		return render_template('index.html',form = form)
    print 'valid not ok'
    return render_template('login.html', form = form)


if __name__ == '__main__':
	app.run(host='0.0.0.0', port=8003, debug=True)
