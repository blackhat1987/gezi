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
#include "statistic_util.h" //@TODO math_util.h
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

		//@FIXME 修改文本格式 
		void load(const string& modelPath)
		{
			vector<int> indexVec;
			vector<double> valueVec;

			vector<string> lines = read_lines(modelPath);
			CHECK(lines.size() > 0) << modelPath;
			int num = 0;
			foreach(string line, lines)
			{
				vector<string> vec = gezi::split(boost::trim_copy(line), "\t");
				if (vec.size() == 2 || (vec.size() == 3 && num == lines.size() - 2))
				{
					indexVec.push_back(INT(boost::trim_copy(vec[0]).substr(1)));
					valueVec.push_back(DOUBLE(boost::trim_copy(vec[1])));
				}
				num++;
			}
			_bias = DOUBLE(lines.back());
			size_t len = indexVec.back() + 1;
			_weights.resize(len, 0);
			for (size_t i = 0; i < indexVec.size(); i++)
			{
				_weights[indexVec[i]] = valueVec[i];
			}

			//@TODO just hack now
			string outPath = boost::replace_last_copy(modelPath, "model.txt", "out.txt");
			ifstream ifs(outPath.c_str());
			string line;
			while (getline(ifs, line))
			{
				boost::trim(line);
				if (startswith(line, "double paramA"))
				{
					_paramA = DOUBLE(boost::trim_copy(split(line.substr(0, line.size() - 1), "=")[1]));
				}
				else if (startswith(line, "double paramB"))
				{
					_paramB = DOUBLE(boost::trim_copy(split(line.substr(0, line.size() - 1), "=")[1]));
				}
			}
			PVAL(_paramA);
			PVAL(_paramB);
		}

		double output(Feature& feature)
		{
			double val = 0;
			foreach(const Feature::Node& node, feature.cnodes())
			{
				if (node.index >= _weights.size())
				{
					continue;
				}
				
				val += _weights[node.index] * node.value;
			}
			val += _bias;
			return val;
		}

		double Predict(Feature& feature)
		{
			double val = 0;
			foreach(const Feature::Node& node, feature.cnodes())
			{
				val += _weights[node.index] * node.value;
			}
			val += _bias;
			return sigmoid(val, _paramA, _paramB);
		}
	private:
		double _bias;
		vector<double> _weights;
		double _paramA;
		double _paramB;
	};
}
#endif  //----end of MODEL__LINEAR_H_
