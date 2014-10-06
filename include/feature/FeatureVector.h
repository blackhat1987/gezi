/**
 *  ==============================================================================
 *
 *          \file   feature/FeatureVector.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-04-10 13:44:32.992130
 *
 *  \Description:  线上使用的特征向量表示，主要增加名字字段，针对特征不是超级多(<10^5)的情况
 *                 超级多的比如文本分类,建议直接用Vector稀疏表示即可
 *                 与Vector不同使用类stl 小写接口
 *  ==============================================================================
 */

#ifndef FEATURE__FEATURE_VECTOR_H_
#define FEATURE__FEATURE_VECTOR_H_
#include "Numeric/Vector/Vector.h"
namespace gezi {

	class FeatureVector : public Vector
	{
	public:
		~FeatureVector() = default;
		FeatureVector(FeatureVector&&) = default;
		FeatureVector& operator = (FeatureVector&&) = default;
		FeatureVector(const FeatureVector&) = default;
		FeatureVector& operator = (const FeatureVector&) = default;

#ifndef GCCXML
		using Vector::Vector;
#endif
	
		//在线始终是dense
		FeatureVector(bool useSparse = true)
			:_useSparseAlso(useSparse)
		{
			int len = 1000;
			values.reserve(len);
			_names.reserve(len);
			keepDense = true;   //@TODO will this is the best ?
		}

		//尽量不用 如果需要 可以考虑直接用Vector 稀疏情况
		FeatureVector(int length_)
			:Vector(length_)
		{

		}
	public:

		struct Feature
		{
			Feature()
			{
			}

			Feature(int index_, value_type value_)
				: index(index_), value(value_)
			{

			}

			Feature(int index_)
				: index(index_)
			{

			}
			int index;
			value_type value;

			bool operator == (const Feature& other) const
			{
				return index == other.index && value == other.value;
			}

			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version)
			{
				ar & index;
				ar & value;
			}
		};

		//注意非多态情况 默认按照dense 处理 但是如果是按照Vector Sparse的话 还是按照二分查找
		value_type operator[](index_type i) const
		{
			return values[i];
		}

		value_type& operator[](index_type i)
		{
			return values[i];
		}

		value_type value_at(int index) const
		{
			int idx = (index + values.size()) % values.size();
			return values[idx];
		}

#ifndef PYTHON_WRAPPER
		value_type& value_at(int index)
		{
			int idx = (index + values.size()) % values.size();
			return values[idx];
		}
#endif

		value_type at(int index) const
		{
			int idx = (index + values.size()) % values.size();
			return values[idx];
		}

#ifndef PYTHON_WRAPPER
		value_type& at(int index)
		{
			int idx = (index + values.size()) % values.size();
			return values[idx];
		}
#endif

		//覆盖掉基类  注意尽量在FeatureVector数据填充完之后 set_length一下(FeatureExtractor)
		int dimension() const
		{
			return Length();
		}

		void finalize()
		{
			if (_sectionNames.size() > 0)
			{
				_nameCounts.push_back(_idx);
			}
			_idx = 0;
		}

		vector<Feature>& features()
		{
			return _features;
		}

		const vector<Feature>& features() const
		{
			return _features;
		}

		//非0的特征数目 注意Vector是Count()
		int count() const
		{
			return _features.size();
		}

		bool empty() const
		{
			return _names.empty();
		}

		void clear()
		{
			Vector::Clear();
			_names.clear();
		}

		string str(string sep = ",")
		{
			std::stringstream ss;

			if (_useSparseAlso && !_features.empty())
			{
				for (Feature& feature : _features)
				{
					ss << feature.index << ":" << feature.value << sep;
				}
			}
			else
			{
				ForEachNonZero([&](int index, value_type value) {
					ss << index << ":" << value << sep;
				});
			}
			return ss.str().substr(0, ss.str().length() - sep.length());
		}

		//展示name 覆盖掉Vector中的Str了 @TODO test 正确性以及对Vector的影响
		string Str(string sep = ",")
		{
			std::stringstream ss;

			if (_useSparseAlso && !_features.empty())
			{
				for (Feature& feature : _features)
				{
					ss << _names[feature.index] << ":" << feature.value << sep;
				}
			}
			else
			{
				ForEachNonZero([&](int index, value_type value) {
					ss << _names[index] << ":" << value << sep;
				});
			}
			return ss.str().substr(0, ss.str().length() - sep.length());
		}

		vector<string>& names()
		{
			return _names;
		}

		const vector<string>& names() const
		{
			return _names;
		}

		vector<string>& section_names()
		{
			return _sectionNames;
		}

		const vector<string>& section_names() const
		{
			return _sectionNames;
		}

		vector<int>& name_counts()
		{
			return _nameCounts;
		}

		const	vector<int>& name_counts() const
		{
			return _nameCounts;
		}

