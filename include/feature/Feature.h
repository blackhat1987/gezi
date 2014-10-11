#ifndef _FEATURE_H_
#define _FEATURE_H_

#include "common_util.h"
using std::vector;
using std::pair;
using std::make_pair;

//@WARNING depreciated -> use FeatureVector.h
namespace gezi {

	//��������������õ� ����Ĭ��ϡ�裬dense��ʾ�����ڣ���������name��Ϣ��ʵ��Ӧ���ǽ������������� ��ʾ
	//@TODO class Feature : public Vector # svec names;
	//��ʵӦ����FeatureVector ����Node ʹ��std::pair �������ã�Node����Feature?
	class Feature
	{
	public:

		struct Node //Node��ʵ��Feature
		{

			Node()
			{
			}

			Node(int index_, Float value_)
				: index(index_), value(value_)
			{

			}

			Node(int index_)
				: index(index_)
			{

			}
			int index;
			Float value;
		};

		typedef vector<Node>::iterator Iter;
		typedef vector<Node>::const_iterator ConstIter;
		typedef vector<Float>::iterator VIter;
		typedef vector<Float>::const_iterator ConstVIter;
		//����һ��zero_thre����ʵ�ʲ���Ҳok ϡ��ʹ���ж�==0 libsvm��tlc�����õ��ж�==0,��Ȼ��һ��������Ϊ�˽��һ����Ȼ�ж�==0
		//Feature feature(-1) ����������ʾһ����ȫdense��ʾ,values,nodes��dense
		//@FIXME h2cc.py���ڹ��캯��:������� ����bug
		Feature(bool keep_dense = false, bool keep_sparse = false, int dimension = 1000, bool use_section_name = true, Float zero_thre = 0.0)
			: _keep_dense(keep_dense), _keep_sparse(keep_sparse), _use_section_name(use_section_name), _zero_thre(zero_thre), _dimension(dimension)
		{
			int len = 1000;
			_nodes.reserve(len);
			_values.reserve(len);
			_name_counts.reserve(len);
			_names.reserve(len);
			_section_names.reserve(len);
		}

		Feature(int length)
			:_dimension(length)
		{

		}
		~Feature() = default;
		Feature(Feature&&) = default;
		Feature& operator = (Feature&&) = default;
		Feature(const Feature&) = default;
		Feature& operator = (const Feature&) = default;

		bool keep_sparse() const
		{
			return _keep_sparse;
		}
		Feature& keep_sparse(bool sparse_)
		{
			_keep_sparse = sparse_;
			return *this;
		}

		bool keep_dense() const
		{
			return _keep_dense;
		}

		Feature& keep_dense(bool dense_)
		{
			_keep_dense = dense_;
			return *this;
		}

		//��ΪĬ����ͬʱdense + sparse ����values����dense ����nodes����sparse
		bool is_dense() const
		{
			return !_values.empty();
		}

		bool is_sparse() const
		{
			return !_nodes.empty();
		}


		bool only_sparse() const
		{
			return _values.empty();
		}

		bool only_dense() const
		{
			return _nodes.empty();
		}

		int size() const
		{
			return _values.size();
		}

		/**
		 * ������������ά��
		 * @return
		 */
		int dimension() const
		{
			if (!_keep_sparse)
			{
				return _names.size();
			}
			else
			{
				return _dimension;
			}
		}

		bool empty() const
		{
			return _names.empty();
		}

		//@TODO remove  feature num Ӧ��������feature��num  ���Ӧ����count���� @FIXME
		//Ҳ����nodes������value��0�� 
		int featureNum() const
		{
			return _nodes.size();
		}

		int feature_num() const
		{
			return _nodes.size();
		}

		int count()
		{
			return _nodes.size();
		}

		int features() const
		{
			return _nodes.size();
		}

		/**
		 * ������������
		 *
		 *
		 * @return
		 */
		vector<Node>& nodes()
		{
			return _nodes;
		}

		const vector<Node>& nodes() const
		{
			return _nodes;
		}

		Feature& dimension(int dimension)
		{
			_dimension = dimension;
			return *this;
		}
		void set_dimension(int dimension)
		{
			_dimension = dimension;
		}
		void to_dense()
		{
			_keep_sparse = false;
			_values.resize(_dimension, 0);
			foreach(Node& node, _nodes)
			{
				_values[node.index] = node.value;
			}
		}
		/**
		 * ��������, ע��feature Node index ��0��ʼ ���ٺ�libsvm����һ�� ��tlc����һ��
		 * /ע�����ǰ һ����Ҫadd_section
		 */
		void add(Float value, string name = "")
		{
			if (name.empty())
			{
				name = (boost::format("%s%d") % _section_names.back() % _idx).str();
			}
			else if (_use_section_name && !_section_names.empty())
			{
				name = (boost::format("%s_%s") % _section_names.back() % name).str();
			}

			if (!_keep_dense && fabs(value) > _zero_thre)
			{
				_nodes.push_back(Node(_names.size(), value));
			}

			_names.push_back(name);
			_idx++;
			if (!_keep_sparse)
			{
				_values.push_back(value);
			}
		}

