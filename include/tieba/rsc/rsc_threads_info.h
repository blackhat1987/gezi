/**
 *  ==============================================================================
 *
 *          \file   tieba/rsc/rsc_threads_info.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-10-27 09:08:41.422772
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_RSC_RSC_THREADS_INFO_H_
#define TIEBA_RSC_RSC_THREADS_INFO_H_

#include "other/CachedFetcher.h"
#include "tieba/get_parsed_info.h"
#include "container/lru_containers.h"
#include "tools/ip.h"
namespace gezi {
	namespace tieba {
		namespace rsc {

			struct ReplyInfo
			{
				uint64 tid;
				uint userId;
				uint64 pid;
				uint64 ip;
				uint64 time;
				double threadRatio;
			};

			struct RscThreadsInfo
			{
				RscThreadsInfo()
				{

				}

				//输入能确保无重复tid
				template<typename ThreadInfoFetcher, typename UserInfoFetcher>
				void Fetch(string substr_, vector<ReplyInfo>& tids, ThreadInfoFetcher& threadFetcher, UserInfoFetcher& userFetcher,
					bool isOnline = false, string historyDir = "./history")
				{
					substr = substr_;
					for (auto item : tids)
					{
						replysInfo[item.tid] = item;
					}

					{//fetch thread info
						vector<uint64> tidVec = from(tids) >> select([](const ReplyInfo& a) { return a.tid; }) >> to_vector();

						//CachedFetcher<uint64, tieba::ThreadInfo, LruHashMap> threadsFetcher;
						threadFetcher.SetCapacity(1000000);
						auto func = [](const vector<uint64>& tids) { return tieba::get_threads_info(tids, true); };
						if (isOnline)
						{
							threadsInfo = threadFetcher.GetValues(tidVec, func);
						}
						else
						{
							threadsInfo = try_get_infos<ThreadInfo>(tidVec, [&](const vector<uint64>& tids) { return threadFetcher.GetValues(tids, func); },
								historyDir, substr_, false, true, "thread");
						}
					}

					{//fetch user info
						vector<uint> uids = from(tids) >> select([](const ReplyInfo& a) { return a.userId; }) >> distinct() >> to_vector();
						userFetcher.SetCapacity(100000);
						auto func = [](const vector<uint>& uids) { return tieba::get_users_info_map(uids, true); };
						if (isOnline)
						{
							usersInfo = userFetcher.GetValuesMap(uids, func);
						}
						else
						{
							usersInfo = try_get_infos_map<uint, UserInfo>(uids, [&](const vector<uint>& uds) { return userFetcher.GetValuesMap(uids, func); }, historyDir, substr_, false, true, "user");
						}
					}
				}

				void Extract()
				{
					for (ThreadInfo& node : threadsInfo)
					{
						node.address = get_location(ipFinder(), node.ip);

						uidCountMap[node.userId] += 1;
						ipCountMap[node.ip] += 1;

						if (node.userId != replysInfo[node.threadId].userId)
						{
							uidDistinctCountMap[node.userId] += 1;
						}

						ipsetPerUid[node.userId].insert(node.ip);
						addressSetPerUid[node.userId].insert(node.address);
						uidsetPerIp[node.ip].insert(node.userId);
						threadNodeMap[node.threadId] = node;

						uidSet.insert(node.userId);
						if (node.userId != replysInfo[node.threadId].userId)
						{
							notSelfUpUidSet.insert(node.userId);
						}
						ipSet.insert(node.ip);
						addressSet.insert(node.address);
					}

					for (auto& item : ipsetPerUid)
					{
						numIpsPerUidMap[item.first] = item.second.size();
					}

					for (auto& item : addressSetPerUid)
					{
						numAddressesPerUidMap[item.first] = item.second.size();
					}

					for (auto& item : uidsetPerIp)
					{
						numUidsPerIpMap[item.first] = item.second.size();
					}
				}


				//原始信息
				string substr;
				vector<ThreadInfo> threadsInfo;
				map<uint, UserInfo> usersInfo;
				map<uint64, ReplyInfo> replysInfo;

				//衍生信息
				map<uint64, ThreadInfo> threadNodeMap;
				map<uint64, int> uidCountMap;
				map<uint64, int> ipCountMap;
				map<uint64, int> uidDistinctCountMap;


				map<uint64, set<uint64> > uidsetPerIp;
				map<uint64, set<uint64> > ipsetPerUid;
				map<uint64, set<string> > addressSetPerUid;

				map<uint64, int> numIpsPerUidMap;
				map<uint64, int> numUidsPerIpMap;
				map<uint64, int> numAddressesPerUidMap;

				set<uint64> uidSet;
				set<uint64> notSelfUpUidSet;
				set<uint64> ipSet;
				set<string> addressSet;

				static IpFinder& ipFinder()
				{
					static thread_local IpFinder _ipFinder;
					static thread_local bool _isIpFinderInited = false;
					if (!_isIpFinderInited)
					{
						string ipData = "./data/qqwry.dat";
						bool ret = _ipFinder.Open(ipData);
						CHECK_EQ(ret, true);
						_isIpFinderInited = true;
					}
					return _ipFinder;
				}
				IpFinder& _ipFinder = ipFinder();

			};
		}  //----end of namespace rsc
	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_RSC_RSC_THREADS_INFO_H_
