/**
 *  ==============================================================================
 *
 *          \file   exp_template.cc
 *
 *        \author   chenghuige
 *
 *          \date   2015-05-12 14:49:21.402584
 *
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "common_util.h"

using namespace std;
using namespace gezi;

DEFINE_int32(vl, 0, "vlog level");
DEFINE_int32(level, 0, "min log level");
DEFINE_string(type, "simple", "");
DEFINE_bool(perf, false, "");
DEFINE_int32(num, 1, "");
DEFINE_string(i, "", "input file");
DEFINE_string(o, "", "output file");

// this is expression, all expressions must inheritate it,
//  and put their type in subtype
template<typename SubType>
struct Exp {
	// returns const reference of the actual type of this expression
	inline const SubType& self(void) const {
		return *static_cast<const SubType*>(this);
	}
};

// binary add expression
// note how it is inheritates from Exp
// and put its own type into the template argument
template<typename TLhs, typename TRhs>
struct BinaryAddExp : public Exp<BinaryAddExp<TLhs, TRhs> > {
	const TLhs &lhs;
	const TRhs &rhs;
	BinaryAddExp(const TLhs& lhs, const TRhs& rhs)
		: lhs(lhs), rhs(rhs) {}
	// evaluation function, evaluate this expression at position i
	inline float Eval(int i) const {
		return lhs.Eval(i) + rhs.Eval(i);
	}

	inline size_t size()
	{
		return lhs.size();
	}
};

class Vec : public Exp<Vec>
{
public:
	Vec(int len)
	{
		data.resize(len, 0);
		Pval(&data[0]);
	}
	Vec()
	{
		LOG(INFO) << "Default construct";
	}
	~Vec()
	{
		LOG(INFO) << "Destruct";
	}
	Vec(const initializer_list<int>& il)
		:data(il)
	{

	}

	inline size_t size()
	{
		return data.size();
	}

	template<typename EType>
	Vec(const Exp<EType>& src_)
	{
		*this = src_;
	}
	// here is where evaluation happens
	template<typename EType>
	inline Vec& operator= (const Exp<EType>& src_) {
		const EType &src = src_.self();
		Pval(src.size());
		data.resize(src.size());
		for (size_t i = 0; i < src.size(); ++i) {
			data[i] = src.Eval(i);
		}
		return *this;
	}
	// evaluation function, evaluate this expression at position i
	inline int Eval(int i) const {
		return data[i];
	}

	vector<int> data;
};


// template add, works for any expressions
template<typename TLhs, typename TRhs>
inline BinaryAddExp<TLhs, TRhs> operator+(const Exp<TLhs> &lhs, const Exp<TRhs> &rhs)
{
	return BinaryAddExp<TLhs, TRhs>(lhs.self(), rhs.self());
}


void run()
{
	Vec b{ 3, 2, 1 }, c{ 2, 3, 4 }, d{ 123, 45, 30 };
	Vec a = b + c + d;
	Pvec(a.data);
}

int main(int argc, char *argv[])
{
	google::InitGoogleLogging(argv[0]);
	google::InstallFailureSignalHandler();
	int s = google::ParseCommandLineFlags(&argc, &argv, false);
	if (FLAGS_log_dir.empty())
		FLAGS_logtostderr = true;
	FLAGS_minloglevel = FLAGS_level;
	//LogHelper::set_level(FLAGS_level);
	if (FLAGS_v == 0)
		FLAGS_v = FLAGS_vl;

	run();

	return 0;
}
