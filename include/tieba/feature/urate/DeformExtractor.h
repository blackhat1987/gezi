/**
 *  ==============================================================================
 *
 *          \file   tieba/feature/urate/DeformExtractor.h
 *
 *        \author   chenghuige
 *
 *          \date   2015-08-07 11:03:53.079663
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef GEZI_TIEBA_FEATURE_URATE__DEFORM_EXTRACTOR_H_
#define GEZI_TIEBA_FEATURE_URATE__DEFORM_EXTRACTOR_H_

#include "tieba/feature/urate/UrateExtractor.h"
#include "deformation-procs/deformation_text.h"

namespace gezi {
	namespace tieba {
		class DeformExtractor : public UrateExtractor
		{
		public:
			DeformExtractor(const string& name = "Deform")
				: UrateExtractor(name)
			{

			}

			virtual void init()
			{
				info().ExtractNormalizedTitles();
				info().ExtractNormalizedContents();
			}

			int NumDeforms(string str)
			{
				if (str.empty())
				{
					return 0;
				}
				vector<trans_unit> vec;
				string fixedStr = deformation().line_procs(str, vec);
				if (vec.size() > 0)
				{
					PVAL(str);
					PVAL(fixedStr);
					PrintVec4(vec, src_word, des_word, trans_pro, trans_ss);
				}
				return vec.size();
			}

			virtual void extract() override
			{
				const auto& titles = info().normalizedTitles;
				const auto& contents = info().normalizedContents;

				int nowNumTitleDeforms = NumDeforms(titles[0]);
				string content = gezi::gbk_substr(contents[0], 0, 20);
				int nowNumContentDeforms = NumDeforms(content);

				int nowNumDeforms = nowNumTitleDeforms + nowNumContentDeforms;

				ADD_FEATURE(nowNumTitleDeforms);
				ADD_FEATURE(nowNumContentDeforms);
				ADD_FEATURE(nowNumDeforms);

				//int numTitleDeforms = nowNumTitleDeforms;
				//int numContentDeforms = nowNumContentDeforms;
				//int len = titles.size();

				//for (size_t i = 1; i < len; i++)
				//{
				//	numTitleDeforms += NumDeforms(titles[i]);
				//	numContentDeforms += NumDeforms(contents[i]);
				//}
				//int numDeforms = numTitleDeforms + numContentDeforms;

				//ADD_FEATURE(numTitleDeforms);
				//ADD_FEATURE(numContentDeforms);
				//ADD_FEATURE(numDeforms);

				//double titleDeformRatio = numTitleDeforms / (double)len;
				//double contentDeformRatio = numContentDeforms / (double)len;
				//double deformRatio = numDeforms / (double)len;
				//ADD_FEATURE(titleDeformRatio);
				//ADD_FEATURE(contentDeformRatio);
				//ADD_FEATURE(deformRatio);
			}
		protected:
		private:
			static deformation_text& deformation()
			{
				static thread_local deformation_text _dt =
					([&]() {
					deform_conf::init("deform.conf", "./conf");
					wordseg::getInstance();
					deform_dict::getInstance();
					deformation_text dt;
					return dt;
				})();
				return _dt;
			}
		};
	} //----end of namespace tieba 
}  //----end of namespace gezi

#endif  //----end of GEZI_TIEBA_FEATURE_URATE__DEFORM_EXTRACTOR_H_
