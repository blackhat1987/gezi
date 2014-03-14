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
#include <strstream>
using namespace std;
//using namespace gezi;
namespace gezi
{
Segmentor _seg;
int _buf_size = 15000;
SegHandle _handle; //单线程使用 全局buffer

bool seg_init(const string& dict_dir, int type,
        const string& conf_path)
{
  return _seg.init(dict_dir, type, conf_path);
}

bool seg_init2(const string& dict_dir, int type,
	const string& conf_path)
{
	bool ret = _seg.init(dict_dir, type, conf_path);
	CHECK_EQ(ret, true);
	_handle.init(_buf_size);
	return true;
}

bool segment(const string& input, SegHandle& handle, int type)
{
  return _seg.segment(input, handle, type);
}

bool segment(const string& input, vector<string>& vec, SegHandle& handle, int type)
{
	bool ret = _seg.segment(input, handle, type);
	for (int i = 0; i < handle.nresult; i++)
	{
		vec.push_back(handle.tokens[i].buffer);
	}
	return ret;
}

bool segment(const string& input, vector<string>& vec, int type)
{
	SegHandle handle(_buf_size);
	bool ret = _seg.segment(input, handle, type);
	for (int i = 0; i < handle.nresult; i++)
	{
		vec.push_back(handle.tokens[i].buffer);
	}
	return ret;
}

string segment(const string& input, string sep, int type)
{
	SegHandle handle(_buf_size);
	bool ret = _seg.segment(input, handle, type);
	if (!ret || handle.nresult < 1)
	{
		return "";
	}
	std::stringstream ss;
	ss << handle.tokens[0].buffer;
	for (int i = 1; i < handle.nresult; i++)
	{
		ss << sep << handle.tokens[i].buffer;
	}
	return ss.str();
}

bool segment2(const string& input, vector<string>& vec, int type)
{
	bool ret = _seg.segment(input, _handle, type);
	for (int i = 0; i < _handle.nresult; i++)
	{
		vec.push_back(_handle.tokens[i].buffer);
	}
	return ret;
}

string segment2(const string& input, string sep, int type)
{
	bool ret = _seg.segment(input, _handle, type);
	if (!ret || _handle.nresult < 1)
	{
		return "";
	}
	std::stringstream ss;
	ss << _handle.tokens[0].buffer;
	for (int i = 1; i < _handle.nresult; i++)
	{
		ss << sep << _handle.tokens[i].buffer;
	}
	return ss.str();
}

void seg_set_bufsize(int max_len)
{
	_buf_size = max_len;
	_handle.init(_buf_size);
}
}
