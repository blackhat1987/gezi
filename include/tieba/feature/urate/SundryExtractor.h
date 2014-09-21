/**
 *  ==============================================================================
 *
 *          \file   tieba/feature/urate/SundryExtractor.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-11 11:59:57.442051
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_FEATURE__SUNDRY_EXTRACTOR_H_
#define TIEBA_FEATURE__SUNDRY_EXTRACTOR_H_
#include "tieba/feature/urate/UrateExtractor.h"
namespace gezi {
	namespace tieba {

		class SundryExtractor : public UrateExtractor
		{
		public:
			SundryExtractor(string name = "Sundry")
				:UrateExtractor(name)
			{

			}

			virtual void extract() override
			{
				//��ǰ���������⻹�ǻظ� TODO Ŀǰ������¥��¥
				add(type(), "PostType");
				//ͳ���û��ܵ���ʷ��Ŀ(���˺��)Ҳ���� ���N�췢���� ���Ҳ������������õ������ʷ��Ŀ
				add(size(), "HistorySize");

				{//������Ŀ
					int numThreads = from(info().postsInfo.isThreads) >> where([](bool a) { return a == true; }) >> count();
					double threadRatio = numThreads / (double)size();
					ADD_FEATURE(numThreads);
					ADD_FEATURE(threadRatio);
				}
				{//���ǻظ���Ӧ������ ���ֵ�distinct�������
					int numDistinctThread = distinct_count(info().postsInfo.tids);
					double distinctThreadRatio = numDistinctThread / (double)size();
					ADD_FEATURE(numDistinctThread);
					ADD_FEATURE(distinctThreadRatio);
				}
			}
		protected:
		private:

		};

	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_URATE__SUNDRY_EXTRACTOR_H_
