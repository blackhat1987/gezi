/**
 *  ==============================================================================
 *
 *          \file   tieba/feature/fullposts/DingtieExtractor.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-20 22:06:16.457436
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_FEATURE_FULLPOSTS__DINGTIE_EXTRACTOR_H_
#define TIEBA_FEATURE_FULLPOSTS__DINGTIE_EXTRACTOR_H_
#include "FullPostsExtractor.h"
#include "tools/uname_util.h"
#include "MatchDict.h"
namespace gezi {
	namespace tieba {

		class DingtieExtractor : public FullPostsExtractor
		{
		public:
			DingtieExtractor(string name = "Dingtie")
				:FullPostsExtractor(name)
			{

			}
			virtual void init() override
			{
				info().ExtractLocations();
				info().ExtractTop2Ips();
			}

			virtual void extract() override
			{

				int numFloors = size() - 1;
				ADD_FEATURE(numFloors);

				bool hasUidsWithSameIp = false;
				bool hasSameIpWithLouzhu = false;

				auto& ips = info().ips;
				auto& uids = info().uids;
				auto& top2Ips = info().top2Ips;
				auto& locations = info().locations;

				uint louzhuUid = info().uids[0];

				uint64 firstIp = ips[0];
				map<uint64, uint> ip2UidMap;
				ip2UidMap[firstIp] = uids[0];

				map<uint64, int> ipCountMap;
				map<uint64, int> top2IpCountMap;
				map<string, int> locationCountMap;
				set<uint64> uidSet; //不包含楼主的uid数目
				int maxNumIps = 0, maxNumTop2Ips = 0, maxNumLocations = 0, numLouzhuPosts = 0;

				for (size_t i = 1; i < ips.size(); i++)
				{
					auto iter = ip2UidMap.find(ips[i]);
					if (iter != ip2UidMap.end())
					{
						if (iter->second != uids[i])
						{
							hasUidsWithSameIp = true;
							if (ips[i] == firstIp)
							{
								hasSameIpWithLouzhu = true;
							}
						}
					}
					else
					{
						ip2UidMap[ips[i]] = uids[i];
					}

					if (uids[i] != louzhuUid)
					{
						{
							int& count = ipCountMap[ips[i]];
							count += 1;
							if (count > maxNumIps)
							{
								maxNumIps = count;
							}
						}
							{
								int& count = top2IpCountMap[top2Ips[i]];
								count += 1;
								if (count > maxNumTop2Ips)
								{
									maxNumTop2Ips = count;
								}
							}
							{
								int& count = locationCountMap[locations[i]];
								count += 1;
								if (count > maxNumLocations)
								{
									maxNumLocations = count;
								}
							}
							uidSet.insert(uids[i]);
					}
					else
					{
						numLouzhuPosts++;
					}
				}

				bool louzhuIsMaxIp = (ipCountMap[ips[0]] == maxNumIps);
				bool louzhuIsMaxTop2Ip = (top2IpCountMap[top2Ips[0]] == maxNumTop2Ips);
				bool louzhuIsMaxLocation = (locationCountMap[locations[0]] == maxNumLocations);

				ADD_FEATURE(louzhuIsMaxIp); //楼主的ip是出现最多的非楼主uid对应的ip
				ADD_FEATURE(louzhuIsMaxTop2Ip);
				ADD_FEATURE(louzhuIsMaxLocation); //楼主的地域是出现最多的非楼主uid对应的地域

				//--------预期下面一组没有太大用处 information已经表示了这些
				ADD_FEATURE(maxNumIps);
				ADD_FEATURE(maxNumTop2Ips);
				ADD_FEATURE(maxNumLocations);
				add(ipCountMap.size(), "numDistinctIps");
				add(top2IpCountMap.size(), "numDistinctTop2Ips");
				add(locationCountMap.size(), "numDistinctLocations");
				add(uidSet.size(), "numDistinctUids");
				double distinctIpRatio = (numFloors == numLouzhuPosts) ? 1 : ipCountMap.size() / (double)(numFloors - numLouzhuPosts);
				double distinctTop2IpRatio = (numFloors == numLouzhuPosts) ? 1 : top2IpCountMap.size() / (double)(numFloors - numLouzhuPosts);
				double distinctLocationsRatio = (numFloors == numLouzhuPosts) ? 1 : locationCountMap.size() / (double)(numFloors - numLouzhuPosts);
				double distinctUidRatio = (numFloors == numLouzhuPosts) ? 1 : uidSet.size() / (double)(numFloors - numLouzhuPosts);
				ADD_FEATURE(distinctIpRatio);
				ADD_FEATURE(distinctTop2IpRatio);
				ADD_FEATURE(distinctLocationsRatio);
				ADD_FEATURE(distinctUidRatio);

				//mean,var,count,ratio,information
				double ipsInformation = gezi::information(info().ips);
				double top2IpsInformation = gezi::information(info().top2Ips);
				double locationsInformation = gezi::information(info().locations);
				double uidsInformation = gezi::information(info().uids);

				double uidsMean = gezi::mean(info().uids);

				//@TODO @FIXME 奇怪 返回的仍然当做 vector<uint> ...
				//vector<int64> uids_ = from(info().uids) >> where([&](uint uid) { return (int64)uid; }) >> to_vector();
				vector<int64> uids_;
				for (auto& uid : info().uids)
				{
					uids_.push_back(uid);
				}
				double uidsVar = gezi::ufo::var(uids_, std::numeric_limits<double>::max());
				svec namePatterns = from(info().unames)
					>> select([](string uname) { return name_pattern(uname); })
					>> to_vector();
				double namePtternsInformation = gezi::information(namePatterns);

				svec simpleNamePatterns = from(info().unames)
					>> select([](string uname) { return simple_name_pattern(uname); })
					>> to_vector();
				double simpleNamePtternsInformation = gezi::information(simpleNamePatterns);

				vector<size_t> nameLengths = from(info().unames)
					>> select([](string uname) { return uname.length(); })
					>> to_vector();
				double nameLengthsInformation = gezi::information(nameLengths);

				//楼主发帖 count, ratio
				int louzhuUidCount = from(info().uids) >> where([&](uint uid) { return uid == louzhuUid; }) >> count();
				double louzhuUidRatio = louzhuUidCount / (double)size();

				//楼主的ip count,ratio
				uint64 louzhuIp = info().ips[0];
				int louzhuIpCount = from(info().ips) >> where([&](uint64 ip) { return ip == louzhuIp; }) >> count();
				double louzhuIpRatio = louzhuIpCount / (double)size();

				int maxIpsPerUid = max_count_by(ips, uids);
				int maxUidsPerIp = max_count_by(uids, ips);

				//含有删前留名类似信息的非楼主帖子比例
				int shanqianCount = from(info().contents) >>
				where([&](string content){
					return shanqianDict().search_count(gezi::extract_chinese(content)) > 0; }
				) >> count();
				int nonLouzhuCount = size() - louzhuUidCount;
				double shanqianRatio = nonLouzhuCount == 0 ? 0 : shanqianCount / (double)nonLouzhuCount;

				ADD_FEATURE(hasUidsWithSameIp);
				ADD_FEATURE(hasSameIpWithLouzhu);
				ADD_FEATURE(ipsInformation);
				ADD_FEATURE(locationsInformation);
				ADD_FEATURE(uidsInformation);
				ADD_FEATURE(uidsMean);
				ADD_FEATURE(uidsVar);
				ADD_FEATURE(namePtternsInformation);
				ADD_FEATURE(simpleNamePtternsInformation);
				ADD_FEATURE(nameLengthsInformation);
				ADD_FEATURE(louzhuUidCount);
				ADD_FEATURE(louzhuUidRatio);
				ADD_FEATURE(louzhuIpCount);
				ADD_FEATURE(louzhuIpRatio);
				ADD_FEATURE(maxIpsPerUid);
				ADD_FEATURE(maxUidsPerIp);
				ADD_FEATURE(shanqianCount);
				ADD_FEATURE(shanqianRatio);
			}
		protected:
		private:
			//for删前留名
			static MatchDict& shanqianDict()
			{ //这样写的好处可以允许多个不同DictMatch实例 拥有不同的blackDict
				static MatchDict _dict = ConstructObj<MatchDict>([&]() {
					string shanqianFile = "./data/wordlist/lou.black.dm";
					PSCONF(shanqianFile, "DictMatch");
					return shanqianFile;
				});
				return _dict;
			}

		};

	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_FULLPOSTS__DINGTIE_EXTRACTOR_H_
