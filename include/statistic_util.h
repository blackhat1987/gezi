/** 
 *  ==============================================================================
 * 
 *          \file   statistic_util.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2010-12-27 18:13:17.196975
 *  
 *  \Description: 
 *  ==============================================================================
 */

#ifndef STATISTIC_UTIL_H_
#define STATISTIC_UTIL_H_

//���ʹ�ø߰汾gcc��Ϊ�Ѿ���std::tr1::tuple��Ҫ����
#if __GNUC__ > 3
#define BOOST_HAS_TR1_TUPLE 1  
#include <boost/tr1/detail/config.hpp>
#undef BOOST_HAS_INCLUDE_NEXT 
#endif

#include <algorithm>
#include <numeric>
//#include <boost/bind.hpp>

#include <boost/math/distributions/students_t.hpp>

#include "common_util.h"
#include "feature/Feature.h"
//#include <boost/accumulators/accumulators.hpp>
//#include <boost/accumulators/statistics/stats.hpp>
//#include <boost/accumulators/statistics/mean.hpp>
//#include <boost/accumulators/statistics/moment.hpp>
namespace gezi
{
typedef double ValType;
//namespace ba = boost::accumulators;
namespace bm = boost::math;
//using boost::bind;
//using boost::ref;

template<typename Iter>
ValType sum(Iter start, Iter end)
{
  return std::accumulate(start, end, 0.0);
}

template<typename Container>
ValType sum(const Container& vec)
{
  return sum(vec.begin(), vec.end());
}

template<typename Iter>
ValType mean(Iter start, Iter end)
{
  return std::accumulate(start, end, 0.0) / (ValType) (end - start);
}

template<typename Container>
ValType mean(const Container& vec)
{
  return std::accumulate(vec.begin(), vec.end(), 0.0) / (ValType) vec.size();
}

template<typename Container>
ValType mean(const Container& vec, int n)
{
  return std::accumulate(vec.begin(), vec.end(), 0.0) / (ValType) n;
}

struct sd_op
{

