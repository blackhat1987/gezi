/**
 *  ==============================================================================
 *
 *          \file   collocation.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-01-18 22:15:02.575571
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef COLLOCATION_H_
#define COLLOCATION_H_
#include "common_util.h"

namespace gezi
{
//chi square 卡方检验 计算单个feature和单个类的卡方值,对类别整体衡量可以取多个类别中最大的或者加权平均
//information gain(信息增益) 也可称为MI(mutual info互信息) 互信息可以从 信息量差和分布相似性两个角度理解 决策树
//MI 二分类的情况下等同IG，多分类情况（A,B,C)是对每个类别比如 A按照A，～A两种情况计算IG 参考搜索引擎那本树 特征选择
//PMI 点互信息，对类别整体衡量可以对多个类别加权平均或者取PMI最大值 D:\baiduyun\ml\machine-learning.pptxt 27
//ECE 期望交叉熵 交叉熵和相对熵概念一致 KL 相对熵衡量用其他分布编码的化需要要多用的bit数，而交叉熵即是采用q分布时候一共要用的bit数
//http://en.wikipedia.org/wiki/Cross_entropy the cross entropy between two probability distributions measures 
//the average number of bits needed to identify an event from a set of possibilities, 
//if a coding scheme is used based on a given probability distribution q, rather than the "true" distribution p.
//\mathrm{H}(p, q) = \mathrm{E}_p[-\log q] = \mathrm{H}(p) + D_{\mathrm{KL}}(p \| q),\!
//期望交叉熵与信息增益很相似,不同之处在于,期望交叉熵只考虑特征在文本中发生的情况,而信息增益同时考虑了特征在文本中发生与不发生两种情况
//H(p,q) = -sum(p(x)log(q(x))
//这里说是期望交叉熵 个人觉得其实是期望相对熵的概念ERE(KL) http://wenku.baidu.com/view/742037946bec0975f465e261.html
//和mi的区别 mi 度量p(c)p(v)与p(c,v)的分布相似性(kl)，而这里试图直接度量p(c),p(c|v)的分布相似性(kl)
//语音语言处理 20.4 WSD word sense disambiguation 词的多义识别 selectional preference
//D:\baiduyun\ml\特征选择SelectionalPreference.pdf
//Information theory provides an appropriate way 
//to quantify the difference between the prior and pos- 
//terior distributions, in the form of relative entropy (Kullback and Leibler, 1951). 
//The model defines the selectional preference strength of a predicate as: ? 
//SR(p) = D(er(clp)[I Pr(c)) = E pr(clp)log Pr(clp) Pr(c) " 
//注意在文本分类里面提到的交叉熵特征选择最后还乘了pr(v) measures_of_rule_quality_for_feature_selection_in_text_categorization.pdf
namespace collocation
{

enum Method
{
  CHI, //chi square
  IG, //information gain(信息增益) 
  MI, //mutual info
  MI2, //the same as mutual info
  PMI, //point mutual info 
  ECE, //expected cross entropy 
  EMI, //expected mutual info
  T_TEST,
  LIR, //likely hood tio
  FREQ, //DF
  IDF,
};

}
//typedef double Float;

struct ChiSquareFunc
{
  /**
   *
   * @param a  coccur num of (term1,ter2)
   * @param n1   occur num of term1
   * @param n2   occur num of occur term2
   * @param n    total words
   * @return     messure
   *
   */
  //float Chi2(int a, int b, int c, int d) 
  //{ 
  //   return 
  //   (a+b+c+d) * ((a*d-b*c)^2) / 
  //      ((a+b)*(a+c)*(c+d)*(b+d)); 
  //}
  //
  //float Chi2_v2(int a, int b, int c, int d)
  //{
  //   double total = a + b + c + d;
  //   double n = Math.Log(total);
  //   double num = 2.0 * Math.Log(Math.Abs((a * d) - (b * c)));
  //   double den = Math.Log(a + b) + Math.Log(a + c) + Math.Log(c + d) + Math.Log(b + d);
  //   return (float) Math.Exp(n+num-den);
  //}

  //  Float operator()(int a00, int nterm1, int nterm2, unsigned long long n)
  //  {
  //    if (!a00)
  //      return 0;
  //    int a10 = nterm1 - a00;
  //    int a01 = nterm2 - a00;
  //    long long a11 = n - a00 - a10 - a01; 
  //    Float t = Float(a00 * a11 - a01 * a10);
  //    return (t / (a00 + a10)) * (t / (a01 + a11))
  //            * (n / Float(a10 + a11)) / (a00 + a01);
  //  }

  Float operator()(int a, int n1, int n2, uint64 total)
  {
    Float n = log(total);
    Float b = n1 - a;
    Float c = n2 - a;
    Float d = total - (a + b + c);
    Float num = 2.0 * log(fabs((a * d) - (b * c)));
    Float den = log(a + b) + log(a + c) + log(c + d) + log(b + d);
    return (Float) exp(n + num - den);
  }
};

