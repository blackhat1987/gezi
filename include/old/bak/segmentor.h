/** 
 *  ==============================================================================
 * 
 *          \file   segmentor.h
 *
 *        \author   chenghuige 
 *          
 *          \date   2010-04-02 15:36:04.667886
 *  
 *  \Description:
 *  ==============================================================================
 */

#ifndef SEGMENTOR_H_
#define SEGMENTOR_H_

#include <string>
#include <vector>
#include "ta_dic_w.h"  //分词
#include <glog/logging.h>
using std::string;
using std::vector;
class Segmentor
{
private:
    segment::PidConfig* m_pconfig; ///分词器设置
    segment::CDic_w m_segObj; ///分词器
public:
    Segmentor(const string & config_file = "segment/config.ini")
    {
        if (!initSegmentor(config_file))
        {
            LOG(FATAL) << "Failed to init segmentor " << config_file << std::endl;
        }
    }
    ~Segmentor()
    {
        clearSegmetor();
    }
    /**初始化分词器, 默认配置文件是"seg/config.ini"*/
    bool initSegmentor(const string & config_file = "segment/config.ini")
    {
        m_pconfig = new segment::PidConfig();
        //TODO 将文件名设置交给配置文件
        if (!m_pconfig->InitPara(config_file.c_str()))
            return false;
        if (m_pconfig->mode)
            return false;

        string dir = config_file.substr(0, config_file.size() - 18); //size of "segment/config.ini" + 1 = 18
        std::cout << (dir + m_pconfig->Idx_Dat) << std::endl;
        if (!m_segObj.Load((dir + m_pconfig->Idx_Dat).c_str(), (dir + m_pconfig->Idx_Map).c_str()))
            return false;

        return true;
    }
    /**清空分词器资源*/
    void clearSegmetor()
    {
        m_segObj.ClearData();
        if (m_pconfig)
            delete m_pconfig;
        m_pconfig = NULL;
    }

public:
    void getSubString(const string& phrase, vector<string>& query_vec)
    {
        if (phrase.empty())
            return;
        query_vec.clear();
        const char* str = phrase.c_str();
        vector<segment::Term> vec;
        m_segObj.MaxSegment(str, str + strlen(str), vec);
        string sub_string;
        for (size_t k = 0; k < vec.size(); k++)
        {
            sub_string = phrase.substr(vec[k].pos, vec[k].len);
            if (sub_string != " ")
                query_vec.push_back(phrase.substr(vec[k].pos, vec[k].len));
        }
    }
    void getOmniSubString(const string& phrase, vector<string>& query_vec)
    {
        if (phrase.empty())
            return;
        query_vec.clear();
        const char* str = phrase.c_str();
        char buf[2048];
        vector<segment::Term> vec;
        m_segObj.OmniSegment(str, str + strlen(str), vec, buf, 2048);
        string sub_string;
        for (size_t k = 0; k < vec.size(); k++)
        {
            sub_string = phrase.substr(vec[k].pos, vec[k].len);
            if (sub_string != " ")
                query_vec.push_back(phrase.substr(vec[k].pos, vec[k].len));
        }
    }
    void getMinSubString(const string& phrase, vector<string>& query_vec)
    {
        if (phrase.empty())
            return;
        query_vec.clear();
        const char* str = phrase.c_str();
        vector<segment::Term> vec;
        m_segObj.MinSegment(str, str + strlen(str), vec);
        Pval(vec.size());
        string sub_string;
        for (size_t k = 0; k < vec.size(); k++)
        {
            sub_string = phrase.substr(vec[k].pos, vec[k].len);
            if (sub_string != " ")
                query_vec.push_back(phrase.substr(vec[k].pos, vec[k].len));
        }
    }
    void getSubCh(const string& phrase, vector<string>& query_vec)
    {
        if (phrase.empty())
            return;

        char single[3];
        single[2] = '\0';

        for (size_t i = 0; i < phrase.size(); i += 2)
        {
            single[0] = phrase[i];
            single[1] = phrase[i + 1];
            query_vec.push_back(single);
        }
    }
    /**一个查询是否可分词*/
    bool canSplit(const string & phrase)
    {
        if (phrase.empty())
            return false;
        //对广告关键词phrase进行分词
        const char* str = phrase.c_str();
        vector<segment::Term> vec;
        m_segObj.MaxSegment(str, str + strlen(str), vec);

        if (vec.size() > 1)
            return true;
        else
            return false;
    }
};
#endif  //----end of SEGMENTOR_H_
