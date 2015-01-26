/**
 *  ==============================================================================
 *
 *          \file   feature/FeatureVector.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-04-10 13:44:32.992130
 *
 *  \Description:  ����ʹ�õ�����������ʾ����Ҫ���������ֶΣ�����������ǳ�����(<10^5)�����
 *                 ������ı����ı�����,����ֱ����Vectorϡ���ʾ����
 *                 ��Vector��ͬʹ����stl Сд�ӿ�
 *                 2014-10-10 ���Ӳ����name��֧�� ����Ԥ������������ѵ�� �ǵ�һ��feature��������
 *                 FeatureVector or Features::useNames() = false;
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

		//����ʼ����dense
		FeatureVector(bool useSparse = true)
			:_useSparseAlso(useSparse)
		{
			int len = 1000;
			values.reserve(len);
			_names.reserve(len);
			keepDense = true;   //@TODO will this is the best ?
		}

		//�������� �����Ҫ ���Կ���ֱ����Vector ϡ�����
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

		//ע��Ƕ�̬��� Ĭ�ϰ���dense ���� ��������ǰ���Vector Sparse�Ļ� ���ǰ��ն��ֲ���
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

		//���ǵ�����  ע�⾡����FeatureVector���������֮�� set_lengthһ��(FeatureExtractor)
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

		//��0��������Ŀ ע��Vector��Count() ע�����_useSparse = false��ôʼ�շ���0�� ���Ե���Vector�ķ�����ȡ������Ŀ
		//����������Ŀ����size���� ��Ϊ��dense��
		int count() const
		{
			if (_useSparseAlso)
			{
				return _features.size();
			}

			return Vector::NumNonZeros();
		}

		bool empty() const
		{
			//return _names.empty();
			return values.empty();
		}

		void clear()
		{
			Vector::Clear();
			_names.clear();
			_features.clear();
			_idx = 0;
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

		//չʾname ���ǵ�Vector�е�Str�� @TODO test ��ȷ���Լ���Vector��Ӱ��
		string Str(string sep = ",")
		{
			if (!useNames())
			{ //no name info
				return str(sep);
			}

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
		//-----------------------����Ҫ���������
		/**
	 * ��������, ע��feature Node index ��0��ʼ ���ٺ�libsvm����һ�� ��tlc����һ��
	 * ע�����ǰ һ����Ҫadd_section
	 */
		void add(value_type value, string name = "")
		{
			//@TODO may is_zero(value) ?
			if (value != _zeroValue && _useSparseAlso)
			{
				//_features.push_back(Feature(_names.size(), value));
				_features.push_back(Feature(values.size(), value));
			}

			Add(value); //Vector���dense����

			if (useNames())
			{
				if (name.empty())
				{
					name = format("{}_{}", _sectionNames.back(), _idx);
				}
				else if (_useSectionName && !_sectionNames.empty())
				{
					name = format("{}_{}", _sectionNames.back(), name);
				}

				_names.push_back(name);
				_idx++;
			}
		}

		////hack for template match error  void add(Vec& values_, string name = "") @FIXME
		////��c++ 11 ������ƥ����ϸ����� �����Զ�תvalue_typeƥ�䣿
		//void add(int value, string name = "")
		//{
		//	add(value_type(value), name);
		//}

		void add(value_type* values_, int len, string name = "")
		{
			if (useNames())
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
						string name_ = format("{}{}", name, i);
						add(values_[i], name_);
					}
				}
			}
			else
			{
				for (int i = 0; i < len; i++)
				{
					add(values_[i]);
				}
			}
		}
		//c++ ò��ģ��ƥ������ȶ�̫���� add(1,"")Ҳ��ƥ��������� ������ƥ�� add(value_type,"")
		//template<typename Vec> void add(Vec& values_, string name = "")
		template<typename T>
		void add(const vector<T>& values_, string name = "")
		{
			if (useNames())
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
					for (size_t i = 0; i < values_.size(); i++)
					{
						string name_ = format("{}{}", name, i);
						add(values_[i], name_);
					}
				}
			}
			else
			{
				for (auto value : values_)
				{
					add(value);
				}
			}
		}

		//@TODO ����add(int, )�����Զ�תvalue_type ƥ����ȷ���� ��������ƥ��ģ�� ��ɴ����ظ�����
		//���Կ���add vector ���� adds ������
		template<typename T, size_t Len>
		void add(std::array<T, Len>& values_, string name = "")
		{
			if (useNames())
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
					for (size_t i = 0; i < values_.size(); i++)
					{
						string name_ = format("{}{}", name, i);
						add(values_[i], name_);
					}
				}
			}
			else
			{
				for (auto value : values_)
				{
					add(value);
				}
			}
		}

		//adds(set.. unordered set or for vector @TODO����ʹ����� ��������� �����Ϊ����
		template<typename Vec>
		void adds(const Vec& values_, string name = "")
		{
			if (useNames())
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
					int i = 0;
					for (auto value : values_)
					{
						string name_ = format("{}{}", name, i++);
						add(value, name_);
					}
				}
			}
			else
			{
				for (auto value : values_)
				{ //֮ǰʹ��add(value)������û��sparse�洢 ���Ǵ�ӡ����strò���ж�!=0��ȥ���ܶ��С�ĸ����� Ȼ������Ǹ��������� ��Ԥ������һ�� �����޸�
					add(value);
				}
			}
		}

		void add_section(string name)
		{
			if (useNames())
			{
				finalize();
				_sectionNames.push_back(name);
			}
		}

		//���� ������ȡһ��sparse ������Vector֮�� ����������Ҫһ����Ҫ��Vector Ȼ��Add(index, value)
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
	public:

#ifndef GCCXML
		static bool& useNames()
		{
			static bool _useNames = true;
			return _useNames;
		}
#endif
	protected:
	private:
		bool _useSectionName = true;
		svec _names;
		svec _sectionNames;
		ivec _nameCounts; //ÿ��section name�� counts
		int _idx = 0; //section �ڲ�index 

		bool _useSparseAlso = true;
		vector<Feature> _features;
	};

	typedef shared_ptr<FeatureVector> FeatureVectorPtr;
	typedef FeatureVector Features;
	typedef FeatureVectorPtr FeaturesPtr;

#ifdef PYTHON_WRAPPER
	class PyFeatures : public Features
	{

	};
#endif

}  //----end of namespace gezi

#endif  //----end of FEATURE__FEATURE_VECTOR_H_
