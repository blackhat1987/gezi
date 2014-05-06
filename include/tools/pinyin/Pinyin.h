/**
 *  ==============================================================================
 *
 *          \file   tools/pinyin/Pinyin.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-03-15 11:25:42.097520
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TOOLS_PINYIN__PINYIN_H_
#define TOOLS_PINYIN__PINYIN_H_
#include "tools/pinyin/IPYFactory.h"
#include "tools/pinyin/IPYNotation.h"
#include "common_util.h"
namespace gezi {

	class Pinyin
	{
	public:
		virtual ~Pinyin()
		{
			FREE(PyNotaion());
		}
		static void Load(string dictPath)
		{
			PyNotaion() = NLP::Pinyin::IPYFactory::getPYInstance();
			string path = dictPath + "/dyz.dat";
			CHECK(PyNotaion()->loadDyzDict(path.c_str()) == true) << path;
			path = dictPath + "/dict.dat";
			CHECK(PyNotaion()->loadDict(path.c_str()) == true) << path;
			path = dictPath + "/duoyong.dat";
			CHECK(PyNotaion()->loadDYDict(path.c_str()) == true) << path;
			path = dictPath + "/dz_pro.dat";
			CHECK(PyNotaion()->loadBMEDict(path.c_str()) == true) << path;
		}
		static string Convert(string input)
		{
			vector<string> result;
			bool ret = PyNotaion()->convertToPY(input.c_str(), &result);
			PVEC(result);
			if (ret && !result.empty())
			{
				return result[0];
			}
			else
			{
				return "";
			}
		}
	protected:
	private:
		static NLP::Pinyin::IPYNotation*& PyNotaion()
		{
			static NLP::Pinyin::IPYNotation* _pyNotaion = NULL;
			return _pyNotaion;
		}
	};
}  //----end of namespace gezi

#endif  //----end of TOOLS_PINYIN__PINYIN_H_
