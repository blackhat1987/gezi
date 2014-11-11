/**
 *  ==============================================================================
 *
 *          \file   Numeric/Vector/WeightVector.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-11-09 21:19:07.361690
 *
 *  \Description:  @TODO��һ��gbdt��ʵ��������û�еط���������WeightVectorȡ��Vector���٣�
 *  ==============================================================================
 */

#ifndef NUMERIC__VECTOR__WEIGHT_VECTOR_H_
#define NUMERIC__VECTOR__WEIGHT_VECTOR_H_

#include "Vector.h"

namespace gezi {
	//�����sofia-ml, WeightVectorĬ���ǳ��õ�Dense,ϡ��ʹ��SparseWeightVector
	class WeightVector : public Vector
	{
	public:
		using Vector::Vector;
		WeightVector() = default; //sparse����ʱ�������length
		virtual ~WeightVector() {}


		WeightVector(int length_)
		{
			SetLength(length_);
		}

		WeightVector(int length_, value_type val)
		{
			Init(length_, val);
		}

		void SetLength(int length_)
		{
			length = length_;
			values.resize(length_, _zeroValue);
			keepDense = true;
		}

		using Vector::Init;
		void Init(int length_, value_type val)
		{
			length = length_;
			values.resize(length_, val);
			keepDense = true;
		}

		void Resize(int length_, value_type value_ = 0)
		{
			values.resize(length_, value_);
			length = length_;
			indices.clear();
			keepDense = true;
		}

		/// Multiples the Vector by a real value
		void ScaleBy(value_type d)
		{
			_scale *= d;

			// Take care of any numerical difficulties.
			if (_scale < 0.00000000001)
			{
				//LOG(WARNING) << "scale_to_one";
				ScaleToOne();
			}
		}

		void ScaleToOne()
		{
			for (size_t i = 0; i < values.size(); i++)
			{
				values[i] *= _scale;
			}
			_scale = 1.0;
		}


		//@FIXME values[index] why wrong?
		value_type operator[](index_type index) const
		{
			return values[index] * _scale;
		}

		value_type& operator[](index_type index)
		{
			return values[index];
		}

		value_type Value(int index) const
		{
			//Pval3(_scale, values[index], values[index] * _scale);
			static int count = 0;
			count++;
			if (count % 100 == 0)
			{
				Pval(count);
			}
			return values[index] * _scale;
		}

		////using Vector::Value; //�����Ӱ�쵽�����dot ����Value Ҳ��ʹ��Vector::value
		////���Ϊ�˺�����ʹ�� ��ʱduplicate,���ǻ���ͬ�������Ƚ�Σ�� ����������ڷ�const�ı������� deleted 
		////���ʹ��using ��ò��û�취ָ��ֻusing��const�汾 @TODO
		////�������������� ҲҪע�� û�е�ʱ�� dot���� ���Բ����ó�const ��Ϊ�������const�汾��Value,�������������� dot����const�������ȵ��������
		////��ȻΪ�˰�ȫҲ���Բ��ṩ����� ǿ�ȷ�const�汾 ֱ��ʹ��values[index]
		//value_type& Value(int index)
		//{
		//	return values[index];
		//}

		//@WARNING ��������������Vector�����ΪVector ��һ���Ƿ�Ӱ�������
		/// Adds the supplied vector to myself.  (this += a) //@TODO check if can use const Vector&
		void Add(const Vector& a)
		{
			if (a.IsSparse())
			{
				for (int i = 0; i < a.indices.size(); i++)
				{
					values[a.indices[i]] += a.values[i] / _scale;
				}

			}
			else
			{
				for (size_t i = 0; i < values.size(); i++)
					values[i] += a.values[i] / _scale;
			}
		}

		void AddSparse(const Vector& a)
		{
			for (int i = 0; i < a.indices.size(); i++)
			{
				values[a.indices[i]] += a.values[i] / _scale;
			}
		}

		//a������*scale,�ٶ�������Vector a��ϡ���,���ı������a
		void AddScale(const Vector& a, value_type scale)
		{
			if (a.IsSparse())
			{
				for (int i = 0; i < a.indices.size(); i++)
				{
					values[a.indices[i]] += a.values[i] * scale / _scale;
				}

			}
			else
			{
				for (size_t i = 0; i < values.size(); i++)
					values[i] += a.values[i] * scale / _scale;
			}
		}

		//�Ὣ����仯 
		Vector ToVector()
		{
			if (_scale != 1.0)
			{
				ScaleToOne();
			}
			return (Vector)*this;
		}


		//ע������dotĬ�Ϻ�����ϡ�� ��ʵ�� dotSparse,����ע��������Ӵ�������Vector::Value Ϊʲô�� @FIXME @TODO
		Float dot(const Vector& other) const
		{
			static size_t count1 = 0, count2 = 0;
			//using WeightVector::Value; // error: 'gezi::WeightVector' is not a namespace
			//using ::Value;
			Float result = 0.0;
			if (other.IsSparse())
			{
				for (size_t i = 0; i < other.indices.size(); i++)
				{
					result += values[other.indices[i]] * other.values[i];
				}
			}
			else
			{
				for (size_t i = 0; i < length; i++)
				{
					result += values[i] * other.values[i];
				}
			}
			return result * _scale;
		}

