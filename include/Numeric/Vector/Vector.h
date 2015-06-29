/**
 *  ==============================================================================
 *
 *          \file   Numeric/Vector/Vector.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-03-26 10:46:03.965585
 *
 *  \Description:  �����ĺ��ı�ʾ
 *								 ֧�ֶ�д��dense and sparse
 ��������֧��binary ����valueΪ�ձ�ʾbinary @TODO
 *   @TODO �Ƿ���Ҫ int length , index ��Ϊint64
 *   @TODO Ҳ�����ṩ�ػ������� DenseVector, SparseVector�����������岻��̫��
 *  ==============================================================================
 */

#ifndef NUMERIC__VECTOR__VECTOR_H_
#define NUMERIC__VECTOR__VECTOR_H_
#include "common_util.h"
#include "serialize_util.h"
namespace gezi {

	//@TODO generic for Vector or IntArray
	//@TODO dotר��һ�������ļ���
	template<typename Vector_, typename Vector2_>
	inline Float dot(const Vector_& a, const Vector2_& b)
	{
		if (!a.Count() || !b.Count())
		{
			return 0;
		}

		//@TODO generalized_same ok &a = & b?
		if (generalized_same(a.indices, b.indices))
		{ //ͬһ��Vector�������߶���Dense(indices�ǿյ�)
			/*if (a.Length() != b.Length())
			{
			THROW("Vectors must have the same dimensionality.");
			}*/
			Float res = 0;
			size_t end = std::min(a.values.size(), b.values.size());
			for (size_t i = 0; i < end; i++)
			{
				res += a.Value(i) * b.Value(i);
			}
			return res;
		}

		Float result = 0;

		//ע��TLC�� ����Ϊ�յ�indices,values�������⴦��  Ϊ�˰�ȫ ������������� ����ٶ���Ҫ���Բ���� 
		//Ŀǰ������������ֻ������train-testģʽlibsvm��ʽ��ͬ�ļ���ȡ��ɵ�featureNum��ͬ
		if (b.IsDense())
		{
			//if (a.length > 0 && a.length <= b.values.size()) //this is safe if you set correct length
			//{
			//	for (size_t i = 0; i < a.indices.size(); i++)
			//	{
			//		result += a.values[i] * b.values[a.indices[i]];
			//	}
			//}
			//else
			{
				int64 i = a.indices.size() - 1; //@TODO��int ok ?
				while (i >= 0 && a.indices[i] >= b.values.size())
					i--;
				for (; i >= 0; i--)
				{
					result += a.Value(i) * b.Value(a.indices[i]);
				}
			}
		}
		else if (a.IsDense())
		{
			//if (b.length > 0 && b.Length() <= a.values.size())
			//{
			//	for (size_t i = 0; i < b.indices.size(); i++)
			//	{
			//		result += a.values[b.indices[i]] * b.values[i];
			//	}
			//}
			//else
			{
				int64 i = b.indices.size() - 1; //@TODO��int ok ?
				while (i >= 0 && b.indices[i] >= a.values.size()) //ֻ��libsvm��ʽ��ʱ��train test��󳤶���Ϣ���ܲ�һ�� Ϊ�˰�ȫ,�����������Ҫ
					i--;
				for (; i >= 0; i--)
				{
					result += a.Value(b.indices[i]) * b.Value(i);
				}
			}
		}
		else
		{ // both sparse
			size_t aI = 0, bI = 0;
			while (aI < a.indices.size() && bI < b.indices.size())
			{
				switch (compare(a.indices[aI], b.indices[bI]))
				{
				case 0:
					PVAL2(a.indices[aI], result);
					result += a.Value(aI++) * b.Value(bI++);
					break;
				case -1:
					aI++;
					break;
				case 1:
					bI++;
					break;
				default:
					break;
				}
			}
		}
		return result;
	}

	template<typename Vector_, typename Vector2_>
	inline Float cos(const Vector_& a, const Vector2_& b)
	{
		return dot(a, b) / (sqrt(a.SquaredNorm()) * sqrt(b.SquaredNorm()));
	}

	template<typename Vector_, typename Vector2_>
	inline Float cos(const Vector_& a, const Vector2_& b, Float l2norm1, Float l2norm2)
	{
		return dot(a, b) / (l2norm1 * l2norm2);
	}

