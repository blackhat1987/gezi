#ifndef _FEATURE_H_
#define _FEATURE_H_

#include "common_util.h"

using std::vector;
using std::pair;
using std::make_pair;
namespace gezi
{

class Feature
{
public:

  struct Node
  {

    Node()
    {
    }

    Node(int index_, double value_)
    : index(index_), value(value_)
    {

    }
    int index;
    double value;
  };

  //如果不用稀疏模式 可以设置 Feature feature(-1);

  Feature(double zero_thre = 0.0000001)
  : _zero_thre(zero_thre)
  {
    int len = 100;
    _nodes.reserve(len);
    _values.reserve(len);
    _name_counts.reserve(len);
    _names.reserve(len);
    _section_names.reserve(len);
  }

  virtual ~Feature()
  {

  }

  /** 
   * 返回特征向量维度
   * @return 
   */
  inline int dimension() const
  {
    return _names.size();
  }

  inline bool empty() const
  {
    return _names.empty();
  }
  /**
   * 返回非零的特征数量
   *
   */
  inline int featureNum() const
  {
    return _nodes.size();
  }

  inline int features() const
  {
    return _nodes.size();
  }

  /** 
   * 返回特征数组
   * 
   * 
   * @return 
   */
  inline vector<Node>& nodes()
  {
    return _nodes;
  }

  inline const vector<Node>& cnodes() const
  {
    return _nodes;
  }

  /**
   * 增加特征, 注意feature Node index 是1开始 和libsvm保持一致
   */
  void add(double value, string name, bool use_section = false)
  {
    if (use_section)
    {
      name = (format("%s::%s") % _section_names.back() % name).str();
    }
    _names.push_back(name);
    _idx++;
    _values.push_back(value);
    if (fabs(value) > _zero_thre)
    {
      _nodes.push_back(Node(_names.size(), value));
    }
  }

  //注意调用前 一定先要add_section

  void add(double value)
  {
    string name = (format("%s%d") % _section_names.back() % _idx).str();
    add(value, name, false);
  }

  void add(double* values, int len, const string& name = "")
  {
    if (name.empty())
    {
      for (int i = 0; i < len; i++)
      {
        add(values[i]);
      }
    }
    else
    {
      for (int i = 0; i < len; i++)
      {
        string name_ = name + STRING(i);
        add(values[i], name_);
      }
    }
  }

  void add(vector<double>& values, const string& name = "")
  {
    if (name.empty())
    {

      foreach(double value, values)
      {
        add(value);
      }
    }
    else
    {
      int len = values.size();
      for (int i = 0; i < len; i++)
      {
        string name_ = name + STRING(i);
        add(values[i], name_);
      }
    }
  }

  void add_section(string name)
  {
    finalize();
    _section_names.push_back(name);
  }

  void finalize()
  {
    if (_section_names.size() > 0)
    {
      _name_counts.push_back(_idx);
    }
    _idx = 0;
  }

  //  void set(int index, double value)
  //  {
  //    if (_nodes.size() < 10)
  //    {
  //
  //      foreach(Node& node, _nodes)
  //      {
  //        if (node.index == index)
  //        {
  //          node.value = value;
  //          break;
  //        }
  //      }
  //    }
  //    else
  //    {
  //      typedef vector<Node>::iterator Iter;
  //      Iter it = std::lower_bound(_nodes.begin(), _nodes.end(),
  //              boost::bind(&Node::index, _1) < boost::bind(&Node::index, _2));
  //      //      Iter it; //sort can as below but lower_bound can not ..
  //      //      std::sort(_nodes.begin(), _nodes.end(),
  //      //              boost::bind(&Node::index, _1) < boost::bind(&Node::index, _2));
  //
  //      if (it != _nodes.end() && it->index == index)
  //      {
  //        it->value = value;
  //      }
  //    }
  //  }

  const double operator[](int index) const {
    for (int i = 0; i < (int) _nodes.size(); i++)
    {
      if (_nodes[i].index == index)
      {
        return _nodes[i].value;
      }
    }
  }

  const double valueAt(int index) const
  {
    int idx = (index + _values.size()) % _values.size();
    return _values[idx];
  }

  string str()
  {
    std::stringstream ss;

    foreach(Node& node, _nodes)
    {
      ss << node.index << ":" << node.value << " ";
    }
    return ss.str();
  }
  //if const vector<string>& names() you need const vector<>& = names() better but not convinent

  inline vector<string>& names()
  {
    return _names;
  }

  inline vector<string>& section_names()
  {
    return _section_names;
  }

  inline vector<int>& name_counts()
  {
    return _name_counts;
  }

  inline vector<double>& values()
  {
    return _values;
  }

  inline const vector<string>& cnames() const
  {
    return _names;
  }

  inline const vector<string>& csection_names() const
  {
    return _section_names;
  }

  inline const vector<int>& cname_counts() const
  {
    return _name_counts;
  }

  inline const vector<double>& cvalues() const
  {
    return _values;
  }

  static double defaultMin()
  {
    return 0;
  }

  static double defaultMean()
  {
    return 0.5;
  }

  static double defaultMax()
  {
    return 1.0;
  }

private:
  vector<Node> _nodes;
  double _zero_thre;

  vector<string> _names;
  vector<string> _section_names;
  vector<double>_values;
  vector<int> _name_counts;
  int _idx; //section 内部index
};

typedef Feature::Node fnode_t;
}
#endif
