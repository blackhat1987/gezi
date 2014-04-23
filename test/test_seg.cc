/**
 *  ==============================================================================
 *
 *          \file   test_seg.cc
 *
 *        \author   chenghuige
 *
 *          \date   2014-03-05 18:12:09.186445
 *
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "common_util.h"
//#include "word_seg.h"
#include "Segmentor.h"
using namespace std;
using namespace gezi;
DEFINE_int32(level, 0, "min log level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

//TEST(test_seg, func)
//{
//	seg_init2();
//	Pval(segment2("我爱你中国速去郭美美吧查看", "|"));
//	Pval(segment2("今天天气不错百度贴吧欢迎你", "|"));
//	seg_init();
//	Pval(segment("我爱你中国速去郭美美吧查看", "|"));
//	Pval(segment("我的扣扣是3456速去美女激晴吧", "|"));
//	Pvec(segment("我爱你中国速去郭美美吧查看我的扣扣是3456速去美女激晴吧"));
//}
//
//TEST(test_seg_basic, func)
//{
//	seg_init2();
//	Pval(segment2("我爱你中国速去郭美美吧查看", "|", SCW_OUT_BASIC));
//	Pval(segment2("今天天气不错百度贴吧欢迎你", "|", SCW_OUT_BASIC));
//	seg_init();
//	Pval(segment("我爱你中国速去郭美美吧查看", "|", SCW_OUT_BASIC));
//	Pval(segment("我的扣扣是3456速去美女激晴吧", "|", SCW_OUT_BASIC));
//}
//
//TEST(test_seg_subph, func)
//{
//	seg_init2();
//	Pval(segment2("我爱你中国速去郭美美吧查看", "|", SCW_OUT_SUBPH));
//	Pval(segment2("今天天气不错百度贴吧欢迎你", "|", SCW_OUT_SUBPH));
//	seg_init();
//	Pval(segment("我爱你中国速去郭美美吧查看", "|", SCW_OUT_SUBPH));
//	Pval(segment("我的扣扣是3456速去美女激晴吧", "|", SCW_OUT_SUBPH));
//}
//
//TEST(test_seg_newword, func)
//{
//	seg_init2();
//	Pval(segment2("我爱你中国速去郭美美吧查看", "|", SCW_OUT_NEWWORD));
//	Pval(segment2("今天天气不错百度贴吧欢迎你", "|", SCW_OUT_NEWWORD));
//	seg_init();
//	Pval(segment("我爱你中国速去郭美美吧查看", "|", SCW_OUT_NEWWORD));
//	Pval(segment("我的扣扣是3456速去美女激晴吧", "|", SCW_OUT_NEWWORD));
//}
//
////SCW_OUT_BOOKNAME SCW_OUT_HUMANNAME
//TEST(test_seg_name, func)
//{
//	seg_init2();
//	Pval(segment2("我爱你中国速去郭美美吧查看", "|", SCW_OUT_HUMANNAME));
//	Pval(segment2("今天天气不错百度贴吧欢迎你", "|", SCW_OUT_HUMANNAME));
//	seg_init();
//	Pval(segment("我爱你中国速去郭美美吧查看", "|", SCW_OUT_HUMANNAME));
//	Pval(segment("我的扣扣是3456速去美女激晴吧", "|", SCW_OUT_HUMANNAME));
//}
//
//
//TEST(test_seg_all, func)
//{//跟basic一样啊。。
//	seg_init2();
//	Pval(segment2("我爱你中国速去郭美美吧查看", "|", SCW_OUT_ALL));
//	Pval(segment2("今天天气不错百度贴吧欢迎你", "|", SCW_OUT_ALL));
//	seg_init();
//	Pval(segment("我爱你中国速去郭美美吧查看", "|", SCW_OUT_ALL));
//	Pval(segment("我的扣扣是3456速去美女激晴吧", "|", SCW_OUT_ALL));
//}
//
//TEST(other, func)
//{
//	seg_init();
//	SegHandle handle = segment_("我爱你中国速去郭美美吧查看我的扣扣是3456速去美女激晴吧");
//	for (int i = 0; i < handle.nresult; i++)
//	{
//		cout << handle.tokens[i].buffer << "\t" << handle.tokens[i].offset << "\t"
//			<< handle.tokens[i].weight << endl;
//	}
//}
//
//TEST(other_newword, func)
//{//--------offset 是相对混排粒度的
//	seg_init();
//	/*SegHandle handle = segment_("我爱你中国速去郭美美吧查看我的扣扣是3456速去美女激晴吧", SCW_OUT_NEWWORD);*/
//	SegHandle handle = segment_("我爱你中国扣扣是速去美女激晴吧", SCW_OUT_NEWWORD);
//	for (int i = 0; i < handle.nresult; i++)
//	{
//		cout << handle.tokens[i].buffer << "\t" << handle.tokens[i].offset << "\t"
//			<< handle.tokens[i].weight << endl;
//	}
//
//	Pval(segment("我爱你中国扣扣是速去美女激晴吧", "|", SCW_OUT_BASIC));
//	Pval(segment("我爱你中国扣扣是速去美女激晴吧", "|", SCW_OUT_SUBPH));
//	Pval(segment("我爱你中国扣扣是速去美女激晴吧", "|", SCW_OUT_WPCOMP));
//	{
//		SegHandle handle = segment_("我爱你中国扣扣是速去美女激晴吧", SCW_OUT_SUBPH);
//		for (int i = 0; i < handle.nresult; i++)
//		{
//			cout << handle.tokens[i].buffer << "\t" << handle.tokens[i].offset << "\t"
//				<< handle.tokens[i].weight << endl;
//		}
//	}
//}

