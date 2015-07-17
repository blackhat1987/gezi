/** 
 *  ==============================================================================
 * 
 *          \file   common_help.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2010-11-15 16:33:52.681821
 *  
 *  \Description:  FIXME remove stl_help.h
 *  ==============================================================================
 */

#ifndef COMMON_HELP_H_
#define COMMON_HELP_H_
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "debug_help.h"

template<typename T>
void convert(const std::vector<T> &ivec, std::vector<std::pair<int, T> > &ovec)
{
    int len = ivec.size();
    ovec.reserve(len);
    for (int i = 0; i < len; i++)
    {
        ovec.push_back(std::make_pair(i, ivec[i]));
    }
}

typedef long long int64;

template<typename Container, typename Data>
bool contains(const Container& container, const Data& data)
{
    return container.find(data) != container.end();
}

template<typename T>
std::string join(const std::vector<T>& vec, const std::string& sep)
{
    std::stringstream s;
    size_t i = 0;
    for (; i < vec.size() - 1; i++)
    {
        s << vec[i] << sep;
    }
    s << vec[i];
    return s.str();
}

template<typename T>
std::string join_first(const std::vector<T>& vec, const std::string& sep)
{
    std::stringstream s;
    size_t i = 0;
    for (; i < vec.size() - 1; i++)
    {
        s << vec[i].first << sep;
    }
    s << vec[i].first;
    return s.str();
}

template<typename T>
std::string join_second(const std::vector<T>& vec, const std::string& sep)
{
    std::stringstream s;
    size_t i = 0;
    for (; i < vec.size() - 1; i++)
    {
        s << vec[i].second << sep;
    }
    s << vec[i].second;
    return s.str();
}

inline void replace_all(string& str, const string& old_value, const string& new_value)
{
    while (true)
    {
        string::size_type pos(0);
        if ((pos = str.find(old_value)) != string::npos)
            str.replace(pos, old_value.length(), new_value);
        else break;
    }
}

inline int search(const string& str, const string& value)
{
    int num = 0;
    int start = 0;
    int len = value.size();
    while (true)
    {
        string::size_type pos(0);
        if ((pos = str.find(value, start)) != string::npos)
        {
            num += 1;
            start += (pos + len);
        }
        else
            return num;
    }
}

template<typename T>
struct VecHash
{//TODO 提到stl help

    inline size_t operator()(const std::vector<T> & vec) const
    {

        unsigned long h = 0;
        for (int i = 0; i < vec.size(); i++)
            h = 5 * h + (uint) vec[i];
        return size_t(h);
    }
};



//---------------------------for file save load

/**
 * 注意 write_ve 与 read_vec配合使用, 只适用于_Node 是简单类型的情况比如int,float struct{int,float}
 */
template<typename _Node>
void write_vec(const std::vector<_Node>& vec, const std::string& file)
{//不输出长度
    std::ofstream ofs(file.c_str(), std::ios::binary);
    ofs.write(reinterpret_cast<const char*> (&vec[0]), sizeof (_Node) * vec.size());
}

template<typename _Node>
bool read_vec(const std::string& file, std::vector<_Node>& vec)
{
    using namespace std;
    std::ifstream ifs(file.c_str(), std::ios::binary);
    if (!ifs.is_open())
        return false;
    vec.clear();
    ifs.seekg(0, std::ios::end);
    int length = ifs.tellg(); //FIXME big file?
    ifs.seekg(0, std::ios::beg);
    vec.resize(length / sizeof (_Node));
    ifs.read(reinterpret_cast<char*> (&vec[0]), length);
    return true;
}

template<typename T>
void write_elem(const T& elem, const std::string& file)
{
    std::ofstream ofs(file.c_str());
    ofs << elem;
}

template<typename T>
bool read_elem(const std::string& file, T& elem)
{
    std::ifstream ifs(file.c_str());
    if (!ifs.is_open())
        return false;
    ifs >> elem;
    return true;
}

template<typename _Node>
void write_vec2d(const std::vector<std::vector<_Node> >& vec, std::ofstream& ofs)
{
    size_t row_len = vec.size();
    if (!row_len)
        return;
    for (size_t i = 0; i < row_len; i++)
    {
        int len = (int) vec[i].size();
        ofs.write(reinterpret_cast<const char*> (&len), sizeof (len));
        if (!len)
            continue;
        ofs.write(reinterpret_cast<const char*> (&vec[i][0]), sizeof (_Node) * vec[i].size());
    }
}

template<typename _Node>
void write_vec2d(const std::vector<std::vector<_Node> >& vec, const std::string& file)
{
    std::ofstream ofs(file.c_str(), std::ios::binary);
    size_t row_len = vec.size();
    ofs.write(reinterpret_cast<const char*> (&row_len), sizeof (row_len));
    write_vec2d(vec, ofs);
}

template<typename _Node>
bool read_vec2d(const std::string& file, std::vector<std::vector<_Node> >& vec)
{
    std::ifstream ifs(file.c_str(), std::ios::binary);
    if (!ifs.is_open())
        return false;
    vec.clear();
    //size_t total_len;
    int total_len; //TODO check 相关词的时候write 的是int
    ifs.read(reinterpret_cast<char*> (&total_len), sizeof (total_len));
    if (!total_len)
        return false;
    vec.resize(total_len);
    for (int i = 0; i < total_len; i++)
    {
        int len;
        ifs.read(reinterpret_cast<char*> (&len), sizeof (len));
        if (!len)
            continue;
        vec[i].resize(len);
        ifs.read(reinterpret_cast<char*> (&vec[i][0]), sizeof (_Node) * len);
    }
    return true;
}

