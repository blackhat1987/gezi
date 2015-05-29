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
#include <cmath>
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
	//namespace ba = boost::accumulators;
	//using boost::bind;
	//using boost::ref;

	//@TODO FIXME 
	//http://stackoverflow.com/questions/17333/most-effective-way-for-float-and-double-comparison 
	inline bool are_same(double a, double b)
	{
		return fabs(a - b) < std::numeric_limits<double>::epsilon();
	}

	inline bool is_zero(double a)
	{
		return fabs(a) < std::numeric_limits<double>::epsilon();
	}

	//A一般取 -2 或者 1 按照logistic regression的习惯 看F(x）=log(p)/log(-1p)  -> A = -1 还是 F(x) = 1/2 * (log(p)/log(1-p)) -> A = -2
	inline double sigmoid(double score, double A = -2.0, double B = 0.0)
	{
		return 1.0 / (1.0 + std::exp(A * score + B));
	}

	template<typename Iter>
	//auto sum(Iter start, Iter end) -> decltype(*start) 
	// In instantiation of 'decltype (* start) gezi::sum(Iter, Iter) [with Iter = __gnu_cxx::__normal_iterator<const int*, std::vector<int> >; decltype (* start) = const int&]':
	typename Iter::value_type sum(Iter start, Iter end)
	{
		return std::accumulate(start, end, 0);
	}

	template<typename Container>
	typename Container::value_type sum(const Container& vec)
	{
		return sum(vec.begin(), vec.end());
	}

	template<typename value_type, typename Iter>
	//auto sum(Iter start, Iter end) -> decltype(*start) 
	// In instantiation of 'decltype (* start) gezi::sum(Iter, Iter) [with Iter = __gnu_cxx::__normal_iterator<const int*, std::vector<int> >; decltype (* start) = const int&]':
	value_type sum(Iter start, Iter end)
	{
		return std::accumulate(start, end, 0);
	}

	template<typename value_type, typename Container>
	value_type sum(const Container& vec)
	{
		return sum<value_type>(vec.begin(), vec.end());
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
	double mean(Iter start, Iter end)
	{
		return std::accumulate(start, end, 0.0) / (double)(end - start);
	}

	template<typename Container>
	double mean(const Container& vec)
	{
		return std::accumulate(vec.begin(), vec.end(), 0.0) / (double)vec.size();
	}

	template<typename Container>
	double mean(const Container& vec, int n)
	{
		return std::accumulate(vec.begin(), vec.end(), 0.0) / (double)n;
	}

	template<typename Container, typename T>
	size_t first_ge(const Container& vec, T value)
	{
		return std::lower_bound(vec.begin(), vec.end(), value) - vec.begin();
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

	template<typename Container>
	void set_zero(Container& vec)
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

	template<typename Container>
	double norm(const Container& values)
	{
		return sqrt(std::accumulate(values.begin(), values.end(), 0.0, sd_op()));
	}

	template<typename Container>
	double sqared_norm(const Container& values)
	{
		return std::accumulate(values.begin(), values.end(), 0.0, sd_op());
	}


	/**
	 *  注意vec的大小如果是1就会/0 返回结果NAN 注意如果 int/int /0会core 而浮点 则是nan
	 *  FIXME boost::optional ?
	 * 注意方差是/(n - 1)的 这个才是无偏估计
	 */
	template<typename Container>
	double var(const Container& vec)
	{
		int n = vec.size();
		double x = std::pow(mean(vec), 2);
		double y = std::accumulate(vec.begin(), vec.end(), 0.0, sd_op()) / (n - 1);
		return y - (x * n / double(n - 1));
	}

	template<typename Container>
	double var(const Container& vec, int n)
	{
		double x = std::pow(mean(vec, n), 2);
		double y = std::accumulate(vec.begin(), vec.end(), 0.0, sd_op()) / (n - 1);
		return y - (x * n / double(n - 1));
	}

	template<typename Iter>
	double var(Iter start, Iter end)
	{
		int n = end - start;
		double x = std::pow(mean(start, end), 2);
		double y = std::accumulate(start, end, 0.0, sd_op()) / (double)(n - 1);
		return y - (x * n / double(n - 1));
	}

	template<typename Iter>
	void mean_var(Iter start, Iter end, double& mean_, double& var_)
	{
		int n = end - start;
		mean_ = mean(start, end);
		double x = std::pow(mean_, 2);
		double y = std::accumulate(start, end, 0.0, sd_op()) / (double)(n - 1);
		var_ = y - (x * n / double(n - 1));
	}

	template<typename Container>
	void mean_var(const Container& vec, double& mean_, double& var_)
	{
		int n = vec.size();
		mean_ = mean(vec);
		double x = std::pow(mean_, 2);
		double y = std::accumulate(vec.begin(), vec.end(), 0.0, sd_op()) / (n - 1);
		var_ = y - (x * n / double(n - 1));
	}

	template<typename Iter>
	double var(Iter start, Iter end, double meanVal)
	{
		int n = end - start;
		double x = std::pow(meanVal, 2);
		double y = std::accumulate(start, end, 0.0, sd_op()) / (double)(n - 1);
		return y - (x * n / double(n - 1));
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
	double var(const Container& vec, double meanVal)
	{
		double sum = 0.0;
		size_t n = vec.size();
		for (size_t i = 0; i < n; i++)
		{
			sum += std::pow(vec[i] - meanVal, 2);
		}
		return sum / (double)(n - 1);
	}

	template<typename Container>
	double var(const Container& vec, double meanVal, int n)
	{
		double sum = 0.0;
		int len = vec.size();
		for (int i = 0; i < len; i++)
		{
			sum += std::pow(vec[i] - meanVal, 2);
		}
		sum += (n - len) * std::pow(meanVal, 2);
		return sum / (double)(n - 1);
	}

	template<typename Container>
	double var_(const Container& vec)
	{
		double x = mean(vec);

		//TODO how to here??
		//    return std::accumulate(vec.begin(), vec.end(), 0.0, boost::bind(sd_op_(_1, _2, x))) / (double) vec.size();
		double sum = 0.0;
		int n = vec.size();
		for (size_t i = 0; i < n; i++)
		{
			sum += std::pow(vec[i] - x, 2);
		}
		return sum / (double)(n - 1);
	}

	template<typename Container>
	double sd(const Container& vec)
	{
		return sqrt(var(vec));
	}

	template<typename Iter>
	double sd(Iter start, Iter end)
	{
		return sqrt(var(start, end));
	}

	namespace ufo {

		//注意如果在相同namespace mean(vec, 0) 会去调用mean(Iter, Iter) mean(vec, 0.0) ok
		template<typename Container>
		double mean(const Container& vec, double defaultValue)
		{
			if (vec.empty())
			{
				return defaultValue;
			}
			return std::accumulate(vec.begin(), vec.end(), 0.0) / (double)vec.size();
		}

		template<typename Container>
		double mean(const Container& vec)
		{
			if (vec.empty())
			{
				return 0;
			}
			return std::accumulate(vec.begin(), vec.end(), 0.0) / (double)vec.size();
		}

		template<typename Container>
		double var(const Container& vec)
		{
			if (vec.size() > 1)
			{
				return 0;
			}
			return gezi::var(vec);
		}

		template<typename Container>
		double var(const Container& vec, double defaultValue, int minCount = 2)
		{
			if (vec.size() < minCount)
			{
				return defaultValue;
			}
			return gezi::var(vec);
		}

		template<typename Container>
		void mean_var(const Container& vec, double& meanVal, double& varVal, int minCount = 2)
		{
			if (vec.empty())
			{
				return;
			}
			meanVal = std::accumulate(vec.begin(), vec.end(), 0.0) / (double)vec.size();

			if (vec.size() < minCount)
			{
				return;
			}
			varVal = gezi::var(vec, meanVal);
		}

		template<typename Container>
		void mean_min_max(const Container& vec, double& meanVal, double& minVal, double& maxVal)
		{
			if (vec.empty())
			{
				return;
			}
			double mean_ = 0, minVal_ = std::numeric_limits<double>::max(), maxVal_ = std::numeric_limits<double>::lowest();
			for (auto& val : vec)
			{
				mean_ += vec;
				if (val > maxVal_)
				{
					maxVal_ = val;
				}
				if (val < minVal_)
				{
					minVal_ = val;
				}
			}
			meanVal = mean_ / vec.size();
			minVal = minVal_;
			maxVal = maxVal_;
		}


		template<typename Container>
		//auto min(const Container& vec) -> decltype(*vec.begin()) //show decltype also work
		typename Container::value_type min(const Container& vec)
		{
			return *(std::min_element(vec.begin(), vec.end()));
		}

		template<typename Container, typename T>
		typename Container::value_type  min(const Container& vec, T defaultValue)
		{
			if (vec.empty())
			{
				return defaultValue;
			}
			return *(std::min_element(vec.begin(), vec.end()));
		}

		template<typename Container, typename Iter>
		Iter min_element(const Container& vec)
		{
			return std::min_element(vec.begin(), vec.end());
		}


		template<typename Container>
		//double max(const Container& vec)
		//auto max(const Container& vec) ->decltype(*vec.begin()) //暂时python wrapper无法处理
		typename Container::value_type max(const Container& vec)
		{
			return *(std::max_element(vec.begin(), vec.end()));
		}

		template<typename Container, typename T>
		typename Container::value_type  max(const Container& vec, T defaultValue)
		{
			if (vec.empty())
			{
				return defaultValue;
			}
			return *(std::max_element(vec.begin(), vec.end()));
		}

		template<typename Container>
		typename Container::const_iterator max_element(const Container& vec)
		{
			return std::max_element(vec.begin(), vec.end());
		}

		template<typename Container, typename ValueType>
		void fill(Container& vec, const ValueType& val)
		{
			std::fill(vec.begin(), vec.end(), val);
		}
	}

	namespace x2 {

		inline double get_val(int n00, int n01, int n10, int n11)
		{
			int n = n00 + n01 + n10 + n11;
			int a = n11 * n00 - n10 * n01;
			//    return (long long)n * ((long long)(a * a) / double((n11 + n01) * (n11 + n10) * (n10 + n00) * (n01 + n00)));
			return (n / double(n11 + n01)) * (a / double(n11 + n10)) * (a / double(n10 + n00)) / double(n01 + n00);
		}

		inline double get_val(int n, int n00, int n01, int n10, int n11)
		{
			int a = n11 * n00 - n10 * n01;
			//TODO 这样可以避免大整数* 超过long long 如何大整数计算呢
			//    return (long long)n * ((long long)(a * a) / double((n11 + n01) * (n11 + n10) * (n10 + n00) * (n01 + n00)));
			return (n / double(n11 + n01)) * (a / double(n11 + n10)) * (a / double(n10 + n00)) / double(n01 + n00);
		}

	}

	//----------为了假设检验,t检验
	//TODO设计成t检验类，考虑以后扩展到其它检验类？ 考虑student_t 作为类的变量?
	namespace student_t {

		/**
		 * 获取t值 参考概率课本p248
		 */
		template<typename Iter>
		double get_val(Iter start, Iter end, double u)
		{
			int n = end - start;
			double m = mean(start, end);
			double x = std::pow(mean(start, end), 2);
			double y = std::accumulate(start, end, 0.0, sd_op()) / (double)(n - 1);
			double deno = sqrt((y - (x * n / double(n - 1))) / (double)n);
			double nume = m - u;
			return nume / deno;
		}

		template<typename Container>
		double get_val(const Container& vec, double u)
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
		inline double get_val(int n, double e, double v, double u)
		{
			double deno = sqrt(v / (double)n);
			double nume = e - u;
			return nume / deno;
		}

		/**
		 * 根据t 值的bound范围 给出原始观测均值需要在的范围
		 * 这个是观测的中心偏离了底下的区间 就拒绝~
		 */
		inline std::pair<double, double> get_bound(const std::pair<double, double>& bound, int n, double e, double v, double u)
		{
			std::pair<double, double> p;
			double deno = sqrt(v / (double)n);
			p.first = bound.first * deno + u;
			p.second = bound.second * deno + u;
			return p;
		}

		/**
		 *  这个其实很灵活，也可以观测的中心判断，如果假设的值 偏离了 这个底下的区间 就拒绝~~
		 */
		inline std::pair<double, double> get_bound2(const std::pair<double, double>& bound, int n, double e, double v, double u)
		{
			std::pair<double, double> p;
			double deno = sqrt(v / (double)n);
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
		int bin_index = (int)((value - min) / span);
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
		std::map<KeyType, int> m;
		for (Iter it = begin; it != end; ++it)
		{
			m[*it] += 1;
		}
		typedef std::pair<const KeyType, int> Pair;
		double res = 0;
		int total = end - begin;

		for(Pair& item : m)
		{
			double prob = item.second / (double)total;
			res += -prob * log(prob);
		}
		return res;
	}

	template<typename T>
	inline double information(const vector<T>& vec)
	{
		return information(vec.begin(), vec.end());
	}

	template<typename KeyType>
	inline double information(const map<KeyType, int>& m)
	{
		double res = 0, total = 0;
		for (auto& item : m)
		{
			total += item.second;
		}

		for (auto& item : m)
		{
			double prob = item.second / (double)total;
			res += -prob * log(prob);
		}
		return res;
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
		set<ValueType> vset;
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
		set<ValueType> vset;
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

	//@TODO prob == 1的边界条件?
	inline double entropy(double prob, bool useLnNotLog2 = true)
	{
		return
			useLnNotLog2
			? -prob * log(prob) - (1 - prob) * log(1 - prob)
			: -prob * log(prob) / log(2) - (1 - prob) * log(1 - prob) / log(2);
		//const double eps = 1e-16f;
		//const double pneg = 1 - prob;
		///*if (prob < eps || pneg < eps)*/
		//if (prob == 0 || pneg == 0)
		//{
		//	return 0;
		//}
		//else
		//{
		//	return
		//		useLnNotLog2
		//		? -prob * log(prob) - (1 - prob) * log(1 - prob)
		//		: -prob * log(prob) / log(2) - (1 - prob) * log(1 - prob) / log(2);
		//}
	}

	/// <summary>
	/// Cross-entropy of two distributions, probTrue must be 0 or 1
	/// </summary>        
	inline double cross_entropy(double probTrue, double probPredicted, bool useLnNotLog2 = true)
	{
		////W0528 15:00:28.226536 21067 statistic_util.h:813] 1 1 0 -nan     0 * log(0) = 0 * inf = nan
		//if (std::isnan(-probTrue * log(probPredicted) - (1 - probTrue) * log(1 - probPredicted)))
		//{
		//	LOG(WARNING) << probTrue << " " << probPredicted << " " << probTrue * log(probPredicted) << " " << (1 - probTrue) * log(1 - probPredicted);
		//}
		//return
		//	useLnNotLog2
		//	? -probTrue * log(probPredicted) - (1 - probTrue) * log(1 - probPredicted)
		//	: -probTrue * log(probPredicted) / log(2) - (1 - probTrue) * log(1 - probPredicted) / log(2);

		double eps = 1e-30f;
		const double pneg = 1 - probPredicted;
		if (probPredicted < eps)
		//if (probPredicted == 0)
		{
			return probTrue > 0 ? 30 : 0;
		}
		else if (pneg < eps)
		//else if (pneg == 0)
		{
			return probTrue > 0 ? 0 : 30;
		}
		else
		{
			return
				useLnNotLog2
				? -probTrue * log(probPredicted) - (1 - probTrue) * log(1 - probPredicted)
				: -probTrue * log(probPredicted) / log(2) - (1 - probTrue) * log(1 - probPredicted) / log(2);
		}
	}

	inline double label2ProbTrueZeroIsMin(double label)
	{
		return label > 0 ? 1 : 0;
	}
	inline double label2ProbTrueZeroNotMin(double label)
	{
		return label > 0 ? 1 : -1;
	}


	inline double cross_entropy_fast(double probTrue, double probPredicted, bool useLnNotLog2 = true)
	{
		return
			useLnNotLog2
			? -probTrue * log(probPredicted) - (1 - probTrue) * log(1 - probPredicted)
			: -probTrue * log(probPredicted) / log(2) - (1 - probTrue) * log(1 - probPredicted) / log(2);
	}

	inline double cross_entropy_toleranced(double probTrue, double probPredicted, int logTolerance = 30.0, bool useLnNotLog2 = true)
	{
		double score = cross_entropy_fast(probTrue, probPredicted, useLnNotLog2);
		if (score > logTolerance || std::isinf(score))
		{
			return logTolerance;
		}
		if (std::isnan(score))
		{
			return 0;
		}
		return score;
	}

	namespace loss {
		//针对output输入的logsitic等价于针对prob输入的cross_entropy
		inline double logistic(double trueProb, double prediction, double beta = 2.0)
		{
			//CHECK(!std::isinf(log(1.0 + std::exp(-beta * trueProb * prediction)))) << trueProb << " " << prediction;
			// exp(760) will be info
			double score = log(1.0 + std::exp(-beta * trueProb * prediction));
			//if (score > 30 || std::isinf(score)) inf will > 30
			if (score > 30.0)
			{
				return 30.0;
			}
			else
			{
				return score;
			}
		}
	} //-----end of namespace loss

} //----end of namespace sta
namespace sta = gezi; //@TODO temply now since I use many sta:: right now
#endif  //----end of STATISTIC_UTIL_H_
