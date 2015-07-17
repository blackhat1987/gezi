/** 
 *  ==============================================================================
 * 
 *          \file   key_id_map_signdict.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-07-25 09:55:46.115746
 *  
 *  \Description:
 *  ==============================================================================
 */

#ifndef KEY_ID_MAP_SIGNDICT_H_
#define KEY_ID_MAP_SIGNDICT_H_

#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>
#include "ul_log_help.h"
#include "signdict_help.h"
#include "common_help.h"
#include "serialize_help.h"

namespace signdict {
/**
 * 暂时只支持string到int编号, TODO 支持int 到int编号
 * T is key type
 * U is val/id type //null id is -1 so if use unsigned like size_t use has/has_key  only
 * better use int, long long, so can use null_id to judge
 */
template<typename T = std::string, typename U = int>
        class KeyIDMapT
{
public:
    KeyIDMapT()
    {

    }
    ~KeyIDMapT()
    {

    }
    typedef T item_type;
    typedef U id_type;

    static const U null_id = -1;
    typedef typename std::vector<T>::iterator iterator;
    typedef typename std::vector<T>::const_iterator const_iterator;
    inline id_type add_(const T& f)
    {
        id_type id = _index.size();
        _dict.add(f, id);
        _index.push_back(f);
        return id;
    }
    /**signdict必须注意add完毕后finalize一下*/
    inline bool finalize()
    {
        _dict.finalize();
    }
    inline bool has(const T& f) const
    {
        return _dict.has(f);
    }
    inline const T& key(id_type id) const
    {
        return _index[id];
    }

    //get a item's id (index in dict),if the item does not exist return null_id
    inline id_type id(const T& f) const
    {
        int value;
        
        bool find = _dict.get(f, value);
        if (!find)
            return null_id;
        else
            return (id_type) value;
    }
    size_t size()const
    {
        return _index.size();
    }
    /**存储二进制结果*/
    void save(const string& dir)
    {
		namespace bf = boost::filesystem;
		bf::path path(dir); //如果索引输出路径文件夹未被建立则首先建立，比如update_data/abc,需要首先建立abc文件夹
		if (!bf::exists(path))
		{
			LOG_WARNING("%s not exist, will create first", dir.c_str());
			bf::create_directories(path);
		}
        std::string file = dir + "/sign.dict";
        _dict.save(file);
		Pval(_index.size());
		Pval(_index.capacity());
        file = dir + string("/vec_index.idx");
        serialize::save(_index, file);
    }
	/**从明文词典创建signdict key id map*/
	bool create(const string& file) 
	{
		std::ifstream ifs(file.c_str());
		if (!ifs.is_open())
		{
			LOG_ERROR("Open %s failed\n", file.c_str());
			return false;
		}

		std::string line, key;
		while (std::getline(ifs, line))
		{
			int pos = line.find("\t");
			if (pos == std::string::npos)
			{
				key = line;
			}
			else
			{
				key = line.substr(0, pos);
			}
			add_(key);
		}
		return finalize();
	}
    /**写明文结果文件*/
    void write(const string& file) const
    {

    }
    bool load(const string& dir)
    {
        std::string file = dir + "/sign.dict";
        if (!_dict.load(file))
            return false;
        file = dir + string("/vec_index.idx");
        if (!serialize::load(file, _index))
            return false;
        return true;
    }
private:
    SignStrDict _dict; //key->id
    std::vector<T> _index; //id->key
};

typedef KeyIDMapT<std::string> KeyIDMap;

} //----end of namespace signdict

#endif  //----end of KEY_ID_MAP_SIGNDICT_H_
