/**
 *  ==============================================================================
 *
 *          \file   Numeric/HypothesisTester.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-04-20 19:18:30.169474
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef NUMERIC__HYPOTHESIS_TESTER_H_
#define NUMERIC__HYPOTHESIS_TESTER_H_
#include "statistic_util.h"
namespace gezi {
	//@FIXME 这个头文件和py++冲突
#include <boost/math/distributions/students_t.hpp>
	namespace bm = boost::math;
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

}  //----end of namespace gezi

#endif  //----end of NUMERIC__HYPOTHESIS_TESTER_H_
