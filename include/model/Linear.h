/**
 *  ==============================================================================
 *
 *          \file   model/Linear.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-03-14 09:56:35.037520
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef MODEL__LINEAR_H_
#define MODEL__LINEAR_H_

//TLC文本格式线性模型输入  @TODO 暂时不考虑normalize
//SVM(Pegasos - Linear) non - zero weights trained as / cl LinearSVM
//
//f0	0.0400000000000002
//f1	0.0200000000000005
//f2	0.0600000000000006
//f3 - 0.0600000000000008
//f4	0.0800000000000009
//f5	0.0799999999999997
//f6	0.16
//f7	0.0999999999999994
//f8	0.160000000000002
//f9	0.2
//f10 - 0.140000000000001
//f11	0.120000000000001
//f12	0.440000000000002
//f13	0.500000000000003
//f14	0.14

#include "common_util.h"
#include "feature/Feature.h"

namespace gezi
{
	class Linear
	{
	public:
		Linear()
		{

		}
		Linear(const string& modelPath)
		{
			load(modelPath);
		}

		//当前tlc的文本输出有些问题 主要是tlc其实主要依靠c#的序列化 文本输出估计没测试 
		//以后修复

		void load(const string& modelPath)
		{
			vector<int> indexVec;
			vector<double> valueVec;

			vector<string> lines = read_lines(modelPath);
			CHECK(lines.size() > 0) << modelPath;
			foreach(string line, lines)
			{
				vector<string> vec = gezi::split(boost::trim_copy(line), "\t");
				if (vec.size() == 2)
				{
					indexVec.push_back(INT(vec[0].substr(1)));
					valueVec.push_back(DOUBLE(vec[1]));
				}
			}
			_bias = DOUBLE(lines.back());
			size_t len = indexVec.back() + 1;
			_weights.resize(len, 0);
			for (size_t i = 0; i < len; i++)
			{
				_weights[indexVec[i]] = valueVec[i];
			}
		}
		double Predict(Feature& feature)
		{
			double val = 0;
			foreach(const Feature::Node& node, feature.cnodes())
			{
				val += _weights[node.index] * node.value;
			}
			val += _bias;
			return val;
		}
	private:
		double _bias;
		vector<double> _weights;
	};
}
#endif  //----end of MODEL__LINEAR_H_
