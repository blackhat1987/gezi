/**
 *  ==============================================================================
 *
 *          \file   SegDict.h
 *
 *        \author   chenghuige
 *
 *          \date   2013-11-03 20:09:02.803205
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef SEG_DICT_H_
#define SEG_DICT_H_

namespace gezi {

#ifndef SEGMENTOR_H_
#define SEGMENTOR_H_
#include "scwdef.h"
#include "property.h"
#include "isegment.h"
#include "tagdict.h"
#include "ul_dict.h"
#include "log_util.h"
//#include "common_util.h"

namespace gezi
{
//线程级别 每个线程一个Segmentor实例
class SegDict
{
public:

  SegDict()
  {

  }

  ~SegDict()
  {
    if (use_tag_)
    {
      tag_close();
    }
    //---关闭分词字典
    if (pwdict_)
      scw_destroy_worddict(pwdict_);
    //---关闭用户需要内部切分字典
    if (split_dict_)
      ds_del(split_dict_);
  }

  bool init(const string& data_dir, bool use_tag = false)
  {
    return init(data_dir.c_str(), use_tag);
  }

  bool init(const char* data_dir, bool use_tag = false)
  {
    use_tag_ = use_tag;
    int ret = -1;
    //--------------打开分词字典
    {
      if (pgconf != NULL)
      {
        scw_destroy_conf(pgconf);
        pgconf = NULL;
      }
      char dict_path[2048];
      sprintf(dict_path, "%s/%s/%s", data_dir, "worddict", "scw.conf");
      pgconf = scw_load_conf(dict_path);
      CHECK_NOTNULL(pgconf);

      pwdict_ = scw_load_worddict(data);
      CHECK_NOTNULL(pwdict_);
    }

    if (use_tag_)
    { //--------------启动标注
      char tag_dict_path[2048];
      sprintf(tag_dict_path, "%s/%s", data_dir, "tagdict");
      ret = tag_open(tag_dict_path);
      CHECK_EQ(ret, 0);
    }
    {
      //---------------尝试打开need split字典，如果不存在或者打开出错就不使用
      char user_dict_path[2048];
      sprintf(user_dict_path, "%s/%s", data_dir, "need_split");
      split_dict_ = ds_load(user_dict_path, "need_split");
      if (!split_dict_)
      {
        LOG_WARNING("Do not use user defined split dictionary, not find %s", user_dict_path);
      }
    }
    return true;
  }

  //TODO
  void seg()
  {
    
  }

private:
  //分词buffer大小,不能开辟太大因为分词scw_create_out的时候会占过多内存
  const int SEG_BUFF_SIZE = 2048; //50*1024
  scw_worddict_t * pwdict_;
  Sdict_search* split_dict_; //自定义不需要在分词字典中去除内部再切分的字典资源 
  //这种如果设计static就没意义 因为析够问题
  //你需要另外一个类 帮你析够
  bool use_tag_ ; //是否使用tag词性标注
};

} //----end of namespace gezi

}  //----end of namespace gezi

#endif  //----end of SEG_DICT_H_
