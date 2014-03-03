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
//�̼߳��� ÿ���߳�һ��Segmentorʵ��
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
    //---�رշִ��ֵ�
    if (pwdict_)
      scw_destroy_worddict(pwdict_);
    //---�ر��û���Ҫ�ڲ��з��ֵ�
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
    //--------------�򿪷ִ��ֵ�
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
    { //--------------������ע
      char tag_dict_path[2048];
      sprintf(tag_dict_path, "%s/%s", data_dir, "tagdict");
      ret = tag_open(tag_dict_path);
      CHECK_EQ(ret, 0);
    }
    {
      //---------------���Դ�need split�ֵ䣬��������ڻ��ߴ򿪳���Ͳ�ʹ��
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
  //�ִ�buffer��С,���ܿ���̫����Ϊ�ִ�scw_create_out��ʱ���ռ�����ڴ�
  const int SEG_BUFF_SIZE = 2048; //50*1024
  scw_worddict_t * pwdict_;
  Sdict_search* split_dict_; //�Զ��岻��Ҫ�ڷִ��ֵ���ȥ���ڲ����зֵ��ֵ���Դ 
  //����������static��û���� ��Ϊ��������
  //����Ҫ����һ���� ��������
  bool use_tag_ ; //�Ƿ�ʹ��tag���Ա�ע
};

} //----end of namespace gezi

}  //----end of namespace gezi

#endif  //----end of SEG_DICT_H_
