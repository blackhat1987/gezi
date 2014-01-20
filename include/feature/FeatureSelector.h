/**
 *  ==============================================================================
 *
 *          \file   FeatureSelector.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-01-19 10:46:46.156630
 *
 *  \Description:   实际是文本类(词,模式)特征的选取，利用特征词(模式）是否出现在某个类别中
 *  ==============================================================================
 */

#ifndef FEATURE_SELECTOR_H_
#define FEATURE_SELECTOR_H_

#include "Matrix.h"
#include "Identifer.h"
#include "collocation.h"
#include "sort_util.h"
namespace gezi
{

//Two options for an aggregate score across classes:
//Weighted average:
//?^2 (???????)=∑_(?∈???????)?〖?(?)  ?^2 (???????,?) 〗
//Highest score among any class:
//?^2 (???????)=max┬(?∈???????)?〖   ?^2 (???????,?)〗

class FeatureSelector : public Identifer
{
public:
  typedef boost::function<Float(int, int, int, uint64) > Func;

  FeatureSelector()
  : _numLabels(2), _method(collocation::CHI), _strategy(MAX)
  {
    init();
    initFunc();
  }

  inline FeatureSelector& labelNum(int labelNum)
  {
    _numLabels = labelNum;
    init();
    return *this;
  }

  void init()
  {
    _classCounts.resize(_numLabels, 0);
    _classPriors.resize(_numLabels, 0);
    _counts.resize(_numLabels);
    _scores.resize(_numLabels + 1); //最后的行是特征对所有类的一个总的评价值
    _ranks.resize(_numLabels + 1);

    foreach(vector<int>& vec, _counts)
    {
      vec.reserve(1024);
    }
  }

  enum Strategy
  {
    MAX,
    AVG
  };

  void initFunc()
  {
    using namespace collocation;
    switch (_method)
    {
      case CHI:
        VLOG(3) << "Chi Square";
        _func = chi_square;
        break;
      case IG:
        VLOG(3) << "Informaion Gain";
        _func = information_gain;
        break;
      case MI:
        VLOG(3) << "Mutual Info";
        _func = mutual_info;
        break;
      case MI2:
        VLOG(3) << "Mutual Info method2";
        _func = mutual_info2;
        break;
      case PMI:
        VLOG(3) << "Point Mutual Info";
        _func = point_mutual_info;
        break;
      case ECE:
        VLOG(3) << "Expected Cross Entropy";
        _func = cross_entropy;
        break;
      default:
        VLOG(3) << "Chi Square";
        _func = chi_square;
        break;
    }
  }

  void clear()
  {
    _ranks.clear();
    _ranks.resize(_numLabels + 1);
    _scores.clear();
    _scores.resize(_numLabels + 1);
  }

  inline int labelNum()
  {
    return _numLabels;
  }

  inline FeatureSelector& method(collocation::Method method)
  {
    _method = method;
    clear();
    initFunc();
    return *this;
  }

  inline FeatureSelector& strategy(Strategy strategy)
  {
    _strategy = strategy;
    clear();
    return *this;
  }

  inline int method()
  {
    return _method;
  }

  inline int strategy()
  {
    return _strategy;
  }

  void add(const vector<string>& words, int label)
  {
    unordered_set<string> wordSet(words.begin(), words.end());
    add(wordSet, label);
  }

  void add(const unordered_set<string>& words, int labelIdx)
  {

    foreach(const string& word, words)
    {
      bool isnew = false;
      int idx = Identifer::add(word, isnew);
      if (isnew)
      {
        _featureCounts.push_back(1);
        _counts[labelIdx].push_back(1);
      }
      else
      {
        _featureCounts[idx] += 1;
        _counts[labelIdx][idx] += 1;
      }
    }
    _classCounts[labelIdx] += 1;
  }

  void add(string doc, int label, string sep = "\t")
  {
    vector<string> words;
    boost::split(words, doc, is_any_of(sep));
    add(words, label);
  }

  //暂时只考虑CHI TODO IG ECE MI PMI

  DMat& calc()
  {
    finalize();
    if (_strategy == AVG)
    {
      for (int labelIdx = 0; labelIdx < _numLabels; labelIdx++)
      {
        _classPriors[labelIdx] = (double) _classCounts[labelIdx] / _numInstances;
      }
    }
    PVEC(_classPriors);
    vector<double>& scores = _scores.back();
    for (int f = 0; f < _numFeatures; f++)
    {
      for (int labelIdx = 0; labelIdx < _numLabels; labelIdx++)
      {
        double score = _func(_counts[labelIdx][f], _classCounts[labelIdx], _featureCounts[f], _numInstances);
        _scores[labelIdx][f] = score;
        if (_strategy == MAX)
        {
          if (score > scores[f])
          {
            scores[f] = score;
          }
        }
        else if (_strategy == AVG)
        {
          scores[f] += _classPriors[labelIdx] * score;
        }
      }
    }
    return _scores;
  }

  void save(string file, int maxFeatureNum = 1024, int idx = -1)
  {
    ofstream ofs(file.c_str());
    save(ofs, maxFeatureNum, idx);
  }

  void save(ostream& os, int maxFeatureNum, int idx)
  {
    if (idx == -1)
      idx = _numLabels;
    PVAL(idx);
    if (maxFeatureNum == -1 || maxFeatureNum > _numFeatures)
      maxFeatureNum = _numFeatures;
    PVAL(maxFeatureNum);
    rank(idx, maxFeatureNum);
    for (int i = 0; i < maxFeatureNum; i++)
    {
      int index = _ranks[idx][i];
      os << _index[index] << "\t" << _scores[idx][index] << endl;
    }
  }

  inline int numFeatures()
  {
    return _numFeatures;
  }

  inline int64 numInstances()
  {
    return _numInstances;
  }

private:

  void finalize()
  {
    _numFeatures = this->size();
    PVAL(_numFeatures);
    _numInstances = std::accumulate(_classCounts.begin(), _classCounts.end(), int64(0));
    PVAL(_numInstances);

    foreach(vector<double>& vec, _scores)
    {
      vec.resize(_numFeatures); //特征数目
    }
  }

  void rank(int maxFeatureNum)
  {
    if (maxFeatureNum > _numFeatures)
      maxFeatureNum = _numFeatures;
    for (int i = 0; i <= _numLabels; i++)
    {
      gezi::sort(_scores[i], _ranks[i], maxFeatureNum);
    }
  }

  void rank(int index, int maxFeatureNum)
  {
    gezi::sort(_scores[index], _ranks[index], maxFeatureNum);
  }

private:
  IMat _counts;
  vector<int> _featureCounts;
  vector<int> _classCounts;
  vector<double> _classPriors;
  int _numLabels;
  int _numFeatures;
  int64 _numInstances;
  Func _func;
  collocation::Method _method;
  Strategy _strategy;

  DMat _scores; //记录各个特征打分
  IMat _ranks; //记录特征打分排序索引
};

} //----end of namespace gezi

#endif  //----end of FEATURE_SELECTOR_H_
