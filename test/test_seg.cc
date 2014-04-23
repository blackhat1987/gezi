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
//	Pval(segment2("�Ұ����й���ȥ�������ɲ鿴", "|"));
//	Pval(segment2("������������ٶ����ɻ�ӭ��", "|"));
//	seg_init();
//	Pval(segment("�Ұ����й���ȥ�������ɲ鿴", "|"));
//	Pval(segment("�ҵĿۿ���3456��ȥ��Ů�����", "|"));
//	Pvec(segment("�Ұ����й���ȥ�������ɲ鿴�ҵĿۿ���3456��ȥ��Ů�����"));
//}
//
//TEST(test_seg_basic, func)
//{
//	seg_init2();
//	Pval(segment2("�Ұ����й���ȥ�������ɲ鿴", "|", SCW_OUT_BASIC));
//	Pval(segment2("������������ٶ����ɻ�ӭ��", "|", SCW_OUT_BASIC));
//	seg_init();
//	Pval(segment("�Ұ����й���ȥ�������ɲ鿴", "|", SCW_OUT_BASIC));
//	Pval(segment("�ҵĿۿ���3456��ȥ��Ů�����", "|", SCW_OUT_BASIC));
//}
//
//TEST(test_seg_subph, func)
//{
//	seg_init2();
//	Pval(segment2("�Ұ����й���ȥ�������ɲ鿴", "|", SCW_OUT_SUBPH));
//	Pval(segment2("������������ٶ����ɻ�ӭ��", "|", SCW_OUT_SUBPH));
//	seg_init();
//	Pval(segment("�Ұ����й���ȥ�������ɲ鿴", "|", SCW_OUT_SUBPH));
//	Pval(segment("�ҵĿۿ���3456��ȥ��Ů�����", "|", SCW_OUT_SUBPH));
//}
//
//TEST(test_seg_newword, func)
//{
//	seg_init2();
//	Pval(segment2("�Ұ����й���ȥ�������ɲ鿴", "|", SCW_OUT_NEWWORD));
//	Pval(segment2("������������ٶ����ɻ�ӭ��", "|", SCW_OUT_NEWWORD));
//	seg_init();
//	Pval(segment("�Ұ����й���ȥ�������ɲ鿴", "|", SCW_OUT_NEWWORD));
//	Pval(segment("�ҵĿۿ���3456��ȥ��Ů�����", "|", SCW_OUT_NEWWORD));
//}
//
////SCW_OUT_BOOKNAME SCW_OUT_HUMANNAME
//TEST(test_seg_name, func)
//{
//	seg_init2();
//	Pval(segment2("�Ұ����й���ȥ�������ɲ鿴", "|", SCW_OUT_HUMANNAME));
//	Pval(segment2("������������ٶ����ɻ�ӭ��", "|", SCW_OUT_HUMANNAME));
//	seg_init();
//	Pval(segment("�Ұ����й���ȥ�������ɲ鿴", "|", SCW_OUT_HUMANNAME));
//	Pval(segment("�ҵĿۿ���3456��ȥ��Ů�����", "|", SCW_OUT_HUMANNAME));
//}
//
//
//TEST(test_seg_all, func)
//{//��basicһ��������
//	seg_init2();
//	Pval(segment2("�Ұ����й���ȥ�������ɲ鿴", "|", SCW_OUT_ALL));
//	Pval(segment2("������������ٶ����ɻ�ӭ��", "|", SCW_OUT_ALL));
//	seg_init();
//	Pval(segment("�Ұ����й���ȥ�������ɲ鿴", "|", SCW_OUT_ALL));
//	Pval(segment("�ҵĿۿ���3456��ȥ��Ů�����", "|", SCW_OUT_ALL));
//}
//
//TEST(other, func)
//{
//	seg_init();
//	SegHandle handle = segment_("�Ұ����й���ȥ�������ɲ鿴�ҵĿۿ���3456��ȥ��Ů�����");
//	for (int i = 0; i < handle.nresult; i++)
//	{
//		cout << handle.tokens[i].buffer << "\t" << handle.tokens[i].offset << "\t"
//			<< handle.tokens[i].weight << endl;
//	}
//}
//
//TEST(other_newword, func)
//{//--------offset ����Ի������ȵ�
//	seg_init();
//	/*SegHandle handle = segment_("�Ұ����й���ȥ�������ɲ鿴�ҵĿۿ���3456��ȥ��Ů�����", SCW_OUT_NEWWORD);*/
//	SegHandle handle = segment_("�Ұ����й��ۿ�����ȥ��Ů�����", SCW_OUT_NEWWORD);
//	for (int i = 0; i < handle.nresult; i++)
//	{
//		cout << handle.tokens[i].buffer << "\t" << handle.tokens[i].offset << "\t"
//			<< handle.tokens[i].weight << endl;
//	}
//
//	Pval(segment("�Ұ����й��ۿ�����ȥ��Ů�����", "|", SCW_OUT_BASIC));
//	Pval(segment("�Ұ����й��ۿ�����ȥ��Ů�����", "|", SCW_OUT_SUBPH));
//	Pval(segment("�Ұ����й��ۿ�����ȥ��Ů�����", "|", SCW_OUT_WPCOMP));
//	{
//		SegHandle handle = segment_("�Ұ����й��ۿ�����ȥ��Ů�����", SCW_OUT_SUBPH);
//		for (int i = 0; i < handle.nresult; i++)
//		{
//			cout << handle.tokens[i].buffer << "\t" << handle.tokens[i].offset << "\t"
//				<< handle.tokens[i].weight << endl;
//		}
//	}
//}

//TEST(final, func)
//{
//	Pval(segment("�Ұ����й��ۿ�����ȥ��Ů�����", "|", SCW_OUT_WPCOMP | SCW_OUT_NEWWORD));
//	Pval(segment("�ҵĿۿ�������������������Ƶ", "|", SCW_OUT_WPCOMP | SCW_OUT_SUBPH));
//	Pval(segment("�ҵĿۿ�������������������Ƶ", "|", SCW_OUT_NEWWORD));
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
	Pval(seg.segment("�Ұ����й��ۿ�����ȥ��Ů�����", "|", SCW_OUT_WPCOMP));

	Pval(seg.segment("�ҵĿۿ�������������������Ƶ", "|", SCW_OUT_WPCOMP));

	Pval(seg.segment("�ҵĿۿ�������������������Ƶ", "|", SEG_MERGE_NEWWORD));

	Pval(seg.set_flag(SCW_CRF).segment("�ҵĿۿ�������������������Ƶ", "|", SCW_OUT_WPCOMP | SCW_OUT_NEWWORD));

	Pval(seg.segment("�ҵĿۿ�������������������Ƶ", "|", SEG_MERGE_NEWWORD));

	Pval(seg.set_flag(0).segment("�ҵĿۿ�������������������Ƶ", "|", SEG_MERGE_NEWWORD));

	Pval(seg.segment("�ظ������°涷�Ʋ�񷴫�桿2014�����»𱬿��š����µ���������	����������ε�ҡ��ҡͷ", "|", SEG_MERGE_NEWWORD));

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
