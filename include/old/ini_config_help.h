/** 
 *  ==============================================================================
 * 
 *          \file   config_help.h
 *
 *        \author   gezi  
 *          
 *          \date   2010-10-16 12:38:04.066790
 *  
 *  \Description:   �����������ļ�֧�� ini,jason,xml������boost property tree,��΢����һ����
 *                  ʹ��д��������Щ�������ļ� adrank/test_property_tree_jason.cc
 *                  ���ֱ����boost��ȡiniʾ��
 *                  int age = pt.get("age2", -28);
 *                  string name = pt.get("main.name", "abc");
 *                  ǰ����key,������Ĭ��value,key���Լ�fild��Ҳ����û�ж�Ӧ�����ļ�����û��
 *
 *                  ����ú�
 *                    ValGet(age, -28);  VAL�ṩ�㲻��Ҫ��filed����� ��û������[DataUpdate]
                      PropGet(age,"", -33); PropGet��Ҫ�ṩfiled�������û����""
 *                    PropGet(updateFile, "DataUpdate", "myfile");
 *
 *                  ini�����ļ���ע����boost.property��ȡ�Ļ���֧��ͬ��ע�ͣ���������һ��
 *                  ;����
 *                  name = chg
 *
 *  ==============================================================================
 */
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ini_parser.hpp>
#ifndef CONFIG_HELP_H_
#define CONFIG_HELP_H_
/**
 * ʹ��֮ǰ��Ҫ
 *
    using boost::property_tree::ptree;
    ptree pt;
 read_ini("config_file", pt);
 */

#define ValGet(s,default_value) s = pt.get(#s,default_value)

#define PropGet(s,field,default_value)\
if (field != "")\
        s = pt.get(std::string(field)+ std::string(".")+ std::string(#s), default_value);\
else\
    s = pt.get(#s, default_value)

#endif  //----end of CONFIG_HELP_H_
