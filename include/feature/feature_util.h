/**
 *  ==============================================================================
 *
 *          \file   feature_util.h
 *
 *        \author   chenghuige
 *
 *          \date   2013-12-09 12:08:19.701910
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef FEATURE_UTIL_H_
#define FEATURE_UTIL_H_

#include "Feature.h"
#include "common_util.h"

//@WARNING depreciated -> use features_util.h
namespace gezi
{

	inline void write_template(const Feature& feature, string outfile)
	{
		ofstream ofs(outfile.c_str());
		int len = feature.names().size();
		for (int i = 0; i < len; i++)
		{
			ofs << "#define " << feature.names()[i] << " fv[" << i << "]" << endl;
		}
	}
	inline void write_def(const Feature& feature, string outfile)
	{
		write_template(feature, outfile);
	}
	template<typename _Stream>
	void debug_print(const Feature& feature, _Stream& out)
	{
		const vector<int>& name_counts = feature.name_counts();
		int idx = 0;
		for (int i = 0; i < (int)name_counts.size(); i++)
		{
			out << format("---[%-3d-%s] len:%d\n") % i % feature.section_names()[i] % name_counts[i];
			for (int j = 0; j < name_counts[i]; j++)
			{
				double val = feature.values()[idx];
				out << format("%-3d %-3d: %-20s : [%f]\n") % (idx + 1) % (j + 1) % feature.names()[idx] % val;
				idx++;
			}
		}
	}

	template<typename _Stream>
	void debug_print(const Feature& feature, _Stream& out,
		const vector<pair<double, double> >& normal_vec,
		const vector<pair<double, double> >& spam_vec)
	{
		const vector<int>& name_counts = feature.name_counts();
		int idx = 0;
		for (int i = 0; i < (int)name_counts.size(); i++)
		{
			out << format("---[%-3d-%s] len:%d\n") % i % feature.section_names()[i] % name_counts[i];
			for (int j = 0; j < name_counts[i]; j++)
			{
				double val = feature.values()[idx];
				double normed_val = feature.value(idx + 1);
				out << format("%-3d %-3d %-25s : [%f:%f] : [NormalMean %f] : [SpamMean %f] : [NormalVar %f] : [SpamVar %f]\n")
					% (idx + 1) % (j + 1) % feature.names()[idx] % val % normed_val
					% normal_vec[idx].first % spam_vec[idx].first
					% normal_vec[idx].second % spam_vec[idx].second;
				idx++;
			}
		}
	}

	inline Feature to_feature(string feature_str_)
	{
		string feature_str = feature_str_;
		libsvm_normalize(feature_str);
		Feature feature;
		vector<string> vec;
		boost::split(vec, feature_str, is_any_of("\t "));
		int len = vec.size();
		for (int i = 0; i < len; i++)
		{
			vector<string> parts;
			boost::split(parts, vec[i], is_any_of(":"));
			feature.nodes().push_back(Feature::Node(INT(parts[0]), DOUBLE(parts[1])));
		}

		return feature;
	}

	template<typename _Stream>
	void write_arff_header(const Feature& feature, _Stream& ofs, string relation, string classes = "spam,normal")
	{
		ofs << "@relation " << relation << "\n" << endl;
		for (int i = 0; i < (int)feature.names().size(); i++)
		{
			ofs << "@attribute " << feature.names()[i] << " numeric" << endl;
		}

		ofs << "@attribute class {" << classes << "}\n" << endl;

		ofs << "@data\n" << endl;
	}

	template<typename _Stream>
	void write_table_header(const Feature& feature, _Stream& ofs, string name = "id", string label = "label")
	{
		ofs << "#";
		if (!name.empty())
		{
			ofs << name << "\t";
		}
		ofs << label;

		foreach(string fname, feature.names())
		{
			ofs << "\t" << fname;
		}
		ofs << endl;
	}

	template<typename _Stream>
	void write_ftable_header(const Feature& feature, _Stream& ofs, string name = "")
	{
		ofs << "instance\ttrue\tprobability\tassigned";
		if (!name.empty())
		{
			ofs << "\t" << name;
		}

		foreach(string fname, feature.names())
		{
			ofs << "\t" << fname;
		}
		ofs << endl;
	}


	inline void write_header(const Feature& feature, std::ostream& ofs)
	{
		foreach(string name, feature.names())
		{
			ofs << name << "," << endl;
		}
	}

	inline void write_header(const Feature& feature, string file)
	{
		ofstream ofs(file.c_str());
		write_header(feature, ofs);
	}

	inline void write_arff(const Feature& feature, string uid, string type, std::ostream& ofs)
	{
		ofs << "{";

		foreach(const Feature::Node& node, feature.nodes())
		{
			ofs << node.index << " " << node.value << ",";
		}
		int index = feature.dimension();
		ofs << index << " " << type;
		ofs << "}" << endl;
	}

	inline void write_libsvm(const Feature& feature, string label, std::ostream& ofs)
	{
		ofs << label << " ";
		size_t i = 0;
		for (; i < feature.featureNum() - 1; i++)
		{
			ofs << feature.nodes()[i].index + 1<< ":" << feature.nodes()[i].value << " ";
		}
		ofs << feature.nodes()[i].index + 1 << ":" << feature.nodes()[i].value << endl;
	}

	//TODO write_tlc tlc支持的稀疏格式
	//tlc也能使用稀疏表示 考虑到目前大部分应用特征不会太多<500 目前只输出dense format 方便使用excell
	//tlc dense 采用标准输出 第一列是名字比如pid 第二列是label 例如下面 另外输出的是原始特征 未经过normalize
	//# 	label	JaccardSimilarity	CTR_s10_Query	CTR_s100_Query	CTR_s1000_Query	LogitCTR_s10_Query	LogitCTR_s100_Query	LogitCTR_s1000_Query	impressions_Query	clicks_Query
	//_lottery|acute leukemia	0	0	0.013693014	0.013704492	0.013818185	-4.277081865	-4.276232328	-4.267855249	103347	1415
	inline void write_sparse(const Feature& feature, string label, ofstream& ofs, string name = "")
	{
		if (!name.empty())
			ofs << "_" << name << "\t" << label;
		else
			ofs << label;

		ofs << "\t" << feature.dimension();

		if (feature.featureNum() == 0)
		{
			ofs << "\t" << "0:0";
		}
		else
		{
			foreach(const Feature::Node& node, feature.nodes())
			{
				ofs << "\t" << node.index << ":" << node.value;
			}
		}
		ofs << endl;
	}

	//注意不要单独使用 一般是在类似下面 情况使用
	inline void write_table(const Feature& feature, string label, ofstream& ofs, string name = "")
	{
		if (feature.only_sparse())
		{
			write_sparse(feature, label, ofs, name);
			return;
		}
		
		if (!name.empty())
			ofs << "_" << name << "\t" << label;
		else
			ofs << label;

		foreach(double value, feature.values())
		{
			ofs << "\t" << value;
		}
		ofs << endl;
	}
	
	//ofs_full << id << "\t" << label << "\t" << 1 << "\t" << 1 << "\t" << content;
	//write_table_feature(feature, ofs_full);
	inline void write_table_feature(const Feature& feature, ofstream& ofs)
	{
		foreach(double value, feature.values())
		{
			ofs << "\t" << value;
		}
		ofs << endl;
	}

	template<typename Vec>
	inline void add_mean_var(Feature* fe, const Vec& vec,
		const string mean_name = "", const string var_name = "")
	{
		double mean = vec.size() > 0 ? sta::mean(vec) : 0;
		fe->add(mean, mean_name);
		double var = vec.size() > 1 ? sta::var(vec, mean) : 0;
		fe->add(var, var_name);
	}

	template<typename Vec>
	inline void add_mean(Feature* fe, const Vec& vec,
		const string mean_name = "")
	{
		double mean = vec.size() > 0 ? sta::mean(vec) : 0;
		fe->add(mean, mean_name);
	}

	template<typename Vec>
	inline void add_var(Feature* fe, const Vec& vec,
		const string var_name = "")
	{
		double var = vec.size() > 1 ? sta::var(vec) : 0;
		fe->add(var, var_name);
	}

	template<typename T>
	inline void add_mean_var(Feature* fe, T begin, T end,
		const string mean_name = "", const string var_name = "")
	{

		double mean = end > begin ? sta::mean(begin, end) : 0;
		fe->add(mean, mean_name);
		double var = end - begin > 1 ? sta::var(begin, end, mean) : 0;
		fe->add(var, var_name);
	}

	template<typename T>
	inline void add_mean(Feature* fe, T begin, T end,
		const string mean_name = "")
	{
		double mean = end > begin ? sta::mean(begin, end) : 0;
		fe->add(mean, mean_name);
	}

	template<typename T>
	inline void add_var(Feature* fe, T begin, T end,
		const string var_name = "")
	{
		double var = end - begin > 1 ? sta::var(begin, end) : 0;
		fe->add(var, var_name);
	}
} //----end of namespace gezi

#endif  //----end of FEATURE_UTIL_H_
