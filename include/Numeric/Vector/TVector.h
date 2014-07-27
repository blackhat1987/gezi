/**
 *  ==============================================================================
 *
 *          \file   Numeric/Vector/TVector.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-03-26 10:46:03.965585
 *
 *  \Description:  �����ĺ��ı�ʾ
 *								 ֧�ֶ�д��dense and sparse
 ��������֧��binary ����valueΪ�ձ�ʾbinary @TODO
 *   @TODO �Ƿ���Ҫ int length , index ��Ϊint64

 *  ==============================================================================
 */

#ifndef NUMERIC__VECTOR__FVECTOR_H_
#define NUMERIC__VECTOR__FVECTOR_H_
#include "common_util.h"
#include "serialize_util.h"
namespace gezi {

	//@TODO TVector �� Vector ͳһ �ϲ��� ĿǰΪ�˲�Ӱ��ʹ��Vector�Ĵ�����ʱ���� TvectorֻҪʹ��
	//TVector<int> Ҳ����fastrank�����IntArray ����fastrank����IntArray������ ��̬int short bool
	//@TODO ȡ��Vector ʹ��TVector<double> ����Vector ֻά��TVector Ŀǰ��Vector�ڲ��д����
	template<typename ValueType>
	class TVector
	{
	public:
		TVector() = default; //sparse����ʱ�������length
		virtual ~TVector() {}
		TVector(TVector&&) = default;
		TVector& operator = (TVector&&) = default;
		TVector(const TVector&) = default;
		TVector& operator = (const TVector&) = default;

		typedef vector<ValueType> Vec;

		//��Ҫ�ⲿע��� ��ʼ����length ��ô�����Add(value) dense��ʽ Ҫ��֤values��󳤶�
		//�ͳ�ʼ���õ�һ�� ��ҪAdd���� ��Ϊʵ��Length()������ʾ�������� �����ʵ��Ҫ���sparse
		TVector(int length_)
			: length(length_)
		{
		}

		TVector(ValueType value_, int length_)
			: length(length_), _zeroValue(value_)
		{
		}

		void Swap(Vector& other)
		{
			length = other.length;
			indices.swap(other.indices);
			values.swap(other.values);
		}

		void Init(Vec& values_)
		{
			ToDense(values_);
		}

		void ToDense(Vec& values_)
		{
			values.swap(values_);
			length = values.size();
			indices.clear();
		}

		void ToDense()
		{
			Vec vec(length, _zeroValue);
			for (size_t i = 0; i < indices.size(); i++)
			{
				vec[indices[i]] = values[i];
			}
			numNonZeros = indices.size();
			indices.clear();
			values.swap(vec);
		}

		void ToSparse()
		{
			if (!length)
				length = values.size();  //Ϊ�˰�ȫ תsparseʱ��������length 
			Vec vec;
			for (size_t i = 0; i < values.size(); i++)
			{
				if (values[i] != _zeroValue)
				{
					indices.push_back(i);
					vec.push_back(values[i]);
				}
			}
			values.swap(vec);
		}

		void MakeDense()
		{
			if (IsSparse())
			{
				ToDense();
			}
		}

		void MakeSparse()
		{
			if (IsDense())
			{
				ToSparse();
			}
		}

		void Add(ValueType value)
		{
			values.push_back(value);
		}

		void Add(int index, ValueType value)
		{
			if (value != _zeroValue)
			{
				indices.push_back(index);
				values.push_back(value);
			}
		}

		void PrepareDense()
		{
			values.reserve(length);
		}

		void Sparsify(Float maxSparsity)
		{
			if (!IsDense() || keepDense)
				return;

			int nonZeroNum = GetNumNonZeros();
			//@TODO �������ȫ��0�����
			if (nonZeroNum < (uint64)(length * maxSparsity))
			{
				ToSparse();
			}
		}


		void Sparsify()
		{
			Sparsify(sparsityRatio);
		}

