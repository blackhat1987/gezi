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

#ifndef __GNUC__ 
#define NO_BAIDU_DEP
#endif //--- __GNUC__

#ifndef NO_BAIDU_DEP
#include "Configure.h"
#endif
#include "log_util.h"
#include "debug_util.h" 
#include "string_util.h"
//#include "common_util.h" 
#include "Exception.h"
#include "string_util.h"
#ifndef NO_BAIDU_DEP
#include "convert_type.h"
#endif
namespace gezi
{
	inline int parse_int_param(string name, string line)
	{
		if (!startswith(line, name))
		{
			THROW(line + "-- not start with " + name);
		}
		return INT(line.substr(name.size()));
	}

	inline string parse_string_param(string name, string line)
	{
		if (!startswith(line, name))
		{
			THROW(line + "-- not start with " + name);
		}
		return line.substr(name.size());
	}

	inline double parse_double_param(string name, string line)
	{
		if (!startswith(line, name))
		{
			THROW(line + "-- not start with " + name);
		}
		return DOUBLE(line.substr(name.size()));
	}

	inline bool parse_bool_param(string name, string line)
	{
		if (!startswith(line, name))
		{
			THROW(line + "-- not start with " + name);
		}
		return BOOL(line.substr(name.size()));
	}
#ifndef NO_BAIDU_DEP
	using comcfg::Configure;

	class SharedConf
	{
	public:

		static comcfg::Configure& get_conf()
		{
			return conf();
		}

		static comcfg::Configure& conf()
		{
			static comcfg::Configure _conf;
			return _conf;
		}

		static comcfg::Configure* instance()
		{
			return &conf();
		}

		static bool init(string config_file = "strategy.conf", string dir = "./conf")
		{
			int ret = conf().load(dir.c_str(), config_file.c_str());
			if (ret != 0)
			{
				//LOG_TRACE("SharedConf init with %s/%s fail", dir.c_str(), config_file.c_str());
			}
			else
			{
				//LOG_TRACE("SharedConf init ok %s/%s", dir.c_str(), config_file.c_str());
			}
			return ret == 0;
		}

	};

	inline void set_val(const comcfg::Configure& conf, string key, string& val)
	{
		char buf[1024];
		int ret = conf[key.c_str()].get_cstr(buf, 1024, "");

		if (ret == 0)
		{
			val = buf;
			//LOG_TRACE("Get config %s : %s", key.c_str(), val.c_str());
		}
		else
		{
			//LOG_TRACE("Using default %s : %s", key.c_str(), val.c_str());
		}
	}

	inline void set_val(const comcfg::Configure& conf, string field, string key, string& val)
	{
		if (field.empty())
		{
			set_val(conf, key, val);
			return;
		}

		char buf[1024];
		int ret = conf[field.c_str()][key.c_str()].get_cstr(buf, 1024, "");

		if (ret == 0)
		{
			val = buf;
			//LOG_TRACE("Get config %s::%s : %s", field.c_str(), key.c_str(), val.c_str());
		}
		else
		{
			//LOG_TRACE("Using default %s::%s : %s", field.c_str(), key.c_str(), val.c_str());
			set_val(conf, key, val);
		}
	}

	inline string get_val(const comcfg::Configure& conf, string key, string default_val)
	{
		string val;
		char buf[1024];
		int ret = conf[key.c_str()].get_cstr(buf, 1024, "");
		if (ret == 0)
		{
			//LOG_TRACE("Get config %s : %s", key.c_str(), val.c_str());
		}
		else
		{
			val = default_val;
			//LOG_TRACE("Using default %s : %s", key.c_str(), val.c_str());
		}
		return val;
	}

	inline string get_val(const comcfg::Configure& conf, string field, string key, string default_val)
	{
		string val;
		if (field.empty())
		{
			return get_val(conf, key, default_val);
		}
		char buf[1024];
		int ret = conf[field.c_str()][key.c_str()].get_cstr(buf, 1024, "");
		if (ret == 0)
		{
			//LOG_TRACE("Get config %s::%s : %s", field.c_str(), key.c_str(), val.c_str());
		}
		else
		{
			val = default_val;
			//LOG_TRACE("Using default %s::%s : %s", field.c_str(), key.c_str(), val.c_str());
			set_val(conf, key, val);
		}
		return val;
	}
	///int

	inline void set_val(const comcfg::Configure& conf, string key, int& val)
	{
		int ori_val = val;
		int ret = conf[key.c_str()].get_int32(&val, ori_val);
		if (ret == 0)
		{
			//LOG_TRACE("Get config %s : %d", key.c_str(), val);
		}
		else
		{
			//LOG_TRACE("Using default %s : %d", key.c_str(), val);
		}
	}

