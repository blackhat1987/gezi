/**
 *  ==============================================================================
 *
 *          \file   sort_util.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-01-19 17:54:00.265288
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef SORT_UTIL_H_
#define SORT_UTIL_H_

namespace gezi
{

/**
 * value从大到小排序  作为默认顺序
 */
struct CmpNode
{

  template<typename _Node>
          bool operator() (const _Node& left, const _Node& right)
  {
    return (left.second > right.second);
  }
};

struct CmpNodeValue
{

  template<typename _Node>
          bool operator() (const _Node& left, const _Node& right)
  {
    return (left.value > right.value);
  }
};

struct CmpNodeReverse
{

  template<typename _Node>
          bool operator() (const _Node& left, const _Node& right)
  {
    return (left.second < right.second);
  }
};

struct CmpNodeReverseValue
{

  template<typename _Node>
          bool operator() (const _Node& left, const _Node& right)
  {
    return (left.value < right.value);
  }
};

struct CmpNodeFirst
{

  template<typename _Node>
          bool operator() (const _Node& left, const _Node& right)
  {
    return (left.first < right.first);
  }
};

struct EqualNodeFirst
{

  template<typename _Node>
          bool operator() (const _Node& left, const _Node& right)
  {
    return (left.first == right.first);
  }
};

struct CmpNodeByID
{

  template<typename _Node>
          bool operator() (const _Node& left, const _Node& right)
  {
    return (left.id < right.id);
  }
};

struct EqualNodeByID
{

  template<typename _Node>
          bool operator() (const _Node& left, const _Node& right)
  {
    return (left.id == right.id);
  }
};

template<typename ValueVec = vector<double>, typename IndexVec = vector<int> >
struct IndexCmper
{
  ValueVec* valueVec;
  typedef typename IndexVec::value_type T;

  bool operator() (T left, T right)
  {
    return ((*valueVec)[left] > (*valueVec)[right]);
  }
};

template<typename ValueVec = vector<double>, typename IndexVec = vector<int> >
struct IndexReverseCmper
{
  ValueVec* valueVec;
  typedef typename IndexVec::value_type T;

  bool operator() (T left, T right)
  {
    return ((*valueVec)[left] < (*valueVec)[right]);
  }
};

template<typename ValueVec, typename IndexVec, typename Func>
void sort(ValueVec& valueVec, IndexVec& indexVec, Func func)
{
  func.valueVec = &valueVec;
  int len = valueVec.size();
  for (int left = 0; left < len; left++)
  {
    indexVec.push_back(left);
  }
  std::sort(indexVec.begin(), indexVec.end(), func);
}

//默认是从大到小排序
template<typename ValueVec, typename IndexVec>
void sort(ValueVec& valueVec, IndexVec& indexVec)
{
  IndexCmper<ValueVec, IndexVec> func;
  sort(valueVec, indexVec, func);
}

template<typename ValueVec, typename IndexVec, typename Func>
void sort(ValueVec& valueVec, IndexVec& indexVec, int maxLen, Func func)
{
  func.valueVec = &valueVec;
  int len = valueVec.size();
  for (int left = 0; left < len; left++)
  {
    indexVec.push_back(left);
  }
  if (len <= maxLen)
  {
    std::sort(indexVec.begin(), indexVec.end(), func);
  }
  else
  {
    std::partial_sort(indexVec.begin(), indexVec.begin() + maxLen, indexVec.end(), func);
  }
}

template<typename ValueVec, typename IndexVec>
void sort(ValueVec& valueVec, IndexVec& indexVec, int maxLen)
{
  IndexCmper<ValueVec, IndexVec> func;
  sort(valueVec, indexVec, maxLen, func);
}
} //----end of namespace gezi

#endif  //----end of SORT_UTIL_H_
