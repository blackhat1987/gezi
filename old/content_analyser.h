/** 
 *  ==============================================================================
 * 
 *          \file   content_analyser.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-06-27 16:14:23.773117
 *  
 *  \Description:   简单的文本分析器，输入文本(string)按照bag of word
 *                  切词统计词频(按照排序返回 vec of (word, freq) )
 *                  为了方便共享分词资源，
 *  ==============================================================================
 */

#ifndef CONTENT_ANALYSER_H_
#define CONTENT_ANALYSER_H_
#include <string>
#include "common_help.h"
#include "common_cmper.h"
#include "debug_help.h"
#include "compat_hashmap.h"
#include "sort_map_by_value.h"
#include "segmentor.h"
#include "ul_log_help.h"
#include "file_set.h"
#include "key_id_map.h"
#include "context_measure.h"
#include "sim_calc.h"
#include "vec_calc.h"
//#include "inverted_index.h"
//#include "inverted_index_printer.h"
using std::string;
using std::vector;
class ContentAnalyser
{
private:
    typedef std::pair<int, int> NodeI;
    bseg::Segmentor2 _segmentor; //分词器,分词资源外部分配好
    token_t* _tokens;
    int _max_term_count;
    const KeyIDMap<>& _keyid_map;
public:
    ContentAnalyser(const KeyIDMap<>& keyid_map)
    : _keyid_map(keyid_map), _tokens(NULL)
    {

    }
    ~ContentAnalyser()
    {
        if (_tokens)
            delete [] _tokens;
    }
    /**初始化分词器*/
    bool init(const bseg::SegInitor2& initor, const int max_term_count = 1248000)
    {
        if (!_segmentor.init(initor, max_term_count))
            return false;
        _tokens = new token_t[max_term_count];
        if (!_tokens)
            return false;
        _max_term_count = max_term_count;
        return true;
    }
    void analyse(const string& content, vector<NodeI>& vec)
    {
        if (content.empty())
            return;
        std::tr1::unordered_map<int, int> hash_map;
        int count = _segmentor.segment(content, _tokens, _max_term_count);
        //        Pval(count);
        //        int ret = tag_postag(_tokens, count);
        //        Pval(ret);
        //        if (ret <= 0)
        //        {
        //            LOG_ERROR("Tagging failed");
        //        }
        for (int i = 0; i < count; i++)
        {
            int id = _keyid_map.id(_tokens[i].buffer);
            if (id != -1)
                hash_map[id] += 1;
        }
        std2::sortMapByValue_reverse(hash_map, vec);
    }
    void analyse_title(const string& title, vector<string>& vec)
    {
        if (title.empty())
            return;
        int count = _segmentor.segment(title, _tokens, _max_term_count);
        for (int i = 0; i < count; i++)
        {
            int id = _keyid_map.id(_tokens[i].buffer);
            if (id != -1)
                vec.push_back(_tokens[i].buffer);
        }
    }
};

#endif  //----end of CONTENT_ANALYSER_H_