	inline void set_val(const comcfg::Configure& conf, string field, string key, int& val)
	{
		if (field.empty())
		{
			set_val(conf, key, val);
			return;
		}
		int ori_val = val;
		int ret = conf[field.c_str()][key.c_str()].get_int32(&val, ori_val);
		if (ret == 0)
		{
			//LOG_TRACE("Get config %s::%s : %d", field.c_str(), key.c_str(), val);
		}
		else
		{
			//LOG_TRACE("Using default %s::%s : %d", field.c_str(), key.c_str(), val);
			set_val(conf, key, val);
		}
	}

	inline int get_val(const comcfg::Configure& conf, string key, int default_val)
	{
		int val;
		int ret = conf[key.c_str()].get_int32(&val, default_val);
		if (ret == 0)
		{
			//LOG_TRACE("Get config %s : %d", key.c_str(), val);
		}
		else
		{
			//LOG_TRACE("Using default %s : %d", key.c_str(), val);
		}
		return val;
	}

	inline int get_val(const comcfg::Configure& conf, string field, string key, int default_val)
	{
		int val;
		if (field.empty())
		{
			return get_val(conf, key, default_val);
		}
		int ret = conf[field.c_str()][key.c_str()].get_int32(&val, default_val);
		if (ret == 0)
		{
			//LOG_TRACE("Get config %s::%s : %d", field.c_str(), key.c_str(), val);
		}
		else
		{
			//LOG_TRACE("Using default %s::%s : %d", field.c_str(), key.c_str(), val);
			set_val(conf, key, val);
		}
		return val;
	}

	//bool

	inline void set_val(const comcfg::Configure& conf, string key, bool& val)
	{
		int val_;
		int ret = conf[key.c_str()].get_int32(&val_);
		if (ret == 0)
		{
			val = val_;
			//LOG_TRACE("Get config %s : %d", key.c_str(), val);
		}
		else
		{
			//LOG_TRACE("Using default %s : %d", key.c_str(), val);
		}
	}

	inline void set_val(const comcfg::Configure& conf, string field, string key, bool& val)
	{
		if (field.empty())
		{
			set_val(conf, key, val);
			return;
		}
		int val_;
		int ret = conf[field.c_str()][key.c_str()].get_int32(&val_);
		if (ret == 0)
		{
			val = val_;
			//LOG_TRACE("Get config %s::%s : %d", field.c_str(), key.c_str(), val);
		}
		else
		{
			//LOG_TRACE("Using default %s::%s : %d", field.c_str(), key.c_str(), val);
			set_val(conf, key, val);
		}
	}

	//inline bool get_val(const comcfg::Configure& conf, string key, bool default_val)
	//{
	//  int val;
	//  try
	//  {
	//    val = conf[key.c_str()].to_int32();
	//    //LOG_TRACE("Get config %s : %d", key.c_str(), val);
	//  }
	//  catch (...)
	//  {
	//    val = default_val;
	//    //LOG_TRACE("Using default %s : %d", key.c_str(), val);
	//  }
	//  return (bool)val;
	//}
	//
	//inline bool get_val(const comcfg::Configure& conf, string field, string key, bool default_val)
	//{
	//  int val;
	//  if (field.empty())
	//  {
	//    return get_val(conf, key, val);
	//  }
	//  try
	//  {
	//    val = conf[field.c_str()][key.c_str()].to_int32();
	//    //LOG_TRACE("Get config %s::%s : %d", field.c_str(), key.c_str(), val);
	//  }
	//  catch (...)
	//  {
	//    val = default_val;
	//    //LOG_TRACE("Using default %s::%s : %d", field.c_str(), key.c_str(), val);
	//    set_val(conf, key, val);
	//  }
	//  return (bool)val;
	//}

	///int64

	inline void set_val(const comcfg::Configure& conf, string key, long long& val)
	{
		long long ori_val = val;
		int ret = conf[key.c_str()].get_int64(&val, ori_val);
		if (ret == 0)
		{
			//LOG_TRACE("Get config %s : %lld", key.c_str(), val);
		}
		else
		{
			//LOG_TRACE("Using default %s : %lld", key.c_str(), val);
		}
	}

