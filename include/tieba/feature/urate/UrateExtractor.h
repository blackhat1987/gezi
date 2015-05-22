/**
 *  ==============================================================================
 *
 *          \file   tieba/feature/urate/UrateExtractor.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-11 11:49:01.757362
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_FEATURE_URATE__URATE_EXTRACTOR_H_
#define TIEBA_FEATURE_URATE__URATE_EXTRACTOR_H_
#include "tieba/urate/extended_urate_info.h"
#include "tieba/urate/get_urate_info.h"
#include "feature/Features.h"
namespace gezi {
	namespace tieba {

		//@TODO 是否需要一个模板类 FeaturesWithDtaExtractor static T& info()
		class UrateExtractor : public FeaturesExtractor
		{
		public:
			using FeaturesExtractor::FeaturesExtractor;

			static size_t size()
			{
				return info().historySize;
			}

			static int type()
			{
				return info().Type();
			}

			bool IsThread()
			{
				return info().Type() == 1;
			}

			static size_t original_size()
			{
				return info().size();
			}
		public:
			//采用同static 这样 不同的子类Extractor如ForumExtractor,DictMatchExtractor可以share相同的info 不采用static 需要指针设计 
			//然后显式的将所有Extrator的info指针指向同一个资源位置for... info = &..,或者引用 那么每个初始化都要传资源取得引用 static将资源类的内部管理更符合逻辑
			//采用同thread_local因为 这个资源还是线程内部共享的概念 不同线程之间存在写竞争, 考虑多个线程同时执行抽取Urate相关特征info的内容
			//显然每个线程应该是不一样的，采用thread local就安全了同时每个线程内部自己不断更新info,另外thread_local=static thread local
			//总之thread_local就是线程内部shared 概念！ 线程内部避免重复开辟空间，线程之间安全各有一份空间,还有就是不调用info()就不产生任何空间占用
			//::info() = 第一次会调用拷贝构造函数还是operator =呢
			static ExtendedUrateInfo& info()
			{
				static thread_local ExtendedUrateInfo _info;
				return _info;
			}
			ExtendedUrateInfo& _info = info(); //can simply use this
		};
	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_URATE__URATE_EXTRACTOR_H_
