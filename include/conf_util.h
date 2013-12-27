/** 
 *  ==============================================================================
 * 
 *          \file   conf_util.h
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
#ifndef CONF_UTIL_H_
#define CONF_UTIL_H_

#include <string>
#include "Configure.h"
#include "log_util.h"
#include "debug_util.h" //common util �����Ѿ���debug util�ˡ��� Ϊɶ����Ҫ TODO FIXME
#include "common_util.h"

namespace gezi
{
using std::string;
using comcfg::Configure;
#define DECLARE_SHAREDCONF\
  comcfg::Configure SharedConf::_conf

class SharedConf
{
public:

  static comcfg::Configure& get_conf()
  {
    return _conf;
  }

  static comcfg::Configure& conf()
  {
    return _conf;
  }

  static comcfg::Configure* instance()
  {
    return &_conf;
  }

  static bool init(const string& path = "./conf", const string& config_file = "strategy.conf")
  {
    int ret = _conf.load(path.c_str(), config_file.c_str());
    if (ret != 0)
    {
      LOG_TRACE("SharedConf init with %s/%s fail", path.c_str(), config_file.c_str());
    }
    else
    {
      LOG_TRACE("SharedConf init ok %s/%s", path.c_str(), config_file.c_str());
    }
    return ret == 0;
  }
private:
  static comcfg::Configure _conf; //comcfg::Configure SharedConf::conf_; need this on one of your cpp
};

inline std::string conf_trim(const std::string& input)
{
  //string input = boost::to_lower_copy(input_);
  if (input.size() > 1)
  {
    if (input[input.size() - 1] == '_')
    {
      return input.substr(0, input.size() - 1);
    }
    else if (input[0] == '_')
    {
      return input.substr(1);
    }
  }
  return input;
}
//string

inline void set_val(const comcfg::Configure& conf, const std::string& key, std::string& val)
{
  try
  {
    val = conf[key.c_str()].to_cstr();
    LOG_TRACE("Get config %s : %s", key.c_str(), val.c_str());
  }
  catch (...)
  {
    LOG_TRACE("Using default %s : %s", key.c_str(), val.c_str());
  }
}

inline void set_val(const comcfg::Configure& conf, const std::string& field, const std::string& key, std::string& val)
{
  if (field.empty())
  {
    set_val(conf, key, val);
    return;
  }

  try
  {
    val = conf[field.c_str()][key.c_str()].to_cstr();
    LOG_TRACE("Get config %s::%s : %s", field.c_str(), key.c_str(), val.c_str());
  }
  catch (...)
  {
    LOG_TRACE("Using default %s::%s : %s", field.c_str(), key.c_str(), val.c_str());
    set_val(conf, key, val);
  }
}

inline std::string get_val(const comcfg::Configure& conf, const std::string& key, const std::string& default_val)
{
  std::string val;
  try
  {
    val = conf[key.c_str()].to_cstr();
    LOG_TRACE("Get config %s : %s", key.c_str(), val.c_str());
  }
  catch (...)
  {
    val = default_val;
    LOG_TRACE("Using default %s : %s", key.c_str(), val.c_str());
  }
  return val;
}

inline std::string get_val(const comcfg::Configure& conf, const std::string& field, const std::string& key, const std::string& default_val)
{
  std::string val;
  if (field.empty())
  {
    return get_val(conf, key, val);
  }
  try
  {
    val = conf[field.c_str()][key.c_str()].to_cstr();
    LOG_TRACE("Get config %s::%s : %s", field.c_str(), key.c_str(), val.c_str());
  }
  catch (...)
  {
    val = default_val;
    LOG_TRACE("Using default %s::%s : %s", field.c_str(), key.c_str(), val.c_str());
    set_val(conf, key, val);
  }
  return val;
}
///int

inline void set_val(const comcfg::Configure& conf, const std::string& key, int& val)
{
  try
  {
    val = conf[key.c_str()].to_int32();
    LOG_TRACE("Get config %s : %d", key.c_str(), val);
  }
  catch (...)
  {
    LOG_TRACE("Using default %s : %d", key.c_str(), val);
  }
}

inline void set_val(const comcfg::Configure& conf, const std::string& field, const std::string& key, int& val)
{
  if (field.empty())
  {
    set_val(conf, key, val);
    return;
  }
  try
  {
    val = conf[field.c_str()][key.c_str()].to_int32();
    LOG_TRACE("Get config %s::%s : %d", field.c_str(), key.c_str(), val);
  }
  catch (...)
  {
    LOG_TRACE("Using default %s::%s : %d", field.c_str(), key.c_str(), val);
    set_val(conf, key, val);
  }
}

inline int get_val(const comcfg::Configure& conf, const std::string& key, int default_val)
{
  int val;
  try
  {
    val = conf[key.c_str()].to_int32();
    LOG_TRACE("Get config %s : %d", key.c_str(), val);
  }
  catch (...)
  {
    val = default_val;
    LOG_TRACE("Using default %s : %d", key.c_str(), val);
  }
  return val;
}

inline int get_val(const comcfg::Configure& conf, const std::string& field, const std::string& key, int default_val)
{
  int val;
  if (field.empty())
  {
    return get_val(conf, key, val);
  }
  try
  {
    val = conf[field.c_str()][key.c_str()].to_int32();
    LOG_TRACE("Get config %s::%s : %d", field.c_str(), key.c_str(), val);
  }
  catch (...)
  {
    val = default_val;
    LOG_TRACE("Using default %s::%s : %d", field.c_str(), key.c_str(), val);
    set_val(conf, key, val);
  }
  return val;
}

//bool

inline void set_val(const comcfg::Configure& conf, const std::string& key, bool& val)
{
  try
  {
    val = conf[key.c_str()].to_int32();
    LOG_TRACE("Get config %s : %d", key.c_str(), val);
  }
  catch (...)
  {
    LOG_TRACE("Using default %s : %d", key.c_str(), val);
  }
}

inline void set_val(const comcfg::Configure& conf, const std::string& field, const std::string& key, bool& val)
{
  if (field.empty())
  {
    set_val(conf, key, val);
    return;
  }
  try
  {
    val = conf[field.c_str()][key.c_str()].to_int32();
    LOG_TRACE("Get config %s::%s : %d", field.c_str(), key.c_str(), val);
  }
  catch (...)
  {
    LOG_TRACE("Using default %s::%s : %d", field.c_str(), key.c_str(), val);
    set_val(conf, key, val);
  }
}

inline bool get_val(const comcfg::Configure& conf, const std::string& key, bool default_val)
{
  int val;
  try
  {
    val = conf[key.c_str()].to_int32();
    LOG_TRACE("Get config %s : %d", key.c_str(), val);
  }
  catch (...)
  {
    val = default_val;
    LOG_TRACE("Using default %s : %d", key.c_str(), val);
  }
  return (bool)val;
}

inline bool get_val(const comcfg::Configure& conf, const std::string& field, const std::string& key, bool default_val)
{
  int val;
  if (field.empty())
  {
    return get_val(conf, key, val);
  }
  try
  {
    val = conf[field.c_str()][key.c_str()].to_int32();
    LOG_TRACE("Get config %s::%s : %d", field.c_str(), key.c_str(), val);
  }
  catch (...)
  {
    val = default_val;
    LOG_TRACE("Using default %s::%s : %d", field.c_str(), key.c_str(), val);
    set_val(conf, key, val);
  }
  return (bool)val;
}

///int64

inline void set_val(const comcfg::Configure& conf, const std::string& key, long long& val)
{
  try
  {
    val = conf[key.c_str()].to_int64();
    LOG_TRACE("Get config %s : %lld", key.c_str(), val);
  }
  catch (...)
  {
    LOG_TRACE("Using default %s : %lld", key.c_str(), val);
  }
}

inline void set_val(const comcfg::Configure& conf, const std::string& field, std::string& key, long long& val)
{
  if (field.empty())
  {
    set_val(conf, key, val);
    return;
  }
  try
  {
    val = conf[field.c_str()][key.c_str()].to_int64();
    LOG_TRACE("Using default %s::%s : %lld", field.c_str(), key.c_str(), val);
  }
  catch (...)
  {
    LOG_TRACE("Using default %s::%s : %lld", field.c_str(), key.c_str(), val);
    set_val(conf, key, val);
  }
}

inline long long get_val(const comcfg::Configure& conf, const std::string& key, long long default_val)
{
  long long val;
  try
  {
    val = conf[key.c_str()].to_int64();
    LOG_TRACE("Get config %s : %lld", key.c_str(), val);
  }
  catch (...)
  {
    val = default_val;
    LOG_TRACE("Using default %s : %lld", key.c_str(), val);
  }
  return val;
}

inline long long get_val(const comcfg::Configure& conf, const std::string& field, std::string& key, long long default_val)
{
  long long val;
  if (field.empty())
  {
    return get_val(conf, key, val);
  }
  try
  {
    val = conf[field.c_str()][key.c_str()].to_int64();
    LOG_TRACE("Using default %s::%s : %lld", field.c_str(), key.c_str(), val);
  }
  catch (...)
  {
    val = default_val;
    LOG_TRACE("Using default %s::%s : %lld", field.c_str(), key.c_str(), val);
    set_val(conf, key, val);
  }
  return val;
}

///double

inline void set_val(const comcfg::Configure& conf, const std::string& key, double& val)
{
  try
  {
    val = conf[key.c_str()].to_double();
    LOG_TRACE("Get config %s : %f", key.c_str(), val);
  }
  catch (...)
  {
    LOG_TRACE("Using default %s : %f", key.c_str(), val);
  }
}
//key not const, default_val const double will cause always ????double  WHY?

inline void set_val(const comcfg::Configure& conf, const std::string& field, const std::string& key, double& val)
{
  if (field.empty())
  {
    set_val(conf, key, val);
    return;
  }
  try
  {
    val = conf[field.c_str()][key.c_str()].to_double();
    LOG_TRACE("Using default %s::%s : %f", field.c_str(), key.c_str(), val);
  }
  catch (...)
  {
    LOG_TRACE("Using default %s::%s : %f", field.c_str(), key.c_str(), val);
    set_val(conf, key, val);
  }
}

inline double get_val(const comcfg::Configure& conf, const std::string& key, double default_val)
{
  double val;
  try
  {
    val = conf[key.c_str()].to_double();
    LOG_TRACE("Get config %s : %f", key.c_str(), val);
  }
  catch (...)
  {
    val = default_val;
    LOG_TRACE("Using default %s : %f", key.c_str(), val);
  }
  return val;
}
//key not const, default_val const double will cause always ????double  WHY?

inline double get_val(const comcfg::Configure& conf, const std::string& field, const std::string& key, double default_val)
{
  double val;
  if (field.empty())
  {
    return get_val(conf, key, val);
  }
  try
  {
    val = conf[field.c_str()][key.c_str()].to_double();
    LOG_TRACE("Using default %s::%s : %f", field.c_str(), key.c_str(), val);
  }
  catch (...)
  {
    val = default_val;
    LOG_TRACE("Using default %s::%s : %f", field.c_str(), key.c_str(), val);
    set_val(conf, key, val);
  }
  return val;
}

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

}

#define SCONF(s)\
  gezi::set_val(gezi::SharedConf::conf(), section, gezi::conf_trim(#s), s)
#define SCONF_CLASS(root,s)\
  gezi::set_val(gezi::SharedConf::conf(), section, gezi::conf_trim(#s), root.s)

#define SCONF2(s,default_value)\
  s = gezi::get_val(gezi::SharedConf::conf(), section, gezi::conf_trim(#s), default_value)
#define SCONF2_CLASS(root,s,default_value)\
  s = gezi::get_val(gezi::SharedConf::conf(), section, gezi::conf_trim(#s), default_value)

#define PSCONF(s, field)\
  gezi::set_val(gezi::SharedConf::conf(), field, gezi::conf_trim(#s), s)

#define PSCONF2(s,field, default_value)\
  s = gezi::get_val(gezi::SharedConf::conf(), field, gezi::conf_trim(#s), default_value)

#define CONF(s)\
  gezi::set_val(conf, section, gezi::conf_trim(#s), s)
#define CONF_CLASS(root,s)\
  gezi::set_val(conf, section, gezi::conf_trim(#s), root.s)

#define CONF2(s,default_value)\
  s = gezi::get_val(conf, section, gezi::conf_trim(#s), default_value)
#define CONF2_CLASS(root,s,default_value)\
  s = gezi::get_val(conf, section, gezi::conf_trim(#s), default_value)

#define CONF_SIMPLE(s)\
  gezi::set_val(conf, section, gezi::conf_trim(#s), s)
#define CONF_SIMPLE_MEMBER(root,s)\
  gezi::set_val(conf, section, gezi::conf_trim(#s), root.s)

#define CONF_SIMPLE_GET(s,default_value)\
  s = gezi::get_val(conf, section, gezi::conf_trim(#s), default_value)
#define CONF_SIMPLE_GET_MEMBER(root,s,default_value))\
  s = gezi::get_val(conf, section, gezi::conf_trim(#s), default_value)


#define CONF_TRY_VAL(s)\
    gezi::set_val(conf, gezi::conf_trim(#s),s)
#define CONF_TRY_PROP(s,field)\
    gezi::set_val(conf, field, gezi::conf_trim(#s), s)

#define CONF_TRY_MEMBER_VAL(root, s)\
    gezi::set_val(conf, gezi::conf_trim(#s),root.s)
#define CONF_TRY_MEMBER_PROP(root, s,field)\
    gezi::set_val(conf, field, gezi::conf_trim(#s), root.s)

#define CONF_GET_VAL(s,default_value)\
    s = gezi::get_val(conf, gezi::conf_trim(#s),default_value)

#define CONF_GET_PROP(s,field,default_value)\
    s = gezi::get_val(conf, field, gezi::conf_trim(#s), default_value)


#define CONF_GET_MEMBER_VAL(root, s,default_value)\
    root.s = gezi::get_val(conf, gezi::conf_trim(#s),default_value)
#define CONF_GET_MEMBER_PROP(root, s,field,default_value)\
    root.s = gezi::get_val(conf, field, gezi::conf_trim(#s), default_value)

#define CONF_STRCPY_VAL(root, s,default_value)\
    std::string VAL_STRCPY_##s##result = gezi::get_val(conf, gezi::conf_trim(#s),default_value);\
    strncpy(root, VAL_STRCPY_##s##result.c_str(), VAL_STRCPY_##s##result.length());\
    root[ VAL_STRCPY_##s##result.length()] = '\0'

#define CONF_STRCPY_PROP(root, s,field,default_value)\
    std::string PROP_STRCPY_##s##result;\
    PROP_STRCPY_##s##result = gezi::get_val(conf, field,gezi::conf_trim(#s), default_value);\
    strncpy(root , PROP_STRCPY_##s##result.c_str(), PROP_STRCPY_##s##result.length());\
    root[PROP_STRCPY_##s##result.length()] = '\0'
#endif  //----end of CONF_UTIL_H_