/** 
 *  ==============================================================================
 * 
 *          \file   test/test_suffixtree.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2013-11-04 23:03:06.680812
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include <iostream>
#include <string>
//#include <vector>
#include <fstream>
#include <algorithm>
#include <glog/logging.h>
#include <gflags/gflags.h>
//#include "common_util.h"
#include "debug_util.h"
#include "log_util.h"
#include "conf_util.h"
#include "ds/SuffixTree.h"
#include "ds/Rstree.h"
#include "string_util.h"
using namespace std;
using namespace gezi;
DEFINE_string(type, "simple", "");
DEFINE_bool(perf, false, "");
DEFINE_int32(num, 1, "");
DEFINE_string(i, "zhenxiai.txt", "input file");
DEFINE_string(o, "", "output file");

void run()
{
	setlocale(LC_ALL, "zh_CN.GB18030");
	SuffixTree st(L"#");
	//Rstree st(L"#");
	//  st.add(L"abcd");
	//  st.add(L"abde");
	//  ifstream ifs(FLAGS_i.c_str());
	//  string s;
	//  wstring ws;
	//  while (getline(ifs, s))
	//  {
	//    boost::trim(s);
	//    ws = str_to_wstr(s);
	//    wcout << ws << endl;
	//    st.add(ws);
	//  }
	//  
	//  for (int i = 0; i < 10; i++)
	//  {
	//    st.add(ws);
	//  }

	string s = "济州岛Jeju Island 过去也写做 Cheju Island，是韩国最大的岛屿，是一座典型的火山岛，世界新七大自然奇观之一。120万年前火山活动而形成，岛中央是通过火山爆发而形成的海拔1951米的韩国最高峰汉拿山。济州岛的海和本土的完全不同-沙滩是纯白色的，海水染着祖母绿宝石色，和画卷里或者是明信片里看到的南太平洋美丽岛屿无二，所以济州岛海有着无论去多少次也不会腻的魅力。济州岛比起外国的景点一点也不逊色-疾驰过熔岩和祖母绿宝石色的大海，有时候“和谐安宁”，有时候“兵戎相见”，让你可以感受到独属于济州岛大海的魅力。另外，来了济州岛一定要去见识一下济州岛的赌场魅力。韩国有16家赌场，其中8家都在济州岛。它们分别在8座5星级酒店里，经过韩国严格管理许可经营的娱乐场所，而且服务也是澳门那边没办法给予的。只要您通过JCI专业赌场洗码中介紫茵（电话号码见标题）过来，就可以让您享受VIP级的待遇—免费提供往返机票+豪车接送+5星级酒店入住+当地美食观光+贴身翻译陪同等一系列优质服务。绝对可以让您在人间仙境济州岛有一个难忘的旅程。济州桥济南桥";
	wstring ws = str_to_wstr(s);
	Pval(s);
	Pval(wstr2str(ws));
	st.add(ws);
	{
		string s2 = "韩国有16";
		wstring ws2 = str_to_wstr(s2);
		int freq = st.find_freq(ws2);
		Pval(freq);
	}
	st.add(wstr("邹红建"));
	st.add(wstr("梅西和乔丹是好朋友提供好服务"));
//  {
//     string s2 = "只要您通过JCI专业赌场洗码中介紫茵（电话号码见标题）过来";
//    wstring ws2 = str_to_wstr(s2);
//    int freq = st.find_freq(ws2);
//    Pval(freq);
//  }
//  
	{
		string s2 = FLAGS_i;
		 wstring ws2 = str_to_wstr(s2);
		int freq = st.find_freq(ws2);
		Pval(freq);
	
	}
	Pval(st.find_freq(wstr("济州岛")));
	//st.print();
}

int main(int argc, char *argv[])
{
	google::InitGoogleLogging(argv[0]);
	google::InstallFailureSignalHandler();
	int s = google::ParseCommandLineFlags(&argc, &argv, false);
	if (FLAGS_log_dir.empty())
		FLAGS_logtostderr = true;
	LogHelper log_helper;

	run();

	return 0;
}