	inline void set_val(const comcfg::Configure& conf, string field, string& key, long long& val)
	{
		if (field.empty())
		{
			set_val(conf, key, val);
			return;
		}
		long long ori_val = val;
		int ret = conf[field.c_str()][key.c_str()].get_int64(&val, ori_val);
		if (ret == 0)
		{
			//LOG_TRACE("Using default %s::%s : %lld", field.c_str(), key.c_str(), val);
		}
		else
		{
			//LOG_TRACE("Using default %s::%s : %lld", field.c_str(), key.c_str(), val);
			set_val(conf, key, val);
		}
	}

	inline long long get_val(const comcfg::Configure& conf, string key, long long default_val)
	{
		long long val;
		int ret = conf[key.c_str()].get_int64(&val, default_val);
		if (ret == 0)
		{
			//LOG_TRACE("Get config %s : %lld", key.c_str(), val);
		}
		else
		{
			//LOG_TRACE("Using default %s : %lld", key.c_str(), val);
		}
		return val;
	}

	inline long long get_val(const comcfg::Configure& conf, string field, string& key, long long default_val)
	{
		long long val;
		if (field.empty())
		{
			return get_val(conf, key, default_val);
		}
		int ret = conf[field.c_str()][key.c_str()].get_int64(&val, default_val);
		if (ret == 0)
		{
			//LOG_TRACE("Using default %s::%s : %lld", field.c_str(), key.c_str(), val);
		}
		else
		{
			//LOG_TRACE("Using default %s::%s : %lld", field.c_str(), key.c_str(), val);
			set_val(conf, key, val);
		}
		return val;
	}

	///double

	inline void set_val(const comcfg::Configure& conf, string key, double& val)
	{
		double ori_val = val;
		int ret = conf[key.c_str()].get_double(&val, ori_val);
		if (ret == 0)
		{
			//LOG_TRACE("Get config %s : %f", key.c_str(), val);
		}
		else
		{
			//LOG_TRACE("Using default %s : %f", key.c_str(), val);
		}
	}
	//key not const, default_val const double will cause always ????double  WHY?

	inline void set_val(const comcfg::Configure& conf, string field, string key, double& val)
	{
		if (field.empty())
		{
			set_val(conf, key, val);
			return;
		}
		double ori_val = val; //理论上不需要先保存public/configure下面这个接口不符合预期val不应该被改变如果出现异常
		//int ret = conf[field.c_str()][key.c_str()].get_double(&val, val);
		int ret = conf[field.c_str()][key.c_str()].get_double(&val, ori_val);
		if (ret == 0)
		{
			//LOG_TRACE("Using default %s::%s : %f", field.c_str(), key.c_str(), val);
		}
		else
		{
			/*Pval2(ori_val, val);
			conf[field.c_str()][key.c_str()].get_double(&val, 3.1415926);
			Pval2(ori_val, val);*/
			//LOG_TRACE("Using default %s::%s : %f", field.c_str(), key.c_str(), val);
			set_val(conf, key, val);
		}
	}

	inline double get_val(const comcfg::Configure& conf, string key, double default_val)
	{
		double val;
		int ret = conf[key.c_str()].get_double(&val, default_val);
		if (ret == 0)
		{
			//LOG_TRACE("Get config %s : %f", key.c_str(), val);
		}
		else
		{
			//LOG_TRACE("Using default %s : %f", key.c_str(), val);
		}
		return val;
	}
	//key not const, default_val const double will cause always ????double  WHY?

	inline double get_val(const comcfg::Configure& conf, string field, string key, double default_val)
	{
		double val;
		if (field.empty())
		{
			return get_val(conf, key, default_val);
		}
		int ret = conf[field.c_str()][key.c_str()].get_double(&val, default_val);
		if (ret == 0)
		{
			//LOG_TRACE("Using default %s::%s : %f", field.c_str(), key.c_str(), val);
		}
		else
		{
			//LOG_TRACE("Using default %s::%s : %f", field.c_str(), key.c_str(), val);
			set_val(conf, key, val);
		}
		return val;
	}

	inline void get_val(const comcfg::Configure& conf, char* dest,
		string key, string default_val)
	{
		string tmp = get_val(conf, key, default_val);
		strncpy(dest, tmp.c_str(), tmp.length());
		dest[tmp.length()] = '\0';
	}

	inline void get_val(const comcfg::Configure& conf, char* dest,
		string field, string key, string default_val)
	{
		string tmp = get_val(conf, field, key, default_val);
		strncpy(dest, tmp.c_str(), tmp.length());
		dest[tmp.length()] = '\0';
	}
#endif
}

#ifndef NO_BAIDU_DEP

