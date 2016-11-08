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

#ifndef NO_BAIDU_DEP
///* define the token type */
//#ifndef TOKEN_TYPE_DEFINED
//#define TOKEN_TYPE_DEFINED
//#define TERM_MAX_LEN 256
//typedef unsigned int uint32_t;
//struct token_t
//{
//  /* term info */
//  uint32_t length : 8;  /* length of term, not include the '\0' */
//  uint32_t offset : 24; /* offset of term in input text */
//  uint32_t type : 8;    /* type info, e.g. POS tag. 0 is invalid, used in postag, NOT used in wordseg */
//  uint32_t weight : 24; /* weight of term */
//
//  /* property */
//  struct prop
//  {
//    uint32_t m_lprop;  /* high 32 bit */
//    uint32_t m_hprop;  /* low 32 bit */
//  };
//
//  /* dict index */
//  long index; /* point to the address of dict item */
//
//  /* term buffer */
//  char buffer[TERM_MAX_LEN];
//
//  //for py auto wrap for vector
//  bool operator == (const token_t& other) const
//  {
//    return offset == other.offset;
//  }
//};
//
//#endif /* TOKEN_TYPE_DEFINED */

#include "scwdef.h"
#include "property.h"
#include "isegment.h"

#ifdef u_int
#undef  u_int
#endif

//-------postag
#include "ipostag.h"
#include "tagdict.h"
extern const char* get_pos_str(unsigned int nPOS); // from libpostag.a

//-------wordner
#include "iwordner.h"
//-------wordrank
#include "iwordrank.h"
#include "itrunk.h"
#include "baidu/uldict_util.h"
#include "ul_dict.h"

#endif

#include <glog/logging.h>
#include "debug_util.h"

#include <string>
#include <vector>
#include <map>
//#include "common_util.h"


namespace gezi {
  using std::vector;
  using std::string;
  using std::map;

#ifndef NO_BAIDU_DEP
  //���̼��� һ�� һ������һ��Segmentor��Դʵ��
  static const int  SEG_USE_NONE = 0;

  static const int SEG_USE_POSTAG = 1;
  static const int SEG_USE_SPLIT = 2;
  static const int SEG_USE_TRIE = 4; //not used right now
  static const int SEG_USE_OFFSETS = 8;
  static const int SEG_USE_WORDNER = 16;
  static const int SEG_USE_WORDNER_AUTO = 32;
  static const int SEG_USE_WORDRANK = 64;
  static const int SEG_USE_WORDRANK_AUTO = 128;
  static const int SEG_USE_ALL = 255;

  static const int  SEG_USE_DEFAULT = SEG_USE_OFFSETS;

  //@TODO ����ʹ��enum class SegType,��ǰ��c style��������ǰ׺
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

  struct SegHandle
  {
    //�ִ�buffer��С,���ܿ���̫����Ϊ�ִ�scw_create_out��ʱ���ռ�����ڴ�
    static const int SEG_BUFF_SIZE = 20480; //50*1024
    //static const int SEG_BUFF_SIZE = 15000; //50*1024

    //SegHandle() = default;

    //SegHandle(int bufsize = SEG_BUFF_SIZE)
    //���Ҫ��Segmentor��ȡ�����ļ�֮�󴴽�
    SegHandle(int bufsize = SEG_BUFF_SIZE)
    {
      init(bufsize);
    }

    void init(int buf_size_ = SEG_BUFF_SIZE)
    {
      if (pout)
      {
        clear();
      }
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
      {
        scw_destroy_out(pout);
        pout = NULL;
      }
      token_vec.clear();
      token_vec.shrink_to_fit();
      tokens = NULL;
    }

    ~SegHandle()
    {
      clear();
    }

    //����basic���ȣ��������ȵ�offset˵������basic���ȵ�offset���������ַ�����offset
    //�����װ���˾���
    size_t offset(int i) const
    {
      return tokens[i].offset;
    }

    // TO python wrapper will ignore length
    size_t length(int i) const
    {
      return tokens[i].length;
    }

    size_t len(int i) const
    {
      return tokens[i].length;
    }

    string word(int i) const
    {
      return tokens[i].buffer;
    }

    size_t type(int i) const
    {
      return tokens[i].type;
    }

    size_t weight(int i) const
    {
      return tokens[i].weight;
    }

    void gen_offsets()
    {
      for (int i = 1; i < nresult; i++)
      {
        tokens[i].offset = tokens[i - 1].offset + tokens[i - 1].length;
      }
    }

    size_t size() const
    {
      return (size_t)nresult;
    }

