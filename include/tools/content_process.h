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
namespace gezi {
	inline string strip_html(string src)
	{
		string pattern = "<a.*class=\"at\">@.{2,20}</a>|(<[^>]*>)|(//[^>]*>)|(&nbsp;)+";
		return reg_remove(src, pattern);
	}

	inline string strip_from(string src)
	{
		erase_from(src, "视频来自");
		erase_from(src, "图片来自");
	}

	inline bool contains_pic(string src)
	{
		string picPattern = "<img.*? src=\"(.+?)\".*?>";
		vector<string> pics = ufo::reg_search(src, picPattern);
		return !pics.empty();
	}

	inline bool contains_at(string src)
	{
		string atPattern = "class=\"at\">@(.{2,20})</a>";
		return !(ufo::reg_search(src, atPattern)).empty();
	}

	inline bool contains_url(string src)
	{
		string urlPattern = "<a.*? href=\"(.+?)\".*?>";
		vector<string> urls = ufo::reg_search(src, urlPattern);
		return !urls.empty();
	}

	//@TODO check
	inline bool contains_general_url(string src)
	{
		src = strip_html(src);
		return gezi::contains(src, "http://");
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
