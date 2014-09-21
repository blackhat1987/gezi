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

		double locationInformation = gezi::information(info().locations);
		ADD_FEATURE(hasUidsWithSameIp);
		ADD_FEATURE(hasSameIpWithLouzhu);
		ADD_FEATURE(locationInformation);
	}
protected:
private:

};

}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_FULLPOSTS__DINGTIE_EXTRACTOR_H_
