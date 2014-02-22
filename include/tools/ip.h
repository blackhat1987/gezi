/**
 *  ==============================================================================
 *
 *          \file   tools/ip.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-02-22 20:24:34.765822
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TOOLS_IP_H_
#define TOOLS_IP_H_

#include "common_def.h"
#include <string>
namespace gezi
{
	//贴吧ip数据 转换成可读的string格式 类似 1577234 -> 192.168.32.78
	inline string to_ipstr(uint64 ipl)
	{
		int ip1 = ipl / (256 * 256 * 256);
		int ip2 = (ipl % (256 * 256 * 256)) / (256 * 256);
		int ip3 = (ipl % (256 * 256)) / 256;
		int ip4 = ipl % 256;
		return (format("%d.%d.%d.%d") % ip4 % ip3 % ip2 % ip1).str();
	}

	//从输入的ip数据 获取到可读的ip格式的4个int array[3] 192 array[2] 168 array[1] 32 array[0] 78
	inline std::array<int, 4> to_iparray(uint64 ipl)
	{
		std::array<int, 4> vec;
		vec[0] = ipl / (256 * 256 * 256);
		vec[1] = (ipl % (256 * 256 * 256)) / (256 * 256);
		vec[2] = (ipl % (256 * 256)) / 256;
		vec[3] = ipl % 256;
#if __GNUC__ > 3
		return std::move(vec);
#else
		return vec;
#endif  
	}
}

#endif  //----end of TOOLS_IP_H_
