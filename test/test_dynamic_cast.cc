/**
 *  ==============================================================================
 *
 *          \file   test_dynamic_cast.cc
 *
 *        \author   chenghuige
 *
 *          \date   2015-05-20 11:54:47.600521
 *
 *  \Description:
 *Instances of a polymorphic class store the dynamic type of their most derived object at runtime.

 (In your example a2 is of type pointer-to-A, and is pointing at an object of type A, however this object is only a base class subobject of the most dervived object of type B. What you want to get is the type of this most derived object B when querying a2. For this you need a polymorphic class.)

 That is how polymorphic classes support dynamic_cast and typeid of the most derived object (as well as virtual function dispatch).

 Non-polymorphic classes do not have this information, so they can only report the static type known at compile-time. Non-polymorphic classes are more compact and efficient then polymorphic classes. That is why not all C++ classes are polymorphic. The language leaves it up to the programmer to chose the tradeoff between performance and functionality. For example:

 struct X { int x; };
 struct Y : X {};
 struct Z : Y {};
 On my system non-polymorphic Z is sizeof(Z) == 4 bytes, same as an int.

 struct X { int x; virtual ~X() {}; };
 struct Y : X {};
 struct Z : Y {};
 Now after making Z polymorphic, sizeof(Z) == 16 bytes. So an array of Z is now 300% larger, because each Z instance has to store its type information at runtime.
 http://stackoverflow.com/questions/17204487/checking-the-object-type-in-c11
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
#include "common_util.h"

using namespace std;
using namespace gezi;
DEFINE_int32(vl, 5, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");


class ITrainer
{
public:
	virtual string Name() = 0; //如果没有virtual 就不算是polynomial 就没有办法使用dynamic了
};

class TrainerBase : public ITrainer
{

};

class IValidateTrainer
{
public:
	string Validate() 
	{
		return "validate";
	}
};


class FastRankTrainer : public TrainerBase, public IValidateTrainer
{
public:
	virtual string Name() override
	{
		return "fr";
	}
};

class SimpleTrainer : public TrainerBase
{
public:
	virtual string Name() override
	{
		return "st";
	}
};

TEST(dynamic_cast, func)
{

	shared_ptr<ITrainer> st = make_shared<SimpleTrainer>();
	shared_ptr<ITrainer> fr = make_shared<FastRankTrainer>();
	//Pval2(st->Name(), fr->Name());
	Pval((dynamic_pointer_cast<SimpleTrainer>(st) == nullptr));
	Pval((dynamic_pointer_cast<FastRankTrainer>(st) == nullptr));
	Pval((dynamic_pointer_cast<SimpleTrainer>(fr) == nullptr));
	Pval((dynamic_pointer_cast<FastRankTrainer>(fr) == nullptr));

	Pval((dynamic_pointer_cast<IValidateTrainer>(fr) == nullptr));
	Pval((dynamic_pointer_cast<IValidateTrainer>(st) == nullptr));
	Pval((dynamic_pointer_cast<IValidateTrainer>(fr)->Validate()));

	Pval((typeid(*st) == typeid(SimpleTrainer)));
	Pval((typeid(*fr) == typeid(IValidateTrainer)));  //注意这里 typeid 只能对最外层的type有效 
	Pval((typeid(*fr) == typeid(FastRankTrainer)));

	Pval(IS_POINTER_TYPE_OF(st, SimpleTrainer));
	//Pval(IS_TYPE_OF(*st, SimpleTrainer));    //not work
	//Pval(IS_TYPE_OF(*fr, IValidateTrainer));
	//Pval(IS_TYPE_OF(*fr, FastRankTrainer));
	Pval(IS_POINTER_TYPE_OF(st, SimpleTrainer));    
	Pval(IS_POINTER_TYPE_OF(st, IValidateTrainer));
	Pval(IS_POINTER_TYPE_OF(fr, IValidateTrainer));
	Pval(IS_POINTER_TYPE_OF(fr, FastRankTrainer));
	//SimpleTrainer a = dynamic_cast<SimpleTrainer>(*st);  //not work
	//test_dynamic_cast.cc:110 : 59 : error : cannot dynamic_cast '* st.std::shared_ptr<ITrainer>::<anonymous>.std::__shared_ptr<_Tp, _Lp>::get<ITrainer, (__gnu_cxx::_Lock_policy)2u>()' (of type 'class ITrainer') to type 'class SimpleTrainer' (target is not pointer or reference)

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
