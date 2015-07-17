/** 
 *  ==============================================================================
 * 
 *          \file   config_help.h
 *
 *        \author   chenghuige
 *          
 *          \date   2011.4.2
 *  
 *                  get_val(conf, "age", 123); <=> age = conf["age"].to_int32();
 *                  GetVal(age, 123);
 *                  string Name; GetVal(Name, "");
 *                  string field = "abc"
 *                  GetFval(Name, field, "chg");
 *
 *  ==============================================================================
 */
#ifndef CONFIG_HELP_H_
#define CONFIG_HELP_H_

#include <string>
#include "Configure.h"

///string
inline std::string get_val(const comcfg::Configure& conf, const std::string& key, const std::string& default_val)
{
    std::string val;
    try
    {
        val = conf[key.c_str()].to_cstr();
    }
    catch (...)
    {
        val = default_val;
    }
    return val;
}
inline std::string get_val(const comcfg::Configure& conf, const std::string& field, const std::string& key, const std::string& default_val)
{
    std::string val;
    try
    {
        val = conf[field.c_str()][key.c_str()].to_cstr();
    }
    catch (...)
    {
        val = default_val;
    }
    return val;
}
///int
inline int get_val(const comcfg::Configure& conf, const std::string& key, int default_val)
{
    int val;
    try
    {
        val = conf[key.c_str()].to_int32();
    }
    catch (...)
    {
        val = default_val;
    }
    return val;
}
inline int get_val(const comcfg::Configure& conf, const std::string& field, const std::string& key, int default_val)
{
    int val;
    try
    {
        val = conf[field.c_str()][key.c_str()].to_int32();
    }
    catch (...)
    {
        val = default_val;
    }
    return val;
}

///int64
inline long long get_val(const comcfg::Configure& conf, const std::string& key, long long default_val)
{
    long long val;
    try
    {
        val = conf[key.c_str()].to_int64();
    }
    catch (...)
    {
        val = default_val;
    }
    return val;
}
inline long long get_val(const comcfg::Configure& conf, const std::string& field, std::string& key, long long default_val)
{
    long long val;
    try
    {
        val = conf[field.c_str()][key.c_str()].to_int64();
    }
    catch (...)
    {
        val = default_val;
    }
    return val;
}

///double
inline double get_val(const comcfg::Configure& conf, const std::string& key, double default_val)
{
    double val;
    try
    {
        val = conf[key.c_str()].to_double();
    }
    catch (...)
    {
        val = default_val;
    }
    return val;
}
//key not const, default_val const double will cause always 重载double  WHY?
inline double get_val(const comcfg::Configure& conf, const std::string& field, const std::string& key, double default_val)
{
    double val;
    try
    {
        val = conf[field.c_str()][key.c_str()].to_double();
        //        cout << "ok val: " << val << endl;
    }
    catch (...)
    {
        //        cout << "default val of double" << endl;
        val = default_val;
    }
    return val;
}

#define VAL_GET(s,default_value)\
    s = get_val(conf, #s,default_value)

#define PROP_GET(s,field,default_value)\
    s = get_val(conf, field, #s, default_value);


#define VAL_GET2(root, s,default_value)\
    root.s = get_val(conf, #s,default_value)
//使用者确保field不空，否则调用VAL_GET
#define PROP_GET2(root, s,field,default_value)\
    root.s = get_val(conf, field, #s, default_value)

#define VAL_STRCPY(root, s,default_value)\
    std::string VAL_STRCPY_##s##result = get_val(conf, #s,default_value);\
    strncpy(root, VAL_STRCPY_##s##result.c_str(), VAL_STRCPY_##s##result.length());\
    root[ VAL_STRCPY_##s##result.length()] = '\0'

#define PROP_STRCPY(root, s,field,default_value)\
    std::string PROP_STRCPY_##s##result;\
    PROP_STRCPY_##s##result = get_val(conf, field,#s, default_value);\
    strncpy(root , PROP_STRCPY_##s##result.c_str(), PROP_STRCPY_##s##result.length());\
    root[PROP_STRCPY_##s##result.length()] = '\0'

inline void get_val(const comcfg::Configure& conf, char* dest,
        const std::string& key, const std::string& default_val)
{
    std::string tmp = get_val(conf, key, default_val);
    strncpy(dest, tmp.c_str(), tmp.length());
    dest[tmp.length()] = '\0';
}
inline void get_val(const comcfg::Configure& conf, char* dest,
        const std::string& field, const std::string& key, const std::string& default_val)
{
    std::string tmp = get_val(conf, field, key, default_val);
    strncpy(dest, tmp.c_str(), tmp.length());
    dest[tmp.length()] = '\0';
}

#endif  //----end of CONFIG_HELP_H_