//@TODO 以后外部都用宏调用 如果#define 。。 可以下面所有变为空去掉对conf的依赖 即代码没有配置完全是默认
#define SCONF(s)\
	gezi::set_val(gezi::SharedConf::conf(), section, gezi::conf_trim(#s), s)
#define SCONF_CLASS(root,s)\
	gezi::set_val(gezi::SharedConf::conf(), section, gezi::conf_trim(#s), root.s)

#define SCONF2(s,default_value)\
	s = gezi::get_val(gezi::SharedConf::conf(), section, gezi::conf_trim(#s), default_value)
#define SCONF_(s,default_value)\
	gezi::get_val(gezi::SharedConf::conf(), section, gezi::conf_trim(#s), default_value)
#define SCONF2_CLASS(root,s,default_value)\
	root.s = gezi::get_val(gezi::SharedConf::conf(), section, gezi::conf_trim(#s), default_value)

#define PSCONF(s, field)\
	gezi::set_val(gezi::SharedConf::conf(), field, gezi::conf_trim(#s), s)

#define PSCONF_WITHNAME(s, name, field)\
	gezi::set_val(gezi::SharedConf::conf(), field, name, s)
#define PSCONF2(s,field, default_value)\
	s = gezi::get_val(gezi::SharedConf::conf(), field, gezi::conf_trim(#s), default_value)

#define PSCONF_(s,field, default_value)\
	gezi::get_val(gezi::SharedConf::conf(), field, gezi::conf_trim(#s), default_value)

#define CONF(s)\
	gezi::set_val(conf, section, gezi::conf_trim(#s), s)
#define CONF_CLASS(root,s)\
	gezi::set_val(conf, section, gezi::conf_trim(#s), root.s)

#define CONF2(s,default_value)\
	s = gezi::get_val(conf, section, gezi::conf_trim(#s), default_value)
#define CONF2_CLASS(root,s,default_value)\
	root.s = gezi::get_val(conf, section, gezi::conf_trim(#s), default_value)

#define PCONF(s, field)\
	gezi::set_val(conf, field, gezi::conf_trim(#s), s)

#define PCONF_CLASS(root,s, field)\
	gezi::set_val(conf, field, gezi::conf_trim(#s), root.s)

#define PCONF2(s,field, default_value)\
	s = gezi::get_val(conf, field, gezi::conf_trim(#s), default_value)

#define PCONF2_CLASS(root, s,field, default_value)\
	root.s = gezi::get_val(conf, field, gezi::conf_trim(#s), default_value)

#define NPSCONF(s, name, field)\
	gezi::set_val(gezi::SharedConf::conf(), field, name + "_" + gezi::conf_trim(#s), s)

#define CONF_TRY_VAL(s)\
	gezi::set_val(conf, gezi::conf_trim(#s), s)
#define CONF_TRY_PROP(s,field)\
	gezi::set_val(conf, field, gezi::conf_trim(#s), s)

#define CONF_TRY_MEMBER_VAL(root, s)\
	gezi::set_val(conf, gezi::conf_trim(#s), root.s)
#define CONF_TRY_MEMBER_PROP(root, s,field)\
	gezi::set_val(conf, field, gezi::conf_trim(#s), root.s)

#define CONF_GET_VAL(s,default_value)\
	s = gezi::get_val(conf, gezi::conf_trim(#s), default_value)

#define CONF_GET_PROP(s,field,default_value)\
	s = gezi::get_val(conf, field, gezi::conf_trim(#s), default_value)

#define CONF_GET_MEMBER_VAL(root, s,default_value)\
	root.s = gezi::get_val(conf, gezi::conf_trim(#s), default_value)
#define CONF_GET_MEMBER_PROP(root, s,field,default_value)\
	root.s = gezi::get_val(conf, field, gezi::conf_trim(#s), default_value)

//-----------with root used 
#define CONF_STRCPY_VAL(root, s,default_value)\
	string VAL_STRCPY_##s##result = gezi::get_val(conf, gezi::conf_trim(#s), default_value); \
	strncpy(root, VAL_STRCPY_##s##result.c_str(), VAL_STRCPY_##s##result.length()); \
	root[VAL_STRCPY_##s##result.length()] = '\0'

#define CONF_STRCPY_PROP(root, s,field,default_value)\
	string PROP_STRCPY_##s##result; \
	PROP_STRCPY_##s##result = gezi::get_val(conf, field, gezi::conf_trim(#s), default_value); \
	strncpy(root, PROP_STRCPY_##s##result.c_str(), PROP_STRCPY_##s##result.length()); \
	root[PROP_STRCPY_##s##result.length()] = '\0'
#endif //NO_BAIDU_DEP
#endif  //----end of CONF_UTIL_H_