  template<typename T1, typename T2 >
          T1 operator()(T1 init, T2 cur)
  {
    return init + cur * cur;
  }
};

/**
 *  ע��vec�Ĵ�С�����1�ͻ�/0 ���ؽ��NAN ע����� int/int /0��core ������ ����nan
 *  FIXME boost::optional ?
 * ע�ⷽ����/(n - 1)�� ���������ƫ����
 */
template<typename Container>
ValType var(const Container& vec)
{
  int n = vec.size();
  ValType x = std::pow(mean(vec), 2);
  ValType y = std::accumulate(vec.begin(), vec.end(), 0.0, sd_op()) / (n - 1);
  return y - (x * n / ValType(n - 1));
}

template<typename Container>
ValType var(const Container& vec, int n)
{
  ValType x = std::pow(mean(vec, n), 2);
  ValType y = std::accumulate(vec.begin(), vec.end(), 0.0, sd_op()) / (n - 1);
  return y - (x * n / ValType(n - 1));
}

template<typename Iter>
ValType var(Iter start, Iter end)
{
  int n = end - start;
  ValType x = std::pow(mean(start, end), 2);
  ValType y = std::accumulate(start, end, 0.0, sd_op()) / (ValType) (n - 1);
  return y - (x * n / ValType(n - 1));
}
//struct sd_op_
//{
//    template<typename T1, typename T2 >
//            T1 operator()(T1 init, T2 cur, T2 del)
//    {
//        return init + std::pow((cur - del), 2);
//    }
//};

template<typename Container>
ValType var(const Container& vec, ValType mean)
{
  ValType sum = 0.0;
  int n = vec.size();
  for (size_t i = 0; i < n; i++)
  {
    sum += std::pow(vec[i] - mean, 2);
  }
  return sum / (ValType) (n - 1);
}

template<typename Container>
ValType var(const Container& vec, ValType mean, int n)
{
  ValType sum = 0.0;
  int len = vec.size();
  for (int i = 0; i < len; i++)
  {
    sum += std::pow(vec[i] - mean, 2);
  }
  sum += (n - len) * std::pow(mean, 2);
  return sum / (ValType) (n - 1);
}

template<typename Container>
ValType var_(const Container& vec)
{
  ValType x = mean(vec);

  //TODO how to here??
  //    return std::accumulate(vec.begin(), vec.end(), 0.0, boost::bind(sd_op_(_1, _2, x))) / (ValType) vec.size();
  ValType sum = 0.0;
  int n = vec.size();
  for (size_t i = 0; i < n; i++)
  {
    sum += std::pow(vec[i] - x, 2);
  }
  return sum / (ValType) (n - 1);
}

template<typename Container>
ValType sd(const Container& vec)
{
  return sqrt(var(vec));
}

template<typename Iter>
ValType sd(Iter start, Iter end)
{
  return sqrt(var(start, end));
}

//----------Ϊ�˼������,t����
//TODO��Ƴ�t�����࣬�����Ժ���չ�����������ࣿ ����student_t ��Ϊ��ı���?
namespace student_t
{

/**
 * ��ȡtֵ �ο����ʿα�p248
 */
template<typename Iter>
ValType get_val(Iter start, Iter end, ValType u)
{
  int n = end - start;
  ValType m = mean(start, end);
  ValType x = std::pow(mean(start, end), 2);
  ValType y = std::accumulate(start, end, 0.0, sd_op()) / (ValType) (n - 1);
  ValType deno = sqrt((y - (x * n / ValType(n - 1))) / (ValType) n);
  ValType nume = m - u;
  return nume / deno;
}

template<typename Container>
ValType get_val(const Container& vec, ValType u)
{
  return get_val(vec.begin(), vec.end(), u);
}

/**
 *
 * @param n ������С
 * @param e ������ֵ
 * @param v ��������
 * @param u �����ֵ
 * @return
 */
inline ValType get_val(int n, ValType e, ValType v, ValType u)
{
  ValType deno = sqrt(v / (ValType) n);
  ValType nume = e - u;
  return nume / deno;
}

/**
 * ����t ֵ��bound��Χ ����ԭʼ�۲��ֵ��Ҫ�ڵķ�Χ
 * ����ǹ۲������ƫ���˵��µ����� �;ܾ�~
 */
inline std::pair<ValType, ValType> get_bound(const std::pair<ValType, ValType>& bound, int n, ValType e, ValType v, ValType u)
{
  std::pair<ValType, ValType> p;
  ValType deno = sqrt(v / (ValType) n);
  p.first = bound.first * deno + u;
  p.second = bound.second * deno + u;
  return p;
}

/**
 *  �����ʵ����Ҳ���Թ۲�������жϣ���������ֵ ƫ���� ������µ����� �;ܾ�~~
 */
inline std::pair<ValType, ValType> get_bound2(const std::pair<ValType, ValType>& bound, int n, ValType e, ValType v, ValType u)
{
  std::pair<ValType, ValType> p;
  ValType deno = sqrt(v / (ValType) n);
  p.first = e - bound.second * deno;
  p.second = e - bound.first * deno;
  return p;
}

}//-----end of namespace student_t_help
namespace sth = student_t;

namespace x2
{

inline ValType get_val(int n00, int n01, int n10, int n11)
{
  int n = n00 + n01 + n10 + n11;
  int a = n11 * n00 - n10 * n01;
  //    return (long long)n * ((long long)(a * a) / ValType((n11 + n01) * (n11 + n10) * (n10 + n00) * (n01 + n00)));
  return (n / ValType(n11 + n01)) * (a / ValType(n11 + n10)) * (a / ValType(n10 + n00)) / ValType(n01 + n00);
}

inline ValType get_val(int n, int n00, int n01, int n10, int n11)
{
  int a = n11 * n00 - n10 * n01;
  //TODO �������Ա��������* ����long long ��δ�����������
  //    return (long long)n * ((long long)(a * a) / ValType((n11 + n01) * (n11 + n10) * (n10 + n00) * (n01 + n00)));
  return (n / ValType(n11 + n01)) * (a / ValType(n11 + n10)) * (a / ValType(n10 + n00)) / ValType(n01 + n00);
}

}

template<typename TestModel = bm::students_t>
class HypothesisTester
{
public:

