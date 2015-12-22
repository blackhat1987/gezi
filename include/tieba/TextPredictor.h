/**
 *  ==============================================================================
 *
 *          \file   TextPredictor.h
 *
 *        \author   chenghuige
 *
 *          \date   2015-03-16 18:33:37.912740
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_TEXT_PREDICTOR_H_
#define TIEBA_TEXT_PREDICTOR_H_
#include "MLCore/TextPredictor.h"
#include "tools/content_process.h"
#include "tieba/tieba_util.h"
#include "string_util.h"
namespace gezi {
	namespace tieba {
		class TextPredictor
		{
		public:
			static string filter_content(string content)
			{
				content = strip_html(content);
				if (content.size() > 100)
				{
					content = gbk_substr(content, 0, 100);
				}
				content = content + " " + normalize_str(content);
				return content;
			}

			static double Predict(string title, string content, const DoubleIdentifer& identifer, const PredictorPtr& predictor,
				int segType = SEG_BASIC, int ngram = 3, int skip = 2, string sep = "\x01")
			{
				title = get_real_title(title);
				title = title + " " + normalize_str(title);
				content = filter_content(content);
				return gezi::TextPredictor::Predict(title, content, identifer, predictor, segType, ngram, skip, sep);
			}

			static double Predict(string content, const DoubleIdentifer& identifer, const PredictorPtr& predictor,
				int segType = SEG_BASIC, int ngram = 3, int skip = 2, string sep = "\x01")
			{
				content = filter_content(content);
				return gezi::TextPredictor::Predict(content, identifer, predictor, segType, ngram, skip, sep);
			}
		protected:
		private:

		};
	}
}  //----end of namespace gezi

#endif  //----end of TIEBA_TEXT_PREDICTOR_H_
