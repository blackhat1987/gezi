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
	//�����sofia-ml
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
				ScaleToOne();
		}

		void ScaleToOne()
		{
			for (size_t i = 0; i < length; i++)
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
			return values[index] * _scale;
		}

		////@TODO how to remove this for duplicate of Vector  @FIXMEΪʲô������ᱨ�� Vector.h:784:15: error: 'gezi::Vector::value_type& gezi::Vector::Value(int)' cannot be overloaded
		//value_type& Value(int index)
		//{
		//	return values[index];
		//}


		//@WARNING ��������������Vector�����ΪVector ��һ���Ƿ�Ӱ�������
		/// Adds the supplied vector to myself.  (this += a) //@TODO check if can use const Vector&
		void Add(Vector& a)
		{
			if (a.Count() == 0)
				return;
			if (a.IsDense())
			{
				for (size_t i = 0; i < values.size(); i++)
					values[i] += a.values[i] / _scale;
			}
			else
			{ // a sparse, this not sparse
				for (int i = 0; i < a.indices.size(); i++)
				{
					values[a.indices[i]] += a.values[i] / _scale;
				}
			}
		}

		Vector GetVector()
		{
			if (_scale == 1.0)
			{
				return (Vector)*this;
			}
			Vector vec(length, _zeroValue);
			for (size_t i = 0; i < length; i++)
			{
				vec.values[i] = values[i] * _scale;
			}
			return vec;
		}

	private:
		Float _scale = 1.0;
		Float _sqaredNorm = 0.0;
	};

}  //----end of namespace gezi

#endif  //----end of NUMERIC__VECTOR__WEIGHT_VECTOR_H_
