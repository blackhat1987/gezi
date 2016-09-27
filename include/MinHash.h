/**
*  ==============================================================================
*
*          \file   MinHash.h
*
*        \author   chenghuige
*
*          \date   2013-09-21 13:16:29.252975
*
*  \Description:
*  ==============================================================================
*/

#ifndef MINHASH_H_
#define MINHASH_H_

#include "MultiHash.h"
#include "common_util.h"
#include <limits>
#include <sstream>
namespace gezi
{
	using namespace std;

	class MinHash : MultiHash
	{
	private:
		const string _separator;
		int _hashNum;
		int _groupNum;

	public:
		MinHash()
			:_separator("$#")
		{

		}
		MinHash(int hashNum, int interval)
			: _hashNum(hashNum), _groupNum(interval),_separator("$#")
		{

		}

		template<typename T>
		void GetSuperShingleFeature(const vector<T>& input, vector<uint>& superShingles)
		{
			vector<uint> sketches;
			GetSketches(input, _hashNum, sketches);
			GetSuperShingles(sketches, _groupNum, superShingles);
		}

		template<typename T>
		void GetSuperShingleFeature(const vector<T>& input, int hashNum, int interval,  vector<uint>& superShingles)
		{
			vector<uint> sketches;
			GetSketches(input, hashNum, sketches);
			GetSuperShingles(sketches, interval, superShingles);
		}

		template<typename T>
		void GetSketches(const vector<T>& input, int n, vector<uint>& sketches)
		{
			if (n <= 0 || n >= SaltCount)
			{
				return;
			}

			sketches.resize(n);

			for (int i = 0; i < n; i++)
			{
				uint minHash = std::numeric_limits<uint>::max();
				for (int j = 0; j < input.size(); j++)
				{
					uint hash = GetHash(input[j], i);
					if (hash < minHash)
					{
						minHash = hash;
					}
				}
				sketches[i] = minHash;
			}
		}

		template<typename T>
		void GetSketches(const vector<T>& input, vector<uint>& sketches)
		{
			GetSketches(input, _hashNum, sketches);
		}

		static double GetSim(const vector<uint>& lfeatures, const vector<uint>& rfeatures)
		{
			int sum = 0;
			for (int i = 0; i < lfeatures.size(); i++)
			{
				if (lfeatures[i] == rfeatures[i])
				{
					sum++;
				}
			}
			return sum / (double)lfeatures.size();
		}

		//split to n parts
		void GetSuperShingles(const vector<uint>& features, int groupNum, vector<uint>& superShingles)
		{
			superShingles.resize(groupNum);
			int interval = features.size() / groupNum;
			for (int i = 0; i < groupNum; i++)
			{
				stringstream builder;
				for (int j = 0; j < interval - 1; j++)
				{
					builder << features[i * interval + j];
					builder << _separator;
				}
				builder << features[i * interval + interval - 1]; //interval should >= 2
				superShingles[i] = GetHash(builder.str(), (int)SaltCount - 1);
			}
		}
	};
}

#endif  //----end of MINHASH_H_
