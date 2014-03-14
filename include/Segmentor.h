/**
 *  ==============================================================================
 *
 *          \file   Segmentor.h
 *
 *        \author   chenghuige
 *
 *          \date   2013-11-03 17:00:58.040370
 *
 *  \Description:  ���ڷִ���˵ һ�� ������Ŀ ��һ���ִ��� ��������ͬһ���಻ͬ�߳�ʵ��
 *                 ������������ �����̹߳���һ�� �����Ƴ��� ��װ ��ô ������ ��Ҫ������� ����ģʽ
 *                 �Ǿ�ֻ����ָ�� ��������ȫ�ֹ���Ķ��� ��װ���� ���岻��
 *                 ���߱���Segmentor�޴����Դÿ���߳�����һ������ ������Ҫ�Գ�ʼ�� ���� �����Ű�ȫ
 *                 �ٻ���ʹ��SegDict �����ȥ�������������ʼ����Ȼ��Segmentor��ÿ���߳�һ��ָ��ָ��SegDict
 *                 �ִ� ����  ���� string  ��� strings
 *                 vector<string> result = seg(input);
 *                 ����������� ��һ��Ҫ����ȫ�ֹ��� ÿ������һ���Լ���segmentor���ʺ� ����
 *                 static Segmentor* seg_;
 *                seg_.seg(input, handle);  //TODO����MatchDict
 *  ==============================================================================
 */

#ifndef SEGMENTOR_H_
#define SEGMENTOR_H_
#include "scwdef.h"
#include "property.h"
#include "isegment.h"
#include "ipostag.h"
#include "ul_dict.h"
#include "log_util.h"
#include "debug_util.h"
#include <string>
#include <vector>
//#include "common_util.h"

namespace gezi
{
	using namespace std;

	struct SegHandle
	{
		//�ִ�buffer��С,���ܿ���̫����Ϊ�ִ�scw_create_out��ʱ���ռ�����ڴ�
		static const int SEG_BUFF_SIZE = 20480; //50*1024

		SegHandle()
			: pout(NULL), tokens(NULL), nresult(0)
		{
		}
		SegHandle(int bufsize)
			: pout(NULL), tokens(NULL), nresult(0)
		{
			init(bufsize);
		}
		void init(int bufsize = SEG_BUFF_SIZE)
		{
			if (pout)
				clear();
			buf_size = bufsize;
			u_int scw_out_flag = SCW_OUT_ALL | SCW_OUT_PROP;
			pout = scw_create_out(bufsize, scw_out_flag);
			CHECK_NOTNULL(pout);
			tokens = new token_t[bufsize];
			CHECK_NOTNULL(tokens);
		}

		void clear()
		{
			if (pout)
				scw_destroy_out(pout);
			if (tokens)
				delete[] tokens;
		}

		~SegHandle()
		{
			clear();
		}

		scw_out_t *pout;
		token_t* tokens;
		int nresult;
		int buf_size;
	};
	//���̼��� һ�� һ������һ��Segmentor��Դʵ��
#define SEG_USE_POSTAG 1
#define SEG_USE_SPLIT 2
#define SEG_USE_TRIE 4
#define SEG_USE_ALL 256
	class Segmentor
	{
	public:

		Segmentor()
			:_type(0),
			_use_tag(false), 
			_pwdict(NULL),
			_split_dict(NULL)
		{

		}

		Segmentor(const string& data_dir, int type = 0, const string& conf_path = "./conf/scw.conf")
			:_type(0),
			_use_tag(false),
			_pwdict(NULL),
			_split_dict(NULL)
		{
			bool ret = init(data_dir, type, conf_path);
			CHECK_EQ(ret, true);
		}

		~Segmentor()
		{
			if (_use_tag)
			{
				tag_close();
			}
			//---�رշִ��ֵ�
			if (_pwdict)
				scw_destroy_worddict(_pwdict);
			//---�ر��û���Ҫ�ڲ��з��ֵ�
			if (_split_dict)
				ds_del(_split_dict);
		}

		bool init(const string& data_dir, int type = 0, const string& conf_path = "./conf/scw.conf")
		{
			return init(data_dir.c_str(), type, conf_path.c_str());
		}

		bool init(const char* data_dir, int type = 0, const char* conf_path = "./conf/scw.conf")
		{
			_type = type;
			_use_tag = (bool)(_type & SEG_USE_POSTAG);
			int ret = -1;
			//--------------�򿪷ִ��ֵ�
			{
				if (pgconf != NULL)
				{
					scw_destroy_conf(pgconf);
					pgconf = NULL;
				}
				pgconf = scw_load_conf(conf_path);
				CHECK(pgconf != NULL) << conf_path;

				_pwdict = scw_load_worddict(data_dir);
				CHECK(_pwdict != NULL) << data_dir << " the path wrong ? or you use wrong segment version ?";
				LOG_INFO("Load segmentor dict data ok");
			}

			if (_use_tag)
			{ //--------------������ע
				char tag_dict_path[2048];
				sprintf(tag_dict_path, "%s/%s", data_dir, "tagdict");
				ret = tag_open(tag_dict_path);
				CHECK_EQ(ret, 0) << tag_dict_path;
				LOG_INFO("Tag open ok");
			}
			else
			{
				LOG_INFO("Do not use pos tag");
			}
			{
				//---------------���Դ�need split�ֵ䣬��������ڻ��ߴ򿪳���Ͳ�ʹ��
				char user_dict_path[2048];
				sprintf(user_dict_path, "%s/%s", data_dir, "need_split");
				_split_dict = ds_load(user_dict_path, "need_split");
				if (!_split_dict)
				{
					LOG_WARNING("Do not use user defined split dictionary, not find %s", user_dict_path);
				}
				else
				{
					LOG_INFO("User defined split dictionary open ok");
				}
			}
			LOG_INFO("Segmentor init ok");
			return true;
		}

		bool segment(const string& input, SegHandle& handle, int type = SCW_OUT_WPCOMP)
		{
			//---------�ִ�
			if (scw_segment_words(_pwdict, handle.pout, input.c_str(), input.length(), LANGTYPE_SIMP_CHINESE, NULL) < 0)
			{
				LOG_ERROR("Segment fail %s %d", input.c_str(), input.length());
				return false;
			}

			//TODO temp change to use basic �з�
			handle.nresult = scw_get_token_1(handle.pout, type, handle.tokens, handle.buf_size);

			if (_type)
			{
				//----------��ע
				if (tag_postag(handle.tokens, handle.nresult) < 0)
				{
					LOG_ERROR("Tagging failed!");
					return false;
				}
			}
			return true;
		}

		//  //���ذ���unicode���зֳ�������
		//  vector<int> segment_w(const string& input, SegHandle& handle, int type = SCW_OUT_WPCOMP)
		//  {
		//    segment(input, handle, type);
		//    
		//  }

	private:
		scw_worddict_t* _pwdict;
		//scw_conf_t* pgconf;
		Sdict_search* _split_dict; //�Զ��岻��Ҫ�ڷִ��ֵ���ȥ���ڲ����зֵ��ֵ���Դ 
		int _type;
		bool _use_tag;
	};

	//util
	inline void print_seg_result(const SegHandle& handle)
	{
		Pval(handle.nresult);
		for (int i = 0; i < handle.nresult; i++)
		{
			VLOG(3) << setiosflags(ios::left) << setfill(' ') << setw(4) << i <<
				handle.tokens[i].buffer << " " << handle.tokens[i].length;
		}
	}
} //----end of namespace gezi

#endif  //----end of SEGMENTOR_H_
