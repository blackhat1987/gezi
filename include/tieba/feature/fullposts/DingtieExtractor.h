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
			}

			virtual void extract() override
			{
				bool hasUidsWithSameIp = false;
				bool hasSameIpWithLouzhu = false;

				auto& ips = info().ips;
				auto& uids = info().uids;

				uint64 firstIp = ips[0];
				map<uint64, uint> ip2UidMap;
				ip2UidMap[firstIp] = uids[0];

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
				}
				//mean,var,count,ratio,information
				double ipsInformation = gezi::information(info().ips);
				double locationsInformation = gezi::information(info().locations);
				double uidsInformation = gezi::information(info().uids);
				svec namePatterns = from(info().unames)
					>> select([](string uname) { return name_pattern(uname); })
					>> to_vector();
				double namePtternsInformation = gezi::information(namePatterns);
				
				//楼主发帖 count, ratio
				uint louzhuUid = info().uids[0];
				int louzhuUidCount = from(info().uids) >> where([&](uint uid) { return uid == louzhuUid; }) >> count();
				double louzhuUidRatio = louzhuUidCount / (double)size();

				//楼主的ip count,ratio
				uint64 louzhuIp = info().ips[0];
				int louzhuIpCount = from(info().ips) >> where([&](uint64 ip) { return ip == louzhuIp; }) >> count();
				double louzhuIpRatio = louzhuIpCount / (double)size();

				ADD_FEATURE(hasUidsWithSameIp);
				ADD_FEATURE(hasSameIpWithLouzhu);
				ADD_FEATURE(ipsInformation);
				ADD_FEATURE(locationsInformation);
				ADD_FEATURE(uidsInformation);
				ADD_FEATURE(namePtternsInformation);
				ADD_FEATURE(louzhuUidCount);
				ADD_FEATURE(louzhuUidRatio);
				ADD_FEATURE(louzhuIpCount);
				ADD_FEATURE(louzhuIpRatio);
			}
		protected:
		private:

		};

	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_FULLPOSTS__DINGTIE_EXTRACTOR_H_
