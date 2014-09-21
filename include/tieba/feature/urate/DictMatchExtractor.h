/**
 *  ==============================================================================
 *
 *          \file   tieba/feature/urate/DictMatchExtractor.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-19 14:27:54.443591
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_FEATURE_URATE__DICT_MATCH_EXTRACTOR_H_
#define TIEBA_FEATURE_URATE__DICT_MATCH_EXTRACTOR_H_
#include "tieba/feature/urate/UrateExtractor.h"
#include "MatchDict.h"
#include "RegexSearcher.h"

namespace gezi {
	namespace tieba {

		class DictMatchExtractor : public UrateExtractor
		{
		public:

			DictMatchExtractor(string name = "DictMatch")
				: UrateExtractor(name)
			{
				_maxMatchCount = 1000;
				PSCONF(_maxMatchCount, name);
				//_result = dm_pack_create(_maxMatchCount);
				_result = MatchDict::dm_pack(_maxMatchCount);
				CHECK_NOTNULL(_result);
			}

			virtual ~DictMatchExtractor()
			{ //使用thread local的buffer 可以不做dm_pack_del 因为只有程序结束才需要 
			/*	if (_result)
				{
					dm_pack_del(_result);
				}*/
			}

			//这样写也ok 将Init放到构造函数 避免外部调用 这样等于资源就在内部了
		/*	static void Init()
			{
				static bool _isInited = false;
				if (!_isInited)
				{
					string section = "DictMatch";
					{
						string black_file = "./data/wordlist/black.dm";
						SCONF(black_file);
						_blackDict.init(black_file);
					}
					{
						string gray_file = "./data/wordlist/gray.dm";
						SCONF(gray_file);
						_grayDict.init(gray_file);
					}
					_isInited = true;
				}
			}*/

			bool ContainsBlack(string& content)
			{
				return _blackDict.search_count(content, _result) > 0;
			}

			bool ContainsGray(string& content)
			{
				return _grayDict.search_count(content, _result) > 0;
			}

			bool ContainsWhite(string& content)
			{
				return _whiteDict.search_count(content, _result) > 0;
			}

			bool containsBlackPattern(wstring& content)
			{
				_blackRegSearcher.has_match(content);
			}

			bool ContainsContentBlackPattern(wstring& content)
			{
				_contentBlackRegSearcher.has_match(content);
			}

			bool ContainsGrayPattern(wstring& content)
			{
				_grayRegSearcher.has_match(content);
			}

			int BlackCount(string& content)
			{
				return _blackDict.search_count(content, _result);
			}

			int GrayCount(string& content)
			{
				return _grayDict.search_count(content, _result);
			}

			void CalcTitleCounts(const svec& vec, int& m, int &n, int& x, int& y)
			{
				bool first = true;

				foreach(string item, vec)
				{
					wstring witem = str_to_wstr(item);
					if (ContainsBlack(item) || containsBlackPattern(witem))
					{
#ifndef NDEBUG
						PVAL(item);
						PVAL(containsBlackPattern(witem));
						PVAL(_result->ppseg_cnt);
						if (_result->ppseg_cnt)
						{
							for (int i = 0; i < _result->ppseg_cnt; i++)
							{
								PVAL_(_result->ppseg[i]->pstr, STRING(i));
							}
						}
#endif
						if (first)
						{
							x++;
						}
						m++;
					}
					if (ContainsGray(item) || ContainsGrayPattern(witem))
					{
#ifndef NDEBUG
						PVAL(item);
						PVAL(_result->ppseg_cnt);
						if (_result->ppseg_cnt)
						{
							for (int i = 0; i < _result->ppseg_cnt; i++)
							{
								PVAL_(_result->ppseg[i]->pstr, STRING(i));
							}
						}
#endif
						if (first)
						{
							y++;
						}
						n++;
					}

					if (first)
					{
						first = false;
					}

				}
			}

			void CalcContentCounts(const svec& vec, int& m, int &n, int& x, int& y)
			{
				bool first = true;

				foreach(string item, vec)
				{
					wstring witem = str_to_wstr(item);
					int b = BlackCount(item);
#ifndef NDEBUG
					PVAL(item);
					PVAL(_result->ppseg_cnt);
					if (_result->ppseg_cnt)
					{
						for (int i = 0; i < _result->ppseg_cnt; i++)
						{
							PVAL_(_result->ppseg[i]->pstr, STRING(i));
						}
					}
					PVAL(b);
#endif  
					int g = GrayCount(item);
#ifndef NDEBUG
					PVAL(item);
					PVAL(_result->ppseg_cnt);
					if (_result->ppseg_cnt)
					{
						for (int i = 0; i < _result->ppseg_cnt; i++)
						{
							PVAL_(_result->ppseg[i]->pstr, STRING(i));
						}
					}
					PVAL(g);
#endif  
					b += (int)ContainsContentBlackPattern(witem);
					PVAL(b);
					g += (int)ContainsGrayPattern(witem);
					PVAL(g);
					if (first)
					{
						x = b;
						y = g;
						first = false;
					}
					m += b;
					n += g;
				}
			}

			void FilterContents(svec& contents)
			{

				for (string& content : contents)
				{
					if (content.size() > 200)
					{
						content = gbk_substr(content, 0, 100) + gbk_substr(content, content.size() - 100);
					}
				}
			}

			virtual void init() override
			{
				info().ExtractHtmlFilteredContents();
				info().ExtractNormalizedContents();
				info().ExtractNormalizedTitles();
			}

			virtual void extract() override
			{
				auto contents = info().htmlFilteredContents;
				FilterContents(contents);
				PVEC(contents);
				auto normedContents = info().replyNormalizedContents;
				FilterContents(normedContents);
				PVEC(normedContents);
				auto& titles = info().postsInfo.titles;
				PVEC(titles);
				auto& normedTitles = info().normalizedTitles;
				PVEC(normedTitles);

				int white_title_count = 0;

				for (string title : titles)
				{
					if (ContainsWhite(title))
					{
						white_title_count++;
					}
				}

				double white_ratio = white_title_count / (double)titles.size();
				/*	if (white_ratio >= 0.2)
					{
					dao()->setWhiteTitle();
					}*/
				add(white_ratio, "whiteTitleRatio");

				//black gray 1 means ori 2 means normed
				int bt1 = 0, bt2 = 0, bc1 = 0, bc2 = 0;
				int gt1 = 0, gt2 = 0, gc1 = 0, gc2 = 0;
				//int min_num = FLAGS_min_posts_num / 2;
				int minPostsNum = 10;
				PSCONF(minPostsNum, "Global");
				int min_num = minPostsNum / 2;
				int now_bt1 = 0, now_bt2 = 0, now_bc1 = 0, now_bc2 = 0;
				int now_gt1 = 0, now_gt2 = 0, now_gc1 = 0, now_gc2 = 0;

				CalcTitleCounts(titles, bt1, gt1, now_bt1, now_gt1);
				CalcTitleCounts(normedTitles, bt2, gt2, now_bt2, now_gt2);
				CalcContentCounts(contents, bc1, gc1, now_bc1, now_gc1);
				CalcContentCounts(normedContents, bc2, gc2, now_bc2, now_gc2);
				PVAL(bt1);
				PVAL(gt1);
				PVAL(bt2);
				PVAL(gt2);
				PVAL(bc1);
				PVAL(gc1);
				PVAL(bc2);
				PVAL(gc2);

				add(now_bt1, "nowBlackTitleCount");
				add(now_gt1, "nowGrayTitleCount");
				add(now_bt2, "NowBlackTitleCount2");
				add(now_gt2, "NowGrayTitleCount2");

				//    add(now_bc1, "NowBlackContentCount");
				//    add(now_gc1, "NowGrayContentCount");
				//    add(now_bc2, "NowBlackContentCount2");
				//    add(now_gc2, "NowGrayContentCount2");
				{
					auto& contents = info().originalPostsInfo.contents;
					add(now_bc1 / (1.0 + contents[0].length()), "nowBlackContentCount");
					add(now_gc1 / (1.0 + contents[0].length()), "nowGrayContentCount");
					add(now_bc2 / (1.0 + contents[0].length()), "mowBlackContentCount2");
					add(now_gc2 / (1.0 + contents[0].length()), "mowGrayContentCount2");
				}

				min_num = std::max(min_num, (int)contents.size());
				if (white_ratio >= 0.4)
				{
					min_num *= 4;
				}
				PVAL(bt1);
				PVAL(min_num);
				add(bt1 / (double)min_num, "blackTitleRatio");
				add(gt1 / (double)min_num, "grayTitleRatio");
				add(bt2 / (double)min_num, "blackTitleRatio2");
				add(gt2 / (double)min_num, "grayTitleRatio2");

				//如果还是相似内容 或者命中某黑词误伤大 考虑引入文本长度 @TODO
				//    add(bc1 / (double) min_num, "BlackContentPerPost");
				//    add(gc1 / (double) min_num, "GrayContentPerPost");
				//    add(bc2 / (double) min_num, "BlackContentPerPost2");
				//    add(gc2 / (double) min_num, "GrayContentPerPost2");
				/*	double tlen = 1.0 + dao()->history2()["TextLengthMean"];
					add(bc1 / tlen, "BlackContentPerPost");
					add(gc1 / tlen, "GrayContentPerPost");
					add(bc2 / tlen, "BlackContentPerPost2");
					add(gc2 / tlen, "GrayContentPerPost2");*/

				{
					//由于用户可能对词修改规避策略 所以越大越好 
					int base = bt2 + gt2;
					double val = base == 0 || (bt1 + gt1) > base ? 1 : (bt1 + gt1 + 0.1) / (base + 0.1);
					add(val, "titleModifyRatio");
				}

				{
					int base = bc2 + gc2;
					double val = base == 0 || bc2 + gc2 > base ? 1 : (bc1 + gc1 + 0.1) / (base + 0.1);
					add(val, "contentModifyRatio");
				}
			}

		private:
			dm_pack_t* _result = NULL;
			int _maxMatchCount; //最多可能匹配的个数

			MatchDict& _blackDict = blackDict();
			MatchDict& _grayDict = grayDict();
			MatchDict& _whiteDict = whiteDict();
			RegexSearcher& _blackRegSearcher = blackRegSearcher();
			RegexSearcher& _contentBlackRegSearcher = contentBlackRegSearcher();
			RegexSearcher& _grayRegSearcher = grayRegSearcher();
		private:
			static MatchDict& blackDict()
			{ //这样写的好处可以允许多个不同DictMatch实例 拥有不同的blackDict
				string blackFile = "./data/wordlist/black.dm";
				PSCONF(blackFile, "DictMatch");
				return SharedObjects<MatchDict>::Instance(blackFile);
			}

			static MatchDict& grayDict()
			{
				string grayFile = "./data/wordlist/gray.dm";
				PSCONF(grayFile, "DictMatch");
				return SharedObjects<MatchDict>::Instance(grayFile);
			}

			static MatchDict& whiteDict()
			{
				string whiteFile = "./data/wordlist/white.dm";
				PSCONF(whiteFile, "DictMatch");
				return SharedObjects<MatchDict>::Instance(whiteFile);
			}

			static RegexSearcher& blackRegSearcher()
			{
				string blackPatternFile = "./data/wordlist/black.pattern";
				PSCONF(blackPatternFile, "DictMatch");
				return SharedObjects<RegexSearcher>::Instance(blackPatternFile);
			}

			static RegexSearcher& contentBlackRegSearcher()
			{
				string contentBlackPatternFile = "./data/wordlist/content.black.pattern";
				PSCONF(contentBlackPatternFile, "DictMatch");
				return SharedObjects<RegexSearcher>::Instance(contentBlackPatternFile);
			}

			static RegexSearcher& grayRegSearcher()
			{
				string grayPatternFile = "./data/wordlist/gray.pattern";
				PSCONF(grayPatternFile, "DictMatch");
				return SharedObjects<RegexSearcher>::Instance(grayPatternFile);
			}

		};

	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_URATE__DICT_MATCH_EXTRACTOR_H_
