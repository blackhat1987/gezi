/**
 *  ==============================================================================
 *
 *          \file   tools/content_process.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-03-03 09:59:08.057036
 *
 *  \Description:  主要针对贴吧文本
 *  ==============================================================================
 */

#ifndef TOOLS_CONTENT_PROCESS_H_
#define TOOLS_CONTENT_PROCESS_H_
#include "string_util.h"
#include "reg_util.h"
#include "stl_util.h"
namespace gezi {
	inline string strip_html(string src)
	{
		string pattern = "<a.*class=\"at\">@.{2,20}</a>|(<[^>]*>)|(//[^>]*>)|(&nbsp;)+";
		return reg_remove(src, pattern);
	}

	inline string strip_from(string src)
	{
		src = erase_from(src, "视频来自");
		src = erase_from(src, "图片来自");
		return src;
	}

	inline vector<string> get_pics(string src)
	{
		string picPattern = "<img.*? src=\"(.+?)\".*?>";
		return ufo::reg_search(src, picPattern);
	}

	inline bool contains_pic(string src)
	{
		return !get_pics(src).empty();
	}

	inline vector<string> get_ats(string src)
	{
		string atPattern = "class=\"at\">@(.{2,20})</a>";
		return ufo::reg_search(src, atPattern);
	}
	inline bool contains_at(string src)
	{
		return !get_ats(src).empty();
	}

	inline vector<string> get_urls(string src)
	{
		string urlPattern = "<a.*? href=\"(.+?)\".*?>";
		return ufo::reg_search(src, urlPattern);
	}

	inline bool contains_url(string src)
	{
		return !get_urls(src).empty();
	}

	inline vector<string> get_nums(string src)
	{
		string skipreg_str("([ *,\\.,!\\(\\)]+)|([0-9\\w]{5,20}@[0-9a-zA-Z]+(\\.[a-z,A-Z]{1,4}){1,3})|(@.{10})");
		string reg_str("(([\x81-\xff].)|:|qq|QQ])[ ]*([0-9]){7,30}");

		vector<string> contentVec = reg_split(src, skipreg_str);
		vector<string> resultVec;
		for (string content : contentVec)
		{
			vector<string> tempVec = ufo::reg_search(content, reg_str);
			merge(resultVec, tempVec);
		}
		return resultVec;
	}

	inline bool contains_num(string src)
	{
		string skipreg_str("([ *,\\.,!\\(\\)]+)|([0-9\\w]{5,20}@[0-9a-zA-Z]+(\\.[a-z,A-Z]{1,4}){1,3})|(@.{10})");
		string reg_str("(([\x81-\xff].)|:|qq|QQ])[ ]*([0-9]){7,30}");

		vector<string> vec = reg_split(src, skipreg_str);

		for (string content : vec)
		{
			if (!(ufo::reg_search(content, reg_str).empty()))
			{
				return true;
			}
		}
		return false;
	}

	inline bool contains_any(string src, string type)
	{
		if (type == "pic")
		{
			return contains_pic(src);
		}

		if (type == "url")
		{
			return contains_url(src);
		}

		if (type == "at")
		{
			return contains_at(src);
		}

		if (type == "num")
		{
			return contains_num(src);
		}

		return false;
	}
}  //----end of namespace gezi

#endif  //----end of TOOLS_CONTENT_PROCESS_H_
