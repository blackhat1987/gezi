/**
 *  ==============================================================================
 *
 *          \file   MatchDict.h
 *
 *        \author   chenghuige
 *
 *          \date   2013-11-01 16:41:46.192610
 *
 *  \Description:    封装dictmatch 适用于黑白名单 即多模式匹配 模式建立词典
 *                   对于新来文本查询匹配模式
 *  ==============================================================================
 */

#ifndef MATCH_DICT_H_
#define MATCH_DICT_H_
#include "ul_dictmatch.h"
#include "log_util.h"
#include <vector>
#include <string>
#include <set>
#include <map>
namespace gezi {
  using std::vector;
  using std::string;
  using std::pair;
  using std::set;
  using std::map;

  static const int MATCH_DICT_SEARCH_ALL = DM_OUT_ALL;
  static const int MATCH_DICT_SEARCH_LONGEST = DM_OUT_FMM;

  //进程级别 多个线程共享一个MatchDict 如果是高版本gcc支持thread local也可以直接search_count多线程使用无代价
  class MatchDict
  {
  public:
    friend class MatchSearcher;
    MatchDict()
      :_dict(NULL)
    {

    }

    MatchDict(string file)
      :_dict(NULL)
    {
      init(file);
    }

    ~MatchDict()
    {
      if (_dict)
      {
        dm_dict_del(_dict);
      }
    }

    struct Node
    {
      string word;
      int offset;
      //py wrap will ignore length..  FIXME! WARNIN!
      int length;
      int property;

      //for py auto wrap for vector
      bool operator == (const Node& other) const
      {
        return offset == other.offset;
      }
    };

    bool init(string file)
    {
      if (!_dict)
      {
        _dict = dm_binarydict_load(file.c_str());
      }
      CHECK_NOTNULL(_dict);
      return true;
    }

    bool Load(string file)
    {
      return init(file);
    }

    bool load(string file)
    {
      return init(file);
    }

    int search(string text, dm_pack_t* result, int strategy=MATCH_DICT_SEARCH_LONGEST)
    {
      //return dm_search(dict_, result, text.c_str(), text.length(), DM_OUT_FMM, DM_CHARSET_GB18030);
      return dm_search(_dict, result, text.c_str(), text.length(), strategy);
    }

    //同上 只是改为返回匹配到的结果数目 如果查找失败返回0 成功的话返回匹配数目>=0
    int search_count(string text, dm_pack_t* result, int strategy = MATCH_DICT_SEARCH_LONGEST)
    {
      //int ret = dm_search(dict_, result, text.c_str(), text.length(), DM_OUT_FMM, DM_CHARSET_GB18030);
      int ret = dm_search(_dict, result, text.c_str(), text.length(), strategy);
      int count = 0;
      if (ret == 0)
      {
        count = result->ppseg_cnt;
      }
      return count;
    }

    int search_count(string text, int strategy = MATCH_DICT_SEARCH_LONGEST)
    {
      return search_count(text, dm_pack(), strategy);
    }

    vector<Node> search(string text, int strategy = MATCH_DICT_SEARCH_LONGEST)
    {
      vector<Node> result;
      int ret = dm_search(_dict, dm_pack(), text.c_str(), text.length(), strategy, DM_CHARSET_GB18030);
      if (ret != 0)
      {
        return result;
      }
      int nresult = dm_pack()->ppseg_cnt;
      for (int i = 0; i < nresult; i++)
      {
        dm_lemma_t* lm = dm_pack()->ppseg[i];
        result.emplace_back(Node{ lm->pstr, dm_pack()->poff[i], lm->len, lm->prop });
      }
      return result;
    }

    set<string> search_words(string text, int strategy = MATCH_DICT_SEARCH_LONGEST)
    {
      set<string> result;
      int ret = dm_search(_dict, dm_pack(), text.c_str(), text.length(), strategy, DM_CHARSET_GB18030);
      if (ret != 0)
      {
        return result;
      }
      int nresult = dm_pack()->ppseg_cnt;
      for (int i = 0; i < nresult; i++)
      {
        dm_lemma_t* lm = dm_pack()->ppseg[i];
        result.insert(lm->pstr);
      }
      return result;
    }

