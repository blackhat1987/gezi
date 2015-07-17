/* 
 * File:   harrod_help.h
 * Author: chenghuige
 *
 * Created on 2010年6月29日, 上午10:19
 *
 * 用于判断dangdang pid是否是百货id,需要预先读取数据库
 * ./read_db -table harrod_pid
 */

#ifndef HARROD_HELP_H
#define	HARROD_HELP_H

#include <tr1/unordered_set>
#include <glog/logging.h>
#include <fstream>
#include <algorithm>
#include "debug_help.h"
class HarrodHelper
{
public:
    typedef std::tr1::unordered_set<int> HashSet;
    HarrodHelper(const char* harrod_pid_file = "static_data/harrod_pid.dat")
    {
        DLOG(INFO) << "Found cookies";
        LOG(INFO) << "init in harrod helper\n";
        load(harrod_pid_file);
    }
    bool isHarrodPid(int pid)
    {
        return m_harrodPidSet.find(pid) != m_harrodPidSet.end();
    }
private:
    void load(const char* file)
    {
        std::ifstream ifs(file);
        if (!ifs)
            LOG(ERROR) << "could not find file " << file << "\n";
        std::istream_iterator<int> data_begin(ifs);
        std::istream_iterator<int> data_end;
        HashSet set_(data_begin, data_end);
        m_harrodPidSet.swap(set_);
        LOG(INFO) << Pval(m_harrodPidSet.size()) << "\n";
    }

private:
    HashSet m_harrodPidSet;
};


#endif	/* HARROD_HELP_H */

