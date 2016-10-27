#ifndef TESTERS__RANKER_TESTER_H_
#define TESTERS__RANKER_TESTER_H_
#include "Tester.h"
namespace gezi {
class RankerTester : public Tester
{
public:
virtual PredictionKind GetPredictionKind();
virtual vector<DatasetMetricsPtr> ConstructDatasetMetrics();
protected:
private:
};
}
#endif