		void add(Float* values, int len, string name = "")
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

		//void add(vector<Float>& values, string name = "")
		template<typename T>
		void add(vector<T>& values, string name = "")
		{
			if (name.empty())
			{
				foreach(T value, values)
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

		void add(int index, Float value)
		{
			if (value)
			{
				_nodes.push_back(Node(index, value));
			}
		}

		template<typename T>
		void add_sparse(vector<T>& values)
		{
			for (size_t i = 0; i < values.size(); i++)
			{
				_nodes.push_back(Node(i, values[i]));
			}
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

		void set(int index, Float value)
		{
			Iter iter = std::lower_bound(_nodes.begin(), _nodes.end(), Node(index),
				[](const Node& l, const Node& r) { return l.index < r.index; });
			if (iter != _nodes.end() && iter->index == index)
			{
				iter->value = value;
			}
		}

		//��ȡϡ��value

		const Float value(int index) const
		{
			ConstIter iter = std::lower_bound(_nodes.begin(), _nodes.end(), Node(index),
				[](const Node& l, const Node& r) { return l.index < r.index; });
			if (iter != _nodes.end() && iter->index == index)
				return iter->value;
			else
				return 0.0;
		}


		//��ȡvalue ���ȳ���dense 
		const Float operator[](int index) const
		{
			if (!_values.empty())
			{
				return _values[index];
			}
			else
			{ //û��dense��ʾ������� Ŀǰ��demo�ȵط� ��������һ��ϡ���ʾ������stringת����ʱ�� ������dense value�������沿��
				return value(index + 1);
			}
		}

		const Float value_at(int index) const
		{
			int idx = (index + _values.size()) % _values.size();
			return _values[idx];
		}

		const Float at(int index) const
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
		vector<string>& names()
		{
			return _names;
		}

		vector<string>& section_names()
		{
			return _section_names;
		}

		vector<int>& name_counts()
		{
			return _name_counts;
		}

		vector<Float>& values()
		{
			return _values;
		}

		const vector<Float>& values() const
		{
			return _values;
		}

		const vector<string>& names() const
		{
			return _names;
		}

		const vector<string>& section_names() const
		{
			return _section_names;
		}

		const vector<int>& name_counts() const
		{
			return _name_counts;
		}

		static Float default_min()
		{
			return 0;
		}

		static Float default_mean()
		{
			return 0.5;
		}

		static Float default_max()
		{
			return 1.0;
		}

		friend  ostream & operator <<(ostream & os, Feature& fe)
		{
			os << fe.str();
			return os;
		}

		//-------------------------�������߽ӿ� ��ʵ��Ҳ����ͨ���̳�ֱ����������� 
		//���� ��Ҫ�޸�feature_util  @TODO
		template<typename ValueVistor>
		void ForEach(ValueVistor visitor) const
		{
			if (is_dense())
			{
				for (size_t i = 0; i < _values.size(); i++)
				{
					visitor(i, _values[i]);
				}
			}
			else
			{
				foreach(const Node& node, _nodes)
				{
					visitor(node.index, node.value);
				}
			}
		}

		template<typename ValueVistor>
		void ForEach(ValueVistor visitor)
		{
			if (is_dense())
			{
				for (size_t i = 0; i < _values.size(); i++)
				{
					visitor(i, ref(_values[i]));
				}
			}
			else
			{
				foreach(Node& node, _nodes)
				{
					visitor(node.index, ref(node.value));
				}
			}
		}

		bool IsDense() const
		{
			return !_values.empty();
		}


		template<typename ValueVistor>
		void ForEachDense(ValueVistor visitor)
		{
			for (size_t i = 0; i < _values.size(); i++)
			{
				visitor(i, ref(_values[i]));
			}
		}

		template<typename ValueVistor>
		void ForEachSparse(ValueVistor visitor) const
		{
			for (size_t i = 0; i < _nodes.size(); i++)
			{
				visitor(_nodes[i].index, _nodes[i].value);
			}
		}

		void Add(Float value)
		{
			_values.push_back(value);
		}

		void Add(int index, Float value)
		{
			if (value)
			{
				_nodes.push_back(Node(index, value));
			}
		}
		int Count() const
		{
			return _nodes.size();
		}

		int Index(int index) const
		{
			return _nodes[index].index;
		}

		int Index(int index)
		{
			return _nodes[index].index;
		}

		Float Value(int index) const
		{
			return _nodes[index].value;
		}

		Float& Value(int index)
		{
			return _nodes[index].value;
		}

		const vector<Float>& Values() const
		{
			return _values;
		}

		vector<Float>& Values()
		{
			return _values;
		}

		int Length()
		{
			return _dimension;
		}

	private:
		vector<Node> _nodes;
		Float _zero_thre;
		bool _use_section_name;

		vector<string> _names;
		vector<string> _section_names;
		vector<Float>_values;
		vector<int> _name_counts;
		int _idx; //section �ڲ�index 
		bool _keep_sparse;
		bool _keep_dense;
		int _dimension;
	public:
		bool normalized = false;
	};

	typedef Feature::Node fnode_t;
}

#endif //end of _FEATURE_H_
