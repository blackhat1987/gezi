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

	//@TODO ĿǰFeature�Ѿ��ĳɰ���TLC��׼ 0 ��ʼ ���Ҳ���ٶ�Ӧ
	//����ĳ���ȫ����TLC��׼ ��Ӧ���� linear svm,svm, logistic regression �ȵ�
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

  //��ǰ����ȫ����libsvm 3.17������ļ���ʽ

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

  //TODO ר�����MinMax Guass Bining Normalizer ͬʱ֧�� incl �� excl
  //���Կ��������������ʱ�� ����normalize �ӽ�0�Ĳ� add  <=> Normalize(value) ������������norm ֮����ȥ��0��
  //TODO ע�⵱ǰ����ƶ���Feature������sparse �� dense ˫��value

  void norm(int index, double value, vector<Feature::Node>& result)
  {
    if (_pairs[index].upper == _pairs[index].lower)
    { //�����ͬ ��������ѵ��������δ���� ��������ѵ���������������ֵ��һ�� scale�ļ���û�����ķ�Χ �����������ߺ��Ե�
      return;
    }
    if (_useTruncate)
    {
      //ע������Ĵ����ǽضϴ�������ȫ����scale ��libsvm�Լ�tlc���洦��ͬ ���ܲ��Լ��Ͻ�����в�ͬ
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
    { //��ǰ���ò��ضϴ��� ���ֺ�libsvm,tlcһ�� TODO ʵ���µ�����������ֵ�Խ��Ӱ��
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
  vector<Pair> _pairs; //ÿ�����������½�
  double _lower; //Ҫ��һ������ �½�
  double _upper;
  int _startIndex;
  bool _useTruncate;
};

}

#endif
