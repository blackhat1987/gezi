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
	//@FIXME ���ͷ�ļ���py++��ͻ
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

}  //----end of namespace gezi

#endif  //----end of NUMERIC__HYPOTHESIS_TESTER_H_