    scw_out_t* pout = NULL;
    token_t* tokens = NULL;
    vector<token_t> token_vec;
    int nresult = 0;
    int buf_size = 0;
    int seg_type = SEG_BASIC;
  };

  struct NerHandle
  {
    static const int MAX_TERM_COUNT = 256;
    NerHandle() = default;

#ifndef GCCXML
    NerHandle(ner_dict_t* pnerdict, int maxt_term_count = MAX_TERM_COUNT)
    {
      pout = ner_out_create(pnerdict, maxt_term_count);
    }
#endif

    ~NerHandle()
    {
      clear();
    }

    void clear()
    {
      if (pout)
      {
        ner_out_destroy(pout);
        pout = NULL;
      }
    }

    size_t size()
    {
      return (size_t)pout->tag_num;
    }

    size_t subtag_size()
    {
      return (size_t)pout->sub_tag_num;
    }

    int nresult = 0;
    ner_out_t *pout = NULL;
    int seg_type = SEG_BASIC;
  };

  struct SegNode
  {
    string word;
    // FIXME pygccxml not support length (bug, may be new version or future version ok, so manully add it right now) ��ʱ����������о���py++ʲô��
    // FIXME!WARNIN!
    int length;
    int offset;
    int type;
    int weight;
    SegNode() = default;
    SegNode(string word_, int length_, int offset_, int type_, int weight_)
      :word(word_), length(length_), offset(offset_), type(type_), weight(weight_)
    {

    }

    //for py auto wrap for vector
    bool operator == (const SegNode& other) const
    {
      return offset == other.offset;
    }
  };

  struct NerNode
  {
    string word;
    // FIXME pygccxml not support length (bug, may be new version or future version ok, so manully add it right now) ��ʱ����������о���py++ʲô��
    // FIXME!WARNIN!
    int type; //ner type
    string name;

    NerNode() = default;
    NerNode(string word_, int type_, string name_ = "")
      :word(word_), type(type_), name(name_)
    {

    }

    //for py auto wrap for vector
    bool operator == (const NerNode& other) const
    {
      return type == other.type;
    }
  };


  //��Ϊ�̰߳�ȫ��� ����ÿ���߳�����һ��Segmentor,����֮ǰ�Ľ��̼������ ��Ȼ�ṩ����
  //SegHandle�Ľӿ� ���Խ�������һ��Segmentor����̹߳��� �Լ����ṩSegHandel�洢���
  //NOTICE _handle֮���ֻ��Ϊ�˺�֮ǰ���ݣ��Ƽ�ʹ�ô�д��ͷ�Ľӿڣ�ͳһ��ʹ��static thrad local�����
  class Segmentor
  {
  public:
    //���� ����ʼ����Դ�ĳ�ʼ�ӿ� �ô��Ǳ�����Ҫ��ȡ�����ļ����ٳ�ʼSegmentor ���û��
    //��Ҫʹ��shared_ptr��ʽ��ָ�� �ﵽ�ӳٳ�ʼ�� ����������SharedSegmentor���
    Segmentor(int seg_buff_size = SegHandle::SEG_BUFF_SIZE)
      :_handle(seg_buff_size)
    {
      //_handle.init(seg_buff_size); //����֮ǰ��Ҫ�ȵ��� Segmentor::init
      //VLOG(3) << "Segmentor handle init ok";
    }

    ~Segmentor()
    {
      //��Ҫ�ȹر��� 
      _handle.clear();

      //Uninit();

      uninit();
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
        {
          scw_destroy_worddict(pwdict());
          pwdict() = NULL;
        }

        //---�ر��û���Ҫ�ڲ��з��ֵ�
        if (split_dict())
        {
          ds_del(split_dict());
          split_dict() = NULL;
        }
        //---�ر�wordner�ʵ�
        if (nerdict())
        {
          ner_dict_destroy(nerdict());
          nerdict() = NULL;
        }

        //---wordrank
        if (rankdict())
        {
          wdr_destroy(rankdict());
          rankdict() = NULL;
        }
        if (trunkdict())
        {
          trk_destroy(trunkdict());
          trunkdict() = NULL;
        }
        if (wordtagdict())
        {
          db_del(wordtagdict());
          wordtagdict() = NULL;
        }
      }
    }

    static void Uninit()
    {
      handle().clear();
      if (UseWordNer())
      {
        ner_handle().clear();
      }
    }

    //������ͨ����� ��������CRF���� ���������ļ��е�crf���� ���ǲ�����Ч��TRACE: 04-16 13:38:28:   * 0 Do not load CRF model, please check scw.conf-->Scw_crf = 1? ԭ����Ҫ����1 Ȼ�������������crf
    Segmentor& set_flag(int flag_)
    {
      flag() = flag_;
      PVAL(flag());
      return *this;
    }

