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

	//@TODO Ҳ����Ҫ��Ϊstd::function ���أ� ����Ŀǰû��func(index,val1, val2)��������ʱ������������
	//������Ҫ����normalize ע��TLC��Vector.ApplyInto ��func<index, val1, val2> ֻ��val2 ���ݵ�ʱ��δ��
	//func(index, vec.Value(index), vec2.Value(index)
	//sparse vector and binary vec apply
	template<typename Func, typename _Vector>
	void apply_sparse(_Vector& vec, const ivec& shiftIndices, Func func)
	{
		_Vector result(vec.Length()); //@NOTICE һ��ע��Ҫ���ϳ��ȹ���
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

	//��vecΪ׼����, shiftIndices ������λ���õķ�0��, func�޷���ֵ ���������޸�ֵ
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
