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
				//ͳ���û��ܵ���ʷ��Ŀ(���˺��)Ҳ���� ���30�췢���� ͬʱҲ������ʵ��ʹ�õ���ʷ����
				add(size(), "HistorySize");
			}
		protected:
		private:

		};

	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_URATE__SUNDRY_EXTRACTOR_H_
