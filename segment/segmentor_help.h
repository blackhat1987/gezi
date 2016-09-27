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
 * �ṩ��Χ�������������ִʽ��string�洢��vector�У����洢�ֳ��Ŀհ�
 * ���������������Ҫ�˿���ֱ��
 * seg.maxSegment(key, out) out��string vec
 * ����û��дֱ�Ӳ���vector<string>��  TODO
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
