/** 
 *  ==============================================================================
 * 
 *          \file   test_escape.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2013-12-29 08:58:04.454086
 *  
 *  \Description:   实际上线后发现compack json formatter 个别转换失败 escape不好 例如
 * "rank": {
                        "http://bbs.meizu.cn/viewthread.php?tid=4407283&highlight=鎸夐敭鏁戞槦涓撲笟鐗": "3.960000"
                    }
 * WARNING: 12-29 08:52:35:  tieba_urate * 6157 [InputParser.h:409:getHistory]: * Line 1, Column 4527
 [:{"rank":{"http://bbs.meizu.cn/viewthread.php?tid=4407283&highlight=鎸夐敭鏁戞槦涓撲笟鐗:"
3.960000"}},"adFeature":"[{\"key\":\"trateThread\",\"value\":null},{\"key\":\"tratePost\",\"value\":] 
  Missing ':' after object member name

 * "taginfo": "?四川\u0002德阳\u0002绵竹市\u0001佀拇\u0002德阳\u0002绵竹市\u0001\u0001儭端?按?\u0002《穷爸爸和富爸爸》\u0001?一生一世\"\u0001吘倨鹗掷\u0001喤懿\u0001嚽厥蓟视?\u0001埡炔枇奶\u0001壘拍镣\u0001娢蠢闯缺ね?缈萍加邢薰?\u0001\u0001\u0001\u0001\u0001",
 *  转换也是有问题 出现未传意处理的“
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
  test("http://bbs.meizu.cn/viewthread.php?tid=4407283&highlight=鎸夐敭鏁戞槦涓撲笟鐗");

  test("德阳\\u0002绵竹市\\u0001\\u0001儭端?按?\\u0002《穷爸爸和富爸爸》\\u0001?一生一世\"\\u0001吘倨鹗掷");
  
  test("?广东广州海珠区伖愣广州越秀区<<三国演义>>\"三寸天堂”  “荷塘月色”  “最炫民族风”叀凹偬焓埂\"张居正”埜智墶爸泄ā幣嗾");
  
  test("?北京顺义区伇本顺义区儭独剂赙月摇《醉玲珑》\"如果我变成回忆\\\"\\\"爱你爱到不怕死\\\"\\\"棉花糖\\\"\\\"旅程\\\"\\\"第三者的第三者\\\"\\\"下雨天\\\"Nobody等等吥汗庵黑执事我的帅管家东京猫猫队守护甜心等等喫足球篮球羽毛球嚥桃懒刘谦埪糜跳舞唱歌拍照壈傧啥喔Mix-box阿yaya尡本┦兴骋迩＠干降谝恢醒");

  test("?河北唐山遵化市伜颖唐山遵化市儭度菀濉\"别说我的眼泪你无所谓");
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
