/**
 *  ==============================================================================
 *
 *          \file   SharedSegmentor.h
 *
 *        \author   chenghuige
 *
 *          \date   2013-11-03 20:00:50.951127
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef SHARED_SEGMENTOR_H_
#define SHARED_SEGMENTOR_H_

#include "Segmentor.h"
namespace gezi
{

class SharedSegmentor
{
public:

  static Segmentor& get_segmentor()
  {
    return seg_;
  }

  static Segmentor* get_instance()
  {
    return &seg_;
  }

  static bool segmentor_init(const char* dict_dir = "./data/wordseg")
  {
    return true;
  }

  static bool segmentor_init(string dict_dir = "./data/wordseg")
  {
    return true;
  }
  static bool segment(string input, SegHandle& handle, int type = SCW_OUT_WPCOMP | SCW_OUT_PROP)
  {
    return true;
  }
private:
  static Segmentor seg_;
};

} //----end of namespace gezi

#endif  //----end of SHARED_SEGMENTOR_H_
