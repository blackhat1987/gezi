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
#include <vector>
#include "isegment.h"
#include "Segmentor.h"
namespace gezi
{
	using std::string;
	using std::vector;
//struct SegHandle;
bool seg_init(const string& dict_dir = "./data/wordseg", int type = 0,
        const string& conf_path = "./conf/scw.conf");

//单线程的初始化
bool seg_init2(const string& dict_dir = "./data/wordseg", int type = 0,
	const string& conf_path = "./conf/scw.conf");

//线程安全
bool segment(const string& input, SegHandle& handle, int type = SCW_OUT_WPCOMP);

//快捷接口 线程安全
bool segment(const string& input, vector<string>& result, int type = SCW_OUT_WPCOMP);

string segment(const string& input, string sep = "\t", int type = SCW_OUT_WPCOMP);

//下面两个更快捷的方式 默认单线程方式 也就是复用外部一个公用空间handle 保证单线程速度 
bool segment2(const string& input, vector<string>& result, int type = SCW_OUT_WPCOMP);

string segment2(const string& input, string sep = "\t", int type = SCW_OUT_WPCOMP);

void seg_set_bufsize(int max_len);

}

#endif  //----end of WORD_SEG_H_
