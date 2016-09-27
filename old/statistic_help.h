/** 
 *  ==============================================================================
 * 
 *          \file   statistic_help.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2010-12-27 18:13:17.196975
 *  
 *  \Description:  不做了。。。 boost 有 学习吧
 *
 *                 还是需要发力 阅读 STL，BOOST， CGAL 数值计算相关的库设计~
 *  ==============================================================================
 */

#ifndef STATISTIC_HELP_H_
#define STATISTIC_HELP_H_

#define BOOST_HAS_TR1_TUPLE 1
#include <boost/tr1/detail/config.hpp>
#undef BOOST_HAS_INCLUDE_NEXT

#include <algorithm>
#include <numeric>
//#include <boost/bind.hpp>

#include <boost/math/distributions/students_t.hpp>
//#include <boost/accumulators/accumulators.hpp>
//#include <boost/accumulators/statistics/stats.hpp>
//#include <boost/accumulators/statistics/mean.hpp>
//#include <boost/accumulators/statistics/moment.hpp>
namespace sta {
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
struct sd_op
{
    template<typename T1, typename T2 >
            T1 operator()(T1 init, T2 cur)
    {
        return init + cur * cur;
    }
};
/**
 *  注意vec的大小如果是1就会/0 返回结果R语言中是NA
 *  FIXME boost::optional ?
 * 注意方差是/(n - 1)的 这个才是无偏估计
 */
template<typename Container>
ValType var(const Container& vec)
{
    int n = vec.size();
    ValType x = std::pow(mean(vec), 2);
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

//----------为了假设检验,t检验
//TODO设计成t检验类，考虑以后扩展到其它检验类？ 考虑student_t 作为类的变量?
namespace student_t_help {
/**
 * 获取t值 参考概率课本p248
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
 * @param n 样本大小
 * @param e 样本均值
 * @param v 样本方差
 * @param u 假设均值
 * @return
 */
inline ValType get_val(int n, ValType e, ValType v, ValType u)
{
    ValType deno = sqrt(v / (ValType) n);
    ValType nume = e - u;
    return nume / deno;
}
/**
 * 根据t 值的bound范围 给出原始观测均值需要在的范围
 * 这个是观测的中心偏离了底下的区间 就拒绝~
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
 *  这个其实很灵活，也可以观测的中心判断，如果假设的值 偏离了 这个底下的区间 就拒绝~~
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
namespace sth = student_t_help;

namespace x2 {
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
    //TODO 这样可以避免大整数* 超过long long 如何大整数计算呢
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
     * 对应t值，获取更糟糕的偏离假设中心的概率总值，如果该值小于我们的置信度 比如a =0.05
     * 这里get_p = 0.012145 那么证明更糟糕的情况概率很小了，我们有大于95%的把握度拒绝掉原假设即观测序列的均值等于我们假设的那个均值
     * t值越大证明越偏离原心
     * 这里有两种决策方式1 是利用get_p 2.是先从置信度出发 计算边界t 值，如果我们的t在边界之外 就有理由大于1-a信任度拒绝
     */
    ValType get_pr(ValType t, int sides = 2)
    {
        if (t > 0)
            return (1 - bm::cdf(dist, t)) * sides;
        else
            return bm::cdf(dist, t) * sides;
    }
    /**
     *  注意没有/2如果需要的话 传入的时候 confidence/2
     *  表示一个区间的confidence,如果假如你考虑2个区间two side,比如置信度总共为0.05 那么你需要传递confidence 0.025
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

} //----end of namespace sta

#endif  //----end of STATISTIC_HELP_H_
