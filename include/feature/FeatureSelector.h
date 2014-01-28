/**
 *  ==============================================================================
 *
 *          \file   FeatureSelector.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-01-19 10:46:46.156630
 *
 *  \Description:   ʵ�����ı���(��,ģʽ)������ѡȡ������������(ģʽ���Ƿ������ĳ�������
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
//?^2 (???????)=��_(?��???????)?��?(?)  ?^2 (???????,?) ��
//Highest score among any class:
//?^2 (???????)=max��(?��???????)?��   ?^2 (???????,?)��

class FeatureSelector : public Identifer
{
public:
  typedef boost::function<Float(int, int, int, uint64) > Func;

  FeatureSelector()
  : _numLabels(2), _method(collocation::CHI), _strategy(MAX), _minSupport(0)
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
    _scores.resize(_numLabels + 1); //���������������������һ���ܵ�����ֵ
    _ranks.resize(_numLabels + 1);

    foreach(vector<int>& vec, _counts)
    {
      vec.reserve(1024);
    }
  }

  enum Strategy
  {
    MAX,
    AVG,
    SUM
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

  void clearScore()
  {
    _ranks.clear();
    _ranks.resize(_numLabels + 1);
    _scores.clear();
    _scores.resize(_numLabels + 1);
  }

  void clear()
  {
    clearScore();
    _counts.clear();
    _featureCounts.clear();
    _classCounts.clear();
    _classPriors.clear();
    init();
  }

  inline int labelNum()
  {
    return _numLabels;
  }

  inline FeatureSelector& method(collocation::Method method)
  {
    _method = method;
    clearScore();
    initFunc();
    return *this;
  }

  inline FeatureSelector& strategy(Strategy strategy)
  {
    _strategy = strategy;
    clearScore();
    return *this;
  }

  inline FeatureSelector& minSupport(int minSupport)
  {
    _minSupport = minSupport;
    return *this;
  }

  inline int minSupport()
  {
    return _minSupport;
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
        _featureCounts.push_back(0);

        foreach(vector<int>& vec, _counts)
        {
          vec.push_back(0);
        }
      }
      _featureCounts[idx] += 1;
      _counts[labelIdx][idx] += 1;
    }
    _classCounts[labelIdx] += 1;
  }

  void add(string doc, int label, string sep = "\t")
  {
    vector<string> words;
    boost::split(words, doc, is_any_of(sep));
    add(words, label);
  }

  //��ʱֻ����CHI TODO IG ECE MI PMI

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
        double score = _func(_counts[labelIdx][f], _featureCounts[f], _classCounts[labelIdx], _numInstances);
        _scores[labelIdx][f] = score;
        switch (_strategy)
        {
          case MAX:
            if (score > scores[f])
            {
              Pval(score);
              Pval(scores[f]);
              scores[f] = score;
            }
            break;
          case AVG:
            scores[f] += _classPriors[labelIdx] * score;
            break;
          case SUM:
            scores[f] += score;
            break;
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
      if (_featureCounts[index] >= _minSupport)
      {
        os << _index[index] << "\t" << _scores[idx][index] << endl;
      }
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
      vec.resize(_numFeatures, 0); //������Ŀ
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
  int _minSupport; //feature���ٳ��ֶ��ٴβ���Ϊ������

  DMat _scores; //��¼�����������
  IMat _ranks; //��¼���������������
};

} //----end of namespace gezi

#endif  //----end of FEATURE_SELECTOR_H_
