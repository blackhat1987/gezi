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

//class Tester
//{
//public:
//	Segmentor _seg;
//};
TEST(segmentor_instance, func)
{
  Segmentor::init();
  {
    Segmentor seg; //ȷ��handle clear�� Segmentor::uninit֮ǰ

    Pval(seg.segment("ߣ��ߣ��������", "|"));
    Pval(seg.segment("ߣ��ߣ��������", "|", SEG_MERGE_NEWWORD));

    Pval(seg.segment("�����ļơ��ܺÿ� �������Ǻ��������Ӷ�Ա", "|", SEG_MERGE_NEWWORD));
    Pval(seg.segment("�����ļơ��ܺÿ� �������Ǻ��������Ӷ�Ա", "|", SEG_WPCOMP));
    Pval(seg.segment("�����ļơ��ܺÿ� �޺꽨�Ǻ��������Ӷ�Ա", "|", SEG_MERGE_NEWWORD));
    Pval(seg.segment("�����ļơ��ܺÿ� �޺꽨�Ǻ��������Ӷ�Ա", "|"));

    Pval(seg.segment("�Ӽ���", "|"));
    Pval(seg.segment("�Ӽ���", "|", SEG_MERGE_NEWWORD));

    Pval(seg.segment("�Ӽ���", "|", SEG_BASIC));
    Pval(seg.segment("�����", "|", SEG_BASIC));
    Pval(seg.segment("�������Ů��Ա", "|", SEG_BASIC));
    Pval(seg.segment("������", "|", SEG_BASIC));

    Pval(seg.segment("�ɻ�����ɡ$*$�ɻ�����ɡͼƬ", "|"));

    Pval(seg.segment("��Ұ���ϴ�߶�", "|"));
    Pval(seg.segment("��Ұ���ϴ�߶�", "|", SEG_MERGE_NEWWORD));

    Pval(seg.segment("���������¶", "|"));
    Pval(seg.segment("���������¶", "|", SEG_MERGE_NEWWORD));

    Pval(seg.segment("�Ұ����й��ۿ�����ȥ��Ů�����", "|", SCW_OUT_WPCOMP));

    Pval(seg.segment("�ҵĿۿ�������������������Ƶ", "|", SCW_OUT_WPCOMP));

    Pval(seg.segment("�ҵĿۿ�������������������Ƶ", "|", SEG_MERGE_NEWWORD));

    Pval(seg.set_flag(SCW_CRF).segment("�ҵĿۿ�������������������Ƶ", "|", SCW_OUT_WPCOMP | SCW_OUT_NEWWORD));

    Pval(seg.segment("�ҵĿۿ�������������������Ƶ", "|", SEG_MERGE_NEWWORD));

    Pval(seg.set_flag(0).segment("�ҵĿۿ�������������������Ƶ", "|", SEG_MERGE_NEWWORD));

    Pval(seg.segment("�ظ������°涷�Ʋ�񷴫�桿2014�����»𱬿��š����µ���������	����������ε�ҡ��ҡͷ", "|", SEG_MERGE_NEWWORD));
    Pval(seg.segment("�����ļơ��ܺÿ� �������Ǻ��������Ӷ�Ա", "|", SEG_MERGE_NEWWORD));
    Pval(seg.segment("�����ļơ��ܺÿ� �������Ǻ��������Ӷ�Ա", "|", SEG_WPCOMP));
    Pval(seg.segment("�����ļơ��ܺÿ� �޺꽨�Ǻ��������Ӷ�Ա", "|", SEG_MERGE_NEWWORD));
    Pval(seg.segment("�����ļơ��ܺÿ� �޺꽨�Ǻ��������Ӷ�Ա", "|"));
  }
  Segmentor::uninit();
  //Tester tester;
}

//TEST(segmentor_thread_local, func)
//{
//	Segmentor::Init();
//	Pval(Segmentor::Segment("�Ұ����й��ۿ�����ȥ��Ů�����", "|", SCW_OUT_WPCOMP));
//	Pval(Segmentor::Segment("�ҵĿۿ�������������������Ƶ", "|", SEG_MERGE_NEWWORD));
//	Segmentor::Uninit();
//}

void print_score(string text)
{
  LOG(INFO) << "print score";
  auto scores = Segmentor::WordRank();
  //Segmentor::NerTag();
  auto ner_scores = Segmentor::NerWordRank();
  const auto& handle = Segmentor::handle();
  for (int i = 0; i < handle.nresult; i++)
  {
    Pval4(handle.word(i), scores[i], handle.offset(i), handle.length(i));
  }

  auto ner_nodes = Segmentor::GetNerNodes();
  for (size_t i = 0; i < ner_nodes.size(); i++)
  {
    Pval2(ner_nodes[i].word, ner_scores[i]);
  }
  print_ner_result(text, Segmentor::handle(), Segmentor::ner_handle());

  auto basic_map = Segmentor::WordRankMap();
  Pval(basic_map.size());
  for (auto& item : basic_map)
  {
    Pval2(item.first, item.second);
  }
  Pval((basic_map.find("����") == basic_map.end()));
  Pval((basic_map.find("abdfasdfdsf") == basic_map.end()));
  Pval(get_value(basic_map, "������", 200.));
  Pval(get_value(basic_map, "����", 200.));
  
  auto ner_map = Segmentor::NerWordRankMap();
  Pval(get_value(ner_map, "��ľҰ�漧", 100.));
  Pval(get_value(ner_map, "ʸ���ݿ�", 100.));
  Pval(get_value(ner_map, "������", 100.));
  Pval(get_value(ner_map, "����", 100.));
  Pval(get_value(ner_map, "2014��", 100.));
  Pval(get_value(ner_map, "���鿥", 100.));
  Pval(get_value(ner_map, "����", 100.));
  Pval(get_value(ner_map, "�е�һ��ѧ", 100.));
  Pval(get_value(ner_map, "�ӱ�ʡ�����е�һ��ѧ", 100.));
}

