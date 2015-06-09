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
#include <vector>
namespace gezi
{
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

		static bool Choose(size_t i)
		{
			return i % rabit::GetWorldSize() == (size_t)rabit::GetRank();
		}
		//@TODO use Allgather
		//No, support arbitrary send / recv will make fault tolerance much harder, and it is rarely used in most of ML cases.
		//	Your case can be described by Allgather operation, which could be implemented(not yet exposed) in rabit.If you only need to save the model, another alternative would simply be save it into different files in parallel from each of the node.
		//@TODO 如果T是string 直接 rabit::Brodacast即可
		template<typename T>
		static void Broadcast(T& data, int root)
		{
			string sdata = rabit::GetRank() == root ? serialize_util::save(data) : "";
			rabit::Broadcast(&sdata, root);
			if (rabit::GetRank() != root)
			{
				serialize_util::load_from_str(data, sdata);
			}
		}

		template<typename T>
		static void Broadcast(std::vector<T>& datas)
		{
			for (size_t i = 0; i < datas.size(); i++)
			{
				Broadcast(datas[i], (int)i % rabit::GetWorldSize());
			}
		}
	};
}
#endif  //----end of RABIT_UTIL_H_
