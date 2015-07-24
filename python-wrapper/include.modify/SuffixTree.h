#ifndef SUFFIX_TREE_H_
#define SUFFIX_TREE_H_
#include <string>
#include <map>
#include <deque>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include "hashmap_util.h"
#include "string_util.h"
namespace gezi
{
class SuffixTree
{
public:
SuffixTree(const wstring& end_mark = L"#");
virtual ~SuffixTree();
void init();
void reset_status();
void reset();
void free();
void clear();
inline size_t tree_size();
inline size_t size();
void build(const wstring& text);
void add(const wstring& text);
void remove();
void remove(int id);
int find_longest(const wstring& text, int start);
int find_longest(const wstring& text, int start, int & freq);
bool find(const wstring& text, int start = 0);
int find_freq(const wstring& text, int start = 0);
void remove_();
public:
void write_result(const string & file);
void print();
};
}
#endif
