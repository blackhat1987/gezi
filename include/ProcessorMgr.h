/**
 *  ==============================================================================
 *
 *          \file   ProcessorMgr.h
 *
 *        \author   chenghuige
 *
 *          \date   2013-10-29 15:32:55.578543
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef PROCESSORMGR_H_
#define PROCESSORMGR_H_
#include "IProcessor.h"
#include "ProcessorMgr.h"
#include <vector>
namespace gezi
{
using namespace std;

template<typename T>
class ProcessorMgr
{
public:
  typedef IProcessor<T> Processor;
  virtual ~ProcessorMgr()
  {
    for (int i = 0; i < (int) processor_list_.size(); i++)
    {
      if (processor_list_[i] != NULL)
      {
        delete processor_list_[i];
      }
    }
  }

  T excute(const T & src)
  {
    T ret;
    for (int i = 0; i < (int) processor_list_.size(); i++)
    {
      if (i == 0)
      {
        ret = processor_list_[i]->process(src);
      }
      ret = processor_list_[i]->process(ret);
    }

    return ret;
  }

  T process(const T & src)
  {
    T ret;
    for (int i = 0; i < (int) processor_list_.size(); i++)
    {
      if (i == 0)
      {
        ret = processor_list_[i]->process(src);
      }
      else
      {
        ret = processor_list_[i]->process(ret);
      }
    }

    return ret;
  }

  void add(Processor* processor)
  {
    processor_list_.push_back(processor);
  }

private:

  vector<Processor*> processor_list_;

};

typedef ProcessorMgr<string> StringProcessorMgr;

} //----end of namespace gezi

#endif  //----end of PROCESSORMGR_H_