    static void SetFlag(int flag_)
    {
      flag() = flag_;
      PVAL(flag());
    }

    static void SetStrategy(int strategy_)
    {
      strategy() = strategy_;
    }

    static void AddStrategy(int strategy_)
    {
      strategy() |= strategy_;
    }

    static void add_strategy(int strategy_)
    {
      strategy() |= strategy_;
    }

    static bool init(string data_dir = "./data/wordseg", int type = SEG_USE_DEFAULT, string conf_path = "./conf/scw.conf", bool need_split_dict = false)
    {
      //only once init
      static bool ret = init(data_dir.c_str(), type, conf_path.c_str(), need_split_dict);
      return ret;
    }

    static bool Init(int seg_buff_size = SegHandle::SEG_BUFF_SIZE, string data_dir = "./data/wordseg", int type = SEG_USE_DEFAULT, string conf_path = "./conf/scw.conf", bool need_split_dict = false, int ner_maxterm_count = NerHandle::MAX_TERM_COUNT)
    {
      //only once init
      static bool ret = init(data_dir.c_str(), type, conf_path.c_str(), need_split_dict);

      if (!ret)
      {
        LOG(ERROR) << "fail load data " << data_dir << " " << conf_path;
        return false;
      }

      InitThread(seg_buff_size, ner_maxterm_count);

      return ret;
    }

    static bool UseWordNer()
    {
      return strategy() & SEG_USE_WORDNER || strategy() & SEG_USE_WORDNER_AUTO;
    }

    static bool UseWordRank()
    {
      return strategy() & SEG_USE_WORDRANK || strategy() & SEG_USE_WORDRANK_AUTO;
    }

    static void InitThread(int seg_buff_size = SegHandle::SEG_BUFF_SIZE, int ner_maxterm_count = NerHandle::MAX_TERM_COUNT)
    {
      handle(seg_buff_size);
      if (UseWordNer())
      {
        ner_handle(ner_maxterm_count);
      }
    }

    //�����Ǵ���SegHandle�� ������Ϊstatic��ʵ static bool seg_words(string input, SegHandle& handle)
    //Segmentor::segment(input, handle) @TODO
    static bool seg_words(string input, SegHandle& handle)
    {
      //---------�ִ�
      if (scw_segment_words(pwdict(), handle.pout, input.c_str(), input.length(), LANGTYPE_SIMP_CHINESE, (void *)flag()) < 0)
      {
        LOG(ERROR) << "Segment fail " << input << " " << input.length();
        return false;
      }
      return true;
    }

    //���ýӿ� �����ӿ� ֻ���� scw_segment_words �зֲ��������������ٽ��и���ȡ�ִʻ���tag����
    static bool SegWords(string input)
    {
      return seg_words(input, handle());
    }

    static int get_tokens(SegHandle& handle, int type = SEG_WPCOMP)
    {
      handle.nresult = scw_get_token_1(handle.pout, type, handle.tokens, handle.buf_size);
      if (strategy() & SEG_USE_OFFSETS)
      {
        handle.gen_offsets();
      }
      handle.seg_type = type;
      return handle.nresult;
    }

    int get_tokens(int type = SEG_WPCOMP)
    {
      return get_tokens(_handle);
    }

    static int GetTokens(int type = SEG_WPCOMP)
    {
      return get_tokens(handle(), type);
    }

    static vector<SegNode> get_segnodes(const SegHandle& handle)
    {
      vector<SegNode> result;
      for (int i = 0; i < handle.nresult; i++)
      {
        result.emplace_back(SegNode{ handle.tokens[i].buffer, handle.tokens[i].length,
          handle.tokens[i].offset, handle.tokens[i].type, handle.tokens[i].weight });
      }
      return result;
    }

    vector<SegNode> get_segnodes()
    {
      return get_segnodes(_handle);
    }

    static vector<SegNode> GetSegNodes()
    {
      return get_segnodes(handle());
    }