    vector<string> search_words_byseq(string text, int strategy = MATCH_DICT_SEARCH_LONGEST)
    {
      vector<string> result;
      set<string> set_;
      int ret = dm_search(_dict, dm_pack(), text.c_str(), text.length(), strategy, DM_CHARSET_GB18030);
      if (ret != 0)
      {
        return result;
      }
      int nresult = dm_pack()->ppseg_cnt;
      for (int i = 0; i < nresult; i++)
      {
        dm_lemma_t* lm = dm_pack()->ppseg[i];
        string word = lm->pstr;
        auto added = set_.insert(word);
        if (added.second)
        {
          result.push_back(word);
        }
      }
      return result;
    }

    map<string, int> search_properties(string text, int strategy = MATCH_DICT_SEARCH_LONGEST, bool count_property=false)
    {
      map<string, int> result;
      int ret = dm_search(_dict, dm_pack(), text.c_str(), text.length(), strategy, DM_CHARSET_GB18030);
      if (ret != 0)
      {
        return result;
      }
      int nresult = dm_pack()->ppseg_cnt;
      for (int i = 0; i < nresult; i++)
      {
        dm_lemma_t* lm = dm_pack()->ppseg[i];
        if (!count_property)
        {
          result[lm->pstr] = lm->prop;
        }
        else
        {
          result[lm->pstr] += 1;
        }
      }
      return result;
    }

    ////仅仅查找返回匹配到的count
    int SearchCount(string text, int strategy = MATCH_DICT_SEARCH_LONGEST)
    {
      dm_pack_t* result = dm_pack_create(text.length());
      if (!result)
      {
        return 0;
      }
      int ret = dm_search(_dict, result, text.c_str(), text.length(), strategy, DM_CHARSET_GB18030);
      int count = 0;
      if (ret == 0)
      {
        count = result->ppseg_cnt;
      }
      dm_pack_del(result);
      return count;
    }
    //type 1, 2, 4 or 3(1 and 2)...
    bool has_word(string text, int type = 1, int strategy = MATCH_DICT_SEARCH_LONGEST)
    {
      return dm_has_word(_dict, type, text.c_str(), text.length(), strategy, DM_CHARSET_GB18030);
    }

    static void set_dm_pack(int maxMatchCount)
    {
      dm_pack(maxMatchCount);
    }
  public:
    static dm_pack_t* dm_pack(int maxMatchCount = 100000)
    {//local 线程安全
      static thread_local dm_pack_t* _result = NULL;
      if (_result == NULL)
      {
        VLOG(3) << "creating dm pack";
        _result = dm_pack_create(maxMatchCount);
      }
      return _result;
    }

    static void free_dm_pack()
    {
      dm_pack_t* buff = dm_pack();
      if (buff)
      {
        VLOG(3) << "del dm pack";
        dm_pack_del(buff);
      }
    }
  private:
    dm_dict_t* _dict;
  };

  ////线程级别 每个线程一个
  class MatchSearcher
  {
  public:
    MatchSearcher(MatchDict* dict, int maxMatchCount = 1000)
      :_dict(dict), _maxMatchCount(maxMatchCount)
    {
      _result = dm_pack_create(_maxMatchCount);
    }

    MatchSearcher(const MatchDict& dict, int maxMatchCount = 1000)
      :_dict(&dict), _maxMatchCount(maxMatchCount)
    {
      _result = dm_pack_create(_maxMatchCount);
    }

    int search_count(const MatchDict& dict, string text)
    {
      return dict.search_count(text, _result);
    }

    int search_count(MatchDict* dict, string text)
    {
      return dict->search_count(text, _result);
    }

    dm_pack_t* search(const MatchDict& dict, string text)
    {
      dict.search(text, _result);
      return _result;
    }

    dm_pack_t* search(MatchDict* dict, string text)
    {
      dict->search(text, _result);
      return _result;
    }

    int search_count(string text)
    {
      return _dict->search_count(text, _result);
    }

    dm_pack_t* search(string text)
    {
      _dict->search(text, _result);
      return _result;
    }

    dm_pack_t* result()
    {
      return _result;
    }

    bool has_word(string text)
    { 
      return _dict->has_word(text);
    }

    int max_match_count()
    {
      return _maxMatchCount;
    }

  private:
    MatchDict* _dict =  NULL; 
    dm_pack_t* _result = NULL;//可以用thread_local变成static 线程内部共享 放到MatchDict中 暂时还保持这种设计
    int _maxMatchCount = 1000; //最多可能匹配的个数
  };
}

#endif  //----end of MATCH_DICT_H_
