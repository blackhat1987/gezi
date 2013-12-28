/** 
 *  ==============================================================================
 * 
 *          \file   test_json.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2013-12-28 15:00:19.003348
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "common_util.h"
#include "json/json.h"
using namespace std;
using namespace gezi;
DEFINE_int32(level, 0, "min log level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

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

TEST(test_json, func)
{
  {
    string content = read_file("./test.data/json/test.json.txt");
    Pval(content);
    Json::Reader reader;
    Json::Value root;
    {
      Pval(reader.parse(content, root));
      Pval(root["likeInfo"][0]["forum_name"]);
      Pval(root["userInfo"]["user_name"]);
      Pval(root["userInfo"]["user_name"].asString());
    }
    {
      content = to_utf8(content);
      Pval(reader.parse(content, root));
      Pval(to_gbk(root["likeInfo"][0]["forum_name"].asString()));
      Pval(to_gbk(root["userInfo"]["user_name"].asString()));
      //    Pval(to_gbk(root["likeInfo"]["user_name"].asString()));
    }
  }
  {
    string content = read_file(FLAGS_i);
    Pval(content);
    Json::Reader reader;
    Json::Value root;
    {
      Pval(reader.parse(content, root));
      Pval(root["likeInfo"][0]["forum_name"]);
      Pval(root["userInfo"]["user_name"]);
      Pval(root["userInfo"]["user_name"].asString());
      Json::Value val = root["userInfo"]["puserinfo"];
      Pval(val["sex"]);
      Pval(val["taginfo"]);
      Pval(val["userdetail"]);
    }
    {
      content = to_utf8(content);
      Pval(reader.parse(content, root));
      Pval(to_gbk(root["likeInfo"][0]["forum_name"].asString()));
      Pval(to_gbk(root["userInfo"]["user_name"].asString()));
      Json::Value val = root["userInfo"]["puserinfo"];
      Pval(val["sex"]);
      Pval(val["taginfo"]);
      Pval(val["userdetail"]);
      Pval(reader.getFormattedErrorMessages());
      //    Pval(to_gbk(root["likeInfo"]["user_name"].asString()));
    }
  }

  {
    string content = read_file(FLAGS_i);
    content = filter(content);
    Pval(content);
    Json::Reader reader;
    Json::Value root;
    {
      Pval(reader.parse(content, root));
      Pval(root["likeInfo"][0]["forum_name"]);
      Pval(root["userInfo"]["user_name"]);
      Pval(root["userInfo"]["user_name"].asString());
      Json::Value val = root["userInfo"]["puserinfo"];
      Pval(val["sex"]);
      Pval(val["taginfo"]);
      Pval(val["userdetail"]);
    }
    {
      content = to_utf8(content);
      Pval(reader.parse(content, root));
      Pval(to_gbk(root["likeInfo"][0]["forum_name"].asString()));
      Pval(to_gbk(root["userInfo"]["user_name"].asString()));
      Json::Value val = root["userInfo"]["puserinfo"];
      Pval(val["sex"]);
      Pval(val["taginfo"]);
      Pval(val["userdetail"]);
      Pval(reader.getFormattedErrorMessages());
      Pval(val["userdetail2"].asString());
      Pval(val["userdetail2"].asString().size());
      Pval(val["birthday_day"]);
      Pval(val["birthday_day"].asString());
      //    Pval(to_gbk(root["likeInfo"]["user_name"].asString()));
    }
  }
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
