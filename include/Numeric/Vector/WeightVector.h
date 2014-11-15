/**
 *  ==============================================================================
 *
 *          \file   Numeric/Vector/WeightVector.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-11-09 21:19:07.361690
 *
 *  \Description:  @TODO看一下gbdt的实现里面有没有地方可以利用WeightVector取代Vector提速？
 *  ==============================================================================
 */

#ifndef NUMERIC__VECTOR__WEIGHT_VECTOR_H_
#define NUMERIC__VECTOR__WEIGHT_VECTOR_H_

#include "Vector.h"

namespace gezi {
	//借鉴自sofia-ml, WeightVector默认是常用的Dense,稀疏使用SparseWeightVector
	class WeightVector : public Vector
	{
	public:
		using Vector::Vector;
		WeightVector() = default; //sparse生成时必须带有length
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
		void ScaleBy(value_type scalingFactor)
		{
			_scale *= scalingFactor;
			squaredNorm *= (scalingFactor * scalingFactor);
			// Take care of any numerical difficulties.
			if (_scale < 0.00000000001)
			{
				//LOG(WARNING) << "scale_to_one";
				ScaleToOne();
			}
		}

		Float Norm()
		{
			return sqrt(squaredNorm);
		}

		void ScaleToOne()
		{
			for (size_t i = 0; i < values.size(); i++)
			{
				values[i] *= _scale;
			}
			_scale = 1.0;
		}

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
			return values[index] * _scale;
		}

		////using Vector::Value; //这个会影响到后面的dot 里面Value 也会使用Vector::value
		////因此为了后面能使用 暂时duplicate,覆盖基类同名函数比较危险 比如这里等于非const的被覆盖了 deleted 
		////如果使用using 又貌似没办法指定只using非const版本 @TODO
		////另外假如加上下面 也要注意 没有的时候 dot函数 可以不设置成const 因为都会调用const版本的Value,但是如果有下面的 dot必须const否则优先调用下面的
		////当然为了安全也可以不提供下面的 强迫非const版本 直接使用values[index]
		//value_type& Value(int index)
		//{
		//	return values[index];
		//}

		//@WARNING 下面两个函数从Vector输入改为Vector 看一下是否影响最后结果
		/// Adds the supplied vector to myself.  (this += a) //@TODO check if can use const Vector&
		void Add(const Vector& other)
		{
			Float innerProduct = 0;
			if (other.IsSparse())
			{
				for (int i = 0; i < other.indices.size(); i++)
				{
					innerProduct += values[other.indices[i]] * other.values[i];
					values[other.indices[i]] += other.values[i] / _scale;
				}
			}
			else
			{
				for (size_t i = 0; i < values.size(); i++)
				{
					innerProduct += values[i] * other.values[i];
					values[i] += other.values[i] / _scale;
				}
			}
			squaredNorm += squaredNorm + (2.0 * _scale * innerProduct);
		}

		void AddSparse(const Vector& other)
		{
			Float innerProduct = 0;
			for (int i = 0; i < other.indices.size(); i++)
			{
				innerProduct += values[other.indices[i]] * other.values[i];
				values[other.indices[i]] += other.values[i] / _scale;
			}
			squaredNorm += squaredNorm + (2.0 * _scale * innerProduct);
		}

		//a的数据*scale,假定操作的Vector a是稀疏的,不改变输入的a
		void AddScale(const Vector& other, value_type scale)
		{
			Float innerProduct = 0;
			if (other.IsSparse())
			{
				for (int i = 0; i < other.indices.size(); i++)
				{
					Float otherVal = other.values[i] * scale;
					innerProduct += values[other.indices[i]] * otherVal;
					values[other.indices[i]] += otherVal / _scale;
				}
			}
			else
			{
				for (size_t i = 0; i < values.size(); i++)
				{
					Float otherVal = other.values[i] * scale;
					innerProduct += values[i] * otherVal;
					values[i] += other.values[i] * scale / _scale;
				}
			}
			squaredNorm += other.SquaredNorm() * scale * scale + (2.0 * _scale * innerProduct);
		}

		//会将自身变化 
		Vector ToVector()
		{
			if (_scale != 1.0)
			{
				ScaleToOne();
			}
			return (Vector)*this;
		}


		//注意这里dot默认后面是稀疏 其实是 dotSparse,另外注意如果不加处理会调用Vector::Value 为什么呢 @FIXME @TODO
		Float dot(const Vector& other) const
		{
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

		Float dot(const Vector& other, Float scale) const
		{
			return dot(other) * scale;
		}

		// this dot (other1 - other2)
		Float dotOnDifference(const Vector& other1, const Vector& other2, Float scale = 1.0) const
		{
			return dot(other1, scale) + dot(other2, -scale);
		}
		
		value_type SquaredNorm() const
		{
			return squaredNorm;
		}

	public:
		Float squaredNorm = 0.0;
	protected:
		Float _scale = 1.0;
	};


	//当前假定操作目标都是sparse表示,未测试，暂时未使用
	class SparseWeightVector : public WeightVector
	{
	public:
		using WeightVector::WeightVector;


		void Add(Vector& a)
		{
			WeightApplyWith(a, [this](int ind, const value_type v1, value_type& v2) { v2 += v1 / _scale; });
		}

		//因为目前没有用虚函数 @TODO duplicate
		void Add(SparseWeightVector& a)
		{
			WeightApplyWith(a, [this](int ind, const value_type v1, value_type& v2) { v2 += v1 / _scale; });
		}

		//a的数据不再保证
		void AddScale(Vector& a, value_type scale)
		{
			WeightApplyWith(a, [this, &scale](int ind, const value_type v1, value_type& v2) { v2 += v1 * scale / _scale; });
		}

		//a的数据不再保证
		void AddScale(SparseWeightVector& a, value_type scale)
		{
			WeightApplyWith(a, [this, &scale](int ind, const value_type v1, value_type& v2) { v2 += v1 * scale / _scale; });
		}


		//@TODO  修改ApplyWith 复用
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
