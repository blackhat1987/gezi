#ifndef SEGMENTOR_H_
#define SEGMENTOR_H_
#ifndef NO_BAIDU_DEP
#include "scwdef.h"
#include "property.h"
#include "isegment.h"
#ifdef u_int
#undef  u_int
#endif
#include "ipostag.h"
#include "tagdict.h"
//extern const char* get_pos_str(unsigned int nPOS);
#include "iwordner.h"
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
namespace gezi {
using std::vector;
using std::string;
using std::map;
#ifndef NO_BAIDU_DEP
static const int  SEG_USE_NONE = 0;
static const int SEG_USE_POSTAG = 1;
static const int SEG_USE_SPLIT = 2;
static const int SEG_USE_TRIE = 4;
static const int SEG_USE_OFFSETS = 8;
static const int SEG_USE_WORDNER = 16;
static const int SEG_USE_WORDNER_AUTO = 32;
static const int SEG_USE_WORDRANK = 64;
static const int SEG_USE_WORDRANK_AUTO = 128;
static const int SEG_USE_ALL = 255;
static const int  SEG_USE_DEFAULT = SEG_USE_OFFSETS;
static const int SEG_MERGE_NEWWORD = SCW_OUT_WPCOMP | SCW_OUT_NEWWORD;
static const int SEG_WPCOMP = SCW_OUT_WPCOMP;
static const int SEG_NEWWORD = SCW_OUT_NEWWORD;
static const int SEG_BASIC = SCW_OUT_BASIC;
static const int SEG_HUMAN_NAME = SCW_OUT_HUMANNAME;
struct SegHandle
{
static const int SEG_BUFF_SIZE = 20480;
SegHandle(int bufsize = SEG_BUFF_SIZE);
void init(int buf_size_ = SEG_BUFF_SIZE);
void clear();
~SegHandle();
size_t offset(int i) const;
size_t length(int i) const;
size_t len(int i) const;
string word(int i) const;
size_t type(int i) const;
size_t weight(int i) const;
void gen_offsets();
size_t size() const;
scw_out_t* pout;
token_t* tokens;
vector<token_t> token_vec;
int nresult;
int buf_size;
int seg_type;
};
struct NerHandle
{
static const int MAX_TERM_COUNT = 256;
NerHandle();
#ifndef GCCXML
NerHandle(ner_dict_t* pnerdict, int maxt_term_count = MAX_TERM_COUNT);
#endif
~NerHandle();
void clear();
size_t size();
size_t subtag_size();
int nresult;
ner_out_t *pout;
int seg_type;
};
struct SegNode
{
string word;
int length;
int offset;
int type;
int weight;
SegNode();
SegNode(string word_, int length_, int offset_, int type_, int weight_);
bool operator == (const SegNode& other) const;
};
struct NerNode
{
string word;
int type;
string name;
NerNode();
NerNode(string word_, int type_, string name_ = "");
bool operator == (const NerNode& other) const;
};
class Segmentor
{
public:
Segmentor(int seg_buff_size = SegHandle::SEG_BUFF_SIZE);
~Segmentor();
static void uninit();
static void Uninit();
Segmentor& set_flag(int flag_);
static void SetFlag(int flag_);
static void SetStrategy(int strategy_);
static void AddStrategy(int strategy_);
static void add_strategy(int strategy_);
static bool init(string data_dir = "./data/wordseg", int type = SEG_USE_DEFAULT, string conf_path = "./conf/scw.conf", bool need_split_dict = false);
static bool Init(int seg_buff_size = SegHandle::SEG_BUFF_SIZE, string data_dir = "./data/wordseg", int type = SEG_USE_DEFAULT, string conf_path = "./conf/scw.conf", bool need_split_dict = false, int ner_maxterm_count = NerHandle::MAX_TERM_COUNT);
static bool UseWordNer();
static bool UseWordRank();
static void InitThread(int seg_buff_size = SegHandle::SEG_BUFF_SIZE, int ner_maxterm_count = NerHandle::MAX_TERM_COUNT);
static bool seg_words(string input, SegHandle& handle);
static bool SegWords(string input);
static int get_tokens(SegHandle& handle, int type = SEG_WPCOMP);
int get_tokens(int type = SEG_WPCOMP);
static int GetTokens(int type = SEG_WPCOMP);
static vector<SegNode> get_segnodes(const SegHandle& handle);
vector<SegNode> get_segnodes();
static vector<SegNode> GetSegNodes();
static vector<NerNode> get_nernodes(string text, const SegHandle& handle, const NerHandle& ner_handle, bool filter = false);
static vector<NerNode> get_nernodes(const SegHandle& handle, const NerHandle& ner_handle, bool filter = false);
static vector<NerNode> get_sub_nernodes(string text, const SegHandle& handle, const NerHandle& ner_handle, bool filter = false);
static vector<NerNode> get_sub_nernodes(const SegHandle& handle, const NerHandle& ner_handle, bool filter = false);
static vector<NerNode> GetNerNodes(string text, bool filter = false);
static vector<NerNode> GetSubNerNodes(string text, bool filter = false);
static vector<NerNode> GetNerNodes(bool filter = false);
static vector<NerNode> GetSubNerNodes(bool filter = false);
static void MergeNewword();
static bool TagPostag();
static bool NerTag();
static vector<float> WordRank();
static map<string, float> WordRankMap(const vector<float>& values);
static map<string, float> WordRankMap();
static vector<float> NerWordRank(const vector<float>& values);
static vector<float> NerWordRank();
static map<string, float> NerWordRankMap(const vector<float>& ner_values);
static map<string, float> NerWordRankMap(string text, const vector<float>& ner_values);
static map<string, float> NerWordRankMap();
static map<string, float> NerWordRankMap(string text);
static float GetWordRank(int offset, int length, const vector<float>& values);
static bool NerTag(SegHandle& handle);
static bool segment(string input, SegHandle& handle, int type = SEG_WPCOMP);
static bool segment(string input, SegHandle& handle, vector<string>& result,
int type = SEG_WPCOMP);
static string segment(string input, SegHandle& handle, string sep, int type = SEG_WPCOMP);
vector<string> segment(string input, int type = SEG_WPCOMP);
static vector<string> Segment(string input, int type = SEG_WPCOMP);
static bool Segment_(string input, int type = SEG_WPCOMP);
static bool Seg(string input, int type = SEG_WPCOMP);
bool segment(string input, vector<string>& result, int type = SEG_WPCOMP);
static bool Segment(string input, vector<string>& result, int type = SEG_WPCOMP);
string segment(string input, string sep, int type = SEG_WPCOMP);
static string Segment(string input, string sep, int type = SEG_WPCOMP);
bool segment(string input, vector<SegNode>& result, int type = SEG_WPCOMP);
vector<SegNode> cut(string input, int type = SEG_WPCOMP);
static vector<SegNode> Cut(string input, int type = SEG_WPCOMP);
static bool Segment(string input, vector<SegNode>& result, int type = SEG_WPCOMP);
SegHandle& get_handle();
static SegHandle& handle(int buf_size = SegHandle::SEG_BUFF_SIZE);
static NerHandle& ner_handle(int ner_maxterm_count = NerHandle::MAX_TERM_COUNT);
private:
static bool init(const char* data_dir, int type = 0, const char* conf_path = "./conf/scw.conf", bool need_split_dict = false);
static int merge_newword(SegHandle& handle);
static scw_worddict_t*& pwdict();
static Sdict_search*& split_dict();
static ner_dict_t*& nerdict();
static trunk_dict_t*& trunkdict();
static rank_dict_t*& rankdict();
static Sdict_build*& wordtagdict();
static int& strategy();
static void set_strategy(int strategy_);
static int& flag(int flag_ = 0);
static void set_flat(int flag_);
private:
SegHandle _handle;
};
#ifndef NO_BAIDU_DEP
inline void print_seg_result(const SegHandle& handle);
inline bool is_noun(size_t type);
inline void print_seg_posttag_result(const gezi::SegHandle& handle);
inline void print_seg_result();
inline void print_seg_posttag_result();
inline void print_ner_result(string input, const SegHandle& handle, const NerHandle& ner_handle);
#endif
#endif
}
#endif
