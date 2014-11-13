/**
 *  ==============================================================================
 *
 *          \file   IProcessor.h
 *
 *        \author   chenghuige
 *
 *          \date   2013-10-29 13:26:08.548268
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef IPROCESSOR_H_
#define IPROCESSOR_H_
#include <string>
#include <iostream>
namespace gezi {

using namespace std;

template<typename T>
class IProcessor
{
public:
    virtual T process(const T &) = 0;
    virtual ~IProcessor(){}
};

typedef IProcessor<string> IStringProcessor;


//---------------below are two examples
class SampleStringProcessor :public IStringProcessor
{
public:
  virtual ~SampleStringProcessor()
  {
    std::cout << "SampleString destruct" << endl;
  }
  virtual string process(string input) override
  {
    return "SampleStringProcessor " + input;
  }
};

class SampleStringProcessor2 :public IStringProcessor
{
public:
   virtual ~SampleStringProcessor2()
  {
    std::cout << "SampleStrings destruct" << endl;
  }
  virtual string process(string input) override
  {
    return "SampleStringProcessor2 " + input;
  }
};

}  //----end of namespace gezi


#endif  //----end of IPROCESSOR_H_