		void Densify(Float maxSparsity)
		{
			if (length > 0 && (keepDense || Count() >= (uint64)(length * maxSparsity)))
			{
				ToDense();
			}
		}

		void Densify()
		{
			Densify(sparsityRatio);
		}

		ValueType operator[](int i) const
		{
			if (i < 0 || i >= length)
				return _zeroValue;
			//THROW((format("Index %d out of range in Vector of length %d") % i % length).str());

			if (IsDense())
			{
				return values[i];
			}
			else
			{
				auto iter = std::lower_bound(indices.begin(), indices.end(), i);
				if (iter == indices.end() || *iter != i)
				{
					return _zeroValue;
				}
				return values[iter - indices.begin()];
			}
		}

		ValueType& operator[](int i)
		{
			/*if (i < 0 || i >= length)
				return _value;*/
			//THROW((format("Index %d out of range in Vector of length %d") % i % length).str());
			if (IsDense())
			{//�ⲿȷ����Խ�磡
				return values[i];
			}
			else
			{
				auto iter = std::lower_bound(indices.begin(), indices.end(), i);
				//hack
				if (iter == indices.end() || *iter != i)
				{
					return _zeroValue;
					//THROW((format("In sparse vector could not find the index %d") % i).str());
				}
				return values[iter - indices.begin()];
			}
		}

		Vector& operator()(int index, ValueType value)
		{
			Add(index, value);
		}

		/// Applies the given ValueVisitor to every element of the vector, in order of index.  (Zeros of sparse vectors will not be included.)
		template<typename ValueVistor>
		void ForEach(ValueVistor visitor) const
		{
			if (IsDense())
			{
				for (size_t i = 0; i < values.size(); i++)
				{
					visitor(i, values[i]);
				}
			}
			else
			{
				for (size_t i = 0; i < values.size(); i++)
				{
					visitor(indices[i], values[i]);
				}
			}
		}

		template<typename ValueVistor>
		void ForEachAll(ValueVistor visitor) const
		{
			if (IsDense())
			{
				for (size_t i = 0; i < values.size(); i++)
				{
					visitor(i, values[i]);
				}
			}
			else
			{
				size_t j = 0;
				for (size_t i = 0; i < values.size(); i++)
				{
					while (j < indices[i])
					{
						visitor(j++, _zeroValue);
					}
					visitor(j++, values[i]);
				}
				while (j < length)
				{
					visitor(j++, _zeroValue);
				}
			}
		}

		template<typename ValueVistor>
		bool ForEachAllIf(ValueVistor visitor) const
		{
			if (IsDense())
			{
				for (size_t i = 0; i < values.size(); i++)
				{
					if (!visitor(i, values[i]))
						return false;
				}
			}
			else
			{
				size_t j = 0;
				for (size_t i = 0; i < values.size(); i++)
				{
					while (j < indices[i])
					{
						if (!visitor(j++, _zeroValue))
							return false;
					}
					if (!visitor(j++, values[i]))
						return false;
				}
				while (j < length)
				{
					if (!visitor(j++, _zeroValue))
						return false;
				}
			}
			return true;
		}

		//@TODO  ����߼���Щ���� Ӧ���Ǳ�������Length �����ǽ�ֹ��values.size()
		template<typename ValueVistor>
		void ForEachAllSparse(ValueVistor visitor) const
		{
			size_t j = 0;
			for (size_t i = 0; i < values.size(); i++)
			{
				while (j < indices[i])
				{
					visitor(j++, _zeroValue);
				}
				visitor(j++, values[i]);
			}
			while (j < length)
			{
				visitor(j++, _zeroValue);
			}
		}

		template<typename ValueVistor>
		bool ForEachAllSparseIf(ValueVistor visitor) const
		{
			size_t j = 0;
			for (size_t i = 0; i < values.size(); i++)
			{
				while (j < indices[i])
				{
					if (!visitor(j++, _zeroValue))
						return false;
				}
				if (!visitor(j++, values[i]))
					return false;
			}
			while (j < length)
			{
				if (!visitor(j++, _zeroValue))
					return false;
			}
			return true;
		}


