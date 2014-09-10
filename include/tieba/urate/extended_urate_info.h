/**
 *  ==============================================================================
 *
 *          \file   tieba/urate/extended_urate_info.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-10 14:00:45.162506
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_URATE_EXTENDED_URATE_INFO_H_
#define TIEBA_URATE_EXTENDED_URATE_INFO_H_

#include "tieba/urate/urate_info.h"
namespace gezi {
namespace tieba {

	struct ExtendedUrateInfo : public UrateInfo
	{
		ExtendedUrateInfo() = default;

		ExtendedUrateInfo(const UrateInfo& urateInfo)
			:UrateInfo(urateInfo)
		{

		}

		vector<string> htmlFilteredContents;
		vector<string> normalizedContents;
		vector<string> normalizedCnContents;

		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive &ar, const unsigned int version)
		{
			ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(UrateInfo);
		}
	};

}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_URATE_EXTENDED_URATE_INFO_H_
