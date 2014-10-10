/**
 *  ==============================================================================
 *
 *          \file   feature/features_util.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-04-10 15:57:48.585606
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef FEATURE_FEATURES_UTIL_H_
#define FEATURE_FEATURES_UTIL_H_

#include "feature/FeatureVector.h"
#include "string_util.h"

namespace gezi {

	inline void write_template(const Features& features, string outfile)
	{
		ofstream ofs(outfile.c_str());
		int len = features.names().size();
		for (int i = 0; i < len; i++)
		{
			ofs << "#define " << features.names()[i] << " fv[" << i << "]" << endl;
		}
	}
	inline void write_def(const Features& features, string outfile)
	{
		write_template(features, outfile);
	}
	template<typename _Stream>
	void debug_print(const Features& features, _Stream& out)
	{
		const vector<int>& name_counts = features.name_counts();
		int idx = 0;
		for (int i = 0; i < (int)name_counts.size(); i++)
		{
			out << boost::format("---[%-3d-%s] len:%d\n") % i % features.section_names()[i] % name_counts[i];
			for (int j = 0; j < name_counts[i]; j++)
			{
				double val = features.values[idx];
				out << boost::format("%-3d %-3d: %-20s : [%f]\n") % (idx) % (j) % features.names()[idx] % val;
				idx++;
			}
		}
	}

	template<typename _Stream>
	void debug_print(const Features& features, _Stream& out,
		const vector<pair<double, double> >& normal_vec,
		const vector<pair<double, double> >& spam_vec)
	{
		const vector<int>& name_counts = features.name_counts();
		int idx = 0;
		for (int i = 0; i < (int)name_counts.size(); i++)
		{
			out << boost::format("---[%-3d-%s] len:%d\n") % i % features.section_names()[i] % name_counts[i];
			for (int j = 0; j < name_counts[i]; j++)
			{
				double normed_val = features.values[idx]; //dense表示的特征被norm
				double val = features[idx + 1]; //稀疏表示的保持不变
				out << boost::format("%-3d %-3d %-25s : [%f:%f] : [NormalMean %f] : [SpamMean %f] : [NormalVar %f] : [SpamVar %f]\n")
					% (idx) % (j) % features.names()[idx] % val % normed_val
					% normal_vec[idx].first % spam_vec[idx].first
					% normal_vec[idx].second % spam_vec[idx].second;
				idx++;
			}
		}
	}

	inline Vector to_features(string sparseFeatureStr)
	{
		normalize_feature_str(sparseFeatureStr);
		Vector features;
		vector<string> vec;
		boost::split(vec, sparseFeatureStr, is_any_of("\t "));
		int len = vec.size();
		for (int i = 0; i < len; i++)
		{
			vector<string> parts;
			boost::split(parts, vec[i], is_any_of(":"));
			features.Add(INT(parts[0]), DOUBLE(parts[1]));
		}
		return features;
	}

	template<typename _Stream>
	void write_arff_header(const Features& features, _Stream& ofs, string relation = "table", string classes = "negative,positive")
	{
		ofs << "@relation " << relation << "\n" << endl;
		for (int i = 0; i < (int)features.names().size(); i++)
		{
			ofs << "@attribute " << features.names()[i] << " numeric" << endl;
		}

		ofs << "@attribute class {" << classes << "}\n" << endl;

		ofs << "@data\n" << endl;
	}

	template<typename _Stream>
	void write_table_header(const Features& features, _Stream& ofs, string name = "id", string label = "label")
	{
		ofs << "#";
		if (!name.empty())
		{
			ofs << name << "\t";
		}
		ofs << label;

		for(string fname : features.names())
		{
			ofs << "\t" << fname;
		}
		ofs << endl;
	}

	template<typename _Stream>
	void write_ftable_header(const Features& features, _Stream& ofs, string name = "")
	{
		ofs << "instance\ttrue\tprobability\tassigned";
		if (!name.empty())
		{
			ofs << "\t" << name;
		}

		for(string fname : features.names())
		{
			ofs << "\t" << fname;
		}
		ofs << endl;
	}


	inline void write_header(const Features& features, std::ostream& ofs)
	{
		for(string name : features.names())
		{
			ofs << name << "," << endl;
		}
	}

	inline void write_header(const Features& features, string file)
	{
		ofstream ofs(file.c_str());
		write_header(features, ofs);
	}

	inline void write_arff(const Features& features, string uid, string type, std::ostream& ofs)
	{
		ofs << "{";

		for (const Features::Feature& node : features.features())
		{
			ofs << node.index << " " << node.value << ",";
		}
		int index = features.dimension();
		ofs << index << " " << type;
		ofs << "}" << endl;
	}

	inline void write_libsvm(const Features& features, string label, std::ostream& ofs)
	{
		ofs << label << " ";
		size_t i = 0;
		for (; i < features.count() - 1; i++)
		{
			ofs << features.features()[i].index + 1 << ":" << features.features()[i].value << " ";
		}
		ofs << features.features()[i].index + 1 << ":" << features.features()[i].value << endl;
	}

	//TODO write_tlc tlc支持的稀疏格式
	//tlc也能使用稀疏表示 考虑到目前大部分应用特征不会太多<500 目前只输出dense format 方便使用excell
	//tlc dense 采用标准输出 第一列是名字比如pid 第二列是label 例如下面 另外输出的是原始特征 未经过normalize
	//# 	label	JaccardSimilarity	CTR_s10_Query	CTR_s100_Query	CTR_s1000_Query	LogitCTR_s10_Query	LogitCTR_s100_Query	LogitCTR_s1000_Query	impressions_Query	clicks_Query
	//_lottery|acute leukemia	0	0	0.013693014	0.013704492	0.013818185	-4.277081865	-4.276232328	-4.267855249	103347	1415

	template<typename T>
	inline void write_sparse(const Features& features, T label, ofstream& ofs)
	{
		ofs << label << "\t" << features.dimension();
		if (features.count() == 0)
		{
			ofs << "\t" << "0:0";
		}
		else
		{
			for(const Features::Feature& node : features.features())
			{
				ofs << "\t" << node.index << ":" << node.value;
			}
		}
		ofs << endl;
	}
	template<typename T, typename U>
	inline void write_sparse(const Features& features, T label, ofstream& ofs, U name)
	{
		ofs << "_" << name << "\t";
		write_sparse(features, label, ofs);
	}

	//注意不要单独使用 一般是在类似下面 情况使用
	template<typename T>
	inline void write_table(const Features& features, T label, ofstream& ofs)
	{
		ofs << label;
		for(auto value : features.values)
		{
			ofs << "\t" << value;
		}
		ofs << endl;
	}

	template<typename T, typename U>
	inline void write_table(const Features& features, T label, ofstream& ofs, U name)
	{
		ofs << "_" << name << "\t";
		write_table(features, label, ofs);
	}

	//ofs_full << id << "\t" << label << "\t" << 1 << "\t" << 1 << "\t" << content;
	//write_table_feature(features, ofs_full);
	inline void write_table_feature(const Features& features, ofstream& ofs)
	{
		for(auto value : features.values)
		{
			ofs << "\t" << value;
		}
		ofs << endl;
	}

	//@TODO 是否允许全0的？ 这个主要是针对稠密特征的 暂时ok
	template<typename IdVec, typename LabelVec, typename Func>
	inline void write_features(const IdVec& ids, const LabelVec& labels, Func func,
		string outFile, string idName = "id")
	{
		ofstream ofsFeatures(outFile);
		//----------------先确保写入header
		size_t i = 0;
		for (i = 0; i < ids.size(); i++)
		{
			Features fe = func(ids[i]);
			if (!fe.empty())
			{
		
				write_table_header(fe, ofsFeatures, idName);
				write_table(fe, labels[i], ofsFeatures, ids[i]);
				i++;
				break;
			}
		}
		Features::useNames() = false;
#pragma omp parallel for
		for (size_t j = i; j < ids.size(); j++)
		{
			Features fe = func(ids[j]);
			if (!fe.empty())
			{
#pragma  omp critical
				write_table(fe, labels[j], ofsFeatures, ids[j]);
			}
		}
	}

	//just for test
	template<typename IdVec, typename LabelVec, typename Func>
	inline void write_features(const IdVec& ids, const IdVec& ids2, const LabelVec& labels, Func func,
		string outFile, string idName = "id")
	{
		ofstream ofsFeatures(outFile);
		//----------------先确保写入header
		size_t i = 0;
		for (i = 0; i < ids.size(); i++)
		{
			Features fe = func(ids[i]);
			if (!fe.empty())
			{
				write_table_header(fe, ofsFeatures, idName);
				write_table(fe, labels[i], ofsFeatures, ids2[i]);
				i++;
				break;
			}
		}

#pragma omp parallel for
		for (size_t j = i; j < ids.size(); j++)
		{
			Features fe = func(ids[j]);
			if (!fe.empty())
			{
#pragma  omp critical
				{
					write_table(fe, labels[j], ofsFeatures, ids2[j]);
				}
			}
		}
	}

	//--下面废弃
	template<typename Vec>
	inline void add_mean_var(Features* fe, const Vec& vec,
		const string mean_name = "", const string var_name = "")
	{
		double mean = vec.size() > 0 ? sta::mean(vec) : 0;
		fe->add(mean, mean_name);
		double var = vec.size() > 1 ? sta::var(vec, mean) : 0;
		fe->add(var, var_name);
	}

	template<typename Vec>
	inline void add_mean(Features* fe, const Vec& vec,
		const string mean_name = "")
	{
		double mean = vec.size() > 0 ? sta::mean(vec) : 0;
		fe->add(mean, mean_name);
	}

	template<typename Vec>
	inline void add_var(Features* fe, const Vec& vec,
		const string var_name = "")
	{
		double var = vec.size() > 1 ? sta::var(vec) : 0;
		fe->add(var, var_name);
	}

	template<typename T>
	inline void add_mean_var(Features* fe, T begin, T end,
		const string mean_name = "", const string var_name = "")
	{

		double mean = end > begin ? sta::mean(begin, end) : 0;
		fe->add(mean, mean_name);
		double var = end - begin > 1 ? sta::var(begin, end, mean) : 0;
		fe->add(var, var_name);
	}

	template<typename T>
	inline void add_mean(Features* fe, T begin, T end,
		const string mean_name = "")
	{
		double mean = end > begin ? sta::mean(begin, end) : 0;
		fe->add(mean, mean_name);
	}

	template<typename T>
	inline void add_var(Features* fe, T begin, T end,
		const string var_name = "")
	{
		double var = end - begin > 1 ? sta::var(begin, end) : 0;
		fe->add(var, var_name);
	}
} //----end of namespace gezi

#endif  //----end of FEATURE_FEATURES_UTIL_H_
