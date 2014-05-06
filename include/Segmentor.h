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

		//SegHandle(int bufsize = SEG_BUFF_SIZE)
		//���Ҫ��Segmentor��ȡ�����ļ�֮�󴴽�
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
			//nlp�ִ���Ƶ� ��� û��Segmentor�������ļ� ����ᴴ��ʧ�ܵġ���@TODO
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

	struct SegNode
	{
		string word;
		int length;
		int offset;
		int weight;
		SegNode() = default;	
		SegNode(string word_, int length_, int offset_, int weight_)
			:word(word_), length(length_), offset(offset_), weight(weight_)
		{

		}
	};
	//���̼��� һ�� һ������һ��Segmentor��Դʵ��
	static const int  SEG_USE_DEFAULT = 0;
	static const int SEG_USE_POSTAG = 1;
	static const int SEG_USE_SPLIT = 2;
	static const int SEG_USE_TRIE = 4;
	static const int SEG_USE_ALL = 255;

	//���źϲ��´�
	static const int SEG_MERGE_NEWWORD = SCW_OUT_WPCOMP | SCW_OUT_NEWWORD;
	//��������
	static const int SEG_WPCOMP = SCW_OUT_WPCOMP;
	//�´ʽ��
	static const int SEG_NEWWORD = SCW_OUT_NEWWORD;
	//����С����
	static const int SEG_BASIC = SCW_OUT_BASIC;
	//�������
	static const int SEG_HUMAN_NAME = SCW_OUT_HUMANNAME;

	//��Ϊ�̰߳�ȫ��� ����ÿ���߳�����һ��Segmentor,����֮ǰ�Ľ��̼������ ��Ȼ�ṩ����
	//SegHandle�Ľӿ� ���Խ�������һ��Segmentor����̹߳��� �Լ����ṩSegHandel�洢���
	class Segmentor
	{
	public:
		//���� ����ʼ����Դ�ĳ�ʼ�ӿ� �ô��Ǳ�����Ҫ��ȡ�����ļ����ٳ�ʼSegmentor ���û��
		//��Ҫʹ��shared_ptr��ʽ��ָ�� �ﵽ�ӳٳ�ʼ�� ����������SharedSegmentor���
		Segmentor(int seg_buff_size = SegHandle::SEG_BUFF_SIZE)
			:_buf_size(seg_buff_size)
		{
			_handle.init(_buf_size); //����֮ǰ��Ҫ�ȵ��� Segmentor::init
			VLOG(3) << "Segmentor handle init ok";
		}

		~Segmentor()
		{
			//��Ҫ�ȹر��� 
			_handle.clear();
		}

		static void uninit()
		{
			LOG(INFO) << "segmentor uninit";
			if (pwdict())
			{
				if (strategy() & SEG_USE_POSTAG)
				{
					tag_close();
				}
				//---�رշִ��ֵ�
				if (pwdict())
					scw_destroy_worddict(pwdict());
				pwdict() = NULL;
				//---�ر��û���Ҫ�ڲ��з��ֵ�
				if (split_dict())
					ds_del(split_dict());
				split_dict() = NULL;
			}
		}
		//������ͨ����� ��������CRF���� ���������ļ��е�crf���� ���ǲ�����Ч��TRACE: 04-16 13:38:28:   * 0 Do not load CRF model, please check scw.conf-->Scw_crf = 1? ԭ����Ҫ����1 Ȼ�������������crf
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

		static bool init(string data_dir = "./data/wordseg", int type = SEG_USE_DEFAULT, string conf_path = "./conf/scw.conf")
		{
			return init(data_dir.c_str(), type, conf_path.c_str());
		}

		//�����Ǵ���SegHandle�� ������Ϊstatic��ʵ static bool seg_words(string input, SegHandle& handle)
		//Segmentor::segment(input, handle) @TODO
		bool seg_words(string input, SegHandle& handle)
		{
			//---------�ִ�
			if (scw_segment_words(pwdict(), handle.pout, input.c_str(), input.length(), LANGTYPE_SIMP_CHINESE, (void *)_flag) < 0)
			{
				LOG_ERROR("Segment fail %s %d", input.c_str(), input.length());
				return false;
			}
			return true;
		}

		static int get_tokens(SegHandle& handle, int type = SEG_WPCOMP)
		{
			handle.nresult = scw_get_token_1(handle.pout, type, handle.tokens, handle.buf_size);
			return handle.nresult;
		}

		int get_tokens(int type = SEG_WPCOMP)
		{
			_handle.nresult = scw_get_token_1(_handle.pout, type, _handle.tokens, _handle.buf_size);
			return _handle.nresult;
		}

		static vector<SegNode> get_segnodes(SegHandle& handle)
		{
			vector<SegNode> result;
			for (int i = 0; i < handle.nresult; i++)
			{
				result.push_back(SegNode(handle.tokens[i].buffer, handle.tokens[i].length,
					handle.tokens[i].offset, handle.tokens[i].weight));
			}
			return result;
		}

		vector<SegNode> get_segnodes()
		{
			return get_segnodes(_handle);
		}

		//@TODO can be static with handle outside Segmentor
		bool segment(string input, SegHandle& handle, int type = SEG_WPCOMP)
		{
			//---------�ִ�
			int* pflag = _flag == 0 ? NULL : &_flag;
			if (scw_segment_words(pwdict(), handle.pout, input.c_str(), input.length(), LANGTYPE_SIMP_CHINESE, (void *)pflag) < 0)
			{
				LOG_ERROR("Segment fail %s %d", input.c_str(), input.length());
				return false;
			}
			if (type != SEG_MERGE_NEWWORD || !handle.pout->pnewword->newwordbtermcount)
			{
				handle.nresult = scw_get_token_1(handle.pout, type, handle.tokens, handle.buf_size);
			}
			else
			{
				handle.nresult = merge_newword(handle);
			}

			//notice you can use if (strategy & ) also
			if (strategy() & SEG_USE_POSTAG)
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
			int type = SEG_WPCOMP)
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

		string segment(string input, SegHandle& handle, string sep, int type = SEG_WPCOMP)
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
		//��ݽӿ�
		vector<string> segment(string input, int type = SEG_WPCOMP)
		{
			vector<string> result;
			//segment(input, GetSegHandle(), result, type);
			segment(input, _handle, result, type);
			return result;
		}

		bool segment(string input, vector<string>& result, int type = SEG_WPCOMP)
		{
			return segment(input, _handle, result, type);
		}

		string segment(string input, string sep, int type = SEG_WPCOMP)
		{
			//return segment(input, GetSegHandle(), sep, type);
			return segment(input, _handle, sep, type);
		}

		//��ҪΪ��python��װ�ķִʻ�ȡoffset,weight��Ϣ
		bool segment(string input, vector<SegNode>& result, int type = SEG_WPCOMP)
		{
			bool ret = segment(input, _handle, type);
			if (!ret)
				return false;
			for (int i = 0; i < _handle.nresult; i++)
			{
				result.push_back(SegNode(_handle.tokens[i].buffer, _handle.tokens[i].length,
					_handle.tokens[i].offset, _handle.tokens[i].weight));
			}
			return true;
		}
		/*vector<string> segment(string input, )*/
		//  //���ذ���unicode���зֳ�������
		//  vector<int> segment_w(string input, SegHandle& handle, int type = SEG_WPCOMP)
		//  {
		//    segment(input, handle, type);
		//    
		//  }

		SegHandle& handle()
		{
			return _handle;
		}

	private:
		static bool init(const char* data_dir, int type = 0, const char* conf_path = "./conf/scw.conf")
		{
			strategy() = type;
			int ret = -1;
			//--------------�򿪷ִ��ֵ�
			if (!pwdict())
			{
				{
					if (pgconf != NULL)
					{
						scw_destroy_conf(pgconf);
						pgconf = NULL;
					}
					pgconf = scw_load_conf(conf_path);
					CHECK(pgconf != NULL) << conf_path;

					pwdict() = scw_load_worddict(data_dir);
					CHECK(pwdict() != NULL) << data_dir << " the path wrong ? or you use wrong segment version ?";
					LOG(INFO) << "Load segmentor dict data ok";
				}

				if (strategy() & SEG_USE_POSTAG)
				{ //--------------������ע
					char tag_dict_path[2048];
					sprintf(tag_dict_path, "%s/%s", data_dir, "tagdict");
					ret = tag_open(tag_dict_path);
					CHECK_EQ(ret, 0) << tag_dict_path;
					LOG(INFO) << "Tag open ok";
				}
				else
				{
					LOG(INFO) << "Do not use pos tag";
				}
				{	//---------------���Դ�need split�ֵ䣬��������ڻ��ߴ򿪳���Ͳ�ʹ��
					char user_dict_path[2048];
					sprintf(user_dict_path, "%s/%s", data_dir, "need_split");
					split_dict() = ds_load(user_dict_path, "need_split");
					if (!split_dict())
					{
						LOG_WARNING("Do not use user defined split dictionary, not find %s", user_dict_path);
					}
					else
					{
						LOG(INFO) << "User defined split dictionary open ok";
					}
				}
			}
			LOG(INFO) << "Segmentor init ok";
			return true;
		}

		//����Ƚ���� c++û������ ����python���ܺܺô���static ����û��  ������������� 
		//SegHandle scw_destroy (pout)���core
		/*	static SegHandle& GetSegHandle(int buf_size = SegHandle::SEG_BUFF_SIZE)
			{
			static SegHandle _handle(buf_size);
			return _handle;
			}*/

		int merge_newword(SegHandle& handle)
		{
			scw_newword_t* pnewword = handle.pout->pnewword;
			scw_out_t* pout = handle.pout;
			token_t* tokens = handle.tokens;

			int i = 0, j = 0, index = 0;
			for (; j < pnewword->newwordbtermcount; i++, index++)
			{
				//int idx1 = pout->wpbtermoffsets[i]; //��������offset����Ի������ȵ�offset
				int idx1 = i;
				int idx2 = pnewword->newwordbtermoffsets[j * 2];//-������2*i,��Ϊoffset�ǲ�һ����
				int pos1 = GET_TERM_POS(pout->wpbtermpos[i]);
				int len1 = GET_TERM_LEN(pout->wpbtermpos[i]);
				if (idx1 == idx2)
				{
					int pos2 = GET_TERM_POS(pnewword->newwordbtermpos[j]);
					int len2 = GET_TERM_LEN(pnewword->newwordbtermpos[j]);
					while (len1 != len2)
					{
						i++;
						len1 += GET_TERM_LEN(pout->wpbtermpos[i]);
					}
					strncpy(tokens[index].buffer, pnewword->newwordbuf + pos2, len2);
					tokens[index].buffer[len2] = '\0';
					tokens[index].length = len2;
					tokens[index].offset = idx2;
					j++;
				}
				else
				{ // can only be idx2 > idx1
					strncpy(tokens[index].buffer, pout->wpcompbuf + pos1, len1);
					tokens[index].buffer[len1] = '\0';
					tokens[index].length = len1;
					tokens[index].offset = idx1;
				}
			}
			for (; i < pout->wpbtermcount; i++, index++)
			{
				int idx1 = pout->wpbtermoffsets[i]; //Ӧ��==i
				int pos1 = GET_TERM_POS(pout->wpbtermpos[i]);
				int len1 = GET_TERM_LEN(pout->wpbtermpos[i]);
				strncpy(handle.tokens[index].buffer, pout->wpcompbuf + pos1, len1);
				handle.tokens[index].buffer[len1] = '\0';
				handle.tokens[index].length = len1;
				handle.tokens[index].offset = idx1;
			}
			return index;
		}

		//����һ������ǵ������һ��SegDict�� ����������Դ���� Ȼ����ΪSegmentor��һ��static��Ա
		//�ر��ǵ�����ͬʱ���ڶ����ͬSegmentorʹ�ò�ͬ��SegDict����
		static scw_worddict_t*& pwdict()
		{
			static scw_worddict_t* _pwdict = NULL;
			return _pwdict;
		}

		static Sdict_search*& split_dict()
		{
			static Sdict_search* _split_dict = NULL;
			return _split_dict;
		}

		static int& strategy()
		{
			static int _strategy = 0; //�Ƿ�ʹ��pos tag �ȵ�
			return _strategy;
		}
	private:
		//scw_conf_t* pgconf;
		SegHandle _handle;
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

} //----end of namespace gezi

#endif  //----end of SEGMENTOR_H_
