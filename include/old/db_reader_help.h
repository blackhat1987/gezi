/** 
 *  ==============================================================================
 * 
 *          \file   db_reader_help.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2010-11-10 18:14:58.146054
 *  
 *  \Description:   db_reader的外包装，方便读取一个日志总表或者读取多个日表合并
 *  ==============================================================================
 */

#ifndef DB_READER_HELP_H_
#define DB_READER_HELP_H_

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/gregorian/gregorian_types.hpp>
#include <string>
#include <vector>
#include "db_reader.h"

template<typename Func>
void run_(DBReader& m_dbReader, Func& reader, std::string& starting_day, int last_days)
{
    using std::string;
    using std::vector;
    if (!care_time)
    { //读取all_key 或者 all_pid_key
        m_dbReader.process(reader);
    }
    else
    { //读取最近n天的日表
        using namespace boost::gregorian;
        days diff(1);
        date day_;
        string table_pri = m_dbReader.getTable();
        string date_str;
        LOG(INFO) << Pval(table_pri);
        if (starting_day == "0")
        { //从昨天开始向前统计last_days
            day_ = day_clock::local_day();
            day_ -= diff; //只能统计昨天及之前的
            date_str = to_iso_string(day_);
            for (int i = 0; i < last_days; i++)
            {//统计last_days的日表
                m_dbReader.setTable(table_pri + date_str);
                m_dbReader.process(reader);
                day_ -= diff;
                date_str = to_iso_string(day_);
            }
        }
        else
        { //从starting_day开始向后统计last_days
            try
            {
                day_ = from_undelimited_string(starting_day);
            }
            catch (...)
            {
                LOG(FATAL) << starting_day << " you set as starting day is not a valid date" << endl;
            }
            days diff_all(last_days - 1);
            date end_day = day_ + diff_all;
            LOG(INFO) << Pval(to_iso_string(end_day));
            LOG(INFO) << Pval(to_iso_string(day_clock::local_day()));
            if (to_iso_string(end_day) >= to_iso_string(day_clock::local_day()))
            {
                LOG(FATAL) << "The lasting days is to many exceed as starting day + last days " << endl;
            }
            date_str = starting_day;
            for (int i = 0; i < last_days; i++)
            {
                m_dbReader.setTable(table_pri + date_str);
                m_dbReader.process(reader);
                day_ += diff;
                date_str = to_iso_string(day_);
            }
        }
    }
}
#endif  //----end of DB_READER_HELP_H_
