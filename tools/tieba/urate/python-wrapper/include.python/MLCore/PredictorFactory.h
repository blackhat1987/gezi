#ifndef PREDICTORS__PREDICTOR_FACTORY_H_
#define PREDICTORS__PREDICTOR_FACTORY_H_
#include "common_util.h"
#include "MLCore/Predictor.h"
namespace gezi {
class PredictorFactory
{
public:
static PredictorPtr CreatePredictor(string name);
static PredictorPtr CreatePredictor(string name, string path);
static PredictorPtr LoadPredictor(string path, bool useCustomModel = false);
static PredictorPtr CreatePredictorFromTextFormat(string name, string path);
static PredictorPtr LoadTextPredictor(string path);
static Predictors LoadPredictors(const svec& paths);
protected:
private:
};
}
#endif
