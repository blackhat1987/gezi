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
 *								  @TODO 写一个通用的hadoop streaming版本
 *  当前是单线程版本 完成添加文本 词编号 计数 计算 排序
 *  可以输出tf,idf信息 如果只需要编号+idf 可以使用Idf.h
 *  ==============================================================================
 */

#ifndef FEATURE_SELECTOR_H_
#define FEATURE_SELECTOR_H_

#include "Matrix.h"
#include "Identifer.h"
#include "Numeric/collocation.h"
#include "sort_util.h"
namespace gezi {

	//Two options for an aggregate score across classes:
	//Weighted average:
	//?^2 (???????)=∑_(?∈???????)?〖?(?)  ?^2 (???????,?) 〗
	//Highest score among any class:
	//?^2 (???????)=max┬(?∈???????)?〖   ?^2 (???????,?)〗

	class FeatureSelector
	{
	public:
		typedef boost::function<Float(int, int, int, uint64) > Func;

		enum Strategy
		{
			MAX,
			AVG,
			SUM
		};

		FeatureSelector()
			: _labelNum(2), _method(collocation::CHI), _strategy(MAX), _minSupport(0)
		{
			init();
			initFunc();
		}

		void init()
		{
			_classCounts.resize(_labelNum, 0);
			_classPriors.resize(_labelNum, 0);
			_counts.resize(_labelNum);
			_scores.resize(_labelNum + 1); //最后的行是特征对所有类的一个总的评价值
			_ranks.resize(_labelNum + 1);

			foreach(vector<int>& vec, _counts)
			{
				vec.reserve(1024);
			}
		}

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
#ifndef PYTHON_WRAPPER
			case ECE:
				VLOG(3) << "Expected Cross Entropy";
				_func = cross_entropy;
				break;
#endif
			default:
				VLOG(3) << "Chi Square";
				_func = chi_square;
				break;
			}
		}

		void clearScore()
		{
			_ranks.clear();
			_ranks.resize(_labelNum + 1);
			_scores.clear();
			_scores.resize(_labelNum + 1);
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
			return _labelNum;
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


		inline FeatureSelector& labelNum(int labelNum)
		{
			_labelNum = labelNum;
			init();
			return *this;
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

		void add(const vector<string>& words, int label)
		{
			set<string> wordSet(words.begin(), words.end());
			add(wordSet, label);
		}

		void add(string doc, int label, string sep = "\t")
		{
			vector<string> words;
			boost::split(words, doc, is_any_of(sep));
			add(words, label);
		}

		//暂时只考虑CHI TODO IG ECE MI PMI

		dmat& calc()
		{
			finalize();
			if (_strategy == AVG)
			{
				for (int labelIdx = 0; labelIdx < _labelNum; labelIdx++)
				{
					_classPriors[labelIdx] = (double)_classCounts[labelIdx] / _instanceNum;
				}
			}
			PVEC(_classPriors);
			vector<double>& scores = _scores.back();
			for (int f = 0; f < _featureNum; f++)
			{
				for (int labelIdx = 0; labelIdx < _labelNum; labelIdx++)
				{
					double score = _func(_counts[labelIdx][f], _featureCounts[f], _classCounts[labelIdx], _instanceNum);
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

		void save(string file, int idx = -1, int maxFeatureNum = -1)
		{
			ofstream ofs(file.c_str());
			save(ofs, maxFeatureNum, idx);
		}

		void show(int maxFeatureNum = 1024, int idx = -1)
		{
			save(std::cout, maxFeatureNum, idx);
		}

		void save(ostream& os, int maxFeatureNum, int idx)
		{
			if (idx == -1)
				idx = _labelNum;
			PVAL(idx);
			if (maxFeatureNum == -1 || maxFeatureNum > _featureNum)
				maxFeatureNum = _featureNum;
			PVAL(maxFeatureNum);
			rank(idx, maxFeatureNum);
			for (int i = 0; i < maxFeatureNum; i++)
			{
				int index = _ranks[idx][i];
				if (_featureCounts[index] >= _minSupport)
				{
					os << _identifer[index] << "\t" << _scores[idx][index];
					for (int j = 0; j < _labelNum; j++)
					{
						os << "\t" << _counts[j][index];
					}
					os << endl;
				}
			}
		}

		void save_idf(string file)
		{
			ofstream ofs(file.c_str());
			size_t len = _identifer.size();
			vector<string>& vec = _identifer.words();
			for (size_t i = 0; i < len; i++)
			{
				double idf = log(_instanceNum / (double)_featureCounts[i]);
				ofs << vec[i] << "\t" << idf << endl;
			}
		}

		void save_all(string dir = "result")
		{
			try_create_dir(dir);

			//词表
			_identifer.save(dir + "/words.txt");
			//idf信息
			save_idf(dir + "/words.idf.txt");
			//0元 总量
			write_elem(_instanceNum, dir + "/total.txt");
			//一元结果 class feature
			write_vec(_classCounts, dir + "/class");
			write_vec(_featureCounts, dir + "/feature");
			//二元统计结果 
			write_vec2d(_counts, dir + "/cooccur");
			//统计后计算的结果如互信息
			write_vec2d(_scores, dir + "/scores");
			this->save(dir + "/score0.txt", 0);
			this->save(dir + "/score1.txt", 1);
			this->save(dir + "/score2.txt");
		}

		inline int featureNum()
		{
			return _featureNum;
		}

		inline int64 instanceNum()
		{
			return _instanceNum;
		}

	private:

		void add(const set<string>& words, int labelIdx)
		{
			foreach(string word, words)
			{
				bool isnew = false;
				int idx = _identifer.add(word, isnew);
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

		void finalize()
		{
			_featureNum = _identifer.size();
			PVAL(_featureNum);
			_instanceNum = std::accumulate(_classCounts.begin(), _classCounts.end(), int64(0));
			PVAL(_instanceNum);

			foreach(vector<double>& vec, _scores)
			{
				vec.resize(_featureNum, 0); //特征数目
			}
		}

		void rank(int maxFeatureNum)
		{
			if (maxFeatureNum > _featureNum)
				maxFeatureNum = _featureNum;
			for (int i = 0; i <= _labelNum; i++)
			{
				gezi::sort(_scores[i], _ranks[i], maxFeatureNum);
			}
		}

		void rank(int index, int maxFeatureNum)
		{
			gezi::sort(_scores[index], _ranks[index], maxFeatureNum);
		}

	private:
		imat _counts; //共现统计
		vector<int> _featureCounts;
		vector<int> _classCounts;
		vector<double> _classPriors;
		int _labelNum;
		int _featureNum;
		int64 _instanceNum;
		Func _func;
		collocation::Method _method;
		Strategy _strategy;
		int _minSupport; //feature至少出现多少次才认为有意义

		dmat _scores; //记录各个特征打分
		imat _ranks; //记录特征打分排序索引

		Identifer _identifer;
	};

} //----end of namespace gezi

#endif  //----end of FEATURE_SELECTOR_H_
