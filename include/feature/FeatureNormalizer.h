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

	//@TODO 目前Feature已经改成按照TLC标准 0 开始 这个也不再对应
	//将会改成完全按照TLC标准 对应增加 linear svm,svm, logistic regression 等等
class FeatureNormalizer
{
public:
  //libsvm use 1 as the first index, while tlc or others use 0

  FeatureNormalizer(int startIndex = 1, bool useTruncate = false, int maxFeatureNum = 102400)
  : _startIndex(startIndex), _useTruncate(useTruncate)
  {
    _pairs.resize(maxFeatureNum + 1);
  }

  FeatureNormalizer& startIndex(int startIndex_)
  {
    _startIndex = startIndex_;
    return *this;
  }

  FeatureNormalizer& useTruncate(bool useTruncate_)
  {
    _useTruncate = useTruncate_;
    return *this;
  }

  FeatureNormalizer& maxFeatureNum(int maxFeatureNum_)
  {
    _pairs.resize(maxFeatureNum_ + 1);
    return *this;
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

  //当前是完全参照libsvm 3.17的输出文件格式

  bool open(const char* file)
  {
    vector<string> lines = read_lines(file);
    if (lines.empty())
    {
      LOG(WARNING) << "Could not open the file " << file;
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
  //TODO 注意当前的设计都是Feature保留有sparse 和 dense 双重value

  void norm(int index, double value, vector<Feature::Node>& result)
  {
    if (_pairs[index].upper == _pairs[index].lower)
    { //如果相同 该特征在训练数据中未出现 或者所有训练数据中这个特征值都一样 scale文件中没有它的范围 这种特征在线忽略掉
      return;
    }
    if (_useTruncate)
    {
      //注意下面的处理是截断处理不是完全线性scale 和libsvm以及tlc里面处理不同 可能测试集合结果略有不同
      if (value <= _pairs[index].lower)
      {
        value = _pairs[index].lower;
      }
      else if (value >= _pairs[index].upper)
      {
        value = _pairs[index].upper;
      }
      else
      {
        value = _lower + (_upper - _lower) * (value - _pairs[index].lower) /
                (_pairs[index].upper - _pairs[index].lower);
      }
    }
    else
    { //当前采用不截断处理 保持和libsvm,tlc一致 TODO 实验下单个特征过大值对结果影响
      value = _lower + (_upper - _lower) * (value - _pairs[index].lower) /
              (_pairs[index].upper - _pairs[index].lower);
    }
    if (value != 0)
    {
      result.push_back(Feature::Node(index, value));
    }
  }

  int normalize(Feature* feature)
  {
    vector<Feature::Node>& nodes = feature->nodes();
    vector<Feature::Node> temp;
    int idx = _startIndex;

    foreach(Feature::Node& node, nodes)
    {
      for (int i = idx; i < node.index; i++)
      {
        norm(i, 0, temp);
      }
      norm(node.index, node.value, temp);
      idx = node.index + 1;
    }
    nodes.swap(temp);
    return 0;
  }
  
private:
  int _featureNum;
  vector<Pair> _pairs; //每个特征的上下界
  double _lower; //要归一化到的 下界
  double _upper;
  int _startIndex;
  bool _useTruncate;
};

}

#endif