  HypothesisTester(TestModel& dist_)
  : dist(dist_)
  {

  }

  /**
   * ��Ӧtֵ����ȡ������ƫ��������ĵĸ�����ֵ�������ֵС�����ǵ����Ŷ� ����a =0.05
   * ����get_p = 0.012145 ��ô֤��������������ʺ�С�ˣ������д���95%�İ��նȾܾ���ԭ���輴�۲����еľ�ֵ�������Ǽ�����Ǹ���ֵ
   * tֵԽ��֤��Խƫ��ԭ��
   * ���������־��߷�ʽ1 ������get_p 2.���ȴ����Ŷȳ��� ����߽�t ֵ��������ǵ�t�ڱ߽�֮�� �������ɴ���1-a���ζȾܾ�
   */
  ValType get_pr(ValType t, int sides = 2)
  {
    if (t > 0)
      return (1 - bm::cdf(dist, t)) * sides;
    else
      return bm::cdf(dist, t) * sides;
  }

  /**
   *  ע��û��/2�����Ҫ�Ļ� �����ʱ�� confidence/2
   *  ��ʾһ�������confidence,��������㿼��2������two side,�������Ŷ��ܹ�Ϊ0.05 ��ô����Ҫ����confidence 0.025
   */
  std::pair<ValType, ValType> get_bound(ValType confidence)
  {
    std::pair<ValType, ValType> p;
    p.first = bm::quantile(dist, confidence);
    p.second = bm::quantile(dist, 1 - confidence);
    return p;
  }

  ValType get_upperbound(ValType confidence)
  {
    return bm::quantile(dist, 1 - confidence);
  }