	//@TODO ͳһʹ��TVector<Float>���
	class Vector
	{
	public:
		Vector() = default; //sparse����ʱ�������length
		virtual ~Vector() {}
		Vector(Vector&&) = default;
		Vector& operator = (Vector&&) = default;
		Vector(const Vector&) = default;
		Vector& operator = (const Vector&) = default;

		typedef int index_type;  //@TODO �޸����п��ܵ�int ��index_type
		typedef Float value_type;
		typedef size_t size_type;
		typedef int  difference_type;
		typedef vector<value_type>::iterator iterator;
		typedef vector<value_type>::const_iterator const_iterator;

		//��Ҫ�ⲿע��� ��ʼ����length ��ô�����Add(value) dense��ʽ Ҫ��֤values��󳤶�
		//�ͳ�ʼ���õ�һ�� ��ҪAdd���� ��Ϊʵ��Length()������ʾ�������� �����ʵ��Ҫ���sparse
		explicit Vector(int length_)
			: length(length_)
		{
		}

		Vector(value_type value_, int length_)
			: length(length_), _zeroValue(value_)
		{
		}

		Vector(int length_, value_type value_)
		{
			values.resize(length_, value_);
			length = length_;
			indices.clear();
		}

		Vector(const map<int, double>& m)
		{
			AddRange(m);
		}

		void Resize(int length_, value_type value_ = 0)
		{
			values.resize(length_, value_);
			length = length_;
			indices.clear();
		}

		void resize(int length_, value_type value_ = 0)
		{
			Resize(length_, value_);
		}

		Vector(int length_, ivec& indices_, vector<value_type>& values_)
			:length(length_)
		{
			indices.swap(indices_);
			values.swap(values_);
		}

		Vector(ivec& indices_, vector<value_type>& values_, int length_ = 1024000)
			:length(length_)
		{
			indices.swap(indices_);
			values.swap(values_);
		}

		//ע��desne��� ����ֱ��������ַ������� �Ƽ� ���ߵ���Add �ӿڣ�
		//Add�ӿ� �ڲ�����length���� 
		Vector(vector<value_type>& values_)
		{
			ToDense(values_);
		}

		//����debug Vector vec("1\t3\t4\t5"); Vector vec("1:2.3\t3:4.5"); or vec("1 3") space is also ok
		Vector(string input, int startIndex = 0, int length_ = 1024000, string sep = ",\t ")
		{
			Init(input, startIndex, length_, sep);
		}

		Vector(iterator first, iterator end)
			:values(first, end)
		{
		}

#ifndef GCCXML
		Vector(const std::initializer_list<value_type>& il)
			: values(il)
		{

		}
#endif

		void Init(string input, int startIndex = 0, int length_ = 0, string sep = ",\t ")
		{
			boost::trim(input); //��Ҫע�� ��ΪDOUBLE����atof���ٵ��ǲ���ȫ ����������һ���ո� ����������
			//ע��split("",sep)�õ����ǿս�� ������1����Ԫ�ص�vector c# python	Ҳ��		
			svec inputs = from(split(input, sep)) >> where([](string a) { return !a.empty(); }) >> to_vector();
			length = length_;
			if (inputs.size() > 0)
			{ //ע�����ϡ��û�д���length
				if (contains(inputs[0], ':'))
				{ //���û��淽ʽ Ϊ�˸��ӷ��� �������������ź����,����debug���Է��������޸�,������ӵ�(index,value)����ǰ����ͬindex��value
					map<index_type, value_type> m;
					index_type maxIndex = -1;
					for (string part : inputs)
					{
						string index_, val_;
						split(part, ':', index_, val_);
						index_type index = INT(index_) + startIndex;
						if (index > maxIndex)
						{
							maxIndex = index;
						}
						value_type val = DOUBLE(val_);
						m[index] = val;
					}
					if (length < maxIndex + 1)
					{
						length = maxIndex * 2;
					}
					AddRange(m);
				}
				else
				{
					length = inputs.size();
					for (string val_ : inputs)
					{
						Add(DOUBLE(val_));
					}
				}
			}
		}

		void Init(int length_, ivec& indices_, vector<value_type>& values_)
		{
			length = length_;
			indices.swap(indices_);
			values.swap(values_);
		}

