/** 
 *  ==============================================================================
 * 
 *          \file   key_id_map_odict.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-04-09 21:32:22.153679
 *  
 *  \Description:   ˫��ӳ���ֵ����ODICT�ڲ�ʵ�֣����ֻ��Ҫ key -> id ����ֱ��ʹ��ODict
 *                  ���ֻ���string������ʵ
 *  ==============================================================================
 */

#ifndef KEY_ID_MAP_ODICT_H_
#define KEY_ID_MAP_ODICT_H_
#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include "ul_log_help.h"
#include "odict_help.h"
#include "common_help.h"
#include "serialize_help.h"

namespace odict {
/**
 * ��ʱֻ֧��string��int���, TODO ֧��int ��int���
 * T is key type
 * U is val/id type //null id is -1 so if use unsigned like size_t use has/has_key  only
 * better use int, long long, so can use null_id to judge 
 */
template<typename T = std::string, typename U = int>
        class KeyIDMapBuilderT
{
public:
    KeyIDMapBuilderT(int hash_num = -1)
    : _dict(hash_num)
    {

    }
    ~KeyIDMapBuilderT()
    {

    }
    typedef T item_type;
    typedef U id_type;

    static const U null_id;
    typedef typename std::vector<T>::iterator iterator;
    typedef typename std::vector<T>::const_iterator const_iterator;
    inline id_type add_(const T& f)
    {
        id_type id = _index.size();
        _dict.add(f, id);
        _index.push_back(f);
        return id;
    }
    inline id_type add(const T& f)
    {
        sodict_snode_t snode;
        int id = _dict.id(f, snode);
        if (id != null_id)
        {
            return id;
        }
        else
        {
            id = _index.size();
            _dict.add(snode, id);
            _index.push_back(f);
            return id;
        }
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
        unsigned int value;
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
    /*�洢�����ƽ��**/
    void save(const string& dir)
    {
        using namespace std;
        _dict.save(dir);
		Pval(_index.size());
		Pval(_index.capacity());
        string file = dir + string("/vec_index.idx");
        //        write_vec(_index, file);
        serialize::save(_index, file);
        //        ofstream ofs(file.c_str());
        //        int len = _index.size();
        //        for (int i = 0; i < len; i++)
        //        {
        //            ofs << _index[i] << endl;
        //        }
    }
    /*д���Ľ���ļ�**/
    void write(const string& file) const
    {

    }
    //ͨ�������ʽ�� keyid_map�����ļ�������keyid map
    bool load(const string& file)
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

        return true;
    }
private:
    ODictBuilder _dict; //key->id
    std::vector<T> _index; //id->key
};
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
        unsigned int value;
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

    //����������ֵ��ļ�
    bool load(const string& dir)
    {
        if (!_dict.load(dir))
            return false;
        std::string file = dir + string("/vec_index.idx");
        //        Pval(file);
        //        if (!read_vec(file, _index))
        //            return false;
        if (!serialize::load(file, _index)) //TODO vector string ��ռ�ڴ档���� Ӳ����1g ����ռ�ڴ�3G����
            return false;
        //        ifstream ifs(file.c_str());
        //        int len = _dict.size();
        //        _index.resize(len);
        //        string key;
        //        for (int i = 0; i < len; i++)
        //        {
        //            ifs >> key;
        //            _index[i] = key;
        //        }

        return true;
    }
private:
    ODict _dict; //key->id
    std::vector<T> _index; //id->key
};

template <typename T, typename U>
        const U KeyIDMapBuilderT<T, U>::null_id = ~(typename KeyIDMapBuilderT<T, U>::id_type)(0); // -1 is null_id

typedef KeyIDMapBuilderT<std::string> KeyIDMapBuilder;
typedef KeyIDMapT<std::string> KeyIDMap;
}
#endif  //----end of KEY_ID_MAP_ODICT_H_