    static vector<NerNode> get_nernodes(string text, const SegHandle& handle, const NerHandle& ner_handle, bool filter = false)
    {
      vector<NerNode> result;
      int num_tags = ner_handle.pout->tag_num;
      for (int i = 0; i < num_tags; i++)
      {
        const auto& tag = ner_handle.pout->tags[i];
        int tag_offset = tag.offset;
        int tag_length = tag.length;
        int tag_type = tag.type;
        if (filter && tag.type == 0)
        {
          continue;
        }
        string tag_name = get_type2name(Segmentor::nerdict(), 1, tag_type);
        int offset = handle.tokens[tag_offset].offset;
        int length = handle.tokens[tag_offset].length;
        for (int j = 1; j < tag_length; j++)
        {
          length += handle.tokens[tag_offset + j].length;
        }
        result.emplace_back(NerNode{ gbk_substr(text, offset, length), tag_type, tag_name });
      }
      return result;
    }

    static vector<NerNode> get_nernodes(const SegHandle& handle, const NerHandle& ner_handle, bool filter = false)
    {
      vector<NerNode> result;
      int num_tags = ner_handle.pout->tag_num;
      for (int i = 0; i < num_tags; i++)
      {
        const auto& tag = ner_handle.pout->tags[i];
        int tag_offset = tag.offset;
        int tag_length = tag.length;
        int tag_type = tag.type;
        if (filter && tag.type == 0)
        {
          continue;
        }
        string tag_name = get_type2name(Segmentor::nerdict(), 1, tag_type);
        int offset = handle.tokens[tag_offset].offset;
        string word = handle.tokens[tag_offset].buffer;
        for (int j = 1; j < tag_length; j++)
        {
          word += handle.tokens[tag_offset + j].buffer;
        }
        result.emplace_back(NerNode{ word, tag_type, tag_name });
      }
      return result;
    }

    static vector<NerNode> get_sub_nernodes(string text, const SegHandle& handle, const NerHandle& ner_handle, bool filter = false)
    {
      vector<NerNode> result;
      int num_tags = ner_handle.pout->sub_tag_num;
      for (int i = 0; i < num_tags; i++)
      {
        const auto& tag = ner_handle.pout->sub_tags[i];
        int tag_offset = tag.offset;
        int tag_length = tag.length;
        int tag_type = tag.type;
        if (filter && tag.type == 0)
        {
          continue;
        }
        string tag_name = get_type2name(Segmentor::nerdict(), 1, tag_type);
        int offset = handle.tokens[tag_offset].offset;
        int length = handle.tokens[tag_offset].length;
        for (int j = 1; j < tag_length; j++)
        {
          length += handle.tokens[tag_offset + j].length;
        }
        result.emplace_back(NerNode{ gbk_substr(text, offset, length), tag_type, tag_name });
      }
      return result;
    }

    static vector<NerNode> get_sub_nernodes(const SegHandle& handle, const NerHandle& ner_handle, bool filter = false)
    {
      vector<NerNode> result;
      int num_tags = ner_handle.pout->sub_tag_num;
      for (int i = 0; i < num_tags; i++)
      {
        const auto& tag = ner_handle.pout->sub_tags[i];
        int tag_offset = tag.offset;
        int tag_length = tag.length;
        int tag_type = tag.type;
        if (filter && tag.type == 0)
        {
          continue;
        }
        string tag_name = get_type2name(Segmentor::nerdict(), 1, tag_type);
        int offset = handle.tokens[tag_offset].offset;
        string word = handle.tokens[tag_offset].buffer;
        for (int j = 1; j < tag_length; j++)
        {
          word += handle.tokens[tag_offset + j].buffer;
        }
        result.emplace_back(NerNode{ word, tag_type, tag_name });
      }
      return result;
    }

    static vector<NerNode> GetNerNodes(string text, bool filter = false)
    {
      return get_nernodes(text, handle(), ner_handle(), filter);
    }

    static vector<NerNode> GetSubNerNodes(string text, bool filter = false)
    {
      return get_sub_nernodes(text, handle(), ner_handle(), filter);
    }

    static vector<NerNode> GetNerNodes(bool filter = false)
    {
      return get_nernodes(handle(), ner_handle(), filter);
    }

    static vector<NerNode> GetSubNerNodes(bool filter = false)
    {
      return get_sub_nernodes(handle(), ner_handle(), filter);
    }

    static void MergeNewword()
    {
      merge_newword(handle());
    }


    static bool TagPostag()
    {
      if (tag_postag(handle().tokens, handle().nresult) < 0)
      {
        LOG(ERROR) << "Tagging failed";
        return false;
      }
      return true;
    }

    static bool NerTag()
    {
      return NerTag(handle());
    }

