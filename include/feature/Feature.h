#ifndef _FEATURE_H_
#define _FEATURE_H_

#include "common_util.h"
using std::vector;
using std::pair;
using std::make_pair;

namespace gezi
{

//��������������õ� ����Ĭ��ϡ�裬dense��ʾ�����ڣ���������name��Ϣ��ʵ��Ӧ���ǽ������������� ��ʾ
//����������Ҫ�����(���Ƿ�ϡ���ʾ�����ֽ�������Instances��Instance��������) TODO

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

    Node(int index_)
    : index(index_)
    {

    }
    int index;
    double value;
  };
  typedef vector<Node>::iterator Iter;
  typedef vector<Node>::const_iterator ConstIter;
	typedef vector<double>::iterator VIter;
	typedef vector<double>::const_iterator ConstVIter;
  //����һ��zero_thre����ʵ�ʲ���Ҳok ϡ��ʹ���ж�==0 libsvm��tlc�����õ��ж�==0,��Ȼ��һ��������Ϊ�˽��һ����Ȼ�ж�==0
  //Feature feature(-1) ����������ʾһ����ȫdense��ʾ,values,nodes��dense

  Feature(bool use_section_name = true, double zero_thre = 0.0)
  : _use_section_name(use_section_name), _zero_thre(zero_thre)
  {
    int len = 1000;
    _nodes.reserve(len);
    _values.reserve(len);
    _name_counts.reserve(len);
    _names.reserve(len);
    _section_names.reserve(len);
  }

  virtual ~Feature()
  {

  }

  inline int size() const
  {
    return _values.size();
  }

  /** 
   * ������������ά��
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
   * ���ط������������
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
   * ������������
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
   * ��������, ע��feature Node index ��1��ʼ ��libsvm����һ��
   */
  void add(double value, string name)
  {
    if (_use_section_name)
    {
      name = (format("%s_%s") % _section_names.back() % name).str();
    }
    _names.push_back(name);
    _idx++;
    _values.push_back(value);
    if (fabs(value) > _zero_thre)
    {
      _nodes.push_back(Node(_names.size(), value));
    }
  }

  //ע�����ǰ һ����Ҫadd_section

  void add(double value)
  {
    string name = (format("%s%d") % _section_names.back() % _idx).str();
    add(value, name);
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

  //����ϡ��index, value 

  void set(int index, double value)
  {
    Iter iter = std::lower_bound(_nodes.begin(), _nodes.end(), Node(index),
            boost::bind(&Node::index, _1) < boost::bind(&Node::index, _2));
    if (iter != _nodes.end() && iter->index == index)
    {
      iter->value = value;
    }
  }

  //��ȡϡ��value

  const double value(int index) const
  {
    ConstIter iter = std::lower_bound(_nodes.begin(), _nodes.end(), Node(index),
            boost::bind(&Node::index, _1) < boost::bind(&Node::index, _2));
    if (iter != _nodes.end() && iter->index == index)
      return iter->value;
    else
      return 0.0;
  }


  //��ȡvalue ���ȳ���dense 
  const double operator[](int index) const {
    if (!_values.empty())
    {
      return _values[index];
    }
    else
    { //û��dense��ʾ������� Ŀǰ��demo�ȵط� ��������һ��ϡ���ʾ������stringת����ʱ�� ������dense value�������沿��
      return value(index + 1);
    }
  }

  const double valueAt(int index) const
  {
    int idx = (index + _values.size()) % _values.size();
    return _values[idx];
  }

  const double at(int index) const
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

  friend inline ostream & operator <<(ostream & os, Feature& fe)
  {
    os << fe.str();
    return os;
  }

private:
  vector<Node> _nodes;
  double _zero_thre;
  bool _use_section_name;

  vector<string> _names;
  vector<string> _section_names;
  vector<double>_values;
  vector<int> _name_counts;
  int _idx; //section �ڲ�index
};

typedef Feature::Node fnode_t;
}

#endif //end of _FEATURE_H_
