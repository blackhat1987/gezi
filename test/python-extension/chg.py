import os
import sys
from pyplusplus import module_builder

mb = module_builder.module_builder_t(
         files=['chg.h'] 
       #,gccxml_path='/home/users/chenghuige/.jumbo/bin/gccxml')
       ,xml_generator_path='/usr/local/bin/castxml'
       ,cflags='-std=c++14')
       #)

mb.build_code_creator( module_name='libchg' ) 

mb.code_creator.user_defined_directories.append( os.path.abspath('.') )

mb.write_module( os.path.join( os.path.abspath('.'), 'chg_py.cc' ) ) 
