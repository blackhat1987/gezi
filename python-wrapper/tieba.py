import os 
import sys
import glob
from pyplusplus import module_builder

mb = module_builder.module_builder_t(
        gccxml_path='~/.jumbo/bin/gccxml',
        files=[
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
				#'/home/users/chenghuige/rsc/third-64/boost/include',
				'/home/users/chenghuige/rsc/third-64/boost.1.53//include',
				'/home/users/chenghuige/rsc/public/configure/output/include',
				'/home/users/chenghuige/rsc/public/uconv/output/include',
				'/home/users/chenghuige/rsc/lib2-64/bsl/include/',
				'/home/users/chenghuige/rsc/com/btest/gtest/include/',
				'/home/users/chenghuige/rsc/app/search/sep/anti-spam/gezi/include.python/',
				'/home/users/chenghuige/rsc/app/search/sep/anti-spam/melt/include.python/'
         ]
        )

mb.build_code_creator( module_name='libtieba' )

mb.code_creator.user_defined_directories.append( os.path.abspath('..') )

mb.write_module( os.path.join( os.path.abspath('./python-wrapper/'), 'tieba_py.cc' )) 
