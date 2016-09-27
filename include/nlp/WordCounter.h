/**
 *  ==============================================================================
 *
 *          \file   WordCounter.h
 *
 *        \author   chenghuige
 *
 *          \date   2016-07-20 19:30:53.621928
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef GEZI_NLP__WORD_COUNTER_H_
#define GEZI_NLP__WORD_COUNTER_H_

#include "common_util.h"
#include "sort_map_by_value.h"
#include "Identifer.h"
namespace gezi {

class WordCounter 
{
public:
  typedef std::pair<string, size_t> WordFreq;

  WordCounter(bool addUnknown = true, string unknownMark = "<UNK>", 
    size_t mostCommon = 0, size_t minCount = 0, 
    bool saveCountInfo = true)
    :_addUnknown(addUnknown), _unknownMark(unknownMark),
    _mostCommon(mostCommon), _minCount(minCount),
    _saveCountInfo(saveCountInfo)
  {

  }

  void save(string file) const
  {
    save_text(file);
  }

  void save_text(string file) const
  {
    ofstream ofs(file);
    if (_unknownSize && _addUnknown)
    {
      ofs << _unknownMark << "\t" << _unknownSize << endl;
    }
    size_t vocabSize = 0;
    for (const auto& item: _ordered)
    {
      ofs << item.first << "\t" << item.second << endl;
      vocabSize++;
      if (vocabSize == _vocabSize)
      {
        break;
      }
    }
  }

  CountIdentifer get_vocabulary()
  {
    CountIdentifer identifer;
    if (_unknownSize && _addUnknown)
    {
      identifer.add(_unknownMark, _unknownSize);
    }
    size_t vocabSize = 0;
    for (const auto& item : _ordered)
    {
      identifer.add(item.first, item.second);
      vocabSize++;
      if (vocabSize == _vocabSize)
      {
        break;
      }
    }
    return identifer;
  }

  void save_vocabulary(string file) const
  {
    auto identifer = get_vocabulary();

    identifer.Save(file);
  }

  Identifer get_identifer()
  {
    Identifer identifer;
    if (_unknownSize && _addUnknown)
    {
      identifer.add(_unknownMark);
    }
    size_t vocabSize = 0;
    for (const auto& item : _ordered)
    {
      identifer.add(item.first);
      vocabSize++;
      if (vocabSize == _vocabSize)
      {
        break;
      }
    }
    return identifer;
  }

  void save_identifer(string file) const
  {
    auto identifer = get_identifer();

    identifer.Save(file);
  }

  void save(string binFile, string countFile)
  {
    finish();

    ofstream ofs(countFile);

    if (_saveCountInfo)
    {
      CountIdentifer identifer;
      if (_unknownSize && _addUnknown)
      {
        ofs << _unknownMark << "\t" << _unknownSize << endl;
        identifer.add(_unknownMark, _unknownSize);
      }
      size_t vocabSize = 0;
      for (const auto& item : _ordered)
      {
        ofs << item.first << "\t" << item.second << endl;
        identifer.add(item.first, item.second);
        vocabSize++;
        if (vocabSize == _vocabSize)
        {
          break;
        }
      }
      identifer.Save(binFile);
    }
    else
    {
      Identifer identifer;
      if (_unknownSize && _addUnknown)
      {
        ofs << _unknownMark << "\t" << _unknownSize << endl;
        identifer.add(_unknownMark);
      }
      size_t vocabSize = 0;
      for (const auto& item : _ordered)
      {
        ofs << item.first << "\t" << item.second << endl;
        identifer.add(item.first);
        vocabSize++;
        if (vocabSize == _vocabSize)
        {
          break;
        }
      }
      identifer.Save(binFile);
    }
  }

  void add(string word) 
  {
    _dict[word]++;
    _corpusSize++;
  }

  //----------------must call most_common or min_count or finish after finish add()

  void most_common(size_t topN)
  {
    _ordered = topN >= _dict.size() ? gezi::sort_map_desc(_dict) : gezi::partial_sort_map_desc(_dict, topN);
    _vocabSize = std::min(_ordered.size(), topN);
    if (_addUnknown)
    {
      _unknownSize = _corpusSize - std::accumulate(_ordered.begin(), _ordered.begin() + _vocabSize, (size_t)0, [](size_t accumulator, const WordFreq& x) { return accumulator + x.second; });
    }
    _finished = true;
  }

  void min_count(size_t minCount)
  {
    size_t totalCount = 0;
    for (const auto &item : _dict)
    {
      if (item.second >= minCount)
      {
        _ordered.push_back(item);
        totalCount += item.second;
      }
    }
    std::sort(_ordered.begin(), _ordered.end(), CmpPairBySecondDesc());
    _vocabSize = _ordered.size();
    _unknownSize = _corpusSize - totalCount;
    _finished = true;
  }
  
  void finish()
  {
    if (!_finished)
    {
      if (_mostCommon)
      {
        most_common(_mostCommon);
      }
      else if (_minCount)
      {
        min_count(_minCount);
      }
      else
      {
        _ordered = gezi::sort_map_desc(_dict);
        _vocabSize = _ordered.size();
      }
    }
    _finished = true;
  }

protected:
private:
  unordered_map<string, size_t> _dict;
  
  vector<WordFreq> _ordered;
  size_t _corpusSize = 0;
  size_t _unknownSize = 0;
  size_t _vocabSize = 0;

  bool _addUnknown = true;
  string _unknownMark = "<UNK>";

  size_t _mostCommon;
  size_t _minCount;

  bool _saveCountInfo;
  bool _finished = false;
};

}  //----end of namespace gezi

#endif  //----end of GEZI_NLP__WORD_COUNTER_H_
