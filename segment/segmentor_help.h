/** 
 *  ==============================================================================
 * 
 *          \file   segmentor_help.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2010-12-05 14:01:54.352895
 *  
 *  \Description:
 *  ==============================================================================
 */

#ifndef SEGMENTOR_HELP_H_
#define SEGMENTOR_HELP_H_

namespace segment {

/**
 * 提供外围帮助函数，将分词结果string存储到vector中，不存储分出的空白
 * 现在这个基本不需要了可以直接
 * seg.maxSegment(key, out) out是string vec
 * 逆向还没有写直接操作vector<string>的  TODO
 */
template<typename Seg>
void maxSegment(const string& key, vector<string>& out, Seg& seg)
{
    out.clear();
    vector<Term> result;
    seg.maxSegment(key, result);
    string s;
    for (size_t i = 0; i < result.size(); i++)
    {
        s = key.substr(result[i].pos, result[i].len);
        if (!(s.size() == 1 && std::isspace(s[0])))
            out.push_back(s);
    }
}

}  //----end of namespace segment

#endif  //----end of SEGMENTOR_HELP_H_
