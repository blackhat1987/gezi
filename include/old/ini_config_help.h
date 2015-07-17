/** 
 *  ==============================================================================
 * 
 *          \file   config_help.h
 *
 *        \author   gezi  
 *          
 *          \date   2010-10-16 12:38:04.066790
 *  
 *  \Description:   用来读配置文件支持 ini,jason,xml，利用boost property tree,稍微加了一个宏
 *                  使得写起来方便些。测试文件 adrank/test_property_tree_jason.cc
 *                  如果直接用boost读取ini示例
 *                  int age = pt.get("age2", -28);
 *                  string name = pt.get("main.name", "abc");
 *                  前面是key,后面是默认value,key可以加fild域也可以没有对应配置文件中有没有
 *
 *                  如果用宏
 *                    ValGet(age, -28);  VAL提供你不需要用filed的情况 即没有类似[DataUpdate]
                      PropGet(age,"", -33); PropGet需要提供filed名，如果没有是""
 *                    PropGet(updateFile, "DataUpdate", "myfile");
 *
 *                  ini配置文件的注释用boost.property读取的话不支持同行注释，必须另起一行
 *                  ;姓名
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
 * 使用之前需要
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
