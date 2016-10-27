#ifndef TESTERS__REGRESSOR_TESTER_H_
#define TESTERS__REGRESSOR_TESTER_H_
#include "Tester.h"
namespace gezi {
class RegressorMetrics : public DatasetMetrics
{
public:
virtual string LabelColumnName();
virtual vector<string> PerInstanceColumnNames();
virtual vector<string> Names();
virtual Fvec ProcessInstance(Float label, Float prediction, Float probability = std::numeric_limits<double>::quiet_NaN(), Float weight = 1.0);
virtual void Finish();
private:
Float sumWeights;
Float totalL1Loss;
};
class RegressorTester : public Tester
{
public:
virtual PredictionKind GetPredictionKind();
virtual vector<DatasetMetricsPtr> ConstructDatasetMetrics();
protected:
private:
};
}
#endif
