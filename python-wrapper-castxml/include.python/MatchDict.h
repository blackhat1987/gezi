#ifndef MATCH_DICT_H_
#define MATCH_DICT_H_
#include "ul_dictmatch.h"
#include "log_util.h"
#include <vector>
#include <string>
#include <set>
#include <map>
namespace gezi {
using std::vector;
using std::string;
using std::pair;
using std::set;
using std::map;
static const int MATCH_DICT_SEARCH_ALL = DM_OUT_ALL;
static const int MATCH_DICT_SEARCH_LONGEST = DM_OUT_FMM;
class MatchDict
{
public:
friend class MatchSearcher;
MatchDict();
MatchDict(string file);
~MatchDict();
struct Node
{
string word;
int offset;
int length;
int property;
bool operator == (const Node& other) const;
};
bool init(string file);
bool Load(string file);
bool load(string file);
int search(string text, dm_pack_t* result, int strategy=MATCH_DICT_SEARCH_LONGEST);
int search_count(string text, dm_pack_t* result, int strategy = MATCH_DICT_SEARCH_LONGEST);
int search_count(string text, int strategy = MATCH_DICT_SEARCH_LONGEST);
vector<Node> search(string text, int strategy = MATCH_DICT_SEARCH_LONGEST);
set<string> search_words(string text, int strategy = MATCH_DICT_SEARCH_LONGEST);
vector<string> search_words_byseq(string text, int strategy = MATCH_DICT_SEARCH_LONGEST);
map<string, int> search_properties(string text, int strategy = MATCH_DICT_SEARCH_LONGEST, bool count_property=false);
int SearchCount(string text, int strategy = MATCH_DICT_SEARCH_LONGEST);
bool has_word(string text, int type = 1, int strategy = MATCH_DICT_SEARCH_LONGEST);
static void set_dm_pack(int maxMatchCount);
public:
static dm_pack_t* dm_pack(int maxMatchCount = 100000);
static void free_dm_pack();
private:
dm_dict_t* _dict;
};
class MatchSearcher
{
public:
MatchSearcher(MatchDict* dict, int maxMatchCount = 1000);
MatchSearcher(const MatchDict& dict, int maxMatchCount = 1000);
int search_count(const MatchDict& dict, string text);
int search_count(MatchDict* dict, string text);
dm_pack_t* search(const MatchDict& dict, string text);
dm_pack_t* search(MatchDict* dict, string text);
int search_count(string text);
dm_pack_t* search(string text);
dm_pack_t* result();
bool has_word(string text);
int max_match_count();
private:
MatchDict* _dict;
dm_pack_t* _result;
int _maxMatchCount;
};
}
#endif
