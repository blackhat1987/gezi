import os 
import sys
import glob
from pyplusplus import module_builder

mb = module_builder.module_builder_t(
        gccxml_path='~/.jumbo/bin/gccxml',
				define_symbols=['GCCXML','PYTHON_WRAPPER'],
        files=[
					'include.python/common_util.h',  #for safe let it be first for without it file_util.h or string_util.h... will fail
					'./include.python/Numeric/Vector/Vector.h',
					'./include.python/feature/FeatureVector.h',
					#------------below has been tested ok
					#feature related
					'./include.python/feature/features_util.h',
					'./include.python/feature/FeaturesExtractor.h',
					'./include.python/feature/FeaturesExtractorMgr.h',
					#-------------predictor 
					#'./include.python/PythonWrapper/TextPredictor.h',
					'./include.python/PythonWrapper/Predictor.h',
					'./include.python/PythonWrapper/PredictorFactory.h',
					#-------------ip util
					'./include.python/tools/IpFinder.h',
					'./include.python/tools/ip.h',
					'./include.python/tools/uname_util.h',
					#-------------redis util
          './include.python/tools/redis/RedisClient.h',
					#-------------feature selector and idf 
					'./include.python/feature/FeatureSelector.h',
					'./include.python/Idf.h',
					'./include.python/Numeric/collocation.h',
					#-------------segmentor 
					'./include.python/Segmentor.h',
					#-------------common utils
					'./include.python/ProgressBar.h',
					'./include.python/Identifer.h',
          './include.python/SharedIdentifers.h',
          './include.python/SharedObjects.h',
					'./include.python/conf_util.h',
					'./include.python/serialize_util.h',
					'./include.python/log_util.h',
					'./include.python/tools/content_process.h',
					'./include.python/string_util.h',
					'./include.python/reg_util.h',
					'./include.python/file_util.h',
					'./include.python/encoding_convert.h',
					#-------------tieba utils 
					'./include.python/tieba/tieba_util.h',
					'./include.python/tieba/get_info.h',
          './include.python/tieba/get_parsed_info.h',
          './include.python/tieba/info/delete_info.h',
          './include.python/tieba/info/forum_info.h',
          './include.python/tieba/info/post_info.h',
          './include.python/tieba/info/thread_info.h',
          './include.python/tieba/info/url_info.h',
          './include.python/tieba/info/user_info.h',
          './include.python/tieba/info/user_posts_info.h',
          './include.python/tieba/info_def.h',
          './include.python/tieba/uname_util.h',
          './include.python/tieba/common_def.h',
          './include.python/tieba/urate/get_urate_info.h',
          './include.python/tieba/urate/urate_info.h'
					],
        include_paths=[ 
					'/home/users/chenghuige/rsc/app/search/ksarch/store/proxy-lib/redis/output/include', 
        	'/home/users/chenghuige/rsc/public/mcpack/include/',
        	'/home/users/chenghuige/rsc/public/ub/include/',
        	'/home/users/chenghuige/rsc/public/nshead/output/include',
        	'/home/users/chenghuige/rsc/public/connectpool/output/',
        	'/home/users/chenghuige/rsc/lib2-64/wordseg', 
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
					'/home/users/chenghuige/rsc/third-64/boost.1.53/include',
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
