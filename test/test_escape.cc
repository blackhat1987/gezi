/** 
 *  ==============================================================================
 * 
 *          \file   test_escape.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2013-12-29 08:58:04.454086
 *  
 *  \Description:   ʵ�����ߺ���compack json formatter ����ת��ʧ�� escape���� ����
 * "rank": {
                        "http://bbs.meizu.cn/viewthread.php?tid=4407283&highlight=按键救星专业�": "3.960000"
                    }
 * WARNING: 12-29 08:52:35:  tieba_urate * 6157 [InputParser.h:409:getHistory]: * Line 1, Column 4527
 [:{"rank":{"http://bbs.meizu.cn/viewthread.php?tid=4407283&highlight=按键救星专业�:"
3.960000"}},"adFeature":"[{\"key\":\"trateThread\",\"value\":null},{\"key\":\"tratePost\",\"value\":] 
  Missing ':' after object member name

 * "taginfo": "?�Ĵ�\u0002����\u0002������\u0001��Ĵ\u0002����\u0002������\u0001\u0001����?��?\u0002����ְֺ͸��ְ֡�\u0001?һ��һ��\"\u0001��������\u0001��ܲ\u0001���ʼ���?\u0001��Ȳ����\u0001������\u0001�δ���ȱ��?�Ƽ����޹?\u0001\u0001\u0001\u0001\u0001",
 *  ת��Ҳ�������� ����δ���⴦��ġ�
 * public/idlcompiler/compack/jsonformatter.h
 *  ==============================================================================
 */

#define private public
#define protected public
#include "common_util.h"

using namespace std;
using namespace gezi;
DEFINE_int32(level, 0, "min log level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");
std::vector<char> _escape_buf;
bool _encoding = true;

void escape(const char* value)
{
  _escape_buf.clear();
  _escape_buf.push_back('\"');
  while (true)
  {
    switch (*value) {
      case '\0':
        _escape_buf.push_back('\"');
        _escape_buf.push_back(0);
        return;
      case '\n':
        _escape_buf.push_back('\\');
        _escape_buf.push_back('n');
        break;
      case '\r':
        _escape_buf.push_back('\\');
        _escape_buf.push_back('r');
        break;
      case '\t':
        _escape_buf.push_back('\\');
        _escape_buf.push_back('t');
        break;
      case '\b':
        _escape_buf.push_back('\\');
        _escape_buf.push_back('b');
        break;
      case '\f':
        _escape_buf.push_back('\\');
        _escape_buf.push_back('f');
        break;
      case '"':
        _escape_buf.push_back('\\');
        _escape_buf.push_back('"');
        break;
      case '\\':
        _escape_buf.push_back('\\');
        _escape_buf.push_back('\\');
        break;
      default:
        if (_encoding && *value < 0)
        {
          _escape_buf.push_back(*value++);
          _escape_buf.push_back(*value);
        }
        else
        {
          _escape_buf.push_back(*value);
        }
    }
    value++;
  }
}
string filter(string input)
{
  //\u0001" \u002"
  string pre_input;
  do
  {
    pre_input = input;
    boost::replace_all(input, "\",", "\",");
  }
  while (input.length() != pre_input.length());
  do
  {
    pre_input = input;
    boost::replace_all(input, "\",", "\",");
  }
  while (input.length() != pre_input.length());
  do
  {
    pre_input = input;
    boost::replace_all(input, "\"}", "\"}");
  }
  while (input.length() != pre_input.length());
  do
  {
    pre_input = input;
    boost::replace_all(input, "\"}", "\"}");
  }
  while (input.length() != pre_input.length());
  do
  {
    pre_input = input;
    boost::replace_all(input, "\"]", "\"]");
  }
  while (input.length() != pre_input.length());
  do
  {
    pre_input = input;
    boost::replace_all(input, "\"]", "\"]");
  }
  while (input.length() != pre_input.length());

  boost::erase_all(input, "\"");
  boost::erase_all(input, "\"");
  boost::erase_all(input, "");
  boost::erase_all(input, "");
  return input;
}
void test(string input)
{
  Pval(input);
  input = filter(input);
  Pval(input);
  escape(input.c_str());
  string s(&_escape_buf[0]);
  Pval(s);
}

TEST(test_escape, func)
{
  test("http://bbs.meizu.cn/viewthread.php?tid=4407283&highlight=按键救星专业�");

  test("����\\u0002������\\u0001\\u0001����?��?\\u0002����ְֺ͸��ְ֡�\\u0001?һ��һ��\"\\u0001��������");
  
  test("?�㶫�����������������Խ����<<��������>>\"�������á�  ��������ɫ��  ����������硱�������ʹ�\"�ž�������������й������");
  
  test("?����˳��������˳��������������ҡ�������硷\"����ұ�ɻ���\\\"\\\"���㰮��������\\\"\\\"�޻���\\\"\\\"�ó�\\\"\\\"�����ߵĵ�����\\\"\\\"������\\\"Nobody�ȵ��ĺ�����ִ���ҵ�˧�ܼ�����èè���ػ������ȵ�������������ë����������ǫ��������������������ɶ�Mix-box��yaya�������˳��ǣ��ɽ��һ���");

  test("?�ӱ���ɽ������ӱ��ɽ�����������\"��˵�ҵ�����������ν");
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
