/**
 *  ==============================================================================
 *
 *          \file   ChNormalizer.h
 *
 *        \author   chenghuige
 *
 *          \date   2015-07-25 11:41:11.382312
 *
 *  \Description:   Normalize text or query using ccode
 *									Assume gbk encoding!
 *  ==============================================================================
 */

#ifndef GEZI_CH_NORMALIZER_H_
#define GEZI_CH_NORMALIZER_H_

#include "ul_ccode.h"
#include "string_def.h"
#include <glog/logging.h>
namespace gezi {

	class ChNormalizer
	{
	public:
		static void Load(string dir = "./data/ccode")
		{
			static bool ret = ul_ccode_load((char *)dir.c_str());
			CHECK_EQ(ret, 0) << "Ccode loading error, dir: " << dir;
		}

		static void Init(string dir = "./data/ccode")
		{
			Load(dir);
		}

		static string ToLower(string src)
		{
			vector<char> dest(src.size() + 1, 0);
			ul_trans2lower((char *)src.c_str(), &dest[0]);
			return string(&dest[0]);
		}

		static string ToSimplified(string src)
		{
			vector<char> dest(src.size() + 1, 0);
			if (ul_trans2gb((char *)src.c_str(), &dest[0], CODETYPE_GB) < 0)
				return src;
			return string(&dest[0]);
		}

		static string ToHalf(string src)
		{
			vector<char> dest(src.size() + 1, 0);
			ul_trans2bj_ext((char *)src.c_str(), &dest[0]);
			return string(&dest[0]);
		}

		//utf8的话 需要CODETYPE_UTF8 另外buffer可能需要更大 @TODO
		static string Normalize(string src, bool toLower = true, bool toSimplified = true, bool toHalf = true)
		{
			vector<char> temp(src.size() + 1, 0);
			char* dest = &temp[0];
			if (toSimplified)
			{
				if (ul_trans2gb((char *)src.c_str(), dest, CODETYPE_GB) < 0)
				{
					if (toHalf)
						ul_trans2bj_ext((char *)src.c_str(), dest);
					if (toLower)
						ul_trans2lower(dest, dest);
				}
				else
				{
					if (toHalf)
						ul_trans2bj_ext(dest, dest);
					if (toLower)
						ul_trans2lower(dest, dest);
				}
			}
			else
			{
				if (toHalf)
					ul_trans2bj_ext((char *)src.c_str(), dest);
				if (toLower)
					ul_trans2lower(dest, dest);
			}
			return string(dest);
		}
	protected:
	private:

	};
	class ThreadChNormalizer
	{
	public:
		ThreadChNormalizer()
		{
			ul_ccode_conv_open();
		}
		~ThreadChNormalizer()
		{
			ul_ccode_conv_close();
		}
	};
}  //----end of namespace gezi

#endif  //----end of GEZI_CH_NORMALIZER_H_
