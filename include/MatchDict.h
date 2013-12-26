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
namespace gezi
{
//进程级别 多个线程共享一个MatchDict
class MatchDict
{
public:
//  friend class MDSearcher;
  MatchDict()
  :dict_(NULL)
  {
    
  }
  ~MatchDict()
  {
    if (dict_)
    {
      dm_dict_del(dict_);
    }
  }
  bool init(const string& file)
  {
    if (!dict_)
    {
      dict_ = dm_binarydict_load(file.c_str());
    }
    CHECK_NOTNULL(dict_);
    return true;
  }
   
   int search(string text, dm_pack_t* result)
   {
     //return dm_search(dict_, result, text.c_str(), text.length(), DM_OUT_FMM, DM_CHARSET_GB18030);
     return dm_search(dict_, result, text.c_str(), text.length(), DM_OUT_FMM);
   }
   
   //同上 只是改为返回匹配到的结果数目 如果查找失败返回0 成功的话返回匹配数目>=0
   int search_count(string text, dm_pack_t* result)
   {
     //int ret = dm_search(dict_, result, text.c_str(), text.length(), DM_OUT_FMM, DM_CHARSET_GB18030);
     int ret = dm_search(dict_, result, text.c_str(), text.length(), DM_OUT_FMM);
     int count = 0;
     if (ret == 0)
     {
       count = result->ppseg_cnt;
     }
     return count;
   }
   //仅仅查找返回匹配到的count
   int search_count(string text)
   {
     dm_pack_t* result =  dm_pack_create(text.length());
     if (!result)
     {
       return 0;
     }
     int ret = dm_search(dict_, result, text.c_str(), text.length(), DM_OUT_FMM, DM_CHARSET_GB18030);
     int count = 0;
     if (ret == 0)
     {
       count = result->ppseg_cnt;
     }
     dm_pack_del(result);
     return count;
   }
   
   //type 1, 2, 4 or 3(1 and 2)...
   bool has_word(string text, int type = 1)
   {
     return dm_has_word(dict_, type, text.c_str(), text.length(), DM_OUT_FMM, DM_CHARSET_GB18030);
   }
private:
  dm_dict_t* dict_;
};

////线程级别 每个线程一个
//class MDSearcher
//{
//public:
//  int search(string text, dm_pack_t* result)
//  {
//    
//  }
//private:
//  MatchDict* dict_;
//};

}


#endif  //----end of MATCH_DICT_H_
