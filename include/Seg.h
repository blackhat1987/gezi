/**
 *  ==============================================================================
 *
 *          \file   Seg.h
 *
 *        \author   chenghuige
 *
 *          \date   2013-11-04 16:49:24.737228
 *
 *  \Description:  类似word_seg.h 封装一下 可以  Seg::init(), Seg::segment()
 *                 如果Segmentor有更多接口 而Seg没有进行更多封装 可以
 *                 Seg::instance()->segment2()
 *                 另外一种做法是不用Segmentor 在word_dict.cpp 完全实现Segmentor的各种功能
 *                 唯一缺点是需要 seg_clear()显示调用 在最后 不过不调用也没事 程序该结束了
 *                 这是处理全局组件的设计思路 封装的花类似单例模式
 * 
 *                 有Segmentor类的话 单线程可以直接使用一个Segmentor即可
 *  ==============================================================================
 */

#ifndef SEG_H_
#define SEG_H_
#include "Segmentor.h"
namespace gezi {

class Seg
{
public:
  
  static Segmentor* instance()
  {
    return &instance_;
  }

public:
  static Segmentor instance_;
};

}  //----end of namespace gezi

#endif  //----end of SEG_H_
