/**
 *  ==============================================================================
 *
 *          \file   tieba/feature/urate/IpExtractor.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-13 20:39:18.321217
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_FEATURE_URATE__IP_EXTRACTOR_H_
#define TIEBA_FEATURE_URATE__IP_EXTRACTOR_H_
#include "tieba/feature/urate/UrateExtractor.h"
namespace gezi {
	namespace tieba {

		class IpExtractor : public UrateExtractor
		{
		public:

			IpExtractor(string name = "Ip")
				:UrateExtractor(name)
			{

			}

			virtual void init() override
			{
				info().ExtractLocations();
			}

			static bool IsForeignLocation(string location)
			{
				return startswith(location, "美国") || startswith(location, "俄罗")
					|| startswith(location, "澳大") || startswith(location, "日本")
					|| startswith(location, "韩国");
			}

			void Extract(const vector<uint64>& ips, const svec& locations,
				const vector<uint64>& times, int maxSpanHours)
			{
				set<string>  locationSet;
				set<uint64> ipSet, top3IpSet, top2IpSet, top1IpSet; //ip 前3位，前2位， 第1位

				int len = ips.size();
				if (times.size() < ips.size())
					len = times.size();

				int64 startTime = (int64)times[0] - maxSpanHours * kOneHour;

				string preLocation;
				uint64 preIp = 0, preTop3Ip = 0, preTop2Ip = 0, preTop1Ip = 0;

				int numLocationChanges = 0, numForeignLocationOccurs = 0;
				int numIpChanges = 0, numTop3IpChanges = 0, numTop2IpChanges = 0, numTop1IpChanges = 0;
				for (int i = 0; i < len; i++)
				{
					//查看时间是否在有效时间内
					int64 time = times[i];

					if (time < startTime)
					{
						PVAL(i);
						break;
					}

					string location = locations[i];
					if (location != "中国")
					{
						locationSet.insert(location);
						if (location != preLocation)
						{
							numLocationChanges++;
						}
						if (IsForeignLocation(location))
						{
							numForeignLocationOccurs++;
						}
					}

					uint64 ip = ips[i];
					ipSet.insert(ip);

					if (ip != preIp)
					{
						numIpChanges++;
					}

					uint64 top3Ip, top2Ip, top1Ip;
					get_ipgroups(ip, top3Ip, top2Ip, top1Ip);
					top3IpSet.insert(top3Ip);
					top2IpSet.insert(top2Ip);
					top1IpSet.insert(top1Ip);
					if (top3Ip != preTop3Ip)
					{
						numTop3IpChanges++;
					}
					if (top2Ip != preTop2Ip)
					{
						numTop2IpChanges++;
					}
					if (top1Ip != preTop1Ip)
					{
						numTop1IpChanges++;
					}

					preLocation = location;
					preIp = ip;
					preTop3Ip = top3Ip;
					preTop2Ip = top2Ip;
					preTop1Ip = top1Ip;
				}

				int numLocations = locationSet.size();
				int numIps = ipSet.size();
				int numTop3Ips = top3IpSet.size();
				int numTop2Ips = top2IpSet.size();
				int numTop1Ips = top1IpSet.size();

				double locationChangeRatio = numLocationChanges / (double)size();
				double ipChangeRatio = numIpChanges / (double)size();
				double top3IpChangeRatio = numTop3IpChanges / (double)size();
				double top2IpChangeRatio = numTop2IpChanges / (double)size();
				double top1IpChangeRatio = numTop1IpChanges / (double)size();

				double foreignLocationRatio = numForeignLocationOccurs / (double)size();

				ADD_FEATURE(numLocations);
				ADD_FEATURE(numIps);
				ADD_FEATURE(numTop3Ips);
				ADD_FEATURE(numTop2Ips);
				ADD_FEATURE(numTop1Ips);

				ADD_FEATURE(numLocationChanges);
				ADD_FEATURE(numIpChanges);
				ADD_FEATURE(numTop3IpChanges);
				ADD_FEATURE(numTop2IpChanges);
				ADD_FEATURE(numTop1IpChanges);

				ADD_FEATURE(locationChangeRatio);
				ADD_FEATURE(ipChangeRatio);
				ADD_FEATURE(top3IpChangeRatio);
				ADD_FEATURE(top2IpChangeRatio);
				ADD_FEATURE(top1IpChangeRatio);

				ADD_FEATURE(numForeignLocationOccurs);
				ADD_FEATURE(foreignLocationRatio);
			}

			virtual void extract() override
			{
				auto& ips = info().postsInfo.ips;
				auto& times = info().postsInfo.times;
				auto& locations = info().locations;
				int maxSpanHours = 72;
				Extract(ips, locations, times, maxSpanHours);
			}

		protected:
		private:

		};

	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_URATE__IP_EXTRACTOR_H_