		template<typename ValueVistor>
		void ForEach(ValueVistor visitor)
		{
			if (IsDense())
			{
				for (size_t i = 0; i < values.size(); i++)
				{
					visitor(i, ref(values[i]));
				}
			}
			else
			{
				for (size_t i = 0; i < values.size(); i++)
				{
					visitor(indices[i], ref(values[i]));
				}
			}
		}

		template<typename ValueVistor>
		void ForEachDense(ValueVistor visitor) const
		{
			for (size_t i = 0; i < values.size(); i++)
			{
				visitor(i, values[i]);
			}
		}

		template<typename ValueVistor>
		bool ForEachDenseIf(ValueVistor visitor) const
		{
			for (size_t i = 0; i < values.size(); i++)
			{
				if (!visitor(i, values[i]))
					return false;
			}
			return true;
		}

		template<typename ValueVistor>
		void ForEachDense(ValueVistor visitor)
		{
			for (size_t i = 0; i < values.size(); i++)
			{
				visitor(i, ref(values[i]));
			}
		}

		template<typename ValueVistor>
		void ForEachSparse(ValueVistor visitor) const
		{
			for (size_t i = 0; i < values.size(); i++)
			{
				visitor(indices[i], values[i]);
			}
		}

		template<typename ValueVistor>
		bool ForEachSparseIf(ValueVistor visitor) const
		{
			for (size_t i = 0; i < values.size(); i++)
			{
				if (!visitor(indices[i], values[i]))
					return false;
			}
			return true;
		}

		template<typename ValueVistor>
		void ForEachSparse(ValueVistor visitor)
		{
			for (size_t i = 0; i < values.size(); i++)
			{
				visitor(indices[i], ref(values[i]));
			}
		}

		//ע���Լ���֤ϡ���ʽvalue����0 һ������print ֻ�� ��ok
		template<typename ValueVistor>
		void ForEachNonZero(ValueVistor visitor) const
		{
			if (IsDense())
			{
				for (size_t i = 0; i < values.size(); i++)
				{
					if (values[i] != _zeroValue)
					{
						visitor(i, values[i]);
					}
				}
			}
			else
			{
				for (size_t i = 0; i < values.size(); i++)
				{
					visitor(indices[i], values[i]);
				}
			}
		}

		template<typename ValueVistor>
		void ForEachNonZero(ValueVistor visitor)
		{
			if (IsDense())
			{
				for (size_t i = 0; i < values.size(); i++)
				{
					if (values[i] != _zeroValue)
					{
						visitor(i, ref(values[i]));
					}
				}
			}
			else
			{
				for (size_t i = 0; i < values.size(); i++)
				{
					visitor(indices[i], ref(values[i]));
				}
			}
		}

	public:
		//ע���TLC������ Ĭ��һ���յ�Vector��Sparse�� Ҳ���Ǳ�ʾ��������ֵ����0�����
		//ע����Ҫ��֤�����sparse indices��valuesʼ�ճ�����ͬ Count() == 0 һ����Sparse
		bool IsDense() const
		{
			return indices.size() != values.size();
		}

		bool IsSparse() const
		{
			return indices.size() == values.size();
		}

		//@TODO  ��������length ��ʹ��Length() ���ﲻһ����Щ�״� ��ҪΪ�˷��� FeatureVecor desne ����add 
		//�����������length �Զ�����values.size(),������ϡ��length�����Ǳ���Ҫ����
		/// Gets a int value representing the dimensionality of the vector.
		int Length() const
		{
			if (length)  
				return length;
			if (indices.empty()) //dense
			{
				return values.size();
			}
			//sparse no lenth return 0 empty
			return length;
		}

		//Сд��ͷ����Ϊ�˼���stl
		int size() const
		{
			return Length();
		}

		void SetLength(int length_)
		{
			length = length_;
		}

