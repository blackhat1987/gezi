/**
 *  ==============================================================================
 *
 *          \file   tieba/feature/rsc_thread/RscThreadExtractor.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-10-25 12:29:30.049699
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_FEATURE_RSC_THREAD__RSC_THREAD_EXTRACTOR_H_
#define TIEBA_FEATURE_RSC_THREAD__RSC_THREAD_EXTRACTOR_H_
#include "feature/features_util.h"
#include "tieba/rsc/rsc_threads_info.h"
#include "tieba/feature/rsc_thread/RscThreadTextScoreExtractor.h"
namespace gezi {
	namespace tieba {
		namespace rsc {
			class RscThreadExtractor : public RscThreadsInfo
			{
			public:
				inline vector<pair<Features, ThreadInfo> > GetFeatures(string substr_, vector<ReplyInfo>& tids,
					bool isOnline = false, string historyDir = "./history")
				{
					RscThreadsInfo::Fetch(substr_, tids, threadsFetcher(), usersFetcher(), isOnline, historyDir);
					RscThreadsInfo::Extract();

					vector<ReplyInfo> candidates;

					for (auto item : tids)
					{
						if (labelMap().empty() || labelMap().count(item.tid))
						{
							if (!labelMap().empty() || !dealMap().count(item.tid))
							{
								candidates.push_back(item);
							}
						}
					}
					vector<pair<Features, ThreadInfo> > featuresVec;
					for (auto& item : candidates)
					{
						uint64 tid = item.tid;
						//不再去重 离线本身tid是去重了的 使用一个时间的记录作为向量
						//在线可以重复计算外部会去重已经删除的tid 已删除不再重复计算
						if (!_labelMap.empty())
						{//offline
							if (_tidSet.count(tid))
							{
								continue;
							}
							_tidSet.insert(tid);
						}

						Features feature;
						ThreadInfo& node = threadNodeMap[tid];
						PVAL6(node.threadId, node.userId, tid, threadNodeMap.size(), tids.size(), threadNodeMap.count(tid));

						if (_labelMap.empty())
						{//online
							if (node.isDeleted)
							{
								_dealMap.insert(make_pair(tid, false));
								continue;
							}
						}

						//本身substr是对应主题中抽取出来的 那么已经删除 不需要再计算 
						//另外这个模型本身用于回复删除主题的
						if (contains(node.title, substr))
						{
							continue;
						}

						//big group for all tid
						feature.add_section("TidsGroup");
						feature.add(uidSet.size() / (double)tids.size(), "UidRatio");
						feature.add(notSelfUpUidSet.size() / (double)tids.size(), "NotSelfUpUidRatio");
						feature.add(ipSet.size() / (double)tids.size(), "IpRatio");
						feature.add(addressSet.size() / (double)tids.size(), "AdressRatio");

						//这个tid所在被重复串召回组的组特征
						feature.add_section("TidGroup");
						feature.add(tids.size(), "TidCount");
						int uidCount = uidCountMap[node.userId];
						feature.add(uidCount, "UidCount");
						feature.add(uidCount / (double)tids.size(), "UidRatio");

						int distinctUidCount = uidDistinctCountMap[node.userId];
						feature.add(distinctUidCount, "DistinctUidCount");
						feature.add(distinctUidCount / (double)tids.size(), "DistinctUidRatio");

						int ipCount = ipCountMap[node.ip];
						feature.add(ipCount, "IpCount");
						feature.add(ipCount / (double)tids.size(), "IpRatio");

						int numIpPerUid = numIpsPerUidMap[node.userId];
						feature.add(numIpPerUid, "NumIpPerUid");
						feature.add(numIpPerUid / (double)tids.size(), "NumIpPerUidRatio");

						int numAddressPerUid = numAddressesPerUidMap[node.userId];
						feature.add(numAddressPerUid, "NumAddressPerUid");
						feature.add(numAddressPerUid / (double)tids.size(), "NumAddressPerUidRatio");

						int numUidPerIp = numUidsPerIpMap[node.ip];
						feature.add(numUidPerIp, "NumUidPerIp");
						feature.add(numUidPerIp / (double)tids.size(), "NumUidPerIpRatio");

						//tid文本特征
						{
							feature.add_section("Text");
							string filteredTitle = gezi::filter_str(node.title);
							{
								double val1 = textScoreExtractor().Predict(node.title, node.content, 0, RscThreadTextScoreExtractor::TextPredictMode::titleContentMerge);
								PVAL(val1);
								feature.add(val1, "TextScore0");

								string filtererdContent = gezi::filter_str(node.content);
								double val2 = textScoreExtractor().Predict(filteredTitle, filtererdContent, 0, RscThreadTextScoreExtractor::TextPredictMode::titleContentMerge);
								feature.add(val2, "FilteredTextScore0");

								feature.add(std::max(val1, val2), "MaxTextScore0");

								double val = (1 + val1) / (1 + val2);
								feature.add(val, "TextScoreCmp0");
							}

							{
								double val1 = textScoreExtractor().Predict(node.title, 1);
								PVAL(val1);
								feature.add(val1, "TextScore1");

								double val2 = textScoreExtractor().Predict(node.title, 1);
								feature.add(val2, "FilteredTextScore1");

								feature.add(std::max(val1, val2), "MaxTextScore1");

								double val = (1 + val1) / (1 + val2);
								feature.add(val, "TextScoreCmp1");
							}

							double val;
							feature.add(node.title.size(), "TitleLength");
							feature.add(filteredTitle.size(), "FilteredTitleLengh");
							val = (double)(1 + filteredTitle.size()) / (1 + node.title.size());
							feature.add(val, "TitleFilterRatio");

							val = std::count(node.title.begin(), node.title.end(), ' ');
							feature.add(val, "SpaceCount");

							string cnOnly = extract_chinese(node.title);
							val = (double)cnOnly.length() / 2 / gezi::word_count(node.title);
							feature.add(val, "CnPartRatio");

							Pval2(node.content, node.content.size());
							feature.add(node.content.size(), "ContentLength");
							feature.add(node.hasMedia, "HasMedia");
						}

						//	double val = (double)(1 + followCount) / (1 + followedCount);
						//	feature.add(val, "FollowedRatio");
						//}

						feature.add(node.userId, "Uid");


						//---tid对应回复之间的关系特征	
						feature.add_section("Reply");
						ReplyInfo& rnode = replysInfo[tid];
						feature.add(rnode.threadRatio, "ThreadRatio");
						string replyAdress = get_address(_ipFinder, rnode.ip);
						feature.add(node.userId == rnode.userId, "IsUidSame");
						feature.add(node.ip == rnode.ip, "IsIpSame");
						feature.add(node.address == replyAdress, "IsAdressSame");

						{
							int span = (int)(rnode.time - node.createTime);
							if (span < 0)
							{
								LOG(WARNING) << rnode.time << "\t" << node.createTime << "\t" << span;
								span = 0;
							}
							feature.add(span, "TimeSpan");
						}

						featuresVec.push_back(make_pair(feature, node));
					}
					return featuresVec;
				}

				static set<uint64>& tidSet()
				{
					static set<uint64> _tidSet;//离线
					return _tidSet;
				}
				set<uint64>& _tidSet = tidSet();

				static map<uint64, int>& labelMap()
				{
					static map<uint64, int> _labelMap;
					return _labelMap;
				}
				map<uint64, int>& _labelMap = labelMap();

				static LruMap<uint64, bool>& dealMap()
				{
					//已经本策略处理或者其它策略删除记录，本策略处理true
					static LruMap<uint64, bool> _dealMap(1000000);
					return _dealMap;
				}
				LruMap<uint64, bool>& _dealMap = dealMap();

				static CachedFetcher<uint64, tieba::ThreadInfo, LruHashMap>& threadsFetcher()
				{
					static CachedFetcher<uint64, tieba::ThreadInfo, LruHashMap> _threadsFetcher(1000000);
					return _threadsFetcher;
				}

				static CachedFetcher<uint, tieba::UserInfo, LruHashMap>& usersFetcher()
				{
					static CachedFetcher<uint, tieba::UserInfo, LruHashMap> _usersFetcher(100000);
					return _usersFetcher;
				}

				static RscThreadTextScoreExtractor& textScoreExtractor()
				{
					static RscThreadTextScoreExtractor _textScoreExtractor;
					return _textScoreExtractor;
				}
			};
		} //----end of namespace rsc
	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_RSC_THREAD__RSC_THREAD_EXTRACTOR_H_
