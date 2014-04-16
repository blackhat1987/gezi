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
	//进程级别 一般 一个程序一个Segmentor资源实例
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
			//---关闭分词字典
			if (_pwdict)
				scw_destroy_worddict(_pwdict);
			//---关闭用户需要内部切分字典
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
			//---------分词
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
			//---------分词
			if (scw_segment_words(_pwdict, handle.pout, input.c_str(), input.length(), LANGTYPE_SIMP_CHINESE, (void *)_flag) < 0)
			{
				LOG_ERROR("Segment fail %s %d", input.c_str(), input.length());
				return false;
			}

			//TODO temp change to use basic 切分
			handle.nresult = scw_get_token_1(handle.pout, type, handle.tokens, handle.buf_size);

			if (_type & SEG_USE_POSTAG)
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

		//快捷接口 线程安全 thread safe 但是一般不需要用到 多线程 类自己维护一个handle即可
		//python等单线程 调用单线程快捷接口
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

		//快捷接口 线程不安全 单线程下更快速
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
		//  //返回按照unicode的切分长度序列
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
			//--------------打开分词字典
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
			{ //--------------启动标注
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
			{	//---------------尝试打开need split字典，如果不存在或者打开出错就不使用
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
		Sdict_search* _split_dict = NULL; //自定义不需要在分词字典中去除内部再切分的字典资源 
		int _type = 0; //是否使用pos tag 等等
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
