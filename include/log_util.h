/** 
 *  ==============================================================================
 * 
 *          \file   log_util
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-04-02 09:36:45.642369
 *  
 *  \Description:   com log wrapper
 *  ==============================================================================
 */

#ifndef LOG_UTIL_H_
#define LOG_UTIL_H_
#include <string>
#include <glog/logging.h>
#include "com_log.h" 
#include "ul_log.h"


#ifdef LOG_FATAL
#undef LOG_FATAL
#endif
#ifdef LOG_ERROR
#undef LOG_ERROR
#endif
#ifdef LOG_WARNING
#undef LOG_WARNING
#endif
#ifdef LOG_DEBUG
#undef LOG_DEBUG
#endif
#ifdef LOG_INFO
#undef LOG_INFO
#endif
#ifdef LOG_NOTICE
#undef LOG_NOTICE
#endif

#define FILE__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define LOG_FATAL(fmt, arg...) do { \
	com_writelog(COMLOG_FATAL, "[%d]: " fmt,  __LINE__, ## arg); \
} while (0)

#define LOG_ERROR(fmt, arg...) do { \
	com_writelog(COMLOG_FATAL, "[%s:%d:%s]: " fmt, FILE__, __LINE__, __FUNCTION__, ## arg); \
} while (0)

#define LOG_WARNING(fmt, arg...) do { \
	com_writelog(COMLOG_WARNING, "[%s:%d:%s]: " fmt, FILE__, __LINE__, __FUNCTION__, ## arg); \
} while (0)

#define LOG_INFO(fmt, arg...) do { \
	com_writelog(COMLOG_NOTICE, "[%s:%d:%s]: " fmt, FILE__, __LINE__, __FUNCTION__, ## arg); \
} while (0)

//#define LOG_NOTICE(log_id, fmt, arg...) do { \
//	com_writelog(COMLOG_NOTICE, "logid[%u]" fmt, log_id, ## arg); \
//} while (0)

#define LOG_NOTICE(fmt, arg...) do { \
	com_writelog(COMLOG_NOTICE, "[%s:%d:%s]: " fmt,  FILE__, __LINE__, __FUNCTION__, ## arg); \
} while (0)


#define LOG_TRACE(fmt, arg...) do { \
	com_writelog(COMLOG_TRACE, "[%s:%d:%s]: " fmt,  FILE__, __LINE__, __FUNCTION__, ## arg); \
} while (0)

#define LOG_DEBUG(fmt, arg...) do { \
	com_writelog(COMLOG_DEBUG, "[%s:%d:%s]: " fmt, FILE__, __LINE__, __FUNCTION__, ## arg); \
} while (0)

#define LOG_SDF(event, log_id, fmt, arg...) do { \
	com_writelog(event, "[%u]" fmt, log_id, ## arg); \
} while (0)

//user defined log type
#define LOG_SELF(type, fmt, arg...) do { \
	com_writelog(type, "[%s:%d:%s]: " fmt, FILE__, __LINE__, __FUNCTION__, ## arg); \
} while (0)

#define LOG_RECORD(type, fmt, arg...) do { \
	com_writelog(type, fmt, ## arg); \
} while (0)

namespace gezi
{
class LogHelper
{
public:

  LogHelper(int log_level = 16)
  { //设置16是打印debug的 8一般OK 没有debug,有trace warning
    com_device_t dev[1];
    com_logstat_t logstat;
    logstat.sysevents = log_level;
    strcpy(dev[0].type, "TTY");
    COMLOG_SETSYSLOG(dev[0]);
    com_openlog("test", dev, 1, &logstat);
  }

  static void set_level(int log_level)
  {
    // 直接调用下面的函数，传入一个新的logstat
    com_logstat_t logstat;
    logstat.sysevents = log_level;
    com_changelogstat(&logstat);
  }

  LogHelper(bool with_conf)
  {
    //cout << "Open log use conf" << endl;
  }

  LogHelper(const std::string& conf_path, const std::string& conf_file)
  {
    com_loadlog(conf_path.c_str(), conf_file.c_str());
  }

  ~LogHelper()
  {
    com_closelog();
  }
};

class ThreadLogHelper
{
public:

  ThreadLogHelper()
  {
    com_openlog_r();
  }

  ~ThreadLogHelper()
  {
    com_closelog_r();
  }
};
}
#endif  //----end of LOG_UTIL_H_
