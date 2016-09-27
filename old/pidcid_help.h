/* 
 * File:   pidcid_help.h
 * Author: chenghuige
 *
 * Created on 2010��6��29��, ����4:15
 * ���pid��cid����Ϣ
 */

#ifndef PIDCID_HELP_H
#define	PIDCID_HELP_H
#include <glog/logging.h>
#include <tr1/unordered_map>
#include <fstream>
#include "debug_help.h"
class PidCidHelper
{
private:
    typedef std::tr1::unordered_map<int, int> HashMapII;
    HashMapII m_pid2cid;
public:
    PidCidHelper(const char* pidcid_file = "temp_data/pid_catid.txt")
    {
        load(pidcid_file);
        LOG(INFO) << Pval(getCid(20094923)) << Pval(getCid(537)) << Pval(getCid(10304040)) << "\n";
    }

    int getCid(int pid)
    {
        if (m_pid2cid.find(pid) == m_pid2cid.end()) //-2 ��ʾû�и�pid��¼��-1��ʾpidû�ж�Ӧ�����Ϣ
            return -2;

        return m_pid2cid[pid];
    }
private:
    void load(const char* file)
    {
        char line[1024];
        int pid, cid;
        std::ifstream ifs(file);
        if (!ifs)
            LOG(FATAL) << "failed to open " << file << "\n";
        while (ifs.getline(line, 1024))
        {
            sscanf(line, "%d %d", &pid, &cid);
            m_pid2cid[pid] = cid;
        }
        ifs.close();
    }

};

#endif	/* PIDCID_HELP_H */

