/**
 *  ==============================================================================
 *
 *          \file   rabit_util.h
 *
 *        \author   chenghuige
 *
 *          \date   2015-06-05 21:56:12.572037
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef RABIT_UTIL_H_
#define RABIT_UTIL_H_

#include "rabit.h"
#include "serialize_util.h"
#include "stl_util.h"
#include <vector>
namespace gezi
{
	//namespace ufo
	//{
	//	//---��Ӧ�����������ͻ��߻���������ϵ�struct��ok��
	//	//@TODO rabit�Ľӿ����ʹ�ñ���ʹ�ú���ָ����Ϊģ�����DType�����Զ��Ƶ��� ������ʾע��
	//	template<typename DType, void(*freduce)(DType &dst, const DType &src)>
	//	inline void Allreduce(DType* dest, size_t count)
	//	{
	//		rabit::Reducer<DType, freduce> reducer;
	//		reducer.Allreduce(dest, count);
	//	}

	//	template<typename DType, void(*freduce)(DType &dst, const DType &src)>
	//	inline void Allreduce(vector<DType>& vec)
	//	{
	//		Allreduce<DType, freduce>(begin_ptr(vec), vec.size());
	//	}

	//	template<typename DType>
	//	inline void Broadcast(DType& data, int root)
	//	{
	//		rabit::Broadcast(&data, sizeof(DType), root);
	//	}

	//	//---not ok refer to http://stackoverflow.com/questions/1174169/function-passed-as-template-argument
	//	//template<typename Func, typename DType>
	//	//inline void Allreduce(DType* dest, size_t count, Func func)
	//	//{
	//	//	//typedef void(*func_)(DType &dst, const DType &src);
	//	//	rabit::Reducer<DType, &func> reducer;
	//	//	reducer.Allreduce(dest, count);
	//	//}

	//	//template<typename Func, typename DType>
	//	//inline void Allreduce(vector<DType>& vec, Func func)
	//	//{
	//	//	Allreduce<Func, DType>(&vec[0], vec.size(), func);
	//	//}
	//}

	namespace op = rabit::op;

	struct RabitObject
	{
		bool visited = false;
	};

	struct Rabit
	{
		Rabit(int argc, char *argv[])
		{
			rabit::Init(argc, argv);
		}
		~Rabit()
		{
			rabit::Finalize();
		}

		static bool& AllowDistribute()
		{
			static bool allwoDistribute = true;
			return allwoDistribute;
		}

		//---------- ���溯��Ĭ��ʹ��%����node�ķ��䷽ʽ
		inline static bool Choose(size_t i)
		{
			return !AllowDistribute() || i % rabit::GetWorldSize() == (size_t)rabit::GetRank();
		}

		inline static bool SimpleChoose(size_t i)
		{
			return i % rabit::GetWorldSize() == (size_t)rabit::GetRank();
		}

		static int GetWorldSize()
		{
			return AllowDistribute() ? rabit::GetWorldSize() : 1;
		}

		static int GetRank()
		{
			return AllowDistribute() ? rabit::GetRank() : 0;
		}

		//@TODO use Allgather
		//No, support arbitrary send / recv will make fault tolerance much harder, and it is rarely used in most of ML cases.
		//	Your case can be described by Allgather operation, which could be implemented(not yet exposed) in rabit.If you only need to save the model, another alternative would simply be save it into different files in parallel from each of the node.
		//@TODO ���T��string ֱ�� rabit::Brodacast����
		template<typename T>
		static void SerializeBroadcast(T& data, int root)
		{
			string sdata = rabit::GetRank() == root ? serialize_util::save(data) : "";
			rabit::Broadcast(&sdata, root);
			if (rabit::GetRank() != root)
			{
				serialize_util::load_from_str(data, sdata);
			}
		}

		//@TODO ͨ�����л���string Ȼ�� broadcast��������ϵ������ڵ㣬��������AllReduce�������� ��������ͨ�Ŷ�ÿ����Ҫ����ͨ�� 
		//��string�ƺ�����allreduce��ȥ rabitֻ��allreduce����������ͻ���������ϵ�struct
		//�ƺ���������rabit::SeralizeReducer����ʵ��
		template<typename T>
		static void SerializeBroadcast(std::vector<T>& datas)
		{
			for (size_t i = 0; i < datas.size(); i++)
			{
				SerializeBroadcast(datas[i], (int)i % rabit::GetWorldSize());
			}
		}

		template<typename DType, void(*freduce)(DType &dst, const DType &src)>
		static void Allreduce(DType* dest, size_t count)
		{
			rabit::Reducer<DType, freduce> reducer;
			reducer.Allreduce(dest, count);
		}

		template<typename DType, void(*freduce)(DType &dst, const DType &src)>
		static void Allreduce(vector<DType>& vec)
		{
			if (!vec.empty())
			{
				Rabit::Allreduce<DType, freduce>(&vec[0], vec.size());
			}
		}

		template<typename DType, void(*freduce)(DType &dst, const DType &src)>
		static void Allreduce(DType& dest)
		{
			rabit::Reducer<DType, freduce> reducer;
			reducer.Allreduce(&dest, 1);
		}


		template<typename OP, typename DType>
		static void Allreduce(vector<DType>& vec,
			void(*prepare_fun)(void *arg) = NULL,
			void *prepare_arg = NULL)
		{
			if (!vec.empty())
			{
				rabit::Allreduce<OP>(&vec[0], vec.size(), prepare_fun, prepare_arg);
			}
		}

		template<typename OP, typename DType>
		static void Allreduce(DType& data)
		{
			rabit::Allreduce<OP>(&data, 1);
		}

		template<typename DType>
		static void Broadcast(DType& data, int root)
		{
			rabit::Broadcast(&data, sizeof(DType), root);
		}

		template<typename DType>
		static void Broadcast(vector<DType>& data, int root)
		{
			rabit::Broadcast(&data, root);
		}

		//template<typename Node>
		//static void Reduce(Node& dest, const Node& src)
		//{
		//	if (src.visited > dest.visited)
		//	{
		//		dest = src;
		//	}
		//}

		////--------@TODO ����ΪCollect���ã� Allgather ? Allgather�����collect���� �ȵ�ǰ��Choose���ã�
		////����ǻ������Ϳ�������AllReduce���ۺ�Ⱥ����Ϣ ���������Ȼʹ��%����
		////@TODO ����������һ�����λǿ�� ���õķ���?
		//template<typename DType>
		//static void Allreduce(std::vector<DType>& datas)
		//{
		//	for (size_t i = 0; i < datas.size(); i++)
		//	{
		//		if (Choose(i))
		//		{
		//			datas[i].visited = true;
		//		}
		//	}
		//	ufo::Allreduce<DType, Reduce<DType> >(datas);
		//}

		//@TODO ��ǰ��һ��û��allgather��workaround����ʹ��broadcast�����ͨ�Ŵ����࣬һ��nodeҪ��һ��broadcast
		template<typename DType>
		static void Allgather(vector<DType>& datas)
		{
			vector<vector<DType> > values(rabit::GetWorldSize());
			values[rabit::GetRank()] = move(datas);
			for (size_t i = 0; i < values.size(); i++)
			{
				Rabit::Broadcast(values[i], i);
			}

			for (auto& value : values)
			{
				gezi::merge(datas, value);
			}
		}

		template<typename DType>
		static vector<DType> Allgather(const DType& datas)
		{
			vector<DType> values(rabit::GetWorldSize());
			values[rabit::GetRank()] = move(datas);
			for (size_t i = 0; i < values.size(); i++)
			{
				rabit::Broadcast(&values[i], sizeof(DType), i);
			}
			return values;
		}

		//��Ե�ǰvector<bool>��broadcast�����⡣�� ������vector<bool>�Ĺ�������
		static void Broadcast(vector<bool>& data, int root)
		{
			vector<unsigned> vec(data.begin(), data.end());
			rabit::Broadcast(&vec, root);
			data.assign(vec.begin(), vec.end());
		}
	};

#define  PARALLEL_CHOOSE(i) \
	if (!Rabit::Choose(i)) \
		continue
}
#endif  //----end of RABIT_UTIL_H_
