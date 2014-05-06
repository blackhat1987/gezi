import os 
import sys
import glob
from pyplusplus import module_builder

mb = module_builder.module_builder_t(
        gccxml_path='~/.jumbo/bin/gccxml',
        files=[
					'./include.python/PythonWrapper/Predictor.h',
					'./include.python/PythonWrapper/PredictorFactory.h',
					'./include.python/file_util.h',
					'./include.python/Numeric/collocation.h',
					'./include.python/conf_util.h',
					'./include.python/serialize_util.h',
					'./include.python/Numeric/Vector/Vector.h',
					'./include.python/Numeric/Vector/vector_util.h',
					'./include.python/feature/FeatureSelector.h',
					'./include.python/Identifer.h',
					'./include.python/Idf.h',
					'./include.python/log_util.h',
					'./include.python/Segmentor.h',
					'./include.python/ProgressBar.h',
					'./include.python/tieba/util.h',
					'./include.python/tools/content_process.h',
					'./include.python/string_util.h',
					'./include.python/reg_util.h',
					'./include.python/feature/FeatureVector.h',
					'./include.python/feature/features_util.h',
					'./include.python/feature/FeaturesExtractor.h',
					'./include.python/feature/FeaturesExtractorMgr.h',
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
				'/home/users/chenghuige/rsc/third-64/gflags/include',
				'/home/users/chenghuige/rsc/third-64/boost/include',
				'/home/users/chenghuige/rsc/public/configure/output/include',
				'/home/users/chenghuige/rsc/public/uconv/output/include',
				'/home/users/chenghuige/rsc/lib2-64/bsl/include/',
				'/home/users/chenghuige/rsc/com/btest/gtest/include/',
				'/home/users/chenghuige/rsc/app/search/sep/anti-spam/gezi/include.python/',
				'/home/users/chenghuige/rsc/app/search/sep/anti-spam/melt/include.python/'
         ]
        )

mb.build_code_creator( module_name='libgezi' )

mb.code_creator.user_defined_directories.append( os.path.abspath('..') )

mb.write_module( os.path.join( os.path.abspath('./python-wrapper/'), 'gezi_py.cc' )) 
