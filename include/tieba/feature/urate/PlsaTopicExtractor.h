/**
 *  ==============================================================================
 *
 *          \file   tieba/feature/urate/PlsaTopicExtractor.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-18 20:59:20.027492
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_FEATURE_URATE__PLSA_TOPIC_EXTRACTOR_H_
#define TIEBA_FEATURE_URATE__PLSA_TOPIC_EXTRACTOR_H_
#include "tieba/feature/urate/UrateExtractor.h"
#include "TopicModel/PLSA/PLSAModel.h"
namespace gezi {
namespace tieba {

class PlsaTopicExtractor : public UrateExtractor
{
public:
	PlsaTopicExtractor(string name = "PlsaTopic")
		:UrateExtractor(name)
	{

	}
	
	virtual void init() override
	{
		Segmentor::Init();
		info().ExtractNormalizedTitles();
		info().ExtractNormalizedContents();
		info().ExtractNormalizedFilteredContents();
	}

	virtual void extract() override
	{
		if (!IsThread())
		{//@TODO 回复打分暂时不考虑topic
			return;
		}

		auto& titles = info().normalizedTitles;
		//auto& contents = info().normalizedContents;
		auto& contents = info().normalizedFilteredContents;
		string content;
		if (!titles.empty() && !contents.empty())
		{
			content = titles[0] + " " + contents[0];
		}

		svec words = Segmentor::Segment(content);

		map<int, Float> m;
		for (string key : words)
		{
			int id = identifer().id(key);
			if (id != identifer().null_id())
			{
				m[id] += 1;
			}
		}

		Fvec topics = model().Inference(m);

		ADD_FEATURE(topics);
	}

protected:
private:
	static Identifer& identifer()
	{
		static Identifer _identifer;
		if (!isIdentiferInited())
		{
			string identiferPath = "./data/plsa.model/identifer.bin";
			PSCONF(identiferPath, "PlsaTopic");
			_identifer.Load(identiferPath);
			isIdentiferInited() = true;
		}
		
		return _identifer;
	}
	static bool& isIdentiferInited()
	{
		static bool _isIdentiferInited = false;
		return _isIdentiferInited;
	}

	static plsa::PLSAModel& model()
	{
		static plsa::PLSAModel _model;
		if (!isModelInited())
		{
			string modelPath = "./data/plsa.model/pzw.idx";
			PSCONF(modelPath, "PlsaTopic");
			_model.Load(modelPath);
			isModelInited() = true;
		}
		
		return _model;
	}
	static bool& isModelInited()
	{
		static bool _isModelInited = false;
		return _isModelInited;
	}
};

}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_URATE__PLSA_TOPIC_EXTRACTOR_H_