		//���ֵ������� ���治�ܹ����� Vector()��ʱ��������������ʱ����ֻ�� const Vector& 
		//������Ҫ&& �������Դ���ʱVector()���� ����תΪ�ڲ�ʹ�õ�
		void Swap(Vector& other)
		{
			length = other.length;
			indices.swap(other.indices);
			values.swap(other.values);
		}

		void Init(vector<value_type>& values_)
		{
			ToDense(values_);
		}

		template<typename Iter>
		void assign(Iter begin, Iter end)
		{
			for (Iter it = begin; it != end; ++it)
			{
				values.push_back(*it);
			}
		}

		iterator begin()
		{
			return values.begin();
		}

		iterator end()
		{
			return values.end();
		}
		value_type front()
		{
			return values.front();
		}
		value_type back()
		{
			return values.back();
		}

		//

		void push_back(value_type item)
		{
			values.push_back(item);
		}

		template<typename Iter>
		void insert(iterator dest, Iter begin, Iter end)
		{
			values.insert(dest, begin, end);
		}

		iterator insert(iterator position, const value_type& val)
		{
			return values.insert(position, val);
		}

		void erase(iterator pos)
		{
			values.erase(pos);
		}

		void erase(iterator first, iterator last)
		{
			values.erase(first, last);
		}

		void ToDense(vector<value_type>& values_)
		{
			values.swap(values_);
			length = values.size();
			indices.clear();
		}

		//ToDesnse��ToSparse�������� ʹ��MakeDesne MakeSparse 
		void ToDense()
		{
			vector<value_type> vec(length, _zeroValue);
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
			vector<value_type> vec;
			for (size_t i = 0; i < values.size(); i++)
			{
				if (values[i] != _zeroValue) //@TODO for double may not work if not 0
				{
					indices.push_back(i);
					vec.push_back(values[i]);
				}
			}
			values.swap(vec);
		}

		void MakeDense()
		{
			if (IsSparse() && !keepSparse)
			{
				ToDense();
			}
		}

		void ForceDense()
		{
			MakeDense();
			keepDense = true;
		}

		void MakeSparse()
		{
			if (IsDense() && !keepDense)
			{
				ToSparse();
			}
		}

		void ForceSparse()
		{
			MakeSparse();
			keepDense = true;
		}


		//@TODO ����ע��python��װ����� l = Vector() l.Add(3.0)��ok�� l.Add(3)����ȥû�� ����ȴʵ�ʲ������á��� Ϊʲôvector��push_backû������ ����ok�� ������Float typedef��ԭ��Ҳ��������Add(Vector v)
		//#ifndef PYTHON_WRAPPER
		void Add(value_type value)
		{
			values.push_back(value);
		}
		//#endif //PYTHON_WRAPPER
		//����ӿ���python����� ���� Add(3, 3.0) ����Add(3,3)����ok�� �����ĸ������bug
		void Add(int index, value_type value)
		{
			if (value != _zeroValue)
			{
				indices.push_back(index);
				values.push_back(value);
			}
		}

		template<typename Range>
		void AddRange(const Range& m)
		{
			for (auto& item : m)
			{
				Add(item.first, item.second);
			}
		}

		template<typename Range>
		void AddMap(const Range& m)
		{
			for (auto& item : m)
			{
				Add(item.first, item.second);
			}
		}

		void AddMap(const map<index_type, value_type>& m)
		{
			for (auto& item : m)
			{
				Add(item.first, item.second);
			}
		}

		void PrepareDense()
		{
			values.reserve(length);
		}

		void Sparsify(value_type maxSparsity)
		{
			if (!IsDense() || keepDense)
				return;

			int nonZeroNum = GetNumNonZeros();
			//@TODO �������ȫ��0�����
			if ((uint64)nonZeroNum < (uint64)(length * maxSparsity))
			{
				ToSparse();
			}
		}


		void Sparsify()
		{
			Sparsify(sparsityRatio);
		}

		void Densify(value_type maxSparsity)
		{
			if (!IsSparse() || keepSparse)
			{
				return;
			}

			if (length > 0 && (keepDense || (uint64)Count() >= (uint64)(length * maxSparsity)))
			{
				ToDense();
			}
		}

