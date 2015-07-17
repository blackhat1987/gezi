/** 
 *  ==============================================================================
 * 
 *          \file   inverted_index_printer.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-05-06 19:06:29.979010
 *  
 *  \Description:   ������Ϣ��ӡ������
 *     //ע�������Ĭ�ϲ�����Ӧģ��_Streamʵ��û���ã�
 *   //�����׷���Ϳ���std::ostream& os = std::cout ע��cout,ofstream,stringstream����������
    //����ǵ÷��������������߱�������Ĳ���������cout,�������취���ټ�һ���������أ������Ҫ��Ĭ��ֵ
    //���͵�Ĭ�ϲ�����û������Ĳο�std::sortֻ���ǿ��д����һ���дһ�����ذ���
 *
 *  Ĭ�ϲ��������أ�ģ�塣���� ҪȨ�� ����ܲ��þͲ�ʹ��ģ��
 *  ==============================================================================
 */

#ifndef INVERTED_INDEX_PRINTER_H_
#define INVERTED_INDEX_PRINTER_H_
#include <limits>
#include <vector>
#include <iostream>
#include "key_id_map.h"
#include <boost/tuple/tuple.hpp>
namespace inverted {
class InvertedIndexPrinter
{
public:
    InvertedIndexPrinter(const KeyIDMap<string>& keyid_map)
    : _keyid_map(keyid_map), _max_invertnum(std::numeric_limits<int>::max())
    {

    }
    void set_max_invertnum(int num)
    {
        _max_invertnum = num;
    }
    void print(const std::vector<boost::tuple<int, float, float> >& vec,
            const string& sep = " | ", std::ostream& os = std::cout)
    {
        for (size_t i = 0; i < vec.size() && i < _max_invertnum; i++)
        {
            os << vec[i].get < 0 > () << " " << _keyid_map.key(vec[i].get < 0 > ()) << " "
                    << vec[i].get < 1 > () << " " << vec[i].get < 2 > () << " " << sep;
        }
        os << "\n";
    }


    void print(const std::vector<int>& vec, std::ostream& os = std::cout)
    {
        for (size_t i = 0; i < vec.size() && i < _max_invertnum; i++)
        {
            os << _keyid_map.key(vec[i]) << "\n";
        }
    }
    template<typename _Iter>
    void print(_Iter iter_s, _Iter iter_e, std::ostream& os = std::cout, const string& sep = " | ")
    {
        for (; iter_s != iter_e; ++iter_s)
        {
            os << *iter_s << " " << _keyid_map.key(*iter_s) << sep;
        }
        os << "\n";
    }
    template<typename _Node>
    void print(const vector<_Node>& vec, std::ostream& os = std::cout, const string& sep = " | ")
    {
        for (size_t i = 0; i < vec.size() && i < _max_invertnum; i++)
        {
            os << _keyid_map.key(vec[i].first) << " " << vec[i].second << sep;

        }
        os << "\n";
    }
    template<typename _Iter>
    void print_key(_Iter iter_s, _Iter iter_e, std::ostream& os = std::cout, const string& sep = " | ")
    {
        for (; iter_s != iter_e; ++iter_s)
        {
            os << _keyid_map.key(*iter_s) << sep;
        }
        os << "\n";
    }

    //why ?test_invert.cc:91: error: no matching function for call
    //to `inverted::InvertedIndexPrinter::print_post(inverted::InvertNode<float>*&, inverted::InvertNode<float>*&)'
    template<typename _Iter>
    void print_post(_Iter iter_s, _Iter iter_e, std::ostream& os = std::cout, const string& sep = " | ")
    {
        for (; iter_s != iter_e; ++iter_s)
        {
            os << _keyid_map.key(iter_s->first) << " " << iter_s->second << sep;
        }
        os << "\n";
    }
    template<typename _Iter>
    void print_post_full(_Iter iter_s, _Iter iter_e, std::ostream& os = std::cout, const string& sep = " | ")
    {
        for (; iter_s != iter_e; ++iter_s)
        {
            os << _keyid_map.key(iter_s->first) << " " << iter_s->first << " " << iter_s->second << sep;
        }
        os << "\n";
    }
    template<typename _Invert>
    void print_post(int id, _Invert& invert, std::ostream & os = std::cout, const string& sep = " | ")
    {
        typedef typename _Invert::Range Range;
        Range range = invert.posting(id);
        print_post(range.first, range.second, sep, os);
    }
private:
    const KeyIDMap<string>& _keyid_map; //�ֵ�
    int _max_invertnum;
};



} //----end of namespace inverted

#endif  //----end of INVERTED_INDEX_PRINTER_H_