//TEST(final, func)
//{
//	Pval(segment("我爱你中国扣扣是速去美女激晴吧", "|", SCW_OUT_WPCOMP | SCW_OUT_NEWWORD));
//	Pval(segment("我的扣扣是马布里杨美美基晴视频", "|", SCW_OUT_WPCOMP | SCW_OUT_SUBPH));
//	Pval(segment("我的扣扣是马布里杨美美基晴视频", "|", SCW_OUT_NEWWORD));
//	SharedSegmentor::GetSegmentor().init();
//}

class Tester
{
public:
	Segmentor _seg;
};
TEST(final, func)
{
	Segmentor::init();
	Segmentor seg;
	Pval(seg.segment("我爱你中国扣扣是速去美女激晴吧", "|", SCW_OUT_WPCOMP));

	Pval(seg.segment("我的扣扣是马布里杨美美基晴视频", "|", SCW_OUT_WPCOMP));

	Pval(seg.segment("我的扣扣是马布里杨美美基晴视频", "|", SEG_MERGE_NEWWORD));

	Pval(seg.set_flag(SCW_CRF).segment("我的扣扣是马布里杨美美基晴视频", "|", SCW_OUT_WPCOMP | SCW_OUT_NEWWORD));

	Pval(seg.segment("我的扣扣是马布里杨美美基晴视频", "|", SEG_MERGE_NEWWORD));

	Pval(seg.set_flag(0).segment("我的扣扣是马布里杨美美基晴视频", "|", SEG_MERGE_NEWWORD));

	Pval(seg.segment("回复：【新版斗破苍穹传奇】2014年最新火爆开放◆数月调试震撼上演	萧炎这才无奈的摇了摇头", "|", SEG_MERGE_NEWWORD));

	Tester tester;
}

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	google::InitGoogleLogging(argv[0]);
	google::InstallFailureSignalHandler();
	int s = google::ParseCommandLineFlags(&argc, &argv, false);
	if (FLAGS_log_dir.empty())
		FLAGS_logtostderr = true;
	FLAGS_minloglevel = FLAGS_level;
	boost::progress_timer timer;

	return RUN_ALL_TESTS();
}
