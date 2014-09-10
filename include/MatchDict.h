/**
 *  ==============================================================================
 *
 *          \file   MatchDict.h
 *
 *        \author   chenghuige
 *
 *          \date   2013-11-01 16:41:46.192610
 *
 *  \Description:    ��װdictmatch �����ںڰ����� ����ģʽƥ�� ģʽ�����ʵ�
 *                   ���������ı���ѯƥ��ģʽ
 *  ==============================================================================
 */

#ifndef MATCH_DICT_H_
#define MATCH_DICT_H_
#include "ul_dictmatch.h"
#include "log_util.h"
namespace gezi {
	//���̼��� ����̹߳���һ��MatchDict ����Ǹ߰汾gcc֧��thread localҲ����ֱ��search_count���߳�ʹ���޴���
	class MatchDict
	{
	public:
		friend class MatchSearcher;
		MatchDict()
			:_dict(NULL)
		{

		}
		~MatchDict()
		{
			if (_dict)
			{
				dm_dict_del(_dict);
			}
		}
		bool init(string file)
		{
			if (!_dict)
			{
				_dict = dm_binarydict_load(file.c_str());
			}
			CHECK_NOTNULL(_dict);
			return true;
		}

		int search(string text, dm_pack_t* result)
		{
			//return dm_search(dict_, result, text.c_str(), text.length(), DM_OUT_FMM, DM_CHARSET_GB18030);
			return dm_search(_dict, result, text.c_str(), text.length(), DM_OUT_FMM);
		}

		//ͬ�� ֻ�Ǹ�Ϊ����ƥ�䵽�Ľ����Ŀ �������ʧ�ܷ���0 �ɹ��Ļ�����ƥ����Ŀ>=0
		int search_count(string text, dm_pack_t* result)
		{
			//int ret = dm_search(dict_, result, text.c_str(), text.length(), DM_OUT_FMM, DM_CHARSET_GB18030);
			int ret = dm_search(_dict, result, text.c_str(), text.length(), DM_OUT_FMM);
			int count = 0;
			if (ret == 0)
			{
				count = result->ppseg_cnt;
			}
			return count;
		}

		int search_count(string text)
		{
			return search_count(text, dm_pack());
		}

		////�������ҷ���ƥ�䵽��count
		int SearchCount(string text)
		{
			dm_pack_t* result = dm_pack_create(text.length());
			if (!result)
			{
				return 0;
			}
			int ret = dm_search(_dict, result, text.c_str(), text.length(), DM_OUT_FMM, DM_CHARSET_GB18030);
			int count = 0;
			if (ret == 0)
			{
				count = result->ppseg_cnt;
			}
			dm_pack_del(result);
			return count;
		}
		//type 1, 2, 4 or 3(1 and 2)...
		bool has_word(string text, int type = 1)
		{
			return dm_has_word(_dict, type, text.c_str(), text.length(), DM_OUT_FMM, DM_CHARSET_GB18030);
		}

	public:
		static dm_pack_t* dm_pack(int maxMatchCount = 1000)
		{
			static thread_local dm_pack_t* _result = NULL;
			if (_result == NULL)
			{
				_result = dm_pack_create(maxMatchCount);
			}
			return _result;
		}
	private:
		dm_dict_t* _dict;
	};

	////�̼߳��� ÿ���߳�һ��
	class MatchSearcher
	{
	public:
		MatchSearcher(MatchDict* dict, int maxMatchCount = 1000)
			:_dict(dict), _maxMatchCount(maxMatchCount)
		{
			_result = dm_pack_create(_maxMatchCount);
		}

		MatchSearcher(const MatchDict& dict, int maxMatchCount = 1000)
			:_dict(&dict), _maxMatchCount(maxMatchCount)
		{
			_result = dm_pack_create(_maxMatchCount);
		}

		int search_count(const MatchDict& dict, string text)
		{
			return dict.search_count(text, _result);
		}

		int search_count(MatchDict* dict, string text)
		{
			return dict->search_count(text, _result);
		}

		dm_pack_t* search(const MatchDict& dict, string text)
		{
			dict.search(text, _result);
			return _result;
		}

		dm_pack_t* search(MatchDict* dict, string text)
		{
			dict->search(text, _result);
			return _result;
		}

		int search_count(string text)
		{
			return _dict->search_count(text, _result);
		}

		dm_pack_t* search(string text)
		{
			_dict->search(text, _result);
			return _result;
		}

		dm_pack_t* result()
		{
			return _result;
		}

		bool has_word(string text)
		{ 
			return _dict->has_word(text);
		}

		int max_match_count()
		{
			return _maxMatchCount;
		}

	private:
		MatchDict* _dict =  NULL; 
		dm_pack_t* _result = NULL;//������thread_local���static �߳��ڲ����� �ŵ�MatchDict�� ��ʱ�������������
		int _maxMatchCount = 1000; //������ƥ��ĸ���
	};
}

#endif  //----end of MATCH_DICT_H_
