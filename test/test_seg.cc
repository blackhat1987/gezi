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

//class Tester
//{
//public:
//	Segmentor _seg;
//};
TEST(segmentor_instance, func)
{
  Segmentor::init();
  {
    Segmentor seg; //确保handle clear在 Segmentor::uninit之前

    Pval(seg.segment("撸啊撸国产自拍", "|"));
    Pval(seg.segment("撸啊撸国产自拍", "|", SEG_MERGE_NEWWORD));

    Pval(seg.segment("《宫心计》很好看 朴兰姬是韩国啦啦队队员", "|", SEG_MERGE_NEWWORD));
    Pval(seg.segment("《宫心计》很好看 朴兰姬是韩国啦啦队队员", "|", SEG_WPCOMP));
    Pval(seg.segment("《宫心计》很好看 邹宏建是韩国啦啦队队员", "|", SEG_MERGE_NEWWORD));
    Pval(seg.segment("《宫心计》很好看 邹宏建是韩国啦啦队队员", "|"));

    Pval(seg.segment("朴姬兰", "|"));
    Pval(seg.segment("朴姬兰", "|", SEG_MERGE_NEWWORD));

    Pval(seg.segment("朴姬兰", "|", SEG_BASIC));
    Pval(seg.segment("刘亦菲", "|", SEG_BASIC));
    Pval(seg.segment("刘亦菲是女演员", "|", SEG_BASIC));
    Pval(seg.segment("郭美美", "|", SEG_BASIC));

    Pval(seg.segment("飞机降落伞$*$飞机降落伞图片", "|"));

    Pval(seg.segment("今野杏南大尺度", "|"));
    Pval(seg.segment("今野杏南大尺度", "|", SEG_MERGE_NEWWORD));

    Pval(seg.segment("张筱雨大胆裸露", "|"));
    Pval(seg.segment("张筱雨大胆裸露", "|", SEG_MERGE_NEWWORD));

    Pval(seg.segment("我爱你中国扣扣是速去美女激晴吧", "|", SCW_OUT_WPCOMP));

    Pval(seg.segment("我的扣扣是马布里杨美美基晴视频", "|", SCW_OUT_WPCOMP));

    Pval(seg.segment("我的扣扣是马布里杨美美基晴视频", "|", SEG_MERGE_NEWWORD));

    Pval(seg.set_flag(SCW_CRF).segment("我的扣扣是马布里杨美美基晴视频", "|", SCW_OUT_WPCOMP | SCW_OUT_NEWWORD));

    Pval(seg.segment("我的扣扣是马布里杨美美基晴视频", "|", SEG_MERGE_NEWWORD));

    Pval(seg.set_flag(0).segment("我的扣扣是马布里杨美美基晴视频", "|", SEG_MERGE_NEWWORD));

    Pval(seg.segment("回复：【新版斗破苍穹传奇】2014年最新火爆开放◆数月调试震撼上演	萧炎这才无奈的摇了摇头", "|", SEG_MERGE_NEWWORD));
    Pval(seg.segment("《宫心计》很好看 朴兰姬是韩国啦啦队队员", "|", SEG_MERGE_NEWWORD));
    Pval(seg.segment("《宫心计》很好看 朴兰姬是韩国啦啦队队员", "|", SEG_WPCOMP));
    Pval(seg.segment("《宫心计》很好看 邹宏建是韩国啦啦队队员", "|", SEG_MERGE_NEWWORD));
    Pval(seg.segment("《宫心计》很好看 邹宏建是韩国啦啦队队员", "|"));
  }
  Segmentor::uninit();
  //Tester tester;
}

//TEST(segmentor_thread_local, func)
//{
//	Segmentor::Init();
//	Pval(Segmentor::Segment("我爱你中国扣扣是速去美女激晴吧", "|", SCW_OUT_WPCOMP));
//	Pval(Segmentor::Segment("我的扣扣是马布里杨美美基晴视频", "|", SEG_MERGE_NEWWORD));
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
  Pval((basic_map.find("奇艺") == basic_map.end()));
  Pval((basic_map.find("abdfasdfdsf") == basic_map.end()));
  Pval(get_value(basic_map, "奇艺网", 200.));
  Pval(get_value(basic_map, "奇艺", 200.));
  
  auto ner_map = Segmentor::NerWordRankMap();
  Pval(get_value(ner_map, "西木野真姬", 100.));
  Pval(get_value(ner_map, "矢泽妮可", 100.));
  Pval(get_value(ner_map, "奇艺网", 100.));
  Pval(get_value(ner_map, "奇艺", 100.));
  Pval(get_value(ner_map, "2014年", 100.));
  Pval(get_value(ner_map, "宫崎骏", 100.));
  Pval(get_value(ner_map, "宫崎", 100.));
  Pval(get_value(ner_map, "市第一中学", 100.));
  Pval(get_value(ner_map, "河北省沧州市第一中学", 100.));
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
    //Segmentor::Init(); //注意需要每个线程都init handle
    Pval2(j, Segmentor::Segment("我的扣扣是马布里杨美美基晴视频", "|"));
    Pval2(j, Segmentor::Segment("我的扣扣是", "|"));
    Pval2(j, Segmentor::Segment("我的扣扣是马布里", "|"));
  }

#pragma omp parallel for
  for (size_t j = 0; j < 10; j++)
  {
    //Segmentor::Init(); //注意需要每个线程都init handle
    Pval2(j, Segmentor::Segment("我的扣扣是马布里杨美美基晴视频", "|"));
  }
#pragma omp parallel for
  for (size_t j = 0; j < 10; j++)
  {
    //Segmentor::Init(); //注意需要每个线程都init handle
    Pval2(j, Segmentor::Segment("这是怎么回事", "|"));
  }


  Pval(Segmentor::Segment("我爱你中国扣扣是速去美女激晴吧", "|", SCW_OUT_WPCOMP));
  print_seg_posttag_result(Segmentor::handle());

  Pval(Segmentor::Segment("我的扣扣是马布里杨美美基晴视频", "|", SEG_MERGE_NEWWORD));
  print_seg_posttag_result(Segmentor::handle());

  Pval(Segmentor::Segment("我的扣扣是马布里杨美美基晴视频你好", "|", SEG_MERGE_NEWWORD));
  print_seg_posttag_result(Segmentor::handle());

  string text = "奇艺网有金陵十三钗吗？ ";
  seg_text(text);

  text = "西木野真姬与矢泽妮可是日本漫画全职高手中的人物是宫崎骏2014年创作";
  seg_text(text);


  text = "西木野真姬与矢泽妮可怎么都是好人";
  seg_text(text);

  text = "河北省沧州市第一中学怎么样";
  seg_text(text);

  Segmentor::Uninit();
}


//// FIXME Segmentor:: Reuse same not ok uni_interface.cpp:346:scw_segment_words(): error: pdict or inbuf or pout or pgconf is NULL or inlen < 0
//TEST(segmentor_wordner, func)
//{
//  Segmentor::SetStrategy(SEG_USE_POSTAG);
//  //Segmentor::AddStrategy(SEG_USE_WORDNER);
//  Segmentor::Init();
//  Pval(Segmentor::Segment("我爱你中国扣扣是速去美女激晴吧", "|", SCW_OUT_WPCOMP));
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
