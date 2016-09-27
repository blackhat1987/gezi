/** 
 *  ==============================================================================
 * 
 *          \file   key_id_map.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-04-09 21:32:22.153679
 *  
 *  \Description:   TODO 可以修改下字典格式。。 其实只需要存储词就可以了。。。 因为按顺序写的
 *                  另外可以考虑使用DATRIE+VECTOR？替代HASH？ I thik it's ok  TODO
 *  ==============================================================================
 */

#ifndef KEY_ID_MAP_H_
#define KEY_ID_MAP_H_
#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include "ul_log_help.h"
#include "compat_hashmap.h"
/**
 * 暂时只支持string到int编号, TODO 支持int 到int编号
 * T is key type
 * U is val/id type //null id is -1 so if use unsigned like size_t use has/has_key  only
 * better use int, long long, so can use null_id to judge 
 */
template<typename T = std::string, typename U = int>
        class KeyIDMap
{
public:
    KeyIDMap()
    {
    }
    ~KeyIDMap()
    {
    }

public:

    typedef T item_type;
    typedef U id_type;

    static const U null_id;
    typedef typename std::vector<T>::iterator iterator;
    typedef typename std::vector<T>::const_iterator const_iterator;
    typedef std::tr1::unordered_map<T, id_type> HashMap;
    typedef typename HashMap::const_iterator const_mapiter;

public:
    iterator begin()
    {
        return m_index.begin();
    }
    iterator end()
    {
        return m_index.end();
    }
    const_iterator begin()const
    {
        return m_index.begin();
    }
    const_iterator end()const
    {
        return m_index.end();
    }
    size_t size()const
    {
        return m_index.size();
    }
    bool empty()const
    {
        return m_index.empty();
    }
    void clear()
    {
        m_hashdict.clear();
        m_index.clear();
    }

    // get a item's key from id  //chage from at to [] do not check 越界
    inline const T& get_key(id_type id) const
    {
        return m_index[id];
    }
    inline const T& key(id_type id) const
    {
        return m_index[id];
    }

    //get a item's id (index in dict),if the item does not exist return null_id
    inline id_type id(const T& f) const
    {
        typename HashMap::const_iterator it = m_hashdict.find(f);
        if (it == m_hashdict.end())
            return null_id;
        return it->second;
    }

    //get a item's id (index in dict),if the item does not exist return null_id
    inline id_type get_id(const T& f) const
    {
        typename HashMap::const_iterator it = m_hashdict.find(f);
        if (it == m_hashdict.end())
            return null_id;
        return it->second;
    }

    //is or not is key item in dict),
    inline bool has_key(const T& f) const
    {
        return m_hashdict.find(f) != m_hashdict.end();
    }
    inline bool has(const T& f) const
    {
        return m_hashdict.find(f) != m_hashdict.end();
    }
    // add a item into dict return new item's id
    inline id_type add_key(const T& f)
    {
        typename HashMap::const_iterator it = m_hashdict.find(f);
        if (it != m_hashdict.end())
            return it->second;

        id_type id = m_index.size();
        m_hashdict[f] = id;
        m_index.push_back(f);
        return id;
    }
    inline id_type add(const T& f)
    {
        typename HashMap::const_iterator it = m_hashdict.find(f);
        if (it != m_hashdict.end())
            return it->second;

        id_type id = m_index.size();
        m_hashdict[f] = id;
        m_index.push_back(f);
        return id;
    }

	inline id_type  add_unique(const T& f)
	{
		id_type id = m_index.size();
		m_hashdict[f] = id;
		m_index.push_back(f);
		return id;
	}

    bool load(const std::string& file)
    {
        return load(file.c_str());
    }
    /**
     * 暂时只支持string 作为key, how to support int also?
     */
    //    bool load(const char *file_name)
    //    {
    //        std::ifstream ifs(file_name);
    //        if (!ifs.is_open())
    //        {
    //            LOG_ERROR("Open %s failed\n", file_name);
    //            return false;
    //        }
    //
    //        std::string line, key;
    //        U id;
    //        int max_id = -1;
    //        while (std::getline(ifs, line))
    //        {
    //            int pos = line.find("\t");
    //            if (pos == std::string::npos)
    //            {
    //                LOG_ERROR("Can nof find key id separator, the file format is wrong\n");
    //                return false;
    //            }
    //            key = line.substr(0, pos);
    //            id = boost::lexical_cast<U > (line.substr(pos + 1, line.size() - pos));
    //            m_hashdict[boost::lexical_cast<T > (key)] = id;
    //            if (id > max_id)
    //                max_id = id;
    //        }
    //        m_index.resize(max_id + 1);
    //        typename HashMap::const_iterator iter = m_hashdict.begin();
    //        for (; iter != m_hashdict.end(); ++iter)
    //        {
    //            m_index[iter->second] = iter->first;
    //        }
    //        return true;
    //    }
    bool load(const char *file_name)
    {
        std::ifstream ifs(file_name);
        if (!ifs.is_open())
        {
            LOG_ERROR("Open %s failed\n", file_name);
            return false;
        }

        std::string line, key;
        U id = 0;
        while (std::getline(ifs, line))
        {
            int pos = line.find("\t");
            if (pos == std::string::npos)
            {
                boost::trim(line);
            }
            else
            {
                line = line.substr(0, pos);
            }
            m_hashdict[line] = id++;
        }
        m_index.resize(id);
        typename HashMap::const_iterator iter = m_hashdict.begin();
        for (; iter != m_hashdict.end(); ++iter)
        {
            m_index[iter->second] = iter->first;
        }
        return true;
    }
    void save(const std::string& file)
    {
        save(file.c_str());
    }
    bool save(const char *fileFullName)
    {
        std::ofstream ofs(fileFullName);
        if (!ofs.is_open())
            return false;

        //        typename HashMap::const_iterator it;
        //        for (it = m_hashdict.begin(); it != m_hashdict.end(); it++)
        //        {
        //            ofs << it->first << "\t" << it->second << std::endl;
        //        }
        int len = int(m_index.size());
        //        for (int i = 0; i < len; i++)
        //        {
        //            ofs << m_index[i] << "\t" << i << std::endl;
        //        }
        for (int i = 0; i < len; i++)
        {
            ofs << m_index[i] << std::endl;
        }
        return true;
    }
    const item_type & operator [] (id_type id) const
    {
        return m_index[id];
    }
    const id_type & operator () (item_type key) const
    {
        typename HashMap::const_iterator it = m_hashdict.find(key);
        if (it == m_hashdict.end())
            return null_id;
        return it->second;
    }
private:
    HashMap m_hashdict;
    std::vector<T> m_index; //kid->key
};

template <typename T, typename U>
        const U KeyIDMap<T, U>::null_id = ~(typename KeyIDMap<T, U>::id_type)(0); // -1 is null_id

typedef KeyIDMap<std::string> StrKeyIDMap;
#endif  //----end of KEY_ID_MAP_H_
