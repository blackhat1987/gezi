/**
 *  ==============================================================================
 *
 *          \file   Identifer.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-01-19 09:53:10.353333
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef IDENTIFER_H_
#define IDENTIFER_H_
#include "common_util.h"
namespace gezi
{

class Identifer
{
public:
  typedef int IdType; //may be changed to int64
  typedef std::vector<string>::iterator iterator;
  typedef std::vector<string>::const_iterator const_iterator;
  typedef unordered_map<string, IdType> HashMap;
  typedef HashMap::const_iterator const_mapiter;
  
public:

  static const IdType null_id()
  {
    static const IdType _null_id = -1;
    return _null_id;
  }

  iterator begin()
  {
    return _index.begin();
  }

  iterator end()
  {
    return _index.end();
  }

  const_iterator begin()const
  {
    return _index.begin();
  }

  const_iterator end()const
  {
    return _index.end();
  }

  size_t size()const
  {
    return _index.size();
  }

  bool empty()const
  {
    return _index.empty();
  }

  void clear()
  {
    _hashdict.clear();
    _index.clear();
  }

  inline const string& key(int id) const
  {
    return _index[id];
  }

  //get a item's id (index in dict),if the item does not exist return null_id()

  inline IdType id(const string& f) const
  {
    HashMap::const_iterator it = _hashdict.find(f);
    if (it == _hashdict.end())
      return null_id();
    return it->second;
  }

  inline bool has(const string& f) const
  {
    return _hashdict.find(f) != _hashdict.end();
  }

  inline IdType add(const string& f)
  {
    HashMap::iterator it = _hashdict.find(f);
    if (it != _hashdict.end())
      return it->second;

    IdType id = _index.size();
    _hashdict[f] = id;
    _index.push_back(f);
    return id;
  }
  
  inline IdType add(const string& f, bool& isnew)
  {
    HashMap::iterator it = _hashdict.find(f);
    if (it != _hashdict.end())
    {
      isnew = false;
      return it->second;
    }
    isnew = true;
    IdType id = _index.size();
    _hashdict[f] = id;
    _index.push_back(f);
    return id;
  }

  string last()
  {
    return _index.back();
  }

  inline IdType add_unique(const string& f)
  {
    int id = _index.size();
    _hashdict[f] = id;
    _index.push_back(f);
    return id;
  }

  bool load(const string& file, string sep = "\t ")
  {
    ifstream ifs(file.c_str());
    CHECK_EQ(ifs.is_open(), true) << file;
    VLOG(3) << "Begin loading " << file;
    string line, key;
    IdType id = 0;
    while (std::getline(ifs, line))
    {
      vector<string> vec;
      boost::split(vec, line, is_any_of(sep));
      _hashdict[vec[0]] = id++;
    }
    _index.resize(id);
    HashMap::const_iterator iter = _hashdict.begin();
    for (; iter != _hashdict.end(); ++iter)
    {
      _index[iter->second] = iter->first;
    }
    VLOG(3) << "End loading " << file;
    return true;
  }

  void save(const string& file)
  {
    ofstream ofs(file.c_str());

    int len = int(_index.size());
    for (int i = 0; i < len; i++)
    {
      ofs << _index[i] << std::endl;
    }
  }

  const string& operator [] (int id) const {
    return _index[id];
  }

  const IdType& operator () (string key) const
  {
    HashMap::const_iterator it = _hashdict.find(key);
    if (it == _hashdict.end())
      return null_id();
    return it->second;
  }
protected:
  HashMap _hashdict;
  vector<string> _index; //kid->key
};


} //----end of namespace gezi

#endif  //----end of IDENTIFER_H_
