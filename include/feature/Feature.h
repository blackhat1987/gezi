#ifndef _FEATURE_H_
#define _FEATURE_H_

#include "common_util.h"
using std::vector;
using std::pair;
using std::make_pair;

//@WARNING depreciated -> use FeatureVector.h
namespace gezi {

	//这个特征是在线用的 所以默认稀疏，dense表示都存在，包含所有name信息，实际应该是叫做：特征向量 表示
	//@TODO class Feature : public Vector # svec names;
	//其实应该是FeatureVector 另外Node 使用std::pair 泛化更好？Node命名Feature?
	class Feature
	{
	public:

		struct Node //Node其实是Feature
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
		//保留一个zero_thre但是实际不用也ok 稀疏使用判断==0 libsvm和tlc都是用的判断==0,虽然有一定浮点误差，为了结果一致仍然判断==0
		//Feature feature(-1) 可以用来表示一个完全dense表示,values,nodes都dense
		//@FIXME h2cc.py对于构造函数:下面多行 存在bug
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

		//因为默认是同时dense + sparse 存在values就是dense 存在nodes就是sparse
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
		 * 返回特征向量维度
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

		//@TODO remove  feature num 应该是所有feature的num  这个应该用count代替 @FIXME
		//也可能nodes里面有value是0的 
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
		 * 返回特征数组
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
		 * 增加特征, 注意feature Node index 是0开始 不再和libsvm保持一致 和tlc保持一致
		 * /注意调用前 一定先要add_section
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

		//设置稀疏index, value 

		void set(int index, Float value)
		{
			Iter iter = std::lower_bound(_nodes.begin(), _nodes.end(), Node(index),
				[](const Node& l, const Node& r) { return l.index < r.index; });
			if (iter != _nodes.end() && iter->index == index)
			{
				iter->value = value;
			}
		}

		//获取稀疏value

		const Float value(int index) const
		{
			ConstIter iter = std::lower_bound(_nodes.begin(), _nodes.end(), Node(index),
				[](const Node& l, const Node& r) { return l.index < r.index; });
			if (iter != _nodes.end() && iter->index == index)
				return iter->value;
			else
				return 0.0;
		}


		//获取value 首先尝试dense 
		const Float operator[](int index) const
		{
			if (!_values.empty())
			{
				return _values[index];
			}
			else
			{ //没有dense表示的情况下 目前在demo等地方 比如输入一个稀疏表示向量的string转特征时候 不生成dense value调用下面部分
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

		//-------------------------兼容离线接口 事实上也可以通过继承直接用离线设计 
		//但是 需要修改feature_util  @TODO
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
		int _idx; //section 内部index 
		bool _keep_sparse;
		bool _keep_dense;
		int _dimension;
	public:
		bool normalized = false;
	};

	typedef Feature::Node fnode_t;
}

#endif //end of _FEATURE_H_
