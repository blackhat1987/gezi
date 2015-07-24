/** 
 *  ==============================================================================
 * 
 *          \file   ch_stoper.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-01-24 11:08:58.371262
 *  
 *  \Description:  一个中文的stop word处理器，支持编译期间的stop word或者提供一个stop word文本动态载入
 *  ==============================================================================
 */

#ifndef CH_STOPER_H_
#define CH_STOPER_H_
#include "ch_stopwords_table.h"
#include "gbk_encode_convert.h"  //for utf-8 to gbk for in source we can only use utf-8
#include <tr1/unordered_set>
#include <iostream>
#include <boost/algorithm/string.hpp>

class CHStoper
{
private:
    typedef std::tr1::unordered_set<std::string> StrHashSet;
    StrHashSet m_set;
public:

    CHStoper()
    {
        init();
    }

    CHStoper(const string& stop_file)
    {
        init();
        init(stop_file);
    }

    void init()
    {
        int len = sizeof (kChStopWords) / sizeof (char*);
        std::string stop_word;
        for (int i = 0; i < len; i++)
        {
            _UTF8_to_GBK_(kChStopWords[i], stop_word);
            m_set.insert(stop_word);
        }
    }

    void init(const std::string& stop_file)
    {
        std::ifstream ifs(stop_file.c_str());
        string line;
        while (getline(ifs, line))
        {
            boost::trim(line);
            m_set.insert(line);
        }
    }

    bool contains(const std::string& phrase) const
    {
        return m_set.find(phrase) != m_set.end();
    }

    bool isStopWord(const string& phrase) const
    {
        return m_set.find(phrase) != m_set.end();
    }
};

#endif  //----end of CH_STOPER_H_
