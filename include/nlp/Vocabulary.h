/**
 *  ==============================================================================
 *
 *          \file   nlp/Vocabulary.h
 *
 *        \author   chenghuige
 *
 *          \date   2015-10-30 13:48:30.800547
 *
 *  \Description: 
 *  ==============================================================================
 */

#ifndef GEZI_NLP__VOCABULARY_H_
#define GEZI_NLP__VOCABULARY_H_
#include "Identifer.h"

namespace gezi {

class Vocabulary : public CountIdentifer
{
public:

  Vocabulary(string file, 
    int num_reserved_ids = 1,
    string start_word = "<S>",
    string end_word = "</S>",
    string unk_word = "<UNK>")
    :_num_reserved_ids(num_reserved_ids),
    _start_word(start_word),
    _end_word(end_word),
    _unk_word(unk_word)
  {
    Load(file);

    _unk_id = CountIdentifer::id(unk_word) + _num_reserved_ids;
    _start_id = CountIdentifer::id(start_word) + _num_reserved_ids;
    
    if (_start_id < _num_reserved_ids)
    {
      _start_id = _unk_id;
    }
    _end_id = CountIdentifer::id(end_word) + _num_reserved_ids;
    if (_end_id < _num_reserved_ids)
    {
      _end_id = _unk_id;
    }
  }

  size_t size() const
  {
    return CountIdentifer::size() + _num_reserved_ids;
  }

  inline IdType id(string key) const
  {
    HashMap::const_iterator it = _hashdict.find(key);
    if (it == _hashdict.end())
      return _unk_id;
    return it->second + _num_reserved_ids;
  }

  inline IdType id(string key, IdType default_val) const
  {
    HashMap::const_iterator it = _hashdict.find(key);
    if (it == _hashdict.end())
      return default_val;
    return it->second + _num_reserved_ids;
  }
  
  size_t freq(IdType index) const
  {
    if (index < _num_reserved_ids)
    {
      return 0;
    }
    return _values[index - _num_reserved_ids];
  }

  size_t count(IdType index) const
  {
    if (index < _num_reserved_ids)
    {
      return 0;
    }
    return _values[index - _num_reserved_ids];
  }

  string key(IdType index) const
  {
    if (index < _num_reserved_ids)
    {
      if (index == 0)
      {
        return "<PAD>";
      }
      return format("<PAD{}>", index);
    }
    return CountIdentifer::key(index - _num_reserved_ids);
  }

  size_t value(int index) const
  {
    return _values[index - _num_reserved_ids];
  }

  //---------no out range core now, return 0 if not in vocab
  size_t get_value(string key) const
  {
    HashMap::const_iterator it = _hashdict.find(key);
    if (it == _hashdict.end())
      return 0;
    return _values[it->second];
  }

  size_t value(string key) const
  {
    HashMap::const_iterator it = _hashdict.find(key);
    if (it == _hashdict.end())
      return 0;
    return _values[it->second];
  }

  size_t freq(string key) const
  {
    HashMap::const_iterator it = _hashdict.find(key);
    if (it == _hashdict.end())
      return 0;
    return _values[it->second];
  }

  size_t count(string key) const
  {
    HashMap::const_iterator it = _hashdict.find(key);
    if (it == _hashdict.end())
      return 0;
    return _values[it->second];
  }

  int num_reserved_ids() const
  {
    return _num_reserved_ids;
  }

  ///text start id
  IdType start_id() const
  {
    return _start_id;
  }

  ///text end id
  IdType end_id() const
  {
    return _end_id;
  }

  IdType unk_id() const
  {
    return _unk_id;
  }

  string start_word() const
  {
    return _start_word;
  }

  string end_word() const
  {
    return _end_word;
  }

  string unk_word() const
  {
    return _unk_word;
  }

protected:
private:
  IdType _start_id = -1;  ///text start id
  IdType _end_id = -1;    ///text end id
  IdType _unk_id = -1;    ///text unknown id
  int _num_reserved_ids = 0; ///rervered ids for 0 pad or other purpuse

  string _start_word;
  string _end_word;
  string _unk_word;
};

}  //----end of namespace gezi

#endif  //----end of GEZI_NLP__VOCABULARY_H_
