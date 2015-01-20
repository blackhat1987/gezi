/**
*  ==============================================================================
*
*          \file   tieba/feature/urate/ImgExtractor.h
*
*        \author   xiesifa
*
*          \date   2014-11-17 09:40:42.778163
*
*  \Description:
*  ==============================================================================
*/

#ifndef TIEBA_FEATURE_URATE__IMG_EXTRACTOR_H_
#define TIEBA_FEATURE_URATE__IMG_EXTRACTOR_H_
#include "tieba/feature/urate/UrateExtractor.h"
namespace gezi {
	namespace tieba {

		class ImgExtractor : public UrateExtractor
		{
		public:
			ImgExtractor(string name = "Img")
				:UrateExtractor(name)
			{

			}

			virtual void extract() override
			{
				ExtractInformation();
				ExtractOCR();
			}
		protected:
		private:
			void ExtractInformation()
			{
				/*图片的基本信息，包括色情打分，游戏色情打分，与作弊图片的相似度
				 *部分特征的取值可能为负的如游戏色情打分
				*/
				VLOG(7) << "extract img feature!";
				//当前帖子的图片特征
				auto& color_rate = info().imginfo.color_rate;
				int maxcolor_rate = ufo::max(color_rate, 0);
				double meancolor_rate = ufo::mean(color_rate, 0);
				
				auto& gameporn_rate = info().imginfo.gameporn_rate;
				int maxgameporn_rate = ufo::max(gameporn_rate, 0);
				double meangameporn_rate = ufo::mean(gameporn_rate, 0);

				auto& porn_rate = info().imginfo.porn_rate;
				int maxporn_rate = ufo::max(porn_rate,0);
				double meanporn_rate = ufo::mean(porn_rate, 0);
		
				auto& simi_rate = info().imginfo.simi_rate;
				int maxsimi_rate = ufo::max(simi_rate, 0);
				double meansimi_rate = ufo::mean(simi_rate, 0);

				auto& text_ratio = info().imginfo.text_ratio;
				int maxtext_ratio = ufo::max(text_ratio, 0);
				double meantext_ratio = ufo::mean(text_ratio, 0);

				auto& textbox_num = info().imginfo.textbox_num;
				int maxtextbox_num = ufo::max(textbox_num, 0);
				double meantextbox_num = ufo::mean(textbox_num, 0);
				//历史帖子的图片特征
				/*auto& color_rates = info().postsInfo.color_rate;
				int maxcolor_rates = ufo::max(color_rates, 0);
				int meancolor_rates = ufo::mean(color_rates, 0);

				auto& gameporn_rates = info().postsInfo.gameporn_rate;
				int maxgameporn_rates = ufo::max(gameporn_rates, 0);
				double meangameporn_rates = ufo::mean(gameporn_rates, 0);

				auto& porn_rates = info().postsInfo.porn_rate;
				int maxporn_rates = ufo::max(porn_rates, 0);
				double meanporn_rates = ufo::mean(porn_rates, 0);*/

				ADD_FEATURE(maxcolor_rate);
				ADD_FEATURE(meancolor_rate);
				ADD_FEATURE(maxgameporn_rate);
				ADD_FEATURE(meangameporn_rate);
				ADD_FEATURE(maxporn_rate);
				ADD_FEATURE(meanporn_rate);
				ADD_FEATURE(maxsimi_rate);
				ADD_FEATURE(meansimi_rate);
				ADD_FEATURE(maxtext_ratio);
				ADD_FEATURE(meantext_ratio);
				ADD_FEATURE(maxtextbox_num);
				ADD_FEATURE(meantextbox_num);
				/*ub_log_pushnotice("maxcolor", "(%i)", maxcolor_rate);
				ub_log_pushnotice("maxgame", "(%i)", maxgameporn_rate);
				ub_log_pushnotice("maxporn_rate", "(%i)", maxporn_rate);
				ub_log_pushnotice("maxsimi_rate", "(%i)", maxsimi_rate);*/
				
			}
			void ExtractOCR()
			{
				int hasocr = 0;
				vector<string>::iterator it;
				auto& ocr_img = info().imginfo.ocr_img;
				for (it = ocr_img.begin(); it != ocr_img.end(); it++)
				if (*it != "")
				{
					hasocr = 1;
					break;
				}			
				ADD_FEATURE(hasocr);
			}
		};

	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_URATE__FORUM_EXTRACTOR_H_