void seg_text(string text)
{
  Pval(text);
  Pval(Segmentor::Segment(text, "|", SEG_BASIC));
  print_ner_result(text, Segmentor::handle(), Segmentor::ner_handle());
  print_seg_posttag_result(Segmentor::handle());
  print_score(text);

  Pval(Segmentor::Segment(text, "|"));
  print_ner_result(text, Segmentor::handle(), Segmentor::ner_handle());
  print_seg_posttag_result(Segmentor::handle());
  print_score(text);

  //Pval(Segmentor::Segment(text, "|", SEG_MERGE_NEWWORD));
  //print_ner_result(text, Segmentor::handle(), Segmentor::ner_handle());
  //print_seg_posttag_result(Segmentor::handle());
  //print_score();
  Segmentor::GetTokens(SEG_BASIC);
  const auto& handle = Segmentor::handle();
  for (int i = 0; i < handle.nresult; i++)
  {
    Pval3(handle.word(i), handle.offset(i), handle.length(i));
  }
  Segmentor::NerTag();
  print_ner_result(text, Segmentor::handle(), Segmentor::ner_handle());
}

TEST(segmentor_postag, func)
{
  Segmentor::SetStrategy(SEG_USE_POSTAG);
  Segmentor::AddStrategy(SEG_USE_WORDNER_AUTO);
  //Segmentor::AddStrategy(SEG_USE_WORDNER);
  //Segmentor::AddStrategy(SEG_USE_OFFSETS);
  Segmentor::AddStrategy(SEG_USE_WORDRANK);
  Segmentor::Init();

  LOG(INFO) << "Begin multi thread";
#pragma omp parallel for
  for (size_t j = 0; j < 100; j++)
  {
    //Segmentor::Init(); //ע����Ҫÿ���̶߳�init handle
    Pval2(j, Segmentor::Segment("�ҵĿۿ�������������������Ƶ", "|"));
    Pval2(j, Segmentor::Segment("�ҵĿۿ���", "|"));
    Pval2(j, Segmentor::Segment("�ҵĿۿ�������", "|"));
  }

#pragma omp parallel for
  for (size_t j = 0; j < 10; j++)
  {
    //Segmentor::Init(); //ע����Ҫÿ���̶߳�init handle
    Pval2(j, Segmentor::Segment("�ҵĿۿ�������������������Ƶ", "|"));
  }
#pragma omp parallel for
  for (size_t j = 0; j < 10; j++)
  {
    //Segmentor::Init(); //ע����Ҫÿ���̶߳�init handle
    Pval2(j, Segmentor::Segment("������ô����", "|"));
  }


  Pval(Segmentor::Segment("�Ұ����й��ۿ�����ȥ��Ů�����", "|", SCW_OUT_WPCOMP));
  print_seg_posttag_result(Segmentor::handle());

  Pval(Segmentor::Segment("�ҵĿۿ�������������������Ƶ", "|", SEG_MERGE_NEWWORD));
  print_seg_posttag_result(Segmentor::handle());

  Pval(Segmentor::Segment("�ҵĿۿ�������������������Ƶ���", "|", SEG_MERGE_NEWWORD));
  print_seg_posttag_result(Segmentor::handle());

  string text = "�������н���ʮ������ ";
  seg_text(text);

  text = "��ľҰ�漧��ʸ���ݿ����ձ�����ȫְ�����е������ǹ��鿥2014�괴��";
  seg_text(text);


  text = "��ľҰ�漧��ʸ���ݿ���ô���Ǻ���";
  seg_text(text);

  text = "�ӱ�ʡ�����е�һ��ѧ��ô��";
  seg_text(text);

  Segmentor::Uninit();
}


//// FIXME Segmentor:: Reuse same not ok uni_interface.cpp:346:scw_segment_words(): error: pdict or inbuf or pout or pgconf is NULL or inlen < 0
//TEST(segmentor_wordner, func)
//{
//  Segmentor::SetStrategy(SEG_USE_POSTAG);
//  //Segmentor::AddStrategy(SEG_USE_WORDNER);
//  Segmentor::Init();
//  Pval(Segmentor::Segment("�Ұ����й��ۿ�����ȥ��Ů�����", "|", SCW_OUT_WPCOMP));
//  print_seg_posttag_result(Segmentor::handle());
//}

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
