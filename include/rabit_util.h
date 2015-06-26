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
	//	//---对应基础数据类型或者基础类型组合的struct是ok的
	//	//@TODO rabit的接口设计使得必须使用函数指针作为模板参数DType不能自动推导了 必须显示注明
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

		//---------- 下面函数默认使用%分配node的分配方式
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
		//@TODO 如果T是string 直接 rabit::Brodacast即可
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

		//@TODO 通过序列化到string 然后 broadcast将结果整合到各个节点，理论上是AllReduce操作更好 现在这样通信多每个都要单独通信 
		//但string似乎不能allreduce出去 rabit只能allreduce传输基本类型或者类型组合的struct
		//似乎可以类似rabit::SeralizeReducer可以实现
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

		////--------@TODO 命名为Collect更好？ Allgather ? Allgather是逐段collect放置 比当前的Choose更好？
		////如果是基本类型可以利用AllReduce来聚合群组信息 假设分组依然使用%分配
		////@TODO 现在是增加一个标记位强制 更好的方法?
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

		//@TODO 当前的一个没有allgather的workaround但是使用broadcast会造成通信次数多，一个node要做一次broadcast
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

		//针对当前vector<bool>的broadcast有问题。。 估计是vector<bool>的构造问题
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