//最后采用AVG或者 MAX模式  TODO AVG 采用 *p(f) ? 当前是 p(c)

inline Float chi_square(int a, int n1, int n2, uint64 total)
{
  Float n = log(total);
  Float b = n1 - a;
  Float c = n2 - a;
  Float d = total - (a + b + c);
  Float num = 2.0 * log(fabs((a * d) - (b * c)));
  Float den = log(a + b) + log(a + c) + log(c + d) + log(b + d);
  return (Float) exp(n + num - den);
}

struct EchoFunc
{

  Float operator()(int a, int n1, int n2, uint64 n)
  {
    return a;
  }
};

struct PointMutualInfoFunc
{

  /**
   *  点互信息
   *  log ( P(AB) / P(A)P(B) ) <=> log(O11/ E11)
   *     (AB / N) / (A / N) (B / N) = (AB * N) / (A * B )
   * 
   */
  Float operator()(int a, int n1, int n2, uint64 n)
  {
    if (!a)
      return std::numeric_limits<int>::min();
    return log(Float(n / n1) * (Float(a) / n2));
  }
};

inline Float point_mutual_info(int a, int n1, int n2, uint64 n)
{
  if (!a)
    return std::numeric_limits<int>::min();
  return log(Float(n / n1) * (Float(a) / n2));
}

//计算信息增益 这个是按照多个class 累加的需要 一次只计算一个class 的贡献  所以这个只有SUM模式才是最终的IG结果
//n1 代表feature出现次数, n2 代表 class出现次数
//??(?,?)=?(?)??(?│?)??(?|??) 
//?∑_(?∈?)?〖?(?)  log??(?) 〗?(?∑_(?∈?)?〖?(?,?)  log?〖?(?│?)〗 〗)?(?∑_(?∈?)?〖?(??,?)  log?〖?(?│??)〗 〗)
//?∑_(?∈?)?(?_?/?_?   log?(?_?/?_? )??_(?,?)/?_?   log?(?_(?,?)/?_? )?(?_???_(?,?))/?_?   log?((?_???_(?,?))/(?_???_? )) ) 
//http://www.cnblogs.com/rocketfan/p/3350450.html

inline Float information_gain(int nfc, int nf, int nc, uint64 n)
{
  Float classRatio = nc / (Float) n;
  int nfc2 = nc - nfc;
  Float p1 = nfc == 0 ? 0 : (nfc / (Float) n) * log(nfc / (Float) nf);
  Float p2 = nfc2 == 0 ? 0 : (nfc2 / (Float) n) * log(nfc2 / (Float) (n - nf));
  return -classRatio * log(classRatio) + p1 + p2;
}

//计算互信息（2class 信息增益) 这个是按照两个class 一次计算综合2个的互信息
//如果是2 class 的情况 那么计算的 两个class 数值应该一样  而且都等于上面SUM模式得到的IG

inline Float mutual_info(int nfc, int nf, int nc, uint64 n)
{
  Float val;
  Float classRatio = nc / (Float) n;
  int nfc2 = nc - nfc;
  Float p1 = nfc == 0 ? 0 : (nfc / (Float) n) * log(nfc / (Float) nf);
  Float p2 = nfc2 == 0 ? 0 : (nfc2 / (Float) n) * log(nfc2 / (Float) (n - nf));
  val = -classRatio * log(classRatio) + p1 + p2;

  classRatio = 1 - classRatio;
  nc = n - nc;
  nfc = nf - nfc;
  nfc2 = nc - nfc;
  p1 = nfc == 0 ? 0 : (nfc / (Float) n) * log(nfc / (Float) nf);
  p2 = nfc2 == 0 ? 0 : (nfc2 / (Float) n) * log(nfc2 / (Float) (n - nf));
  return val - classRatio * log(classRatio) + p1 + p2;
}

//计算互信息 方式2 应该和上面的结果相同 just for test 只按上面就好 
//http://www.cnblogs.com/rocketfan/p/3350450.html

