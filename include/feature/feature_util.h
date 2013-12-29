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

namespace gezi
{

template<typename _Stream>
void debug_print(const Feature& feature, _Stream& out)
{
  const vector<int>& name_counts = feature.cname_counts();
  int idx = 0;
  for (int i = 0; i < (int) name_counts.size(); i++)
  {
    out << format("---[%-3d-%s] len:%d\n") % i % feature.csection_names()[i] % name_counts[i];
    for (int j = 0; j < name_counts[i]; j++)
    {
      double val = feature.cvalues()[idx];
      out << format("%-3d %-3d: %-20s : [%f]\n") % (idx + 1) % (j + 1) % feature.cnames()[idx] % val;
      idx++;
    }
  }
}

template<typename _Stream>
void debug_print(const Feature& feature, _Stream& out,
        const vector<pair<double, double> >& normal_vec,
        const vector<pair<double, double> >& spam_vec)
{
  const vector<int>& name_counts = feature.cname_counts();
  int idx = 0;
  for (int i = 0; i < (int) name_counts.size(); i++)
  {
    out << format("---[%-3d-%s] len:%d\n") % i % feature.csection_names()[i] % name_counts[i];
    for (int j = 0; j < name_counts[i]; j++)
    {
      double val = feature.cvalues()[idx];
      double normed_val = feature[idx + 1];
      out << format("%-3d %-3d %-25s : [%f:%f] : [NormalMean %f] : [SpamMean %f] : [NormalVar %f] : [SpamVar %f]\n")
              % (idx + 1) % (j + 1) % feature.cnames()[idx] % val % normed_val
              % normal_vec[idx].first % spam_vec[idx].first
              % normal_vec[idx].second % spam_vec[idx].second;
      idx++;
    }
  }
}

inline void libsvm_normalize(string& feature_str)
{
  boost::trim(feature_str);
  feature_str = gezi::remove_dupspace(feature_str);
}

inline Feature to_feature(const string& feature_str_)
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

#ifdef __GXX_EXPERIMENTAL_CXX0X__
  return std::move(feature);
#else
  return feature;
#endif
}

template<typename _Stream>
void write_arff_header(const Feature& feature, _Stream& ofs, string relation, string classes = "spam,normal")
{
  ofs << "@relation " << relation << "\n" << endl;
  for (int i = 0; i < (int) feature.cnames().size(); i++)
  {
    ofs << "@attribute " << feature.cnames()[i] << " numeric" << endl;
  }

  ofs << "@attribute class {" << classes << "}\n" << endl;

  ofs << "@data\n" << endl;
}

template<typename _Stream>
void write_tlc_header(const Feature& feature, _Stream& ofs, string name = "name")
{
  ofs << "#" << name << "\t" << "label";
  foreach(string fname, feature.cnames())
  {
    ofs << "\t" << fname;
  }
  ofs << endl;
}

template<typename _Stream>
void write_header(const Feature& feature, _Stream& ofs)
{
  foreach(string name, feature.cnames())
  {
    ofs << name << endl;
  }
}

inline void write_arff(const Feature& feature, const string& uid, const string& type, std::ostream& ofs)
{
  ofs << "{";

  foreach(const Feature::Node& node, feature.cnodes())
  {
    ofs << node.index - 1 << " " << node.value << ",";
  }
  int index = feature.dimension();
  //ofs << index << " " << uid << ",";
  //index++;
  ofs << index << " " << type;
  ofs << "}" << endl;
}

inline void write_libsvm(const Feature& feature, const string& label, std::ostream& ofs)
{
  ofs << label << " ";
  size_t i = 0;
  for (; i < feature.featureNum() - 1; i++)
  {
    ofs << feature.cnodes()[i].index << ":" << feature.cnodes()[i].value << " ";
  }
  ofs << feature.cnodes()[i].index << ":" << feature.cnodes()[i].value << endl;
}

//TODO write_tlc tlc支持的稀疏格式
//tlc也能使用稀疏表示 考虑到目前大部分应用特征不会太多<500 目前只输出dense format 方便使用excell
//tlc dense 采用标准输出 第一列是名字比如pid 第二列是label 例如下面 另外输出的是原始特征 未经过normalize
//# 	label	JaccardSimilarity	CTR_s10_Query	CTR_s100_Query	CTR_s1000_Query	LogitCTR_s10_Query	LogitCTR_s100_Query	LogitCTR_s1000_Query	impressions_Query	clicks_Query
//_lottery|acute leukemia	0	0	0.013693014	0.013704492	0.013818185	-4.277081865	-4.276232328	-4.267855249	103347	1415
inline void write_csv(const Feature& feature, const string& uid, const string& label, ofstream& ofs)
{
  ofs << "_" << uid << "\t" << label; 
  foreach(double value, feature.cvalues())
  {
    ofs << "\t" << value;
  }
  ofs << endl;
}

template<typename T>
inline void addMeanVar(Feature* fe, const vector<T>& vec,
        const string mean_name = "", const string var_name = "")
{
  double mean = vec.size() > 0 ? sta::mean(vec) : 0;
  fe->add(mean, mean_name);
  double var = vec.size() > 1 ? sta::var(vec, mean) : 0;
  fe->add(var, var_name);
}

template<typename T>
inline void addMean(Feature* fe, const vector<T>& vec,
        const string mean_name = "")
{
  double mean = vec.size() > 0 ? sta::mean(vec) : 0;
  fe->add(mean, mean_name);
}

template<typename T>
inline void addVar(Feature* fe, const vector<T>& vec,
        const string var_name = "")
{
  double var = vec.size() > 1 ? sta::var(vec) : 0;
  fe->add(var, var_name);
}
} //----end of namespace gezi

#endif  //----end of FEATURE_UTIL_H_