    ///basic���ȴʵ�wordrank��Ϣ����
    static vector<float> WordRank()
    {
      if (handle().seg_type != SEG_BASIC)
      {
        GetTokens(SEG_BASIC);
      }

      int nresult = handle().nresult;
      const char* terms[nresult];
      vector<float> term_values(nresult, 1.0 / nresult);
      for (int i = 0; i < nresult; i++)
      {
        terms[i] = handle().tokens[i].buffer;
      }
      
      //if fail return < 0, and input term_values unchanged
      wdr_evaluate(rankdict(), terms, nresult, &term_values[0]);
      
      return term_values;
    }

    static map<string, float> WordRankMap(const vector<float>& values)
    {
      map<string, float> result;
      int nresult = handle().nresult;
      for (int i = 0; i < nresult; i++)
      {
        result[handle().tokens[i].buffer] = values[i];
      }
      return result;
    }

    static map<string, float> WordRankMap()
    {
      return WordRankMap(WordRank());
    }

    static vector<float> NerWordRank(const vector<float>& values)
    {
      //must ner tag before NerWordRank!  NOTICE!!
      if (ner_handle().seg_type != SEG_BASIC)
      {//before doing this make sure make handle() be basic, WordRank will force this
        //LOG(INFO) << "nertag in nerwordrank";
        NerTag();
      }
      vector<float> ner_values;
      int num_tags = ner_handle().pout->tag_num;
      for (int i = 0; i < num_tags; i++)
      {
        const auto& tag = ner_handle().pout->tags[i];
        int tag_offset = tag.offset;
        int tag_length = tag.length;
        float value = values[tag_offset];
        for (int j = 1; j < tag_length; j++)
        {
          value += values[tag_offset + j];
        }
        ner_values.push_back(value);
      }
      return ner_values;
    }

    ///ner���ȴʵ�wordrank��Ϣ����
    static vector<float> NerWordRank()
    {
      auto values = WordRank();
      auto ner_values = NerWordRank(values);
      return ner_values;
    }

    static map<string, float> NerWordRankMap(const vector<float>& ner_values)
    {
      map<string, float> result;
      auto ner_nodes = GetNerNodes();
      int nresult = (int)ner_nodes.size();
      for (int i = 0; i < nresult; i++)
      {
        result[ner_nodes[i].word] = ner_values[i];
      }
      return result;
    }

    static map<string, float> NerWordRankMap(string text, const vector<float>& ner_values)
    {
      map<string, float> result;
      auto ner_nodes = GetNerNodes(text);
      int nresult = (int)ner_nodes.size();
      for (int i = 0; i < nresult; i++)
      {
        result[ner_nodes[i].word] = ner_values[i];
      }
      return result;
    }

    static map<string, float> NerWordRankMap()
    {
      return NerWordRankMap(NerWordRank());
    }

    static map<string, float> NerWordRankMap(string text)
    {
      return NerWordRankMap(text, NerWordRank());
    }

    ///��ȡ�ض��ʵ�wordrank��Ϣ,ע��handle��Ҫ��basic����tokens,������WordRank()֮�������ִ�У�WordRank��ǿ��basic
    static float GetWordRank(int offset, int length, const vector<float>& values)
    {
      float value = 0.;
      CHECK_EQ(handle().seg_type, SEG_BASIC);
      int end = offset + length;
      size_t i = 0;
      while(i < handle().nresult && handle().tokens[i].offset < offset)
      {
        i++;
      }
      for (size_t j = i; j < handle().nresult; j++)
      {
        if (handle().tokens[j].offset + length > end)
        {
          break;
        }
        value += values[j];
      }
      return value;
    }

    static bool NerTag(SegHandle& handle)
    {
      if (ner_tag(nerdict(), handle.tokens, handle.nresult, ner_handle().pout, 1) < 0)
      {
        LOG(ERROR) << "Wordner tagging failed";
        return false;
      }
      ner_handle().nresult = (int)ner_handle().size();
      ner_handle().seg_type = handle.seg_type;
      return true;
    }

