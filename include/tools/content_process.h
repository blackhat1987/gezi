/**
 *  ==============================================================================
 *
 *          \file   tools/content_process.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-03-03 09:59:08.057036
 *
 *  \Description:  主要针对贴吧文本 @TODO 应该是content_parse
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
		src = erase_from(src, "内容来自");
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

	inline vector<string> get_videos(string src)
	{
		string videoPattern = "<embed.*? src=\"(.+?)\".*?>";
		return ufo::reg_search(src, videoPattern);
	}

	inline bool contains_video(string src)
	{
		return !get_videos(src).empty();
	}

	//@FIXME why R"abc@3" fail with @..? raw string bug? raw string似乎不支持@
	inline vector<string> get_emails(string src)
	{
		//string emailPattern = R"[a-zA-Z0-9]+@[a-zA-Z0-9\-\_]{2,}\.(com|cn|tk|biz|org|edu|net|tw|us|info|gov)";
		string emailPattern = "([a-zA-Z0-9]+@[a-zA-Z0-9\\-\\_]{2,}\\.(com|cn|tk|biz|org|edu|net|tw|us|info|gov))";
		return ufo::reg_search(src, emailPattern);
	}

	inline bool contains_emails(string src)
	{
		return !get_emails(src).empty();
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
	{ //@TODO 验证是否ok 和配置文件完全一样 不需要Raw string?
		//string skipRegStr("([ *,\\.,!\\(\\)]+)|([0-9\\w]{5,20}@[0-9a-zA-Z]+(\\.[a-z,A-Z]{1,4}){1,3})|(@.{10})");
		//string skipRegStr("([,\\.,!]+)|([0-9\\w]{5,20}@[0-9a-zA-Z]+(\\.[a-z,A-Z]{1,4}){1,3})|(@.{10})");
		string skipRegStr("[0-9\\w]{5,20}@[0-9a-zA-Z]+(\\.[a-z,A-Z]{1,4}){1,3}");
		string regStr("(^|[\\x81-\\xff]|:|q|qq|Q|QQ|\\(|\\[)[ ]*([0-9]{7,15})");
		int matchIndex = 2;
		PVAL(skipRegStr);
		PVAL(regStr);

		svec contentVec = reg_split(src, skipRegStr);
		PVEC(contentVec);
		//PVEC(ufo::reg_search(src, skipRegStr));
		vector<string> resultVec;
		for (string content : contentVec)
		{
			vector<string> tempVec = ufo::reg_search(content, regStr, matchIndex);
			PVEC(tempVec);
			merge(resultVec, tempVec);
			PVEC(resultVec);
		}
		return resultVec;
	}

	inline bool contains_num(string src)
	{//@TODO 使用raw string
		//string skipRegStr("([ *,\\.,!\\(\\)]+)|([0-9\\w]{5,20}@[0-9a-zA-Z]+(\\.[a-z,A-Z]{1,4}){1,3})|(@.{10})");
		string skipRegStr("([,\\.,!]+)|([0-9\\w]{5,20}@[0-9a-zA-Z]+(\\.[a-z,A-Z]{1,4}){1,3})|(@.{10})");
		string regStr("(^|[\\x81-\\xff]|:|q|qq|Q|QQ|\\(|\\[)[ ]*([0-9]{7,15})");
		int matchIndex = 2;
		PVAL(skipRegStr);
		PVAL(regStr);

		svec vec = reg_split(src, skipRegStr);
		for (string content : vec)
		{
			if (!(ufo::reg_search(content, regStr, matchIndex).empty()))
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
