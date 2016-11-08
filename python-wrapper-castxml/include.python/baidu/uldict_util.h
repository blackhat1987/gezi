#ifndef ULDICT_UTIL_H_
#define ULDICT_UTIL_H_
#include <string>
#include "ul_dict.h"
#include "ul_sign.h"
namespace gezi
{
using std::string;
class UlDict
{
public:
const static int kMaxLine = 1024;
Sdict_build* wordDict;
UlDict();
UlDict(string file, int dictSize = 4096);
~UlDict();
int load(string file, int dictSize = 4096);
Sdict_build*& word_dict();
int init_dict(char* file, int dictSize = 4096);
void save(char* path, char* filename);
inline bool query_dict(char* word);
};
}
#endif