		void Densify()
		{
			Densify(sparsityRatio);
		}

		value_type operator[](index_type index) const
		{
			if (index < 0 || index >= length)
				return _zeroValue;
			//THROW((format("Index %d out of range in Vector of length %d") % i % length).str());

			if (IsDense())
			{
				return values[index];
			}
			else
			{
				auto iter = std::lower_bound(indices.begin(), indices.end(), index);
				if (iter == indices.end() || *iter != index)
				{
					return _zeroValue;
				}
				return values[iter - indices.begin()];
			}
		}

		value_type& operator[](index_type index)
		{
			/*if (i < 0 || i >= length)
				return _value;*/
			//THROW((format("Index %d out of range in Vector of length %d") % i % length).str());
			if (IsDense())
			{//�ⲿȷ����Խ�磡
				return values[index];
			}
			else
			{
				auto iter = std::lower_bound(indices.begin(), indices.end(), index);
				//hack
				if (iter == indices.end() || *iter != index)
				{//@FIXME ��Ӧ���ṩ ��const�汾�� zeroValue��Ӧ�ñ��ı� ����
					return _zeroValue;
					//THROW((format("In sparse vector could not find the index %d") % i).str());
				}
				return values[iter - indices.begin()];
			}
		}

		Vector& operator()(int index, value_type value)
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
				{ //@TODO fixme ���ں�С�ĸ������� ò��Ҳ���Զ������ == 0�� ��ɽ����һ�� �ο�FeaturesVector��һ��ʹ��
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
					if (values[i] != _zeroValue) //@TODO use gezi::are_same(values[i], _zeroValue) ?
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

		//@TODO  ��������length ������Length or size
		/// Gets a int value representing the dimensionality of the vector.
		int Length() const
		{
			if (length)
				return length;
			if (indices.empty()) //dense
			{
				return values.size();
			}
			//sparse no length return 0 empty
			return length;
		}

		//Сд��ͷ����Ϊ�˼���stl
		size_t size() const
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

		const vector<value_type>& Values() const
		{
			return values;
		}

		ivec& Indices()
		{
			return indices;
		}

		vector<value_type>& Values()
		{
			return values;
		}

		index_type Index(index_type index) const
		{
			return indices[index];
		}

		//the same as Value() python wrapper problem hack,now will deal at h2interface.py which wil comment as //index_type& Index(index_type index)
		index_type& Index(index_type index)
		{
			return indices[index];
		}
		void SetIndex(index_type index, index_type indexValue)
		{
			indices[index] = indexValue;
		}

		value_type Value(index_type index) const
		{
			//VLOG(0) << "vector value int const";
			return values[index];
		}

		//@FIXME why fail boost.python @TODO UseVec(Vector) ? �����������õ� ���� operator[]��û���� ����GCCXML��û����__setitem__�Ӷ��޷���python��д��������l[2]=3
		//../../../../../../third-64/boost.1.53/include/boost/mpl/assert.hpp:223:13: error: no matching function for call to 'assertion_failed(mpl_::failed************ boost::mpl::or_<boost::is_class<double>, boost::is_union<double>, mpl_::bool_<false>, mpl_::bool_<false>, mpl_::bool_<false> >::************)'
		//GCCXML WARNING: value_type & gezi::Vector::Value(int index) [member function]
		//> warning W1008 : The function returns non - const reference to "Python immutable" type.The value cannot be modified from Python.
		value_type& Value(index_type index)
		{
			//VLOG(0) << "vector value int non const";
			return values[index];
		}

		void SetValue(index_type index, value_type value)
		{
			values[index] = value;
		}

		void Clear()
		{
			length = 0;
			indices.clear();
			values.clear();
		}

		void clear()
		{
			Clear();
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

//#ifndef GCCXML
		//@TODO �ӳټ���ķ�ʽ�� operator + - * /
		Vector& operator *= (value_type d)
		{
			ScaleBy(d);
			return *this;
		}

		Vector& operator /= (value_type d)
		{
			ScaleBy(1.0 / d);
			return *this;
		}


		Vector& operator += (const Vector& other)
		{
			Add(other);
			return *this;
		}

		Vector& operator -= (const Vector& other)
		{
			Subtract(other);
			return *this;
		}
//#endif // GCCXML

		Float dot(const Vector& other) const
		{
			return gezi::dot(*this, other);
		}

		/// Multiples the Vector by a real value
		void ScaleBy(value_type d)
		{
			if (d == 1.0)
				return;

			if (d == 0)
			{
				if (!keepDense)
				{
					values.clear();
					indices.clear();
				}
				else
				{
					for (size_t i = 0; i < values.size(); i++)
						values[i] = 0;
				}
			}
			else
			{
				for (size_t i = 0; i < values.size(); i++)
					values[i] *= d;
			}
		}

		/// Adds the supplied vector to myself.  (this += a) 
		inline void Add(const Vector& other)
		{
			ApplyWith(other, [](value_type& v1, value_type v2) { v1 += v2; });
		}

		inline void Subtract(const Vector& other)
		{
			ApplyWith(other, [](value_type& v1, value_type v2) { v1 -= v2; });
		}


		/// Applies the ParallelManipulator to each corresponding pair of elements where the argument is non-zero, in order of index.
		template<typename ParallelManipulator>
		void ApplyWith(const Vector& a, ParallelManipulator manip)
		{
			/*if (a.length != length)
			{
			THROW("Vectors must have the same dimensionality.");
			}*/

			if (a.Count() == 0)
				return;

			if (a.IsDense())
			{
				if (IsDense())
				{ // both dense
					for (size_t i = 0; i < values.size(); i++)
					{
						manip(ref(values[i]), a.Value(i)); //ref������ҪΪ�˿ɶ��� ����manip����ʹ��ֵ���ʹ���
					}
				}
				else
				{  // this sparse, a not sparse
					vector<value_type> newValues(length);
					int myI = 0;
					for (size_t i = 0; i < newValues.size(); i++)
					{
						if (myI < Count() && indices[myI] == i)
						{
							newValues[i] = values[myI++];
						} // else, newValues[i] is already zero
						manip(ref(newValues[i]), a.Value(i));
					}

					indices.clear();
					values.swap(newValues);
				}
				Sparsify();
			}
			else if (IsDense())
			{ // a sparse, this not sparse
				for (size_t i = 0; i < a.indices.size(); i++)
				{
					manip(ref(values[a.indices[i]]), a.Value(i));
				}
			}
			else if (&a.indices == &indices)
			{ // both sparse, same indices
				for (size_t i = 0; i < values.size(); i++)
				{
					manip(ref(values[i]), a.Value(i));
				}
			}
			else if (Count() == 0)
			{
				values.resize(a.Count(), 0);
				//indices.swap(a.indices);
				//�������� ����б�Ҫ ���Կ���indices��shared ptr ��������indicesһ��Ƚ�С��
				//����������������
				indices = a.indices;
				for (size_t i = 0; i < values.size(); i++)
				{
					manip(ref(values[i]), a.Value(i));
				}
			}
			else
			{ // both sparse
				vector<index_type> newIndices;
				vector<value_type> newValues;
				size_t myI = 0, aI = 0;
				for (; myI < indices.size() && aI < a.indices.size();)
				{
					if (indices[myI] == a.indices[aI])
					{
						value_type val = values[myI];
						manip(ref(val), a.Value(aI));
						if (val != 0)
						{
							newIndices.push_back(indices[myI]);
							newValues.push_back(val);
						}
						myI++;
						aI++;
					}
					else if (indices[myI] < a.indices[aI])
					{
						value_type val = values[myI];
						manip(ref(val), 0);
						if (val != 0)
						{
							newIndices.push_back(indices[myI]);
							newValues.push_back(val);
						}
						myI++;
					}
					else
					{
						value_type val = 0;
						manip(ref(val), a.Value(aI));
						if (val != 0)
						{
							newIndices.push_back(a.indices[aI]);
							newValues.push_back(val);
						}
						aI++;
					}
				}

				for (; myI < indices.size(); myI++)
				{
					value_type val = values[myI];
					manip(ref(val), 0);
					if (val != 0)
					{
						newIndices.push_back(indices[myI]);
						newValues.push_back(values[myI]);
					}
				}

				for (; aI < a.indices.size(); aI++)
				{
					value_type val = 0;
					manip(ref(val), a.Value(aI));
					if (val != 0)
					{
						newIndices.push_back(indices[aI]);
						newValues.push_back(values[aI]);
					}
				}

				indices.swap(newIndices);
				values.swap(newValues);
				Densify();

				//---TLC������ ����һ�α�����ȷ��indice���� ���ٺÿռ�,���ж��Ƿ�����ͬ��indices�ȵ�
				//size_t myI = 0;
				//size_t newLength = indices.size();
				//// try to find each a index in my indices, counting how many more we'll add
				//for (size_t aI = 0; aI < a.indices.size(); aI++)
				//{
				//	int aIndex = a.indices[aI];
				//	while (myI < indices.size() && indices[myI] < aIndex)
				//	{
				//		myI++;
				//	}
				//	if (myI == indices.size())
				//	{
				//		newLength += a.indices.size() - aI;
				//		break;
				//	}
				//	else if (indices[myI] == aIndex)
				//	{
				//		myI++;
				//	}
				//	else
				//	{
				//		newLength++;
				//	}
				//}

				//myI = 0;

				//if (newLength == indices.size())
				//{
				//	if (newLength == a.indices.size())
				//	{ // we actually have the same indices!
				//		for (size_t i = 0; i < values.size(); i++)
				//		{
				//			manip(ref(values[i]), a.Value(i));
				//		}
				//	}
				//	else
				//	{
				//		for (size_t aI = 0; aI < a.indices.size(); aI++)
				//		{
				//			int aIndex = a.indices[aI];
				//			while (indices[myI] < aIndex)
				//				myI++;
				//			manip(ref(values[myI++]), a.Value(aI));
				//		}
				//	}
				//}
				//else if (newLength == a.indices.size())
				//{
				//	vector<value_type> newVals(newLength, 0);

				//	for (int aI = 0; aI < a.indices.size(); aI++)
				//	{
				//		int aIndex = a.indices[aI];
				//		if (myI < indices.size() && indices[myI] == aIndex)
				//		{
				//			newVals[aI] = values[myI++];
				//		}

				//		manip(ref(newVals[aI]), a.Value(aI));
				//	}

				//	//indices.swap(a.indices);
				//	indices = a.indices;
				//	values.swap(newVals);
				//}
				//else
				//{
				//	ivec newIndices(newLength, 0);
				//	vector<value_type> newVals(newLength, 0);

				//	int newI = 0;
				//	for (size_t aI = 0; aI < a.indices.size(); aI++)
				//	{
				//		int aIndex = a.indices[aI];
				//		while (myI < indices.size() && indices[myI] < aIndex)
				//		{
				//			newVals[newI] = values[myI];
				//			newIndices[newI] = indices[myI];
				//			myI++;
				//			newI++;
				//		}
				//		if (myI == indices.size())
				//		{
				//			while (aI < a.indices.size())
				//			{
				//				newIndices[newI] = a.indices[aI];
				//				manip(ref(newVals[newI]), a.Value(aI));
				//				aI++;
				//				newI++;
				//			}
				//			break;
				//		}

				//		value_type myVal = 0;
				//		if (indices[myI] == aIndex)
				//		{
				//			myVal = values[myI++];
				//		}

				//		manip(ref(myVal), a.Value(aI));
				//		newVals[newI] = myVal;
				//		newIndices[newI] = aIndex;
				//		newI++;
				//	}

				//	while (myI < indices.size())
				//	{
				//		newVals[newI] = values[myI];
				//		newIndices[newI] = indices[myI];
				//		myI++;
				//		newI++;
				//	}

				//	indices.swap(newIndices);
				//	values.swap(newVals);

				//	Densify();
				//}
			}
		}

		//l2norm @TODO�����Ż� WeightVector�ػ�
		value_type Norm() const
		{
			return sqrt(std::accumulate(values.begin(), values.end(), 0.0, sd_op()));
		}

		value_type SquaredNorm() const
		{
			return std::accumulate(values.begin(), values.end(), 0.0, sd_op());
		}

		string Str(string sep = ",") const
		{
			stringstream ss;
			ForEachNonZero([&](int index, value_type value) {
				ss << index << ":" << value << sep;
			});
			return ss.str().substr(0, ss.str().length() - sep.length());
		}

		string AllStr(string sep = ",") const
		{
			stringstream ss;
			ForEachAll([&](int index, value_type value) {
				ss << index << ":" << value << sep;
			});
			//return ss.str();
			return ss.str().substr(0, ss.str().length() - sep.length());
		}

		string DenseStr(string sep = ",") const
		{
			stringstream ss;
			ForEachAll([&](int index, value_type value) {
				ss << value << sep;
			});
			//return ss.str();
			return ss.str().substr(0, ss.str().length() - sep.length());
		}

		string str(string sep = ",") const
		{
			stringstream ss;
			ForEachNonZero([&](int index, value_type value) {
				ss << index << ":" << value << sep;
			});
			//return ss.str();
			return ss.str().substr(0, ss.str().length() - sep.length());
		}

		//friend value_type dot(const Vector& l, const Vector& r);

		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive &ar, const unsigned int version)
		{
			/*ar & indices;
			ar & values;
			ar & length;
			ar & sparsityRatio;
			ar & keepDense;
			ar & keepSparse;
			ar & normalized;
			ar & numNonZeros;
			ar & _zeroValue;*/

			ar & BOOST_SERIALIZATION_NVP(indices);
			ar & BOOST_SERIALIZATION_NVP(values);
			ar & BOOST_SERIALIZATION_NVP(length);
			ar & BOOST_SERIALIZATION_NVP(sparsityRatio);
			ar & BOOST_SERIALIZATION_NVP(keepDense);
			ar & BOOST_SERIALIZATION_NVP(keepSparse);
			ar & BOOST_SERIALIZATION_NVP(normalized);
			ar & BOOST_SERIALIZATION_NVP(numNonZeros);
			ar & BOOST_SERIALIZATION_NVP(_zeroValue);
		}
	private:
		//��ȡdense��ʽ��ʾ�ṹ�еķ�0��Ŀ
		int GetNumNonZeros()
		{
			int nonZeroNum = 0;
			for (auto item : values)
			{
				if (item != _zeroValue) //@TODO��may be are_same(item, _zeroValue)
				{
					nonZeroNum++;
				}
			}
#pragma omp critical 
			numNonZeros = nonZeroNum; //save non zero num
			return numNonZeros;
		}
	public:
		//@TODO ��û�б�Ҫд��shared_ptr<ivec> indices; //������� ��������Vector��ͬindice ��ͬvalue ���⿽��
		//shared_ptr<vector<index_type>> _indices; index_type* indices; ���������л��鷳Щ
		vector<index_type> indices; //��ʹ��Node(index,value)������� ͬʱ��������һ��Ϊ��
		vector<value_type> values; //@TODO may be vector<value_type>Ptr ���߼�һ��ָ�� �޸Ĵ��� ���ָ�벻�ǿ� ʹ��ָ��ָ���
		//non_zero count < ratio to sparse, non_zero count >= ratio to dense
		value_type sparsityRatio = 0.25;
		bool keepDense = false;
		bool keepSparse = false;
		bool normalized = false;
		int numNonZeros = -1; //-1 means unknow
	protected:
		int length = 0;
		value_type _zeroValue = 0.0;
	};

	typedef shared_ptr<Vector> VectorPtr;

	//��Ҫ��ϡ����󹹽�ͨ������map����(��֤key�����)
	template<typename Map>
	void add(Vector& fe, const Map& m)
	{
		for (auto& item : m)
		{
			fe.Add(item.first, item.second);
		}
	}


	//template<typename Vector_>
	//inline Float dot(const Vector_& a, const Vector_& b)
	//{
	//	return dot<Vector_, Vector_>(a, b);
	//}

	//@FIXME /home/users/chenghuige/rsc/myspace/sep/chenghuige/melt-train/test/../../../../../app/search/sep/anti-spam/melt/include/Predictors/LinearPredictor.h:122: undefined reference to `gezi::dot(gezi::Vector const&, gezi::Vector const&)'

	//inline Float dot(const Vector& a, const Vector& b)
	//{
	//	return dot<Vector, Vector>(a, b);
	//}

#ifndef GCCXML
	inline Vector operator+(const Vector& l, const Vector& r)
	{
		Vector vec(l);
		vec += r;
		return vec;
	}
#endif
}  //----end of namespace gezi

#endif  //----end of NUMERIC__VECTOR__VECTOR_H_
