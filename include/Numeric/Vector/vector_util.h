/**
 *  ==============================================================================
 *
 *          \file   Numeric/Vector/vector_util.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-04-09 08:37:54.558044
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef NUMERIC__VECTOR_VECTOR_UTIL_H_
#define NUMERIC__VECTOR_VECTOR_UTIL_H_
#include "common_def.h"
#include "Numeric/Vector/Vector.h"
namespace gezi {

	//dense vector and binary vec apply
	template<typename Func>
	void apply(Fvec& values, const ivec& shiftIndices, Func func)
	{
		int bI = 0;
		for (size_t i = 0; i < values.size(); i++)
		{
			Float bVal = 0;
			if (bI < shiftIndices.size() && i == shiftIndices[bI])
			{
				bI++;
				bVal = 1;
			}
			values[i] = func(i, values[i], bVal);
		}
	}

	//@TODO 也许需要改为std::function 重载？ 由于目前没有func(index,val1, val2)的需求暂时不做泛化处理
	//现在主要用于normalize 注意TLC中Vector.ApplyInto 是func<index, val1, val2> 只是val2 传递的时候未用
	//func(index, vec.Value(index), vec2.Value(index)
	//sparse vector and binary vec apply
	template<typename Func, typename _Vector>
	void apply_sparse(_Vector& vec, const ivec& shiftIndices, Func func)
	{
		_Vector result(vec.Length()); //@NOTICE 一定注意要加上长度构造
		int len = shiftIndices.size();
		int len2 = vec.Count();

		Float val;
		int index, index2;
		int i = 0, j = 0;
		for (; i < len && j < len2;)
		{
			index = shiftIndices[i];
			index2 = vec.Index(j);
			if (index == index2)
			{
				val = vec.Value(j);
				func(index, ref(val));
				result.Add(index, val);
				i++;
				j++;
			}
			else if (index < index2)
			{
				val = 0;
				func(index, ref(val));
				result.Add(index, val);
				i++;
			}
			else
			{
				val = vec.Value(j);
				func(index2, ref(val));
				result.Add(index2, val);
				j++;
			}
		}
		for (; i < len; i++)
		{
			index = shiftIndices[i];
			val = 0; //@TODO vec.ZeroValue()
			func(index, ref(val));
			result.Add(index, val);
		}

		for (; j < len2; j++)
		{
			index2 = vec.Index(j);
			val = vec.Value(j);
			func(index2, ref(val));
			result.Add(index2, val);
		}

		//vec.Swap(result);
		vec = move(result);
	}

	//以vec为准遍历, shiftIndices 辅助定位有用的非0项, func无返回值 采用引用修改值
	template<typename Func>
	void apply(Vector& vec, const ivec& shiftIndices, Func func)
	{
		if (vec.IsDense())
		{
			for (size_t i = 0; i < vec.values.size(); i++)
			{
				func(i, vec.values[i]);
			}
		}
		else
		{
			apply_sparse(vec, shiftIndices, func);
		}
	}
}  //----end of namespace gezi

#endif  //----end of NUMERIC__VECTOR_VECTOR_UTIL_H_
