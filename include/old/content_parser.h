/** 
 *  ==============================================================================
 * 
 *          \file   content_parser.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-07-31 15:36:57.483615
 *  
 *  \Description:   提供文本内容初步分析，分词，统计词频，提供TF*IDF排序结果
 *  ==============================================================================
 */

#ifndef CONTENT_PARSER_H_
#define CONTENT_PARSER_H_
#include <string>
#include "common_help.h"
#include "common_cmper.h"
#include "debug_help.h"
#include "compat_hashmap.h"
#include "sort_map_by_value.h"
#include "segmentor.h"
#include "ul_log_help.h"
#include "context_measure.h"
#include "sim_calc.h"
#include "vec_calc.h"
#include "key_id_map.h"

namespace gezi {
using std::string;
using std::vector;
class ContentParser
{
protected:
    typedef std::pair<int, int> NodeI;
    typedef std::pair<int, float> NodeF;
    bseg::Segmentor2 _segmentor; //分词器,分词资源外部分配好
    token_t* _tokens;
    int _max_term_count;
    const KeyIDMap<>& _keyid_map;
    vector<float>& _idf_vec;
public:
    ContentParser(const KeyIDMap<>& keyid_map, vector<float>& idf_vec)
    : _keyid_map(keyid_map), _tokens(NULL), _idf_vec(idf_vec)
    {

    }
    ~ContentParser()
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
    void parse(const string& content, vector<NodeI>& vec)
    {
        if (content.empty() || content.size() > _max_term_count)
            return;
        std::tr1::unordered_map<int, int> hash_map;
        int count = _segmentor.segment(content, _tokens, _max_term_count);

        for (int i = 0; i < count; i++)
        {
            int id = _keyid_map.id(_tokens[i].buffer);
            if (id != -1)
                hash_map[id] += 1;
        }
        std::copy(hash_map.begin(), hash_map.end(), std::back_inserter(vec));
    }
    enum
    {
        tf,
        tfidf
    };
    void parse(const string& content, vector<NodeF>& vec, int type = tfidf)
    {
        if (content.empty() || content.size() > _max_term_count)
            return;
        std::tr1::unordered_map<int, int> hash_map;
        int count = _segmentor.segment(content, _tokens, _max_term_count);
        int total = 0;
        for (int i = 0; i < count; i++)
        {
            int id = _keyid_map.id(_tokens[i].buffer);
            if (id != -1)
            {
                hash_map[id] += 1;
                total++;
            }
        }
        std::copy(hash_map.begin(), hash_map.end(), std::back_inserter(vec));
        int len = vec.size();
        for (int i = 0; i < len; i++)
        {
            switch (type)
            {
                case tf:
                    vec[i].second /= total;
                    break;
                case tfidf:
                    vec[i].second = vec[i].second / total * _idf_vec[vec[i].first];
                    break;
                default:
                    break;
            }
        }
    }
};
} //----end of namespace chg

#endif  //----end of CONTENT_PARSER_H_