    //@TODO can be static with handle outside Segmentor
    static bool segment(string input, SegHandle& handle, int type = SEG_WPCOMP)
    {
      //---------�ִ�
      int* pflag = flag() == 0 ? NULL : &flag();
      if (scw_segment_words(pwdict(), handle.pout, input.c_str(), input.length(), LANGTYPE_SIMP_CHINESE, (void *)pflag) < 0)
      {
        LOG(ERROR) << "Segment fail " << input << " " << input.length();
        return false;
      }

      //TODO merge newword now not ok with split dict
      if (type != SEG_MERGE_NEWWORD || !handle.pout->pnewword->newwordbtermcount)
      {
        if (split_dict())
        {//---------���û���Ҫ���зִʴ���
          handle.nresult = seg_split(split_dict(), handle.pout, handle.tokens, handle.buf_size);
        }
        else
        {//---�ִ�תtoken_t
          handle.nresult = scw_get_token_1(handle.pout, type, handle.tokens, handle.buf_size);
        }
      }
      else
      {
        handle.nresult = merge_newword(handle);
      }

      handle.seg_type = type;

      //notice you can use if (strategy & ) also
      if (strategy() & SEG_USE_POSTAG)
      {
        //----------��ע
        if (tag_postag(handle.tokens, handle.nresult) < 0)
        {
          LOG(ERROR) << "Tagging failed";
          return false;
        }
      }

      //FIXME why ner_handle().result = -1 will core ?
      if (strategy() & SEG_USE_WORDNER_AUTO)
      {
        //1 means chinese
        //if (ner_tag(nerdict(), handle.tokens, handle.nresult, ner_handle().pout, 1) < 0)
        //{
        //  LOG(ERROR) << "Wordner tagging failed";
        //  return false;
        //}
        if (!NerTag(handle))
        {
          return false;
        }
      }

      if (strategy() & SEG_USE_OFFSETS)
      {
        handle.gen_offsets();
      }

      return true;
    }

    static bool segment(string input, SegHandle& handle, vector<string>& result,
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

    static string segment(string input, SegHandle& handle, string sep, int type = SEG_WPCOMP)
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
      segment(input, _handle, result, type);
      return result;
    }

    //��ݽӿ�
    static vector<string> Segment(string input, int type = SEG_WPCOMP)
    {
      vector<string> result;
      segment(input, handle(), result, type);
      return result;
    }

    static bool Segment_(string input, int type = SEG_WPCOMP)
    {
      return segment(input, handle(), type);
    }

    //���ýӿ� �зֲ��ҳ��Ը���tag���� ���ǲ�����string��� �����ٴ���
    static bool Seg(string input, int type = SEG_WPCOMP)
    {
      return segment(input, handle(), type);
    }

    bool segment(string input, vector<string>& result, int type = SEG_WPCOMP)
    {
      return segment(input, _handle, result, type);
    }

    static bool Segment(string input, vector<string>& result, int type = SEG_WPCOMP)
    {
      return segment(input, handle(), result, type);
    }

    string segment(string input, string sep, int type = SEG_WPCOMP)
    {
      return segment(input, _handle, sep, type);
    }

    static string Segment(string input, string sep, int type = SEG_WPCOMP)
    {
      return segment(input, handle(), sep, type);
    }

    //��ҪΪ��python��װ�ķִʻ�ȡoffset,weight��Ϣ
    bool segment(string input, vector<SegNode>& result, int type = SEG_WPCOMP)
    {
      bool ret = segment(input, _handle, type);
      if (!ret)
        return false;
      for (int i = 0; i < _handle.nresult; i++)
      {
        result.emplace_back(SegNode{ _handle.tokens[i].buffer, _handle.tokens[i].length,
          _handle.tokens[i].offset, _handle.tokens[i].type, _handle.tokens[i].weight });
      }
      return true;
    }

    vector<SegNode> cut(string input, int type = SEG_WPCOMP)
    {
      vector<SegNode> result;
      bool ret = segment(input, _handle, type);
      if (!ret)
        return result;
      for (int i = 0; i < _handle.nresult; i++)
      {
          result.emplace_back(SegNode{ _handle.tokens[i].buffer,
            _handle.tokens[i].length,
            _handle.tokens[i].offset,
            _handle.tokens[i].type,
            _handle.tokens[i].weight });
      }

      return result;
    }

    static vector<SegNode> Cut(string input, int type = SEG_WPCOMP)
    {
      vector<SegNode> result;
      bool ret = segment(input, handle(), type);
      if (!ret)
        return result;

      for (int i = 0; i < handle().nresult; i++)
      {
        result.emplace_back(SegNode{ handle().tokens[i].buffer,
          handle().tokens[i].length,
          handle().tokens[i].offset,
          handle().tokens[i].type,
          handle().tokens[i].weight });
      }
    
      return result;
    }

