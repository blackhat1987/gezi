/**
 *  ==============================================================================
 *
 *          \file   word_seg.h
 *
 *        \author   chenghuige
 *
 *          \date   2013-11-03 19:04:42.478788
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef WORD_SEG_H_
#define WORD_SEG_H_
#include <string> 
#include "isegment.h"
#include "Segmentor.h"
namespace gezi
{
using namespace std;
//struct SegHandle;
bool seg_init(const string& dict_dir = "./data/wordseg", int type = 0,
        const string& conf_path = "./conf/scw.conf");

bool segment(const string& input, SegHandle& handle, int type = SCW_OUT_WPCOMP);
}

#endif  //----end of WORD_SEG_H_