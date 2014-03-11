import os
import sys
from pyplusplus import module_builder

mb = module_builder.module_builder_t(
        gccxml_path='~/.jumbo/bin/gccxml',
        files=['./include/word_seg.h',
					'./include/log_util.h',
					'./include/Matrix.h',
					'./include/numeric/collocation.h',
					'./include/feature/FeatureSelector.h',
					'./include/tools/content_process.h',
					'./include/string_util.h',
					'./include/reg_util.h',
					#'./include/debug_util.h',
					#'./include/conf_util.h',
					#'./include/convert_type.h',
					#'./include/common_def.h',
					'./include/ProgressBar.h',
					#'./include/tieba/uname_util.h',
					'./include/tieba/util.h',
					'./include/encoding_convert.h',
					'./include/Identifer.h',
					'./include/Idf.h',
					#'./include/file_util.h'
					],
        include_paths=[ '/home/users/chenghuige/rsc/lib2-64/wordseg', 
        '/home/users/chenghuige/rsc/lib2-64/postag/include',
        '/home/users/chenghuige/rsc/lib2-64/dict/include',
        '/home/users/chenghuige/rsc/lib2-64/libcrf/include',
        '/home/users/chenghuige/rsc/lib2-64/others-ex/include',
        '/home/users/chenghuige/rsc/lib2-64/ullib/include',
        '/home/users/chenghuige/rsc/public/comlog-plugin',
				'/home/users/chenghuige/rsc/lib2-64/ccode/include',
				'/home/users/chenghuige/rsc/public/odict/output/include',
				'/home/users/chenghuige/rsc/third-64/glog/include',
				'/home/users/chenghuige/rsc/third-64/glog/include/glog',
				'/home/users/chenghuige/rsc/app/search/sep/anti-spam/gezi/include',
				'/home/users/chenghuige/rsc/third-64/gflags/include',
				'/home/users/chenghuige/rsc/third-64/boost/include',
				'/home/users/chenghuige/rsc/public/configure/output/include',
				'/home/users/chenghuige/rsc/public/uconv/output/include',
				'/home/users/chenghuige/rsc/lib2-64/bsl/include/',
				'/home/users/chenghuige/rsc/com/btest/gtest/include/',
				'/home/users/chenghuige/rsc/app/search/sep/anti-spam/gezi/include/'
         ]
        )

mb.build_code_creator( module_name='libgezi' )

mb.code_creator.user_defined_directories.append( os.path.abspath('..') )

mb.write_module( os.path.join( os.path.abspath('./python-wrapper/'), 'gezi_py.cc' )) 
