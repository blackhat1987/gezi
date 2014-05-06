/**
 *  ==============================================================================
 *
 *          \file   Segmentor.h
 *
 *        \author   chenghuige
 *
 *          \date   2013-11-03 17:00:58.040370
 *
 *  \Description:  对于分词来说 一般 整个项目 就一个分词器 不仅仅是同一个类不同线程实例
 *                 而且是所有类 所有线程公用一个 如果设计成类 封装 那么 所有类 都要引用这个 单例模式
 *                 那就只能是指针 本质上是全局共享的东西 封装成类 意义不大
 *                 或者本身Segmentor无大的资源每个线程启用一个可以 但是需要对初始化 析构 加锁才安全
 *                 再或者使用SegDict 分离出去共享管理浙西初始化，然后Segmentor是每个线程一个指针指向SegDict
 *                 分词 本质  输入 string  输出 strings
 *                 vector<string> result = seg(input);
 *                 保留下面的类 万一需要不是全局共享 每个类有一个自己的segmentor的适合 可以
 *                 static Segmentor* seg_;
 *                seg_.seg(input, handle);  //TODO类似MatchDict
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
		//分词buffer大小,不能开辟太大因为分词scw_create_out的时候会占过多内存
		//static const int SEG_BUFF_SIZE = 20480; //50*1024
		static const int SEG_BUFF_SIZE = 15000; //50*1024

		SegHandle() = default;

		//SegHandle(int bufsize = SEG_BUFF_SIZE)
		//这个要在Segmentor读取配置文件之后创建
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
			//nlp分词设计的 如果 没有Segmentor读配置文件 这里会创建失败的。。@TODO
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
	//进程级别 一般 一个程序一个Segmentor资源实例
	static const int  SEG_USE_DEFAULT = 0;
	static const int SEG_USE_POSTAG = 1;
	static const int SEG_USE_SPLIT = 2;
	static const int SEG_USE_TRIE = 4;
	static const int SEG_USE_ALL = 255;

	//混排合并新词
	static const int SEG_MERGE_NEWWORD = SCW_OUT_WPCOMP | SCW_OUT_NEWWORD;
	//混排粒度
	static const int SEG_WPCOMP = SCW_OUT_WPCOMP;
	//新词结果
	static const int SEG_NEWWORD = SCW_OUT_NEWWORD;
	//基本小粒度
	static const int SEG_BASIC = SCW_OUT_BASIC;
	//人名结果
	static const int SEG_HUMAN_NAME = SCW_OUT_HUMANNAME;

	//改为线程安全设计 可以每个线程启动一个Segmentor,兼容之前的进程级别设计 仍然提供接受
	//SegHandle的接口 可以进程启动一个Segmentor多个线程共享 自己再提供SegHandel存储结果
	class Segmentor
	{
	public:
		//保留 不初始化资源的初始接口 好处是比如需要读取配置文件后再初始Segmentor 如果没有
		//需要使用shared_ptr方式用指针 达到延迟初始化 这样不方便SharedSegmentor设计
		Segmentor(int seg_buff_size = SegHandle::SEG_BUFF_SIZE)
			:_buf_size(seg_buff_size)
		{
			_handle.init(_buf_size); //在这之前需要先调用 Segmentor::init
			VLOG(3) << "Segmentor handle init ok";
		}

		~Segmentor()
		{
			//需要先关闭它 
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
				//---关闭分词字典
				if (pwdict())
					scw_destroy_worddict(pwdict());
				pwdict() = NULL;
				//---关闭用户需要内部切分字典
				if (split_dict())
					ds_del(split_dict());
				split_dict() = NULL;
			}
		}
		//理论上通过这个 可以配置CRF开关 覆盖配置文件中的crf开关 但是测试无效　TRACE: 04-16 13:38:28:   * 0 Do not load CRF model, please check scw.conf-->Scw_crf = 1? 原因是要设置1 然后这里可以屏蔽crf
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

		//输入是带有SegHandle的 可以作为static其实 static bool seg_words(string input, SegHandle& handle)
		//Segmentor::segment(input, handle) @TODO
		bool seg_words(string input, SegHandle& handle)
		{
			//---------分词
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
			//---------分词
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
				//----------标注
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
		//快捷接口
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

		//主要为了python封装的分词获取offset,weight信息
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
		//  //返回按照unicode的切分长度序列
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
			//--------------打开分词字典
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
				{ //--------------启动标注
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
				{	//---------------尝试打开need split字典，如果不存在或者打开出错就不使用
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

		//这个比较奇怪 c++没有问题 但是python不能很好处理static 运行没事  最后程序结束析构 
		//SegHandle scw_destroy (pout)会出core
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
				//int idx1 = pout->wpbtermoffsets[i]; //混排粒度offset是相对基本粒度的offset
				int idx1 = i;
				int idx2 = pnewword->newwordbtermoffsets[j * 2];//-这里是2*i,因为offset是不一样的
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
				int idx1 = pout->wpbtermoffsets[i]; //应该==i
				int pos1 = GET_TERM_POS(pout->wpbtermpos[i]);
				int len1 = GET_TERM_LEN(pout->wpbtermpos[i]);
				strncpy(handle.tokens[index].buffer, pout->wpcompbuf + pos1, len1);
				handle.tokens[index].buffer[len1] = '\0';
				handle.tokens[index].length = len1;
				handle.tokens[index].offset = idx1;
			}
			return index;
		}

		//另外一种设计是单独提出一个SegDict类 处理所有资源数据 然后作为Segmentor的一个static成员
		//特别是当比如同时存在多个不同Segmentor使用不同的SegDict数据
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
			static int _strategy = 0; //是否使用pos tag 等等
			return _strategy;
		}
	private:
		//scw_conf_t* pgconf;
		SegHandle _handle;
		int _flag = 0; //dynfloag 是否开启crf等 当前主要考虑设置是否开启crf
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
