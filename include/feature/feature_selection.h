/**
 *  ==============================================================================
 *
 *          \file   feature_selection.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-01-19 07:15:19.149498
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef FEATURE_SELECTION_H_
#define FEATURE_SELECTION_H_

#include "common_util.h"
#include "Matrix.h"
#include "collocation.h"
namespace gezi
{

enum ScoreFeatureStrategy
{
  MAX,
  AVG
};


//TODO p >= MIN_SUPPORT && q >= MIN_SUPPORT

template<typename Func = ChiSquareFunc>
void score_feature(IMat& counts,
        vector<int>& featureCounts, vector<int>& classTotals,
        uint64 numInstances, vector<double> scores, const Func& func = Func(),
        ScoreFeatureStrategy strategy = MAX)
{
  int numFeatures = featureCounts.size();
  int numLabels = classTotals.size();
  vector<double> classPriors;
  if (strategy == AVG)
  {
    classPriors.resize(numLabels); 
    for (int labelIdx = 0; labelIdx < numLabels; labelIdx++)
    {
      classPriors[labelIdx] = (double)classTotals[labelIdx] / numInstances;
    }
  }
  for (int f = 0; f < numFeatures; f++)
  {
    for (int labelIdx = 0; labelIdx < numLabels; labelIdx++)
    {
      double score = func(counts[labelIdx][f], featureCounts[f], classTotals[labelIdx], numInstances);

      if (strategy == MAX)
      {
        if (score > scores[f])
        {
          scores[f] = score;
        }
      }
      else if (strategy == AVG)
      {
        scores[f] += classPriors[labelIdx] * score;
      }
    }
  }
}
}
#endif  //----end of FEATURE_SELECTION_H_
