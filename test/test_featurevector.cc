/**
 *  ==============================================================================
 *
 *          \file   test_featurevector.cc
 *
 *        \author   chenghuige
 *
 *          \date   2014-04-10 14:27:39.544342
 *
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "common_util.h"
#include "feature/Features.h"
using namespace std;
using namespace gezi;
DEFINE_int32(level, 0, "min log level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

TEST(featurevector, func)
{
	FeatureVector fv(5);
	fv.Add(1, 3);
	fv.Add(3, 4);
	Pval(fv[1]); // 3 or 4 ?
}


void show(Vector& fv)
{
	Pval(fv[1]);
}
TEST(featurevector2, func)
{
	{
		VectorPtr fv = make_shared<FeatureVector>(10);
		fv->Add(1, 3);
		fv->Add(3, 4);
		show(*fv);
	}
	{
		FeatureVectorPtr fv = make_shared<FeatureVector>(10);
		fv->Add(1, 3);
		fv->Add(3, 4);
		show(*fv);
	}
}


class AExtractor : public FeaturesExtractor
{
public:
	AExtractor(string name = "A")
		:FeaturesExtractor(name)
	{

	}

	virtual void extract() override
	{
		double value = 3.5;
		add(value, "first");
		add(value);
		std::array<double, 5> values = { 1, 2, 3, 4, 5 };
		add(values, "haha");
	}
};

class BExtractor : public FeaturesExtractor
{
public:
	BExtractor(string name = "B")
		:FeaturesExtractor(name)
	{

	}

	virtual void extract() override
	{
		double value = 3.5;
		add(value, "first");
		add(value);
		add(value + 1);
		std::array<double, 5> values = { 1, 2, 0, 0, 5 };
		add(values, "hahaha");

		add(&values[0], 5);
	}
};
TEST(extractor, func)
{
	Features fe;
	FeaturesExtractorMgr mgr;
	mgr.add(new AExtractor());
	mgr.add(new BExtractor());

	//如果有数据资源绑定需求 参考
	/* foreach(FeatureExtractor* fe, _mgr.extractors())
		{
		((AbstractExtractor*) fe)->bind_dao(_dao);
		}        */
	mgr.extract(fe);

	Pval(fe.str());
	Pvec(fe.Values());
	Pval(fe.Length());
	Pval(fe.IsDense());
	Pvec(fe.names());
}

#include "feature/FeatureExtractorMgr.h"
class CExtractor : public FeatureExtractor
{
public:
	CExtractor(string name = "C")
		:FeatureExtractor(name)
	{

	}

	virtual void extract() override
	{
		double value = 3.5;
		add(value, "first");
		add(value);
		dvec values = { 1, 2, 3, 4, 5 };
		add(values, "haha");
	}
};

TEST(extractor_old, func)
{
	Feature fe;
	FeatureExtractorMgr mgr;
	mgr.add(new CExtractor());
	mgr.extract(&fe);
	Pvec(fe.names());
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
