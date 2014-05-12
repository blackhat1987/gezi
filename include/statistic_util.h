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

//如果使用高版本gcc因为已经有std::tuple需要下面
#if __GNUC__ > 3
#define BOOST_HAS_TR1_TUPLE 1  
#include <boost/tr1/detail/config.hpp>
#undef BOOST_HAS_INCLUDE_NEXT 
#endif

#include <algorithm>
#include <numeric>
//#include <boost/bind.hpp>

#include "hashmap_util.h"
#include "common_util.h"

#include "Numeric/find_bins.h"

//#include <boost/accumulators/accumulators.hpp>
//#include <boost/accumulators/statistics/stats.hpp>
//#include <boost/accumulators/statistics/mean.hpp>
//#include <boost/accumulators/statistics/moment.hpp>
namespace gezi {
	static const Float EPSILON = (Float)1e-15;
	typedef double ValType;
	//namespace ba = boost::accumulators;
	//using boost::bind;
	//using boost::ref;

	//@TODO FIXME 
	//http://stackoverflow.com/questions/17333/most-effective-way-for-float-and-double-comparison 
	inline bool are_same(double a, double b)
	{
		return fabs(a - b) < EPSILON;
	}

	inline bool is_zero(double a)
	{
		return fabs(a) < EPSILON;
	}

	inline double sigmoid(double score, double A, double B)
	{
		return 1.0 / (1 + exp(A * score + B));
	}

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
	size_t num_zeros(Iter start, Iter end)
	{
		typedef typename Iter::value_type ValueType;
		return std::accumulate(start, end, (size_t)0, [](ValueType a) { return a == 0; });
	}

	template<typename Container>
	size_t num_zeros(const Container& vec)
	{
		return num_zeros(vec.begin(), vec.end());
	}

	template<typename Iter>
	size_t num_nonzeros(Iter start, Iter end)
	{
		typedef typename Iter::value_type ValueType;
		return std::accumulate(start, end, (size_t)0, [](ValueType a) { return a != 0; });
	}

	template<typename Container>
	size_t num_nonzeros(const Container& vec)
	{
		return num_nonzeros(vec.begin(), vec.end());
	}

	template<typename Iter>
	ValType mean(Iter start, Iter end)
	{
		return std::accumulate(start, end, 0.0) / (ValType)(end - start);
	}

	template<typename Container>
	ValType mean(const Container& vec)
	{
		return std::accumulate(vec.begin(), vec.end(), 0.0) / (ValType)vec.size();
	}

	template<typename Container>
	ValType mean(const Container& vec, int n)
	{
		return std::accumulate(vec.begin(), vec.end(), 0.0) / (ValType)n;
	}

	template<typename Container, typename T>
	size_t first_ge(const Container& vec, T value)
	{
		return std::lower_bound(vec.begin(), vec.end(), value) - vec.begin();
	}

	namespace ufo {

		template<typename Container>
		ValType min(const Container& vec)
		{
			return *(std::min_element(vec.begin(), vec.end()));
		}

		template<typename Container, typename Iter>
		Iter min_element(const Container& vec)
		{
			return std::min_element(vec.begin(), vec.end());
		}


		template<typename Container>
		ValType max(const Container& vec)
		{
			return *(std::max_element(vec.begin(), vec.end()));
		}

		template<typename Container, typename Iter>
		Iter max_element(const Container& vec)
		{
			return std::max_element(vec.begin(), vec.end());
		}

		template<typename Container, typename ValueType>
		void fill(const Container& vec, const ValueType& val)
		{
			std::fill(vec.begin(), vec.end(), val);
		}
	}

	template<typename Container>
	size_t min_index(const Container& vec)
	{
		return std::min_element(vec.begin(), vec.end()) - vec.begin();
	}

	template<typename Container>
	size_t max_index(const Container& vec)
	{
		return std::max_element(vec.begin(), vec.end()) - vec.begin();
	}

	//如果找不到 返回vec.size()
	template<typename Container, typename ValueType>
	size_t find_index(const Container& vec, const ValueType& val)
	{
		return std::find(vec.begin(), vec.end(), val) - vec.begin();
	}

	template<typename Container>
	void zeroset(Container& vec)
	{
		std::fill(vec.begin(), vec.end(), 0);
	}

	template<typename Iter, typename Iter2>
	void fill_range(Iter dest, Iter2 src, int len)
	{
		for (int i = 0; i < len; i++)
		{
			*dest++ = *src++;
		}
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
	 *  注意vec的大小如果是1就会/0 返回结果NAN 注意如果 int/int /0会core 而浮点 则是nan
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
		ValType y = std::accumulate(start, end, 0.0, sd_op()) / (ValType)(n - 1);
		return y - (x * n / ValType(n - 1));
	}

	template<typename Iter, typename ValType>
	void mean_var(Iter start, Iter end, ValType& mean_, ValType& var_)
	{
		int n = end - start;
		mean_ = mean(start, end);
		ValType x = std::pow(mean_, 2);
		ValType y = std::accumulate(start, end, 0.0, sd_op()) / (ValType)(n - 1);
		var_ = y - (x * n / ValType(n - 1));
	}

	template<typename Container, typename ValType>
	void mean_var(const Container& vec, ValType& mean_, ValType& var_)
	{
		int n = vec.size();
		mean_ = mean(vec);
		ValType x = std::pow(mean(vec), 2);
		ValType y = std::accumulate(vec.begin(), vec.end(), 0.0, sd_op()) / (n - 1);
		var_ = y - (x * n / ValType(n - 1));
	}

