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

		//����ʼ����dense
		FeatureVector()
		{
			keepDense = true;
		}
		FeatureVector(int length_, bool useSparse = true)
			:Vector(length_), _useSparseAlso(useSparse)
		{
			FeatureVector();
			values.reserve(length);
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

		//ע��Ƕ�̬��� Ĭ�ϰ���dense ���� ��������ǰ���Vector Sparse�Ļ� ���ǰ��ն��ֲ���
		Float operator[](int i) const
		{
			return values[i];
		}

		Float operator[](int i)
		{
			return values[i];
		}

		//���ǵ�����  ע�⾡����FeatureVector���������֮�� set_lengthһ��(FeatureExtractor)
		int dimension() const
		{
			return _names.size();
		}

		void set_length()
		{
			length = _names.size();
		}

		void set_length(int len)
		{
			length = len;
		}

		void finalize()
		{
			if (_sectionNames.size() > 0)
			{
				_nameCounts.push_back(_idx);
			}
			_idx = 0;
			set_length();
		}

		vector<Feature>& features()
		{
			return _features;
		}

		const vector<Feature>& features() const
		{
			return _features;
		}

		//��0��������Ŀ ע��Vector��Count()
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

			if (_useSparseAlso)
			{
				for (Feature& feature : _features)
				{
					ss << feature.index << ":" << feature.value << " ";
				}
			}
			else
			{
				ForEachNonZero([&ss](int index, Float value) {
					ss << index << ":" << value << " ";
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

		//-----------------------����Ҫ���������
		/**
	 * ��������, ע��feature Node index ��0��ʼ ���ٺ�libsvm����һ�� ��tlc����һ��
	 * ע�����ǰ һ����Ҫadd_section
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
			Add(value); //Vector���dense����
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

		template<typename Vec>
		void add(Vec& values, string name = "")
		{
			if (name.empty())
			{
				for(auto value : values)
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
			_sectionNames.push_back(name);
		}

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
		ivec _nameCounts; //ÿ��section name�� counts
		int _idx = 0; //section �ڲ�index 

		bool _useSparseAlso = true;
		vector<Feature> _features;
	};

	typedef shared_ptr<FeatureVector> FeatureVectorPtr;
	typedef FeatureVector Features;
	typedef FeatureVectorPtr FeaturesPtr;
}  //----end of namespace gezi

#endif  //----end of FEATURE__FEATURE_VECTOR_H_
