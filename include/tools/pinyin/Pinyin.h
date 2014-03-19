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
			FREE(_pyNotaion);
		}
		void Load(const string& dictPath)
		{
			_pyNotaion = NLP::Pinyin::IPYFactory::getPYInstance();
			string path = dictPath + "/dyz.dat";
			CHECK(_pyNotaion->loadDyzDict(path.c_str()) == true) << path;
			path = dictPath + "/dict.dat";
			CHECK(_pyNotaion->loadDict(path.c_str()) == true) << path;
			path = dictPath + "/duoyong.dat";
			CHECK(_pyNotaion->loadDYDict(path.c_str()) == true) << path;
			path = dictPath + "/dz_pro.dat";
			CHECK(_pyNotaion->loadBMEDict(path.c_str()) == true) << path;
		}
		string Convert(const string& input)
		{
			vector<string> result;
			bool ret = _pyNotaion->convertToPY(input.c_str(), &result);
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
		NLP::Pinyin::IPYNotation* _pyNotaion;
	};
}  //----end of namespace gezi

#endif  //----end of TOOLS_PINYIN__PINYIN_H_
