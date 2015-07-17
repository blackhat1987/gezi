/** 
 *  ==============================================================================
 * 
 *          \file   query_statistic_mapper.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-11-05 14:29:09.274512
 *  
 *  \Description:   统计单个词的频率
 *  ==============================================================================
 */

#ifndef QUERY_STATISTIC_MAPPER_H_
#define QUERY_STATISTIC_MAPPER_H_
#include <string>
#include <strstream>
#include <gflags/gflags.h>
#include <boost/algorithm/string.hpp>
#include "segmentor.h"
#include "file_set.h"
#include "common_help.h"
#include "compat_hashmap.h"
#include "ul_log_help.h"
#include "signdict_help.h"
#include "hadoop_counter_common.h"
using namespace semantic;
class QueryStatisticMapper
{
public:
    StrFileSet _stopwords; ///停用词
    SignStrSet _dictwords; ///词典中的词
    token_t _tokens[MAX_TERM_COUNT];
    std::tr1::unordered_map<std::string, size_t> _map; //二元
    bseg::BSegmentor2 _segmentor;
    typedef std::tr1::unordered_map<std::string, size_t>::iterator Iter;
    int _max_len;
public:
    QueryStatisticMapper(int map_size)
    : _max_len(map_size / 16)
    {

    }
    bool load(const string& seg_dir)
    {
        bool seg_status = _segmentor.init(seg_dir, MAX_TERM_COUNT);
        if (!seg_status)
        {
            LOG_ERROR("seg open failed");
            return false;
        }
        else
        {
            LOG_ERROR("Finish seg load");
        }

        string stop_words = seg_dir + string("/stop_words.txt");
        if (!_stopwords.load(stop_words))
        {
            LOG_ERROR("Stop words load fail %s", stop_words.c_str());
            return false;
        }
        else
        {
            LOG_ERROR("Finish stop words load");
        }

        string all_words = seg_dir + string("/all_words_signset");
        if (!_dictwords.load(all_words))
        {
            LOG_ERROR("Dict words load fail %s", all_words.c_str());
            return false;
        }
        else
        {
            LOG_ERROR("Finish all words load");
        }

        return true;
    }
    void add_line(string& line, int num = 1)
    {
        size_t found;
        found = line.find(" ");
        if (found != string::npos)
            line = line.substr(0, found);
        int count = _segmentor.segment(line, _tokens, MAX_TERM_COUNT);
    }
    void print_map()
    {
        for (Iter iter = _map.begin(); iter != _map.end(); ++iter)
        {
            std::cout << iter->first << "\t" << iter->second << std::endl;
        }
        _map.clear();
    }
    void finish()
    {
        print_map();
    }
};

#endif  //----end of QUERY_STATISTIC_MAPPER_H_
