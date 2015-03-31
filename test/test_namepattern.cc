/** 
 *  ==============================================================================
 * 
 *          \file   test_namepattern.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-03-15 14:15:22.461516
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "common_util.h"
#include "tools/uname_util.h"
#include "reg_util.h"
using namespace std;
using namespace gezi;
DEFINE_int32(level, 0, "min log level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

TEST(test_namepattern, func)
{
	string pattern = "[[\x81-\xff].q|^q|q[\x81-\xff]|qq|��|��|��].{0,6}([0-9]){7,30}";
	gezi::Timer t;
	Pval(reg_find("qΪ30457893", pattern));
	Pval(reg_find("q30457893", pattern));
	Pval(reg_find("��30356893", pattern));
	Pval(reg_find("��30356893", pattern));
	Pval(reg_find("abc30356893", pattern));
	Pval(reg_find("����32329984", pattern));
	Pval(t.elapsed_ms());

	Pval(name_pattern(""));
	Pval(name_pattern("�̻ݸ�"));
	Pval(name_pattern("��v������"));
	Pval(name_pattern("jordan"));
	Pval(name_pattern("��֮q364784386"));
	Pval(name_pattern("dsfokff16253"));
	Pval(name_pattern("ؼ���ɵ���"));
	Pval(name_pattern("ë��musicman"));
	Pval(name_pattern("��׿�ֻ�׬3��"));
	Pval(name_pattern("dr456rd"));
	Pval(name_pattern("332152391h"));
	Pval(name_pattern("Aeqkl_Rui"));
	Pval(name_pattern("loveһС��"));
	Pval(name_pattern("����������"));
	Pval(name_pattern("Ӳ����_С��"));
	Pval(name_pattern("8xuxu8dan"));
	Pval(name_pattern("��������AAA123"));
	Pval(name_pattern("LP����_����"));
}

TEST(test_namepattern2, func)
{
	Pval(simple_name_pattern("�̻ݸ�"));
	Pval(simple_name_pattern("jordan"));
	Pval(simple_name_pattern("��֮q364784386"));
	Pval(simple_name_pattern("dsfokff16253"));
	Pval(simple_name_pattern("ؼ���ɵ���"));
	Pval(simple_name_pattern("ë��musicman"));
	Pval(simple_name_pattern("��׿�ֻ�׬3��"));
	Pval(simple_name_pattern("dr456rd"));
	Pval(simple_name_pattern("332152391h"));
	Pval(simple_name_pattern("Aeqkl_Rui"));
	Pval(simple_name_pattern("loveһС��"));
	Pval(simple_name_pattern("����������"));
	Pval(simple_name_pattern("Ӳ����_С��"));
	Pval(simple_name_pattern("8xuxu8dan"));
	Pval(simple_name_pattern("��������AAA123"));
	Pval(simple_name_pattern("LP����_����"));
}

TEST(test_namepattern3, func)
{
		Pval(join(name_feature("�̻ݸ�")));
		Pval(join(name_feature("33443322")));
		Pval(join(name_feature("jordan")));
		Pval(join(name_feature("��֮q364784386")));
		Pval(join(name_feature("dsfokff16253")));
		Pval(join(name_feature("ؼ���ɵ���")));
		Pval(join(name_feature("ë��musicman")));
		Pval(join(name_feature("��׿�ֻ�׬3��")));
		Pval(join(name_feature("dr456rd")));
		Pval(join(name_feature("332152391h")));
		Pval(join(name_feature("Aeqkl_Rui")));
		Pval(join(name_feature("loveһС��")));
		Pval(join(name_feature("����������")));
		Pval(join(name_feature("Ӳ����_С��")));
		Pval(join(name_feature("8xuxu8dan")));
		Pval(join(name_feature("��������AAA123")));
		Pval(join(name_feature("LP����_����")));

		dvec vec = {0.1, 0.2, 0.3};
		double x = ufo::min(vec, 0);
		Pval(x);
		Pval((std::numeric_limits<double>::min()));
		Pval((-std::numeric_limits<double>::max()));
		Pval((std::numeric_limits<double>::lowest()));
		Pval((-std::numeric_limits<int>::lowest()));
		 std::cout << "Minimum value for int: " << std::numeric_limits<int>::min() << '\n';
		   std::cout << "Maximum value for int: " << std::numeric_limits<int>::max() << '\n';
			   std::cout << "int is signed: " << std::numeric_limits<int>::is_signed << '\n';
				   std::cout << "Non-sign bits in int: " << std::numeric_limits<int>::digits << '\n';
					   std::cout << "int has infinity: " << std::numeric_limits<int>::has_infinity << '\n';

		dvec vec2 = {1, 2, 3};
		std::transform(vec.begin(), vec.end(), vec2.begin(), vec2.end(),
			plus<double>());

		Pvec(vec);
		Pvec(vec2);
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
