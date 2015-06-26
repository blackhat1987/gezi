/**
 *  ==============================================================================
 *
 *          \file   urate_train.cpp
 *
 *        \author   chenghuige
 *
 *          \date   2015-06-16 15:23:13.159986
 *
 *  \Description:
 *  ==============================================================================
 */



#include "urate_train.h"
#include "common_util.h"
#include "feature/Features.h"
#include "tieba/urate/get_urate_info.h"
#include "tieba/urate/urate_features.h"
using namespace std;
using namespace gezi;
using namespace gezi::tieba;

inline void gen_features(const std::vector<unsigned long long>& pids, const std::vector<bool>& lables,
std::string output = "feature.txt", std::string history = "./history");
{
	write_features(pids, labels,
		[&](uint64 pid) { return gen_urate_features(pid, history); }, output);
}

