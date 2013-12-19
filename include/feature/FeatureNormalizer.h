#ifndef _NORMALIZE_FILTER_H_
#define _NORMALIZE_FILTER_H_

#include "Feature.h"
#include "common_util.h"
#include "stdio.h"
#include "stdlib.h"
#include <math.h>
#include <string.h>
namespace gezi
{

class FeatureNormalizer
{
public:
  static const int max_feature_num = 102400;

  FeatureNormalizer()
  {
    _pairs.resize(max_feature_num + 1);
  }

  struct Pair
  {

    Pair()
    : lower(0), upper(0)
    {

    }

    Pair(double lower_, double upper_)
    : lower(lower_), upper(upper_)
    {

    }
    double lower;
    double upper;
  };

  bool open(const char* file)
  {
    vector<string> lines = read_lines(file);
    if (lines.empty())
    {
      LOG_WARNING("Could not open the file %s", file);
      return false;
    }

    vector<string> parts;
    boost::split(parts, lines[1], is_any_of("\t "));
    _lower = DOUBLE(parts[0]);
    _upper = DOUBLE(parts[1]);

    size_t i = 2;
    for (; i < lines.size(); i++)
    {
      vector<string> parts;
      boost::split(parts, lines[i], is_any_of("\t "));
      int index = INT(parts[0]);
      _pairs[index] = Pair(DOUBLE(parts[1]), DOUBLE(parts[2]));
      if (i == (lines.size() - 1))
      {
        _featureNum = index;
      }
    }

    Pval(_featureNum);

    return true;
  }

  int featureNum()
  {
    return _featureNum;
  }

  //TODO 专门提出MinMax Guass Bining Normalizer 同时支持 incl 和 excl
  //可以考虑在添加特征的时候 就做normalize 接近0的不 add  <=> Normalize(value) 或者这里整体norm 之后再去掉0的
  int normalize(Feature* feature)
  {
    vector<Feature::Node>& nodes = feature->nodes();
    foreach(Feature::Node& node, nodes)
    {
      if (node.value < _pairs[node.index].lower)
      {
        node.value = _lower;
      }
      else if (node.value > _pairs[node.index].upper)
      {
        node.value = _upper;
      }
      else
      {
        node.value = _lower +
                (_upper - _lower) * (node.value - _pairs[node.index].lower) /
                (_pairs[node.index].upper - _pairs[node.index].lower);
      }
    }
    return 0;
  }

private:
  int _featureNum;
  vector<Pair> _pairs; //每个特征的上下界
  double _lower; //要归一化到的 下界
  double _upper;
};

}
#endif
