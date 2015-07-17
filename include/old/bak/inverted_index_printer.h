/** 
 *  ==============================================================================
 * 
 *          \file   inverted_index_printer.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-05-06 19:06:29.979010
 *  
 *  \Description:   µπ≈≈–≈œ¢¥Ú”°∞Ô÷˙¿‡
 *  ==============================================================================
 */

#ifndef INVERTED_INDEX_PRINTER_H_
#define INVERTED_INDEX_PRINTER_H_
#include <limits>
#include <vector>
#include "key_id_map.h"
#include <boost/tuple/tuple.hpp>
namespace inverted {
class InvertedIndexPrinter
{
private:
    KeyIDMap<string>& _keyid_map; //◊÷µ‰
    int _max_invertnum;
public:
    InvertedIndexPrinter(KeyIDMap<string>& keyid_map)
    : _keyid_map(keyid_map), _max_invertnum(std::numeric_limits<int>::max())
    {

    }
    void set_max_invertnum(int num)
    {
        _max_invertnum = num;
    }
    void print(const std::vector<int>& vec)
    {
        for (size_t i = 0; i < vec.size() && i < _max_invertnum; i++)
        {
            cout << vec[i] << " " << _keyid_map.get_key(vec[i]) << "\n";
        }
    }
    void print(const std::vector<boost::tuple<int, float, float> >& vec)
    {
        for (size_t i = 0; i < vec.size() && i < _max_invertnum; i++)
        {
            cout << vec[i].get < 0 > () << " " << _keyid_map.get_key(vec[i].get < 0 > ()) << " "
                    << vec[i].get < 1 > () << " " << vec[i].get < 2 > () << " " << "\n";
        }
    }
    template<typename _Stream>
    void print(const std::vector<int>& vec, _Stream& ofs)
    {
        for (size_t i = 0; i < vec.size() && i < _max_invertnum; i++)
        {
            ofs << _keyid_map.get_key(vec[i]) << "\n";
        }
    }
    template<typename _Stream>
    void print(const std::vector<boost::tuple<int, float, float> >& vec, _Stream& ofs)
    {
        for (size_t i = 0; i < vec.size() && i < _max_invertnum; i++)
        {
            //            ofs.setprecision(2);
            ofs << setprecision(2) << _keyid_map.get_key(vec[i].get < 0 > ()) << " "
                    << vec[i].get < 1 > () << " " << vec[i].get < 2 > () << " " << "\n";
        }
    }
    template<typename _Iter>
    void print(_Iter iter_s, _Iter iter_e)
    {
        for (; iter_s != iter_e; ++iter_s)
        {
            cout << *iter_s << " " << _keyid_map.get_key(*iter_s) << "\n";
        }
    }
    template<typename _Iter, typename _Stream>
    void print(_Iter iter_s, _Iter iter_e, _Stream& ofs)
    {
        for (; iter_s != iter_e; ++iter_s)
        {
            ofs << _keyid_map.get_key(*iter_s) << "\n";
        }
    }
    template<typename _Node>
    void print(const vector<_Node>& vec)
    {
        for (size_t i = 0; i < vec.size() && i < _max_invertnum; i++)
        {
            cout << _keyid_map.get_key(vec[i].id) << " " << vec[i].weight << " | ";

        }
        cout << "\n";
    }
    template<typename _Invert>
    void print_post(int id, _Invert& invert)
    {
        vector<typename _Invert::InvertNodeType> vec;
        invert.get_post(id, vec);
        print(vec);
    }
    template<typename _Node, typename _Stream>
    void print(const vector<_Node>& vec, _Stream& os)
    {
        for (size_t i = 0; i < vec.size() && i < _max_invertnum; i++)
        {
            os << _keyid_map.get_key(vec[i].id) << " " << vec[i].weight << "\n";
        }
    }
    template<typename _Invert, typename _Stream>
    void print_post(int id, _Invert& invert, _Stream& os)
    {
        vector<typename _Invert::InvertNodeType> vec;
        invert.get_post(id, vec);
        print(vec, os);
    }
};



} //----end of namespace inverted

#endif  //----end of INVERTED_INDEX_PRINTER_H_