class Vec2dWriter
{
public:

    Vec2dWriter(const std::string& file)
    : _ofs(file.c_str(), std::ios::binary)
    {
    }

    template<typename _Node>
    void write(const std::vector<_Node>& vec)
    {
        int len = (int) vec.size();
        _ofs.write(reinterpret_cast<const char*> (&len), sizeof (len));
        if (!len)
            return;
        _ofs.write(reinterpret_cast<const char*> (&vec[0]), sizeof (_Node) * len);
    }

    template<typename _Iter>
    void write(_Iter begin, _Iter end)
    {
        typedef typename _Iter::value_type value_type;
        int len = std::distance(begin, end);
        _ofs.write(reinterpret_cast<const char*> (&len), sizeof (len));
        if (!len)
            return;
        while (begin != end)
        {
            _ofs.write(reinterpret_cast<const char*> (&(*begin)), sizeof (value_type));
        }
    }

    void close()
    {
        _ofs.close();
    }
private:
    std::ofstream _ofs;
};

class VecWriter
{
public:

    VecWriter(const std::string& file)
    : _ofs(file.c_str(), std::ios::binary)
    {
    }

    template<typename _Node>
    void write(const std::vector<_Node>& vec)
    {
        int len = (int) vec.size();
        _ofs.write(reinterpret_cast<const char*> (&vec[0]), sizeof (_Node) * len);
    }

    template<typename _Iter>
    void write(_Iter begin, _Iter end)
    {
        typedef typename _Iter::value_type value_type;
        while (begin != end)
        {
            _ofs.write(reinterpret_cast<const char*> (&(*begin)), sizeof (value_type));
        }
    }

    void close()
    {
        _ofs.close();
    }
private:
    std::ofstream _ofs;
};
//---------------------------------common define
typedef long long int64;
#include <boost/lexical_cast.hpp>
#define TO_INT boost::lexical_cast<int>
#define TO_UINT boost::lexical_cast<unsigned int>
#define TO_INT64 boost::lexical_cast<long long>
#define TO_UINT64 boost::lexical_cast<unsigned long long>
#define TO_BOOL boost::lexical_cast<bool>
#define TO_FLOAT boost::lexical_cast<float>
#define TO_DOUBLE boost::lexical_cast<double>
#define TO_STRING boost::lexical_cast<std::string>
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&); \
    void operator=(const TypeName&)
#include <boost/algorithm//string.hpp>
#include <boost/format.hpp>
using boost::format;
#include <boost/scoped_ptr.hpp>
using boost::scoped_ptr; //TODO compat with tr1

/**
 * 解析位图文件,and load into bitset, the bitfile is 8 * n bit size
 * Notice while(!ifs.eof()) will read one line more!
 */
#include <boost/dynamic_bitset.hpp>

template<typename T>
bool init(boost::dynamic_bitset<T> & bit_set, const std::string& file)
{
    bit_set.clear();
    std::ifstream ifs(file.c_str(), std::ios::binary);
    if (!ifs.is_open())
    {
        return false;
    }
    //    try
    //    {
    //        ifs >> bit_set; //not ok, might not use bit but 0 ans one byte 1 as one byte
    //    }
    //    catch(...)
    //    {
    //        return false;
    //    }
    ifs.seekg(0, std::ios::end);
    int length = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    unsigned char byte;
    for (int i = 0; i < length; i++)
    {
        ifs.read(reinterpret_cast<char*> (&byte), sizeof (byte));
        bit_set.append(byte);
    }

    //    Pval(bit_set.count());
    //    Pval(bit_set.size());
    //    Pval(bit_set.max_size());

    //    std::ofstream ofs("temp");
    //    //    ofs << bit_set;
    //    boost::to_block_range(bit_set, std::ostream_iterator<unsigned char>(ofs)); // this is fine
    return true;
}

#include <boost/date_time/posix_time/posix_time.hpp>

class MicrosecTimer
{
public:

    MicrosecTimer() : _start_time(boost::posix_time::microsec_clock::local_time())
    {
    }

    ~MicrosecTimer()
    {
    }

    void restart()
    {
        _start_time = boost::posix_time::microsec_clock::local_time();
    }

    double elapsed()
    {
        boost::posix_time::time_duration d = boost::posix_time::microsec_clock::local_time() - _start_time;
        double result = d.ticks();
        return result /= d.ticks_per_second();
    }

private:
    boost::posix_time::ptime _start_time;
};

#include "common_cmper.h"
#include <boost/serialization/serialization.hpp>
namespace std2
{

template<class T1, class T2>
struct pair
{
    typedef T1 first_type;
    typedef T2 second_type;
    T1 first;
    T2 second;

    pair()
    : first(), second()
    {
    }

    /** Two objects may be passed to a @c pair constructor to be copied.  */
    pair(const T1& __a, const T2 & __b)
    : first(__a), second(__b)
    {
    }

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & first;
        ar & second;
    }
};
}
#include "serialize_help.h"
//namespace boost {
//namespace serialization {
//template<class Archive, class T1, class T2>
//void serialize(Archive & ar, std::pair<T1, T2> & g, const unsigned int version)
//{
//    ar & g.first;
//    ar & g.second;
//}
//} // namespace serialization
//} // namespace boost
#include <boost/scoped_ptr.hpp>
using boost::scoped_ptr;
#include <boost/tuple/tuple.hpp>

#include "ul_log_help.h"

#endif  //----end of COMMON_HELP_H_