		bool Empty() const
		{
			return length == 0;
		}

		bool empty() const
		{
			return length == 0;
		}

		/// Gets the number of explicitly represented values in the vector.
		int Count() const
		{
			return values.size();
		}

		//ע��ֻ�����ڳ�ʼ���ú� ��������޸�Vector���� �������NumNonZerors�������
		int NumNonZeros()
		{
			if (IsSparse())
			{
				return indices.size();
			}
			else if (numNonZeros >= 0)
			{
				return numNonZeros;
			}
			else
			{
				return GetNumNonZeros();
			}
		}

		const ivec& Indices() const
		{
			return indices;
		}

		const Vec& Values() const
		{
			return values;
		}

		ivec& Indices()
		{
			return indices;
		}

		Vec& Values()
		{
			return values;
		}

		int Index(int index) const
		{
			return indices[index];
		}

		int Index(int index)
		{
			return indices[index];
		}

		ValueType Value(int index) const
		{
			return values[index];
		}

		//@FIXME why fail boost.python
#ifndef GCCXML
		ValueType& Value(int index)
		{
			return values[index];
		}
		//#else 
		//		double& Value(int index) //���û���⵫��python���� ������ ���� fe.Value(3) = 4
		//		{
		//			return values[index];
		//		}
#endif

		void Clear()
		{
			length = 0;
			indices.clear();
			values.clear();
		}

		void CheckInvariants()
		{
			if (IsDense())
			{
				CHECK_EQ(values.size(), length);
			}
			else
			{
				CHECK_EQ(values.size(), indices.size());
				//@TODO �������indice���ں���Χ�� ����
			}
		}

		string Str(string sep = ",")
		{
			stringstream ss;
			ForEachNonZero([&](int index, ValueType value) {
				ss << index << ":" << value << sep;
			});
			return ss.str();
		}

		string DenseStr(string sep = ",")
		{
			stringstream ss;
			ForEachAll([&](int index, ValueType value) {
				ss << index << ":" << value << sep;
			});
			return ss.str();
		}

		string str(string sep = ",")
		{
			stringstream ss;
			ForEachNonZero([&](int index, ValueType value) {
				ss << index << ":" << value << sep;
			});
			return ss.str();
		}

		const ValueType ZeroValue() const
		{
			return _zeroValue;
		}

		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive &ar, const unsigned int version)
		{
			ar & indices;
			ar & values;
			ar & length;
			ar & sparsityRatio;
			ar & keepDense;
			ar & keepSparse;
			ar & normalized;
			ar & numNonZeros;
			ar & _zeroValue;
		}
	private:
		//��ȡdense��ʽ��ʾ�ṹ�еķ�0��Ŀ
		int GetNumNonZeros()
		{
			int nonZeroNum = 0;
			for (auto item : values)
			{
				if (item != 0)
				{
					nonZeroNum++;
				}
			}
			numNonZeros = nonZeroNum; //save non zero num
			return numNonZeros;
		}
	public:
		//@TODO ��û�б�Ҫд��shared_ptr<ivec> indices; //������� ��������Vector��ͬindice ��ͬvalue ���⿽��
		ivec indices; //��ʹ��Node(index,value)������� ͬʱ��������һ��Ϊ��
		Vec values; //@TODO may be VecPtr ���߼�һ��ָ�� �޸Ĵ��� ���ָ�벻�ǿ� ʹ��ָ��ָ���
		//non_zero count < ratio to sparse, non_zero count >= ratio to dense
		Float sparsityRatio = 0.3; //the same as fastrank
		bool keepDense = false;
		bool keepSparse = false;
		bool normalized = false;
		int numNonZeros = -1; //-1 means unknow
	private:
		int length = 0;
		ValueType _zeroValue = 0;
	};

	typedef TVector<int> IntArray;

	class PyIntArray : public IntArray
	{

	};
}  //----end of namespace gezi

#endif  //----end of NUMERIC__VECTOR__FVECTOR_H_
