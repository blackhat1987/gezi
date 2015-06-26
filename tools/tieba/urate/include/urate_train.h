/**
 *  ==============================================================================
 *
 *          \file   urate_train.h
 *
 *        \author   chenghuige
 *
 *          \date   2015-06-16 15:21:33.988599
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef URATE_TRAIN_H_
#define URATE_TRAIN_H_

#include <string>
#include <vector>

inline void gen_features(const std::vector<unsigned long long>& pids, const std::vector<bool>& lables, 
	std::string output = "feature.txt", std::string history = "./history");

#endif  //----end of URATE_TRAIN_H_