    static bool Segment(string input, vector<SegNode>& result, int type = SEG_WPCOMP)
    {
      bool ret = segment(input, handle(), type);
      if (!ret)
        return false;
      for (int i = 0; i < handle().nresult; i++)
      {
        result.emplace_back(SegNode{ handle().tokens[i].buffer, handle().tokens[i].length,
          handle().tokens[i].offset, handle().tokens[i].type, handle().tokens[i].weight });
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

    SegHandle& get_handle()
    {
      return _handle;
    }

    static SegHandle& handle(int buf_size = SegHandle::SEG_BUFF_SIZE)
    {
      static thread_local SegHandle _handle = ([&](){
        SegHandle _handle(buf_size);
        return _handle;
      })();
      return _handle;
    }

    static NerHandle& ner_handle(int ner_maxterm_count = NerHandle::MAX_TERM_COUNT)
    {
      static thread_local NerHandle _handle = ([&](){
        NerHandle _handle(nerdict(), ner_maxterm_count);
        return _handle;
      })();
      return _handle;
    }

  private:
    static bool init(const char* data_dir, int type = 0, const char* conf_path = "./conf/scw.conf", bool need_split_dict = false)
    {
      strategy() |= type;
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
          VLOG(1) << "Load segmentor dict data ok";
        }

        if (strategy() & SEG_USE_POSTAG)
        { //--------------������ע
          char tag_dict_path[2048];
          sprintf(tag_dict_path, "%s/%s", data_dir, "tagdict");
          ret = tag_open(tag_dict_path);
          CHECK_EQ(ret, 0) << tag_dict_path;
          VLOG(1) << "Tag open ok";
        }
        else
        {
          VLOG(1) << "Do not use pos tag";
        }

        if (UseWordNer())
        {
          char ner_dict_path[2048];
          sprintf(ner_dict_path, "%s/%s", data_dir, "nedict");
          nerdict() = ner_dict_load(ner_dict_path);
          CHECK_NE(nerdict(), NULL);
        }
        string split_dict_path = "need_split";
        string split_dict_name = "need_split";
        if (UseWordRank())
        {
          {
            char dict_path[2048];
            sprintf(dict_path, "%s/%s", data_dir, "wordrank/trkdict");
            trunkdict() = trk_create(dict_path);
            CHECK_NE(trunkdict(), NULL);
          }
          {
            char dict_path[2048];
            sprintf(dict_path, "%s/%s", data_dir, "wordrank/rankdict");
            rankdict() = wdr_create(dict_path);
            CHECK_NE(rankdict(), NULL);
          }
          { //NOTICE be sure this file not exceeds 4096, otherwise might change in UlDict!
            char dict_path[2048];
            sprintf(dict_path, "%s/%s", data_dir, "wordrank/wordtagdict/word_tag.txt");
            UlDict uldict(dict_path);
            wordtagdict() = uldict.wordDict;
            CHECK_NE(wordtagdict(), NULL);
          }

          need_split_dict = true;
          split_dict_path = "wordrank/splitphrasedict";
          split_dict_name = "splitphrasedict";
        }

        if (need_split_dict)
        {	//---------------���Դ�need split�ֵ䣬��������ڻ��ߴ򿪳���Ͳ�ʹ��
          char dict_path[2048];
          sprintf(dict_path, "%s/%s", data_dir, split_dict_path.c_str());
          split_dict() = ds_load(dict_path, split_dict_name.c_str());
          if (!split_dict())
          {
            VLOG(1) << "Do not use split dictionary, not find " << dict_path;
          }
          if (UseWordRank())
          {
            CHECK_NE(split_dict(), NULL);
          }
        }

      }
      VLOG(0) << "Segmentor init ok";
      return true;
    }

    //����Ƚ���� c++û������ ����python���ܺܺô���static ����û��  ������������� 
    //SegHandle scw_destroy (pout)���core
    /*	static SegHandle& GetSegHandle(int buf_size = SegHandle::SEG_BUFF_SIZE)
      {
      static SegHandle _handle(buf_size);
      return _handle;
      }*/

    //TODO check offset make sure it is same as phrase
    static int merge_newword(SegHandle& handle)
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
    //�ر��ǵ�����ͬʱ���ڶ����ͬSegmentorʹ�ò�ͬ��SegDict���� ����staticֱ��ָ��Ҳ����(����������Ҫ�����潫dict��ʼ����Ȼ���ַ�������ڲ����������ڲ�dict��ʼ�� ����ÿ���̶߳���һ��dict����copy)
    //��SegDict + static �ô��ǲ�ͬsegmentor���Բ�ͬSegDict ������ÿ���߳�ֻ��һ��Segmentor ���ܶ����ͬDict����ͬ���͵�Segmentor��Ϊ��static һ��Segmentor����ֻ�ܶ�Ӧһ����Դ 
    //��SegDict + ָ�� ����� ��װ�Բ�һ�� �ⲿ����dict һ��Segmentor���Զ����ͬʵ����Ӧʹ�ò�ͬdict
    //����������ֻ��һ��Segmentor һ������dict ��ô����ϲ���������װԭ��
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