  ValType get_lowerbound(ValType confidence)
  {
    return bm::quantile(dist, confidence);
  }
public:
  TestModel& dist;
};

//----------------Ͱ���� ����2��Ͱ [0,0.5) 0 [0.5,1) 1

inline int bin_index(double value, int bin_num, double min = 0, double max = 1.0)
{
  if (value <= min)
  {
    return 0;
  }
  if (value >= max)
  {
    return bin_num - 1;
  }
  double span = (max - min) / bin_num;
  int bin_index = (value - min) / span;
  return bin_index;
}

inline int bin_index(double value, const vector<double>& thres)
{
  int i = 0;
  for (; i < (int) thres.size(); i++)
  {
    if (value < thres[i])
    {
      return i;
    }
  }
  return i;
}

inline vector<int> bin_counts(const vector<double>& values, int bin_num,
        double min = 0, double max = 1.0)
{
  vector<int> bins(bin_num, 0);

  foreach(double value, values)
  {
    int bin_index_ = bin_index(value, bin_num, min, max);
    bins[bin_index_]++;
  }
#ifdef __GXX_EXPERIMENTAL_CXX0X__
  return std::move(bins);
#else
  return bins;
#endif
}

inline vector<double> bin_values(const vector<double>& values, int bin_num,
        double min = 0, double max = 1.0)
{
  vector<double> bin_values(bin_num, 0);
  vector<int> bins = bin_counts(values, bin_num, min, max);
  int count = values.size();
  for (int i = 0; i < bin_num; i++)
  {
    bin_values[i] = (double) bins[i] / count;
  }
#ifdef __GXX_EXPERIMENTAL_CXX0X__
  return std::move(bin_values);
#else
  return bin_values;
#endif
}

//����thes 0.3,0.5,0.7  ���� ..,0.3) [0.3,0.5)[0.5,0.7) [0.7,...  4��Ͱ

inline vector<int> bin_counts(const vector<double>& values, const vector<double>& thres)
{
  int bin_num = thres.size() + 1;
  vector<int> bins(bin_num, 0);

  foreach(double value, values)
  {
    int bin_index_ = bin_index(value, thres);
    bins[bin_index_]++;
  }
#ifdef __GXX_EXPERIMENTAL_CXX0X__
  return std::move(bins);
#else
  return bins;
#endif
}

inline vector<double> bin_values(const vector<double>& values, const vector<double>& thres)
{
  int bin_num = thres.size() + 1;
  vector<double> bin_values(bin_num, 0);
  vector<int> bins = bin_counts(values, thres);
  int count = values.size();
  for (int i = 0; i < bin_num; i++)
  {
    bin_values[i] = (double) bins[i] / count;
  }
#ifdef __GXX_EXPERIMENTAL_CXX0X__
  return std::move(bin_values);
#else
  return bin_values;
#endif
}

//TODO verify

inline double discretize(double value, double from, double to, int bins, bool norm = true)
{
  double step = (to - from) / bins;
  double res;
  if (value <= from)
  {
    res = from;

  }
  else if (value >= to)
  {
    res = to - step;
  }
  else
  {
    res = from + floor((value - from) / step) * step;

  }
  if (norm)
  {
    res = (res - from) / (to - from - step);
  }
  return res;
}
template<typename Iter>
inline double information(Iter begin, Iter end) 
{
  typedef typename Iter::value_type KeyType;
  std::tr1::unordered_map<KeyType, int> m;
  for (Iter it = begin; it != end; ++it) 
  {
    add_one(m, *it);
  }
  typedef std::pair<const KeyType, int> Pair; 
  double res = 0;
  int total = end - begin;
  foreach(Pair& item, m) 
  {
    double prob = item.second / (double)total;
    res += -prob * log(prob);
  }
  return res;
}

template<typename T>
inline double information(vector<T>& vec)
{
  return information(vec.begin(), vec.end());
}

//TODO ���ֱ���Ƶ�ValueType �������ֲ��� �õ����Ǳ���const long long &
//template<typename Iter, typename Func>
//std::size_t distinct_count(Iter begin, Iter end, Func func)
//{
//    typedef typename Func::result_type ValueType;
//    std::tr1::unordered_set<ValueType> vset;
//    for(Iter it = begin; it != end; ++it)
//    {
//        vset.insert(func(*it));
//    }
//    return vset.size();
//}

template<typename ValueType, typename Iter, typename Func>
std::size_t distinct_count(Iter begin, Iter end, Func func)
{
  std::tr1::unordered_set<ValueType> vset;
  for (Iter it = begin; it != end; ++it)
  {
    vset.insert(func(*it));
  }
  return vset.size();
}

template<typename Iter, typename Func>
std::size_t distinct_count(Iter begin, Iter end, Func func)
{
  typedef typename Iter::value_type ValueType;
  std::tr1::unordered_set<ValueType> vset;
  for (Iter it = begin; it != end; ++it)
  {
    vset.insert(func(*it));
  }
  return vset.size();
}

template<typename Iter>
std::size_t distinct_count(Iter begin, Iter end)
{
  typedef typename Iter::value_type ValueType;
  std::tr1::unordered_set<ValueType> vset;
  for (Iter it = begin; it != end; ++it)
  {
    vset.insert(*it);
  }
  return vset.size();
}

template<typename Container>
std::size_t distinct_count(Container& vec)
{
  distinct_count(vec.begin(), vec.end());
}

template<typename Container, typename Func>
std::size_t distinct_count(Container& vec, Func func)
{
  return distinct_count(vec.begin(), vec.end(), func);
}

} //----end of namespace sta
namespace sta = gezi; //TODO temply now since I use many sta:: right now
#endif  //----end of STATISTIC_UTIL_H_
