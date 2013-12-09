/**
 *  ==============================================================================
 *
 *          \file   Seg.h
 *
 *        \author   chenghuige
 *
 *          \date   2013-11-04 16:49:24.737228
 *
 *  \Description:  ����word_seg.h ��װһ�� ����  Seg::init(), Seg::segment()
 *                 ���Segmentor�и���ӿ� ��Segû�н��и����װ ����
 *                 Seg::instance()->segment2()
 *                 ����һ�������ǲ���Segmentor ��word_dict.cpp ��ȫʵ��Segmentor�ĸ��ֹ���
 *                 Ψһȱ������Ҫ seg_clear()��ʾ���� ����� ����������Ҳû�� ����ý�����
 *                 ���Ǵ���ȫ����������˼· ��װ�Ļ����Ƶ���ģʽ
 * 
 *                 ��Segmentor��Ļ� ���߳̿���ֱ��ʹ��һ��Segmentor����
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
