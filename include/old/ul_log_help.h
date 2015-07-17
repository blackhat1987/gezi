/** 
 *  ==============================================================================
 * 
 *          \file   ul_log_help.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-04-02 09:36:45.642369
 *  
 *  \Description:   包装一下ul log
 *  ==============================================================================
 */

#ifndef UL_LOG_HELP_H_
#define UL_LOG_HELP_H_
#include <string>
#include "com_log.h" //TODO remove ul_log
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

#define LOG_FATAL(fmt, arg...) do { \
	com_writelog(COMLOG_FATAL, "[%d]: " fmt,  __LINE__, ## arg); \
} while (0)

#define LOG_ERROR(fmt, arg...) do { \
	com_writelog(COMLOG_FATAL, "[%d:%s]: " fmt,  __LINE__, __FUNCTION__, ## arg); \
} while (0)

#define LOG_WARNING(fmt, arg...) do { \
	com_writelog(COMLOG_WARNING, "[%d:%s]: " fmt, __LINE__, __FUNCTION__, ## arg); \
} while (0)

#define LOG_INFO(fmt, arg...) do { \
	com_writelog(COMLOG_NOTICE, "[%d:%s]: " fmt,  __LINE__, __FUNCTION__, ## arg); \
} while (0)

#define LOG_NOTICE(log_id, fmt, arg...) do { \
	com_writelog(COMLOG_NOTICE, "logid[%u]" fmt, log_id, ## arg); \
} while (0)

#define LOG_TRACE(fmt, arg...) do { \
	com_writelog(COMLOG_TRACE, "[%d]: " fmt,  __LINE__, ## arg); \
} while (0)

#define LOG_DEBUG(fmt, arg...) do { \
	com_writelog(COMLOG_DEBUG, "[%d:%s]: " fmt,  __LINE__, __FUNCTION__, ## arg); \
} while (0)

#define LOG_SDF(event, log_id, fmt, arg...) do { \
	com_writelog(event, "[%u]" fmt, log_id, ## arg); \
} while (0)

//user defined log type
#define LOG_DEBUG2(type, fmt, arg...) do { \
	com_writelog(type, "[%d:%s]: " fmt, __LINE__, __FUNCTION__, ## arg); \
} while (0)
class LogHelper
{
public:
    LogHelper(int log_level = 8)
    { //设置16是打印debug的 8一般OK 没有debug,有trace warning
        com_device_t dev[1];
        com_logstat_t logstat;
        logstat.sysevents = log_level;
        strcpy(dev[0].type, "TTY");
        COMLOG_SETSYSLOG(dev[0]);
        com_openlog("test", dev, 1, &logstat);
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
        com_closelog(6000);
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

#endif  //----end of UL_LOG_HELP_H_