    //only used if use wordner
    static ner_dict_t*& nerdict()
    {
      static ner_dict_t* _nerdict = NULL;
      return _nerdict;
    }

    //below used only in wordrank
    static trunk_dict_t*& trunkdict()
    {
      static trunk_dict_t* _trunkdict = NULL;
      return _trunkdict;
    }

    static rank_dict_t*& rankdict()
    {
      static rank_dict_t* _rankdict = NULL;
      return _rankdict;
    }

    static Sdict_build*& wordtagdict()
    {
      static Sdict_build* _wordtagdict = NULL;
      return _wordtagdict;
    }

    static int& strategy()
    {
      static int _strategy = SEG_USE_DEFAULT; //�Ƿ�ʹ��pos tag �ȵ�
      return _strategy;
    }

    //ע����py��װ����Ҫʹ��SetStrategy
    static void set_strategy(int strategy_)
    {
      strategy() = strategy_;
    }

    static int& flag(int flag_ = 0)
    {//dynfloag �Ƿ���crf�� ��ǰ��Ҫ���������Ƿ���crf
      static int _flag = flag_;
      return _flag;
    }

    static void set_flat(int flag_)
    {
      flag() = flag_;
    }

  private:
    //scw_conf_t* pgconf;
    SegHandle _handle;
  };

#ifndef NO_BAIDU_DEP
  //util
  inline void print_seg_result(const SegHandle& handle)
  {
    for (int i = 0; i < handle.nresult; i++)
    {
      std::cerr << handle.tokens[i].buffer << " " << handle.tokens[i].offset << " " << handle.tokens[i].length << endl;
    }
  }

  //inline string get_pos_str(size_t type)
  //{
  //  const static vector<string> pos_strs = { "", "Ag", "Dg", "Ng", "Tg", "Vg", "a", "ad", "an", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "nr", "ns", "nt", "nx", "nz", "o", "p", "q", "r", "s", "t", "u", "v", "vd", "vn", "w", "y", "z"};
  //  return pos_strs[type];
  //}

  inline bool is_noun(size_t type)
  {
    const char* stag = ::get_pos_str((unsigned int)type);
    return stag && stag[0] == 'n';
  }

  inline void print_seg_posttag_result(const gezi::SegHandle& handle)
  {
    for (int i = 0; i < handle.nresult; i++)
    {
      const char* stag = ::get_pos_str(handle.tokens[i].type);
      if (stag)
        printf("%s/%s  ", handle.tokens[i].buffer, stag);
      else
        printf("%s  ", handle.tokens[i].buffer);
    }
    printf("\n");
  }

  inline void print_seg_result()
  {
    print_seg_result(Segmentor::handle());
  }

  inline void print_seg_posttag_result()
  {
    print_seg_posttag_result(Segmentor::handle());
  }

  inline void print_ner_result(string input, const SegHandle& handle, const NerHandle& ner_handle)
  {
    LOG(INFO) << "tag result";
    int num_tags = ner_handle.pout->tag_num;
    for (int i = 0; i < num_tags; i++)
    {
      const auto& tag = ner_handle.pout->tags[i];
      int tag_offset = tag.offset;
      int tag_length = tag.length;
      int tag_type = tag.type;
      string tag_name = get_type2name(Segmentor::nerdict(), 1, tag_type);
      Pval2(tag_offset, tag_length);
      int offset = handle.tokens[tag_offset].offset;
      int length = handle.tokens[tag_offset].length;
      for (int j = 1; j < tag_length; j++)
      {
        length += handle.tokens[tag_offset + j].length;
      }
      Pval5(gbk_substr(input, offset, length), offset, length, tag_type, tag_name);
    }

    LOG(INFO) << "sub tag result";
    int num_sub_tags = ner_handle.pout->sub_tag_num;
    for (int i = 0; i < num_sub_tags; i++)
    {
      const auto& tag = ner_handle.pout->sub_tags[i];
      int tag_offset = tag.offset;
      int tag_length = tag.length;
      int tag_type = tag.type;
      string tag_name = get_type2name(Segmentor::nerdict(), 1, tag_type);
      Pval2(tag_offset, tag_length);
      int offset = handle.tokens[tag_offset].offset;
      int length = handle.tokens[tag_offset].length;
      for (int j = 1; j < tag_length; j++)
      {
        length += handle.tokens[tag_offset + j].length;
      }
      Pval5(gbk_substr(input, offset, length), offset, length, tag_type, tag_name);
    }
  }

#endif

#endif // !NO_BAIDU_DEP
} //----end of namespace gezi



#endif  //----end of SEGMENTOR_H_