	template<typename Iter>
	ValType var(Iter start, Iter end, ValType mean)
	{
		int n = end - start;
		ValType x = std::pow(mean, 2);
		ValType y = std::accumulate(start, end, 0.0, sd_op()) / (ValType)(n - 1);
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
		size_t n = vec.size();
		for (size_t i = 0; i < n; i++)
		{
			sum += std::pow(vec[i] - mean, 2);
		}
		return sum / (ValType)(n - 1);
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
		return sum / (ValType)(n - 1);
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
		return sum / (ValType)(n - 1);
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

	//----------为了假设检验,t检验
	//TODO设计成t检验类，考虑以后扩展到其它检验类？ 考虑student_t 作为类的变量?
	namespace student_t {

		/**
		 * 获取t值 参考概率课本p248
		 */
		template<typename Iter>
		ValType get_val(Iter start, Iter end, ValType u)
		{
			int n = end - start;
			ValType m = mean(start, end);
			ValType x = std::pow(mean(start, end), 2);
			ValType y = std::accumulate(start, end, 0.0, sd_op()) / (ValType)(n - 1);
			ValType deno = sqrt((y - (x * n / ValType(n - 1))) / (ValType)n);
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
			ValType deno = sqrt(v / (ValType)n);
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
			ValType deno = sqrt(v / (ValType)n);
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
			ValType deno = sqrt(v / (ValType)n);
			p.first = e - bound.second * deno;
			p.second = e - bound.first * deno;
			return p;
		}

	}//-----end of namespace student_t_help
	namespace sth = student_t;
	//----------------桶计数 比如2个桶 [0,0.5) 0 [0.5,1) 1

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
		for (; i < (int)thres.size(); i++)
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
		return bins;
	}

	inline vector<double> bin_values(const vector<double>& values, int bin_num,
		double min = 0, double max = 1.0)
	{
		vector<double> bin_values(bin_num, 0);
		vector<int> bins = bin_counts(values, bin_num, min, max);
		int count = values.size();
		for (int i = 0; i < bin_num; i++)
		{
			bin_values[i] = (double)bins[i] / count;
		}
		return bin_values;
	}

	//例如thes 0.3,0.5,0.7  就是 ..,0.3) [0.3,0.5)[0.5,0.7) [0.7,...  4个桶

	inline vector<int> bin_counts(const vector<double>& values, const vector<double>& thres)
	{
		int bin_num = thres.size() + 1;
		vector<int> bins(bin_num, 0);

		foreach(double value, values)
		{
			int bin_index_ = bin_index(value, thres);
			bins[bin_index_]++;
		}
		return bins;
	}

	inline vector<double> bin_values(const vector<double>& values, const vector<double>& thres)
	{
		int bin_num = thres.size() + 1;
		vector<double> bin_values(bin_num, 0);
		vector<int> bins = bin_counts(values, thres);
		int count = values.size();
		for (int i = 0; i < bin_num; i++)
		{
			bin_values[i] = (double)bins[i] / count;
		}
		return bin_values;
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

	//信息量
	template<typename Iter>
	inline double information(Iter begin, Iter end)
	{
		typedef typename Iter::value_type KeyType;
		std::unordered_map<KeyType, int> m;
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

	//TODO 如何直接推导ValueType 下面这种不行 得到的是比如const long long &
	//template<typename Iter, typename Func>
	//std::size_t distinct_count(Iter begin, Iter end, Func func)
	//{
	//    typedef typename Func::result_type ValueType;
	//    unordered_set<ValueType> vset;
	//    for(Iter it = begin; it != end; ++it)
	//    {
	//        vset.insert(func(*it));
	//    }
	//    return vset.size();
	//}

	//如果数据量少 unordered_set比set要慢
	template<typename ValueType, typename Iter, typename Func>
	std::size_t distinct_count(Iter begin, Iter end, Func func)
	{
		unordered_set<ValueType> vset;
		for (Iter it = begin; it != end; ++it)
		{
			vset.insert(func(*it));
		}
		return vset.size();
	}

	template<typename ValueType, typename Container, typename Func>
	std::size_t distinct_count(Container& vec, Func func)
	{
		return distinct_count<ValueType>(vec.begin(), vec.end(), func);
	}


	template<typename Iter>
	std::size_t distinct_count(Iter begin, Iter end)
	{
		typedef typename Iter::value_type ValueType;
		unordered_set<ValueType> vset;
		for (Iter it = begin; it != end; ++it)
		{
			vset.insert(*it);
		}
		return vset.size();
	}

	template<typename Container>
	std::size_t distinct_count(Container& vec)
	{
		return distinct_count(vec.begin(), vec.end());
	}


#if __GNUC__ > 3

	template<typename Iter, typename Func>
	std::size_t distinct_count(Iter begin, Iter end, Func func)
	{
		if (begin == end)
			return 0;
		auto a = func(*begin);
		typedef decltype(a) ValueType;
		unordered_set<ValueType> vset;
		for (Iter it = begin; it != end; ++it)
		{
			vset.insert(func(*it));
		}
		return vset.size();
	}

	template<typename Container, typename Func>
	std::size_t distinct_count(Container& vec, Func func)
	{
		return distinct_count(vec.begin(), vec.end(), func);
	}
#endif

} //----end of namespace sta
namespace sta = gezi; //@TODO temply now since I use many sta:: right now
#endif  //----end of STATISTIC_UTIL_H_
