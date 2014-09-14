/** 
 *  ==============================================================================
 * 
 *          \file   test_content_process.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-09-01 21:06:30.280730
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
#include "common_util.h"
#include "tools/content_process.h"

using namespace std;
using namespace gezi;
DEFINE_int32(vl, 0, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");


void test(string content)
{
	Pval(content);
	Pval(strip_html(content));
	Pval(strip_from(content));
	Pval(contains_url(content));
	Pval(contains_at(content));
	Pval(contains_pic(content));
	Pval(contains_num(content));
	Pvec(get_urls(content));
}
TEST(content_process, func)
{
	test("约咆圣网：<a href=\"http://nazr.in/Dqi\" target=\"_blank\">http://nazr.in/Dqi</a>");
	test("没睡的深夜拿黑利。－、、、<a href=\"http://50r.cn/M66mJU\" target=\"_blank\">http://50r.cn/M66mJU</a>");
	test("速度看这→<a href=\"http://tieba.baidu.com/i/sys/jump?un=BLack%CB%C0%CD%F6%D0%FD%C2%C9\" onclick=\"Stats.sendRequest('fr=tb0_forum&st_mod=pb&st_value=atlink');\" onmouseover=\"showattip(this)\" onmouseout=\"hideattip(this)\" username=\"BLack%CB%C0%CD%F6%D0%FD%C2%C9\" target=\"_blank\" class=\"at\">@BLack死亡旋律</a> 的075帖&子有方\"式");
	string content = "吴亦凡cut(禁二传）E02<div class=\"video_src_wrapper\"><embed allowfullscreen=\"true\" pluginspage=\"http://www.macromedia.com/go/getflashplayer\" type=\"application/x-shockwave-flash\" wmode=\"transparent\" play=\"true\" loop=\"false\" menu=\"false\" allowscriptaccess=\"never\" scale=\"noborder\" src=\"http://player.youku.com/player.php/sid/XNzYxMDIxOTU2/v.swf\" class=\"BDE_Flash\" width=\"500\" height=\"450\" vsrc=\"http://v.youku.com/v_show/id_XNzYxMDIxOTU2.html?from=y1.2-1-85.3.8-1.1-1-1-7\" vpic=\"http://g4.ykimg.com/0100641F4653F9EA95DA2D1779C0309D5A966D-B8FB-D45A-8D72-A457E6337E4E\" pkey=\"8e6eea06c931a6b1df3d5a86dba0e394\"><span class=\"apc_src_wrapper\">视频来自：<a href=\"http://v.youku.com/v_show/id_XNzYxMDIxOTU2.html?from=y1.2-1-85.3.8-1.1-1-1-7\" target=\"_blank\">优酷</a></span></div>";
	test(content);
	test(strip_from(content));
	test("~/游^-//戏//^==/入//=^/口：<br><br><br>https:// ## <a href=\"http://AISGLM.KADR.MD##FGSDF\" target=\"_blank\">http://AISGLM.KADR.MD##FGSDF</a>");
	test("<img class = \"BDE_Image\" pic_type=\"1\" width=\"560\" height=\"413\" src=\"http://imgsrc.baidu.com/forum/pic/item/76436b87e950352a9bb173185043fbf2b3118b7a.jpg\" pic_ext=\"jpeg\"  >");
}

void test_num(string content)
{
	Pval(content);
	Pval(contains_num(content));
	Pvec(get_nums(content)); 
}

TEST(num, func)
{
	test_num("abcd efg");
	test_num("29109317 在哪里");
	test_num("我q29109317");
	test_num("29109317@qq.com 楼主.加油.哈哈");
	test_num("abc@qq.com 嘻嘻");
}

void test_email(string content)
{
	Pval(content);
	Pval(contains_emails(content));
	Pvec(get_emails(content));
}

TEST(email, func)
{
	test_email("29109317@qq.com楼主好人");
	test_email("感谢楼主 chenghuige@gmail.com");
	test_email("邮箱 chenghuige@pku.edu.cn");
}

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	google::InitGoogleLogging(argv[0]);
	google::InstallFailureSignalHandler();
	int s = google::ParseCommandLineFlags(&argc, &argv, false);
	if (FLAGS_log_dir.empty())
		FLAGS_logtostderr = true;
	if (FLAGS_v == 0)
		FLAGS_v = FLAGS_vl;
	
	return RUN_ALL_TESTS();
}
