/**
 *  ==============================================================================
 *
 *          \file   word_seg.cpp
 *
 *        \author   chenghuige
 *
 *          \date   2013-11-04 09:37:57.728356
 *
 *  \Description:
 *  ==============================================================================
 */

#include "word_seg.h"
#include "Segmentor.h"
#include <string>
using namespace std;
//using namespace gezi;
namespace gezi
{
Segmentor g_seg;
bool seg_init(const string& dict_dir, int type,
        const string& conf_path)
{
  return g_seg.init(dict_dir, type, conf_path);
}

bool segment(const string& input, SegHandle& handle, int type)
{
  return g_seg.segment(input, handle, type);
}
}