		/*	vector<value_type>& values()
			{
			return values;
			}

			const vector<value_type>& values() const
			{
			return values;
			}*/
		//-----------------------最重要的添加数据
		/**
	 * 增加特征, 注意feature Node index 是0开始 不再和libsvm保持一致 和tlc保持一致
	 * 注意调用前 一定先要add_section
	 */
		void add(value_type value, string name = "")
		{
			if (name.empty())
			{
				name = (format("%s_%d") % _sectionNames.back() % _idx).str();
			}
			else if (_useSectionName && !_sectionNames.empty())
			{
				name = (format("%s_%s") % _sectionNames.back() % name).str();
			}

			if (value != 0 && _useSparseAlso)
			{
				_features.push_back(Feature(_names.size(), value));
			}

			_names.push_back(name);
			_idx++;
			Add(value); //Vector添加dense数据
		}

		////hack for template match error  void add(Vec& values_, string name = "") @FIXME
		////是c++ 11 的重载匹配变严格了吗 不会自动转value_type匹配？
		//void add(int value, string name = "")
		//{
		//	add(value_type(value), name);
		//}

		void add(value_type* values_, int len, string name = "")
		{
			if (name.empty())
			{
				for (int i = 0; i < len; i++)
				{
					add(values_[i]);
				}
			}
			else
			{
				for (int i = 0; i < len; i++)
				{
					string name_ = name + STRING(i);
					add(values_[i], name_);
				}
			}
		}
		//c++ 貌似模板匹配的优先度太高了 add(1,"")也会匹配下面这个 而不会匹配 add(value_type,"")
		//template<typename Vec> void add(Vec& values_, string name = "")
		template<typename T>
		void add(const vector<T>& values_, string name = "")
		{
			if (name.empty())
			{
				for (auto value : values_)
				{
					add(value);
				}
			}
			else
			{
				int len = values_.size();
				for (int i = 0; i < len; i++)
				{
					string name_ = name + STRING(i);
					add(values_[i], name_);
				}
			}
		}

		//@TODO 由于add(int, )不会自动转value_type 匹配正确重载 而是优先匹配模板 造成代码重复。。
		//可以考虑add vector 改名 adds 更清晰
		template<typename T, size_t Len>
		void add(std::array<T, Len>& values_, string name = "")
		{
			if (name.empty())
			{
				for (auto value : values_)
				{
					add(value);
				}
			}
			else
			{
				int len = values_.size();
				for (int i = 0; i < len; i++)
				{
					string name_ = name + STRING(i);
					add(values_[i], name_);
				}
			}
		}

		//adds(set.. unordered set or for vector @TODO尽量使用这个 避免上面的 上面仅为兼容
		template<typename Vec>
		void adds(const Vec& values_, string name = "")
		{
			if (name.empty())
			{
				for (auto value : values_)
				{
					add(value);
				}
			}
			else
			{
				int len = values_.size();
				for (int i = 0; i < len; i++)
				{
					string name_ = name + STRING(i);
					add(values_[i], name_);
				}
			}
		}

		void add_section(string name)
		{
			finalize();
			_sectionNames.push_back(name);
		}

		//慎用 仅仅获取一个sparse 独立于Vector之外 如果有这个需要一般需要用Vector 然后Add(index, value)
		void add(int index, value_type value)
		{
			if (value)
			{
				_features.push_back(Feature(index, value));
			}
		}

		template<typename T>
		void add_sparse(vector<T>& values)
		{
			for (size_t i = 0; i < values.size(); i++)
			{
				_features.push_back(Feature(i, values[i]));
			}
		}
		//---------------------------

		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive &ar, const unsigned int version)
		{
			ar & BOOST_SERIALIZATION_BASE_OBJECT(Vector);
			ar & BOOST_SERIALIZATION_NVP(_useSectionName);
			ar & BOOST_SERIALIZATION_NVP(_names);
			ar & BOOST_SERIALIZATION_NVP(_sectionNames);
			ar & BOOST_SERIALIZATION_NVP(_nameCounts);
			ar & BOOST_SERIALIZATION_NVP(_idx);
			ar & BOOST_SERIALIZATION_NVP(_useSparseAlso);
			ar & BOOST_SERIALIZATION_NVP(_features);
		}
	protected:
	private:
		bool _useSectionName = true;
		svec _names;
		svec _sectionNames;
		ivec _nameCounts; //每个section name的 counts
		int _idx = 0; //section 内部index 

		bool _useSparseAlso = true;
		vector<Feature> _features;
	};

	typedef shared_ptr<FeatureVector> FeatureVectorPtr;
	typedef FeatureVector Features;
	typedef FeatureVectorPtr FeaturesPtr;

	class PyFeatures : public Features
	{

	};
}  //----end of namespace gezi

#endif  //----end of FEATURE__FEATURE_VECTOR_H_
