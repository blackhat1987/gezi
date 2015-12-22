import os 
import sys
import glob
from pyplusplus import module_builder

root = '/home/users/chenghuige/rsc/'
name = 'tieba'
#define_symbols = ['GCCXML','PYTHON_WRAPPER','NO_BAIDU_DEP']
define_symbols = ['GCCXML','PYTHON_WRAPPER']

files = [
					'include.python/common_util.h',  #for safe let it be first for without it file_util.h or string_util.h... will fail
          'include.python/tieba/urate/urate_features.h',
				]

paths = [
            #'./gezi.include.python/Numeric/Vector/',
            #'./include.python/MLCore/',
            #'./include.python/Prediction/Instances/',
        ]

#import gezi 
#for path in paths:
#    files += [f for f in gezi.get_filepaths(path) if f.endswith('.h')]

include_paths=[ 
				'third-64/glog',
				'third-64/gflags',
        'third-64/gtest',
				'third-64/boost.1.53',
        'lib2-64/bsl',
        'lib2-64/postag',
        'lib2-64/dict',
        'lib2-64/libcrf',
        'lib2-64/others-ex',
        'lib2-64/ullib',
        'lib2-64/ccode',
        'public/odict/output',
        'public/uconv/output',
        'public/configure/output',
        'st/nlp/lm-score',
				'app/search/sep/anti-spam/gezi/third/rabit',
	      ]

include_paths_python = [
				'app/search/sep/anti-spam/gezi/python-wrapper',
		       ]

include_paths_obsolute = [
          #'app/search/sep/anti-spam/melt/python-wrapper/gezi.include.python',
        	'lib2-64/wordseg', 
        	'public/comlog-plugin',
					'app/search/sep/anti-spam/gezi/third',
        ]

mb = module_builder.module_builder_t(
        gccxml_path = '~/.jumbo/bin/gccxml',
        define_symbols = define_symbols,
        files = files,
        include_paths = [root + f + '/include' for f in include_paths]
                        + [root + f + '/include.python' for f in include_paths_python]
                        + [root + f  for f in include_paths_obsolute]
        )

mb.build_code_creator( module_name='lib%s'%name )

mb.code_creator.user_defined_directories.append( os.path.abspath('.') )

mb.write_module( os.path.join( os.path.abspath('./'), '%s_py.cc'%name) ) 
