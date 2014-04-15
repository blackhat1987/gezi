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

			Feature(int index_, Float value_)
				: index(index_), value(value_)
			{

			}

			Feature(int index_)
				: index(index_)
			{

			}
			int index;
			Float value;

			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version)
			{
				ar & index;
				ar & value;
			}
		};

		//注意非多态情况 默认按照dense 处理 但是如果是按照Vector Sparse的话 还是按照二分查找
		Float operator[](int i) const
		{
			return values[i];
		}

		Float operator[](int i)
		{
			return values[i];
		}

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
		int count()
		{
			return _features.size();
		}

		bool empty() const
		{
			return _names.empty();
		}

		string str()
		{
			std::stringstream ss;

			if (_useSparseAlso && !_features.empty())
			{
				for (Feature& feature : _features)
				{
					ss << feature.index << ":" << feature.value << "\t";
				}
			}
			else
			{
				ForEachNonZero([&ss](int index, Float value) {
					ss << index << ":" << value << "\t";
				});
			}
			return ss.str();
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

		/*	vector<Float>& values()
			{
			return values;
			}

			const vector<Float>& values() const
			{
			return values;
			}*/
		//-----------------------最重要的添加数据
		/**
	 * 增加特征, 注意feature Node index 是0开始 不再和libsvm保持一致 和tlc保持一致
	 * 注意调用前 一定先要add_section
	 */
		void add(Float value, string name = "")
		{
			if (name.empty())
			{
				name = (format("%s%d") % _sectionNames.back() % _idx).str();
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
		////是c++ 11 的重载匹配变严格了吗 不会自动转float匹配？
		//void add(int value, string name = "")
		//{
		//	add(Float(value), name);
		//}

		void add(Float* values_, int len, string name = "")
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
		//c++ 貌似模板匹配的优先度太高了 add(1,"")也会匹配下面这个 而不会匹配 add(Float,"")
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

		//@TODO 由于add(int, )不会自动转float 匹配正确重载 而是优先匹配模板 造成代码重复。。
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
		void add(int index, Float value)
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
			ar & boost::serialization::base_object<Vector>(*this);
			ar & _useSectionName;
			ar & _names;
			ar & _sectionNames;
			ar & _nameCounts;
			ar & _idx;
			ar & _useSparseAlso;
			ar & _features;
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
}  //----end of namespace gezi

#endif  //----end of FEATURE__FEATURE_VECTOR_H_
