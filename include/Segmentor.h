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

namespace gezi
{
	using namespace std;

	struct SegHandle
	{
		//分词buffer大小,不能开辟太大因为分词scw_create_out的时候会占过多内存
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
	//进程级别 一般 一个程序一个Segmentor资源实例
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
			//---关闭分词字典
			if (_pwdict)
				scw_destroy_worddict(_pwdict);
			//---关闭用户需要内部切分字典
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

			if (_use_tag)
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
			{
				//---------------尝试打开need split字典，如果不存在或者打开出错就不使用
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
			//---------分词
			if (scw_segment_words(_pwdict, handle.pout, input.c_str(), input.length(), LANGTYPE_SIMP_CHINESE, NULL) < 0)
			{
				LOG_ERROR("Segment fail %s %d", input.c_str(), input.length());
				return false;
			}

			//TODO temp change to use basic 切分
			handle.nresult = scw_get_token_1(handle.pout, type, handle.tokens, handle.buf_size);

			if (_type)
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

		//  //返回按照unicode的切分长度序列
		//  vector<int> segment_w(const string& input, SegHandle& handle, int type = SCW_OUT_WPCOMP)
		//  {
		//    segment(input, handle, type);
		//    
		//  }

	private:
		scw_worddict_t* _pwdict;
		//scw_conf_t* pgconf;
		Sdict_search* _split_dict; //自定义不需要在分词字典中去除内部再切分的字典资源 
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
