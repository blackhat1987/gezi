/**
 *  ==============================================================================
 *
 *          \file   tools/ip.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-02-22 20:24:34.765822
 *
 *  \Description:  注意贴吧ip数据的存储格式uint 4个int的存储和普通正常存储正好相反
 *                 因此不能直接调用IpFinder.GetAddressByIp(uint ...) 否则结果不对
 *                 可以调用 IpFinder.GetAddressByIp（to_ipstr(uint) ...)
 *  ==============================================================================
 */

#ifndef TOOLS_IP_H_
#define TOOLS_IP_H_

#include "common_def.h"
#include <string>
#include "tools/IpFinder.h"
namespace gezi
{
	//下面都按照贴吧格式ip数据处理
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

	inline string get_address(IpFinder& ipFinder, uint64 ipl)
	{
		string country, location;
		ipFinder.GetAddressByIp(to_ipstr(ipl), country, location);
		string result = country.size() < 4 ? country : country.substr(0, 4);
		return result;
	}
}

#endif  //----end of TOOLS_IP_H_
