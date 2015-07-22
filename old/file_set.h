/** 
 *  ==============================================================================
 * 
 *          \file   file_set.h
 *
 *        \author   gezi  
 *          
 *          \date   2010-07-23 22:01:32.665018
 *  
 *  \Description:   将文本内容读出来建立一个set,适用于建立黑白名单：）
 *
 *  注意这个不考虑空格因素 ”美帝 加湿器“ 会成为两个词，
 *  另一种是考虑每个词用单独一行的形式可以处理
 *
 *  黑名单
 *  {
 *    中国足球
 *    卓越
 *    ....
 *  }
 *
 * TODO 提供一个file map 直接读取
 * A 3
 * B 4
 * 存储map?
 *  ==============================================================================
 */

#ifndef FILE_SET_H_
#define FILE_SET_H_
#include <set>
#include <fstream>
#include <algorithm>
#include "compat_hashmap.h"
#include "ul_log_help.h"
#include "debug_help.h"
struct FileSetEmptyFunc
{
    template<typename T>
            void operator()(const T & elem)
    {

    }
};
template<class T = std::string, class Func = FileSetEmptyFunc>
class FileSet
{
public:
    typedef std::tr1::unordered_set<T> Set;
    Set m_set;
    FileSet(const string& file)
    {
        init(file);
    }
    FileSet()
    {
    }
    bool load(const std::string& file)
    {
        std::ifstream ifs(file.c_str());
        if (!ifs.is_open())
        {
            LOG_ERROR("open %s failed", file.c_str());
            return false;
        }

        //        ifs.unsetf(std::ios::skipws);
        std::istream_iterator<T> data_begin(ifs);
        std::istream_iterator<T> data_end;
        std::copy(data_begin, data_end, std::inserter(m_set, m_set.begin()));
        return true;
    }
    void open(const std::string& file)
    {
        init(file);
    }
    void init(const std::string& file)
    {
        std::ifstream ifs(file.c_str());
        if (!ifs.is_open())
        {
            LOG_ERROR("open %s failed", file.c_str());
            return;
        }

        //        ifs.unsetf(std::ios::skipws);
        std::istream_iterator<T> data_begin(ifs);
        std::istream_iterator<T> data_end;
        std::copy(data_begin, data_end, std::inserter(m_set, m_set.begin()));
        //Pval(m_set.size());
    }
    bool contains(const T& phrase)
    {
        return m_set.find(phrase) != m_set.end();
    }
    bool has(const T& phrase)
    {
        return m_set.find(phrase) != m_set.end();
    }
    bool empty()
    {
        return m_set.empty();
    }
    int size()
    {
        return m_set.size();
    }
    void insert(const T& phrase)
    {
        m_set.insert(phrase);
    }
    Set& get_set()
    {
        return m_set;
    }
};

typedef FileSet<std::string, FileSetEmptyFunc> StrFileSet;
class FileSet2
{
public:
    typedef std::tr1::unordered_set<std::string> Set;
    Set m_set;
    FileSet2(const string& file)
    {
        load(file);
    }
    FileSet2()
    {
    }
    bool load(const string& file)
    {
        std::ifstream ifs(file.c_str());
        if (!ifs.is_open())
        {
            LOG_WARNING("Unable to load %s", file.c_str());
            return false;
        }
        std::string line;
        while (std::getline(ifs, line))
        {
            line = line.substr(0, line.find("\t"));
            m_set.insert(line);
        }
        //Pval(m_set.size());
        return true;
    }
    bool contains(const std::string& key)
    {
        return m_set.find(key) != m_set.end();
    }
    bool has(const std::string& key)
    {
        return m_set.find(key) != m_set.end();
    }
    int size()
    {
        return m_set.size();
    }
    bool empty()
    {
        return m_set.empty();
    }
};
template<class T = std::string, class Func = FileSetEmptyFunc>
class OrderedFileSet
{
public:
    typedef std::set<T> Set;
    Set m_set;
    OrderedFileSet(const string& file)
    {
        init(file);
    }
    OrderedFileSet()
    {
    }
    void init(const string& file)
    {
        std::ifstream ifs(file.c_str());
        //        ifs.unsetf(std::ios::skipws);
        std::istream_iterator<T> data_begin(ifs);
        std::istream_iterator<T> data_end;
        std::copy(data_begin, data_end, std::inserter(m_set, m_set.begin()));
        Pval(m_set.size());
    }
    bool contains(const T& phrase)
    {
        return m_set.find(phrase) != m_set.end();
    }
    int size()
    {
        return m_set.size();
    }
    void insert(const T& phrase)
    {
        m_set.insert(phrase);
    }
    bool empty()
    {
        return m_set.empty();
    }
    Set& get_set()
    {
        return m_set;
    }
};

typedef OrderedFileSet<std::string, FileSetEmptyFunc> OrderedStrFileSet;

#endif  //----end of FILE_SET_H_