inline Float mutual_info2(int nfc, int nf, int nc, uint64 n)
{
  Float val = 0;
  //this feature | this class
  if (nfc)
    val += ((Float) nfc / n) * log((n / (Float) nf) * (nfc / (Float) nc));
  Float nf2 = n - nf;
  Float nc2 = n - nc;
  //not this feature | this class
  Float nf2c = nc - nfc;
  if (nf2c)
  {
    val += ((Float) nf2c / n) * log((n / (Float) nf2) * (nf2c / (Float) nc));
  }
  //this feature | not this class
  Float nfc2 = nf - nfc;
  if (nfc2)
  {
    val += ((Float) nfc2 / n) * log((n / (Float) nf) * (nfc2 / (Float) nc2));
  }
  //not this feature | not this class
  Float nf2c2 = n - nf - nc + nfc;
  if (nf2c2)
  {
    val += ((Float) nf2c2 / n) * log((n / (Float) nf2) * (nf2c2 / (Float) nc2));
  }
  return val; //不在最后/n一次 而是前面都/n 是担心数值过大
}

//TODO need * p(f) ? or as now * p(c) in AVG mode?
//p(c|f) * log(p(c|f)/p(c)

inline Float cross_entropy(int nfc, int nf, int nc, uint64 n)
{
  if (!nfc)
    return 0;
  Float pf_c = nfc / (Float) nf;
  Float pc = nc / (Float) n;
  return pf_c * log(pf_c / pc);
}

struct DiscountedMutualInfoFunc
{

  /**
   *  点互信息
   *  log ( P(AB) / P(A)P(B) ) <=> log(O11/ E11)
   *     (AB / N) / (A / N) (B / N) = (AB * N) / (A * B )
   *
   */
  Float operator()(int a00, int nterm1, int nterm2, unsigned long long n)
  {
    if (!a00)
      return 0;
    int m = std::min(nterm1, nterm2);
    return ( (a00 / Float(a00 + 1)) * (m / Float(m + 1)))
            * log(Float(n / nterm1) * (Float(a00) / nterm2)) / log(2);
  }
};

struct EMutualInfoFunc
{

  /**
   * 互信息的期望值
   * E(plog ( P(AB) / P(A)P(B) )
   * 互信息的基础上 * 实际二元共现概率，矫正互信息对于低频词的偏爱
   */
  Float operator()(int a00, int nterm1, int nterm2, unsigned long long n)
  {
    if (!a00)
      return 0;
    return (Float(a00) / n) * (log(Float(n / nterm1) * (Float(a00) / nterm2)) / log(2));
  }

};

struct TTestFunc
{

  /**
   * t_test
   *  ( mean(actual) - mean(bad suppose) ) / (sd(actual) )
   *  分值越大表明bad suppose不相关假定越不靠普，也就是搭配程度越高
   *  FIXME 经常出nan
   */
  Float operator()(int a00, int nterm1, int nterm2, unsigned long long n)
  {
    if (!a00)
      return 0;
    //        return Float( a00  - nterm1 * nterm2 / n) / sqrt(a00 * n);
    return Float(a00 - (nterm1 * nterm2) / n) / sqrt(a00) * sqrt(n);
  }
};

struct EChiSquareFunc
{

  /**
   *
   * @param a00  coccur num of (term1,ter2)
   * @param nl   occur num of term1
   * @param nr   occur num of occur term2
   * @param n    total words
   * @return     messure
   *
   *  x^2 = N(a00a11 - a01a10)^2/(a00 + a01)(a00 + a10)(a01 + a11)(a10 + a11)
   *  为了防止分子过大先做了除法 较为耗时
   */
  Float operator()(int a00, int nterm1, int nterm2, unsigned long long n)
  {
    if (!a00)
      return 0;
    int a10 = nterm1 - a00;
    int a01 = nterm2 - a00;
    long long a11 = n - a00 - a10 - a01;
    Float t = Float(a00 * a11 - a01 * a10);
    return Float(a00) * (t / (a00 + a10)) * (t / (a01 + a11))
            * (n / Float(a10 + a11)) / (a00 + a01);
  }
};

struct LogEChiSquareFunc
{

  /**
   *
   * @param a00  coccur num of (term1,ter2)
   * @param nl   occur num of term1
   * @param nr   occur num of occur term2
   * @param n    total words
   * @return     messure
   *
   *  x^2 = N(a00a11 - a01a10)^2/(a00 + a01)(a00 + a10)(a01 + a11)(a10 + a11)
   *  为了防止分子过大先做了除法 较为耗时
   *  注意确保a00 > 0
   */
  Float operator()(int a00, int nterm1, int nterm2, unsigned long long n)
  {
    if (!a00)
      return 0;
    int a10 = nterm1 - a00;
    int a01 = nterm2 - a00;
    long long a11 = n - a00 - a10 - a01;
    Float t = Float(a00 * a11 - a01 * a10);
    return log(a00) * Float(t / (a00 + a10)) * (t / (a01 + a11))
            * (n / Float(a10 + a11)) / (a00 + a01);
  }
};
}
#endif  //----end of COLLOCATION_H_
