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
	PlsaTopicExtractor(bool onlyNow = true, string name = "PlsaTopic")
		:UrateExtractor(name), _onlyNow(onlyNow)
	{

	}

	bool _onlyNow = true;

	virtual void init() override
	{
		Segmentor::Init();
		info().ExtractNormalizedTitles();
		info().ExtractNormalizedContents();
		info().ExtractNormalizedFilteredContents();
	}

	Fvec GetTopics(int i)
	{
		auto& titles = info().normalizedTitles;
		//auto& contents = info().normalizedContents;
		auto& contents = info().normalizedFilteredContents;
		string content;
		if (!titles.empty() && !contents.empty())
		{
			content = titles[i] + " " + contents[i];
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
		return topics;
	}
	virtual void extract() override
	{
		//if (!IsThread())
		//{//@TODO 回复打分暂时不考虑topic
		//	return;
		//}

		Fvec topics = GetTopics(0);

		if (!_onlyNow)
		{
			for (size_t i = 1; i < size(); i++)
			{
				Fvec topics2 = GetTopics(i);
				add_vec(topics, topics2);
			}
		}

		for (auto& val : topics)
		{
			val /= size();
		}

		ADD_FEATURE(topics);
	}

protected:
private:
	static Identifer& identifer()
	{
		static Identifer _identifer = ([&]()
		{
			Identifer identifer;
			string identiferPath = "./data/plsa.model/identifer.bin";
			PSCONF(identiferPath, "PlsaTopic");
			identifer.Load(identiferPath);
			return identifer;
		})();
		return _identifer;
	}

	//static plsa::PLSAModel ConstructModel()
	//{
	//	plsa::PLSAModel _model;
	//	string modelPath = "./data/plsa.model/pzw.idx";
	//	PSCONF(modelPath, "PlsaTopic");
	//	_model.Load(modelPath);
	//	return _model;
	//}
	static plsa::PLSAModel& model()
	{
		/*static plsa::PLSAModel _model = ConstructModel();*/
		static plsa::PLSAModel _model = ([&]() { 
			plsa::PLSAModel _model;
			string modelPath = "./data/plsa.model/pzw.idx";
			PSCONF(modelPath, "PlsaTopic");
			_model.Load(modelPath);
			return _model;
		})();
		return _model;
	}
};

}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_URATE__PLSA_TOPIC_EXTRACTOR_H_
