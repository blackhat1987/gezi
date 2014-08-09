/**
 *  ==============================================================================
 *
 *          \file   Idf.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-03-10 16:34:09.041438
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef IDF_H_
#define IDF_H_

#include "Identifer.h"
#include "common_util.h"
namespace gezi {

	class Idf
	{
	public:
		virtual ~Idf()
		{
		}
		Idf()
			:_instanceNum(0)
		{
		}
		void add(string doc, string sep = "\t")
		{
			add(split(doc, sep));
		}

		void add(const vector<string>& words)
		{
			set<string> wordSet(words.begin(), words.end());
			add(wordSet);
		}

		void save(string file)
		{
			ofstream ofs(file.c_str());
			size_t len = _identifer.size();
			vector<string>& vec = _identifer.words();
			for (size_t i = 0; i < len; i++)
			{
				double idf = log((double) _instanceNum / _featureCounts[i]);
				ofs << vec[i] << "\t" << idf << "\t" << _featureCounts[i] << endl;
			}
		}

		void save(string file, int minCount, int minIdf)
		{
			ofstream ofs(file.c_str());
			size_t len = _identifer.size();
			vector<string>& vec = _identifer.words();
			for (size_t i = 0; i < len; i++)
			{
				if (_featureCounts[i] < minCount)
				{
					continue;
				}
				
				double idf = log((double)_instanceNum / _featureCounts[i]);

				if (idf < minIdf)
				{
					continue;
				}
				
				ofs << vec[i] << "\t" << idf << "\t" << _featureCounts[i] << endl;
			}
		}

		//展示排序后的 按照idf从高到低
		void show(int maxNum = 1024)
		{
			size_t len = _identifer.size();
			if (maxNum < 0 || maxNum > len)
			{
				maxNum = len;
			}
			vector<double> scores(len);
			
			for (size_t i = 0; i < len; i++)
			{
				scores[i] = log(_instanceNum / (double) _featureCounts[i]);
			}

			vector<int> ranks;
		
			gezi::sort(scores, ranks, maxNum);

			vector<string>& words = _identifer.words();
			for (size_t i = 0; i < maxNum; i++)
			{
				int idx = ranks[i];
				cout << words[idx] << "\t" << scores[idx] << endl;
			}
		}

	protected:
	private:
		void add(const set<string>& words)
		{
			foreach(string word, words)
			{
				bool isnew = false;
				int idx = _identifer.add(word, isnew);
				if (isnew)
				{
					_featureCounts.push_back(0);
				}
				_featureCounts[idx]++;
			}
			_instanceNum++;
		}
	private:
		Identifer _identifer;
		vector<int> _featureCounts;
		int _instanceNum;
	};
}  //----end of namespace gezi

#endif  //----end of IDF_H_