	protected:
		Float _scale = 1.0;
		Float _sqaredNorm = 0.0;
	};


	//��ǰ�ٶ�����Ŀ�궼��sparse��ʾ,δ���ԣ���ʱδʹ��
	class SparseWeightVector : public WeightVector
	{
	public:
		using WeightVector::WeightVector;


		void Add(Vector& a)
		{
			WeightApplyWith(a, [this](int ind, const value_type v1, value_type& v2) { v2 += v1 / _scale; });
		}

		//��ΪĿǰû�����麯�� @TODO duplicate
		void Add(SparseWeightVector& a)
		{
			WeightApplyWith(a, [this](int ind, const value_type v1, value_type& v2) { v2 += v1 / _scale; });
		}

		//a�����ݲ��ٱ�֤
		void AddScale(Vector& a, value_type scale)
		{
			WeightApplyWith(a, [this, &scale](int ind, const value_type v1, value_type& v2) { v2 += v1 * scale / _scale; });
		}

		//a�����ݲ��ٱ�֤
		void AddScale(SparseWeightVector& a, value_type scale)
		{
			WeightApplyWith(a, [this, &scale](int ind, const value_type v1, value_type& v2) { v2 += v1 * scale / _scale; });
		}


		//@TODO  �޸�ApplyWith ����
		template<typename Vector_, typename ParallelManipulator>
		void WeightApplyWith(Vector_& a, ParallelManipulator manip)
		{
			if (a.Count() == 0)
				return;

			if (&a.indices == &indices)
			{ // both sparse, same indices
				for (size_t i = 0; i < values.size(); i++)
				{
					manip(indices[i], a.Value(i), ref(values[i]));
				}
			}
			else if (Count() == 0)
			{
				values.resize(a.Count(), 0);
				indices.swap(a.indices);
				for (size_t i = 0; i < values.size(); i++)
				{
					manip(indices[i], a.Value(i), ref(values[i]));
				}
			}
			else
			{ // both sparse
				size_t myI = 0;

				size_t newLength = indices.size();
				// try to find each a index in my indices, counting how many more we'll add
				for (size_t aI = 0; aI < a.indices.size(); aI++)
				{
					int aIndex = a.indices[aI];
					while (myI < indices.size() && indices[myI] < aIndex)
					{
						myI++;
					}
					if (myI == indices.size())
					{
						newLength += a.indices.size() - aI;
						break;
					}
					else if (indices[myI] == aIndex)
					{
						myI++;
					}
					else
					{
						newLength++;
					}
				}

				myI = 0;

				if (newLength == indices.size())
				{
					if (newLength == a.indices.size())
					{
						for (size_t i = 0; i < values.size(); i++)
						{
							manip(indices[i], a.Value(i), ref(values[i]));
						}
						//a.indices = indices;
					}
					else
					{
						for (size_t aI = 0; aI < a.indices.size(); aI++)
						{
							int aIndex = a.indices[aI];
							while (indices[myI] < aIndex)
								myI++;
							manip(aIndex, a.Value(aI), ref(values[myI++]));
						}
					}
				}
				else if (newLength == a.indices.size())
				{
					vector<value_type> newVals(newLength, 0);

					for (int aI = 0; aI < a.indices.size(); aI++)
					{
						int aIndex = a.indices[aI];
						if (myI < indices.size() && indices[myI] == aIndex)
						{
							newVals[aI] = values[myI++];
						}

						manip(aIndex, a.Value(aI), ref(newVals[aI]));
					}

					indices.swap(a.indices);
					values.swap(newVals);
				}
				else
				{
					ivec newIndices(newLength, 0);
					vector<value_type> newVals(newLength, 0);

					int newI = 0;
					for (size_t aI = 0; aI < a.indices.size(); aI++)
					{
						int aIndex = a.indices[aI];
						while (myI < indices.size() && indices[myI] < aIndex)
						{
							newVals[newI] = values[myI];
							newIndices[newI] = indices[myI];
							myI++;
							newI++;
						}
						if (myI == indices.size())
						{
							while (aI < a.indices.size())
							{
								newIndices[newI] = a.indices[aI];
								manip(aIndex, a.Value(aI), ref(newVals[newI]));
								aI++;
								newI++;
							}
							break;
						}

						value_type myVal = 0;
						if (indices[myI] == aIndex)
						{
							myVal = values[myI++];
						}

						manip(aIndex, a.Value(aI), ref(myVal));
						newVals[newI] = myVal;
						newIndices[newI] = aIndex;
						newI++;
					}

					while (myI < indices.size())
					{
						newVals[newI] = values[myI];
						newIndices[newI] = indices[myI];
						myI++;
						newI++;
					}

					indices.swap(newIndices);
					values.swap(newVals);

					Densify();
				}
			}
		}
	};

}  //----end of namespace gezi

#endif  //----end of NUMERIC__VECTOR__WEIGHT_VECTOR_H_
