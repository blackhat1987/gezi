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

namespace gezi {
	using namespace std;

	struct SegHandle
	{
		//�ִ�buffer��С,���ܿ���̫����Ϊ�ִ�scw_create_out��ʱ���ռ�����ڴ�
		//static const int SEG_BUFF_SIZE = 20480; //50*1024
		static const int SEG_BUFF_SIZE = 15000; //50*1024

		SegHandle() = default;

		SegHandle(int bufsize)
		{
			init(bufsize);
		}

		void init(int buf_size_ = SEG_BUFF_SIZE)
		{
			if (pout)
				clear();
			buf_size = buf_size_;
			u_int scw_out__flag = SCW_OUT_ALL | SCW_OUT_PROP;
			pout = scw_create_out(buf_size, scw_out__flag);
			CHECK_NOTNULL(pout);
			token_vec.resize(buf_size);
			tokens = &token_vec[0];
		}

		void clear()
		{
			if (pout)
				scw_destroy_out(pout);
			pout = NULL;
			token_vec.clear();
			token_vec.shrink_to_fit();
			tokens = NULL;
		}

		~SegHandle()
		{
			clear();
		}

		scw_out_t* pout = NULL;
		token_t* tokens = NULL;
		vector<token_t> token_vec;
		int nresult = 0;
		int buf_size = 0;
	};
	//���̼��� һ�� һ������һ��Segmentor��Դʵ��
#define  SEG_SIMPLE 0
#define SEG_USE_POSTAG 1
#define SEG_USE_SPLIT 2
#define SEG_USE_TRIE 4
#define SEG_USE_ALL 255
	class Segmentor
	{
	public:
		Segmentor() = default;

		Segmentor(string data_dir, int type = SEG_SIMPLE, string conf_path = "./conf/scw.conf")
		{
			bool ret = init(data_dir, type, conf_path);
			CHECK_EQ(ret, true);
		}

		~Segmentor()
		{
			if (_type & SEG_USE_POSTAG)
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

		Segmentor& set_flag(int flag)
		{
			_flag = flag;
			return *this;
		}

		Segmentor& set_buff_size(int buff_size)
		{
			_buf_size = buff_size;
			return *this;
		}

		bool init(string data_dir = "./data/wordseg", int type = SEG_SIMPLE, string conf_path = "./conf/scw.conf")
		{
			return init(data_dir.c_str(), type, conf_path.c_str());
		}

		bool seg_words(string input, SegHandle& handle)
		{
			//---------�ִ�
			if (scw_segment_words(_pwdict, handle.pout, input.c_str(), input.length(), LANGTYPE_SIMP_CHINESE, (void *)_flag) < 0)
			{
				LOG_ERROR("Segment fail %s %d", input.c_str(), input.length());
				return false;
			}
			return true;
		}

		int get_tokens(SegHandle& handle, int type = SCW_OUT_WPCOMP)
		{
			handle.nresult = scw_get_token_1(handle.pout, type, handle.tokens, handle.buf_size);
			return handle.nresult;
		}

		bool segment(string input, SegHandle& handle, int type = SCW_OUT_WPCOMP)
		{
			//---------�ִ�
			if (scw_segment_words(_pwdict, handle.pout, input.c_str(), input.length(), LANGTYPE_SIMP_CHINESE, (void *)_flag) < 0)
			{
				LOG_ERROR("Segment fail %s %d", input.c_str(), input.length());
				return false;
			}

			//TODO temp change to use basic �з�
			handle.nresult = scw_get_token_1(handle.pout, type, handle.tokens, handle.buf_size);

			if (_type & SEG_USE_POSTAG)
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
		
		bool segment(string input, SegHandle& handle, vector<string>& result,
			int type = SCW_OUT_WPCOMP)
		{
			bool ret = segment(input, handle, type);
			if (!ret)
			{
				return;
			}
			
			for (int i = 0; i < handle.nresult; i++)
			{
				result.push_back(handle.tokens[i].buffer);
			}
		}

		string segment(string input, SegHandle& handle, string sep, int type = SCW_OUT_WPCOMP)
		{
			bool ret = segment(input, handle, type);
			if (!ret || handle.nresult < 1)
			{
				return "";
			}
			std::stringstream ss;
			ss << handle.tokens[0].buffer;
			for (int i = 1; i < handle.nresult; i++)
			{
				ss << sep << handle.tokens[i].buffer;
			}
			return ss.str();
		}

		//��ݽӿ� �̰߳�ȫ thread safe ����һ�㲻��Ҫ�õ� ���߳� ���Լ�ά��һ��handle����
		//python�ȵ��߳� ���õ��߳̿�ݽӿ�
		vector<string> segment_ts(string input, int type = SCW_OUT_WPCOMP)
		{
			SegHandle handle(_buf_size);
			vector<string> result;
			segment(input, handle, result, type); 
			return result;
		}

		string segment_ts(string input, string sep, int type = SCW_OUT_WPCOMP)
		{
			SegHandle handle(_buf_size);
			return segment(input, handle, sep, type);
		}

		//��ݽӿ� �̲߳���ȫ ���߳��¸�����
		vector<string> segment(string input, int type = SCW_OUT_WPCOMP)
		{
			vector<string> result;
			segment(input, GetSegHandle(), result, type);
			return result;
		}

		string segment(string input, string sep, int type = SCW_OUT_WPCOMP)
		{
			return segment(input, GetSegHandle(), sep, type);
		}
		/*vector<string> segment(string input, )*/
		//  //���ذ���unicode���зֳ�������
		//  vector<int> segment_w(string input, SegHandle& handle, int type = SCW_OUT_WPCOMP)
		//  {
		//    segment(input, handle, type);
		//    
		//  }
	private:
		bool init(const char* data_dir, int type = 0, const char* conf_path = "./conf/scw.conf")
		{
			_type = type;
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

			if (_type & SEG_USE_POSTAG)
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
			{	//---------------���Դ�need split�ֵ䣬��������ڻ��ߴ򿪳���Ͳ�ʹ��
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

		static SegHandle& GetSegHandle(int buf_size = SegHandle::SEG_BUFF_SIZE)
		{
			static SegHandle _handle(buf_size);
			return _handle;
		}
	private:
		scw_worddict_t* _pwdict = NULL;
		//scw_conf_t* pgconf;
		Sdict_search* _split_dict = NULL; //�Զ��岻��Ҫ�ڷִ��ֵ���ȥ���ڲ����зֵ��ֵ���Դ 
		int _type = 0; //�Ƿ�ʹ��pos tag �ȵ�
		int _flag = 0; //dynfloag �Ƿ���crf�� ��ǰ��Ҫ���������Ƿ���crf
		int _buf_size = SegHandle::SEG_BUFF_SIZE;
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

	class SharedSegmentor
	{
	public:
		static Segmentor* Instance()
		{
			return &GetSegmentor();
		}

		static Segmentor& GetSegmentor()
		{
			static Segmentor _segmentor;
			return _segmentor;
		}
	};

	typedef SharedSegmentor Seg;
} //----end of namespace gezi

#endif  //----end of SEGMENTOR_H_
