#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   forums.py
#        \author   chenghuige  
#          \date   2015-12-20 15:04:46.259375
#   \Description  
# ==============================================================================

from flask.ext.wtf import Form
from wtforms import TextField,PasswordField
from wtforms.validators import Required,Length
class LoginForm(Form):
	username= TextField('username',validators = [Required()])
	password = PasswordField('username',validators = [Required()])
