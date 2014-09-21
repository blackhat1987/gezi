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
		return vec;
	}

	//n 只能取3,2,1
	inline uint64 get_topn_ipgroup(uint64 ipl, int n)
	{
		return ipl % (uint64)pow(256, n);
	}

	//输入ip数据输出 ip前三位，ip前两位，ip首位
	inline void get_ipgroups(uint64 ipl, uint64& top3, uint64& top2, uint64& top1)
	{
		top3 = ipl % (256 * 256 * 256);
		top2 = ipl % (256 * 256);
		top1 = ipl % 256;
	}

	inline string get_address(IpFinder& ipFinder, uint64 ipl)
	{
		string country, location;
		ipFinder.GetAddressByIp(to_ipstr(ipl), country, location);
		string result = country.size() < 4 ? country : country.substr(0, 4);
		return result;
	}

	inline string get_location(IpFinder& ipFinder, uint64 ipl)
	{
		string country, location;
		ipFinder.GetAddressByIp(to_ipstr(ipl), country, location);
		string result = country.size() < 4 ? country : country.substr(0, 4);
		return result;
	}

	//单例模式也可以写到IpFinder类里面 static IpFinder& Instance()
	inline static IpFinder& ipFinder() //不使用static thread_local 每次ipfinder会被重置重新加载 ExtendedUrateInfo a = b;
	{
		static thread_local IpFinder _ipFinder;
		static thread_local bool _isIpFinderInited = false;
		if (!_isIpFinderInited)
		{
			string ipFinderPath = "./data/qqwry.dat";
			PSCONF(ipFinderPath, "Global");
			bool ret = _ipFinder.Open(ipFinderPath);
			CHECK_EQ(ret, true);
			_isIpFinderInited = true;
		}
		return _ipFinder;
	}
}

#endif  //----end of TOOLS_IP_H_
