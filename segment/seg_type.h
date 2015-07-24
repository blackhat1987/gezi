/** 
 *  ==============================================================================
 * 
 *          \file   seg_type.h
 *
 *        \author   gezi  
 *          
 *          \date   2010-09-25 22:06:50.832098
 *  
 *  \Description: seg中类型的定义
 *  ==============================================================================
 */

#ifndef SEG_TYPE_H_
#define SEG_TYPE_H_
#include <tr1/unordered_map>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <algorithm>
#include <functional>
#include <boost/bind.hpp>
#include <boost/tuple/tuple.hpp>
namespace segment
{
using std::string;
using std::vector;
using boost::tuple;
typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned int uint;
typedef std::tr1::unordered_map<ushort, short> HashMapUs_s;
//typedef std::map<ushort, short> HashMapUs_s;
typedef vector<string> VEC_STR;
typedef vector<int> VEC_INT;
typedef std::map<string, int> MAP_STR_INT;
typedef std::pair<string, int> PAIR_STR_INT;
typedef vector<PAIR_STR_INT> VEC_PAIR_STR_INT;
typedef std::basic_string<short> u16_string;
///为了encoder以及分词共用的一部分常量定义
static const short FRST_OFFSET_CH = 8000; ///汉字部分首字区域长度
static const short KEYCNTMAX = 15; ///最多连续词数目
static const short AMBOFFSET = 16; ///歧义串切分存储偏移
static const int KEYTYPEBIT = 0xffff; //歧义串切分低字节信息位
static const short DIANYALIGUO = 0x7fff; //"电压力锅"类型的岐义串编码, 标示需要完全切分，可能需要去掉这种支持，不加即是全切分 TODO
const static int kMaxAmbiLen = 15; //当前不允许歧义串>=16因为 我们存储的时候只能占据16个位置,注意和离线模型保持一致
const static double threshold = 0.98; //概率分词概率阙值

enum LexType
{
    ambiguity, common, special, english, unknown
}; //词典类型，汉歧/汉普/汉专/英专
static const char* const LexTypeStr[] = {"ambiguity", "common", "special", "english", "unknown"};

//typedef vector<short> u16_string;
///-------tag for gbk_encoder确定是在线模式还是离线训练模式

/***online serving*/
struct OnlineMode
{
};

/**offline training*/
struct OfflineMode
{
};
#ifndef WorkWithOldSeg
///分词结果的存储

struct Term
{

    Term()
    {
    }

    Term(int pos_, int len_, int level_)
    : pos(pos_), len(len_), level(level_)
    {
    }

    bool operator<(const Term & other) const
    {
        return pos < other.pos || (pos == other.pos && len < other.len);
//                ||(pos == other.pos && len == other.len && level == other.level);
    }
    int pos;
    short len;
    short level;
};
#endif
///-------------切分类型

struct MaxSegBase
{
};

struct OmniSegBase
{
};

/**最大切分*/
struct MaxSegType : public MaxSegBase
{
};

struct MaxProbSeg : public MaxSegBase
{
};

/**带有离线岐义预处理的最大切分*/
struct MaxSegWithAmbi : public MaxSegBase
{
};

/**切分结果存储词编号的最大/概率切分*/
struct MaxSegWithIdentifer : public MaxSegBase
{
    
};

/**
 * 全切分，存储所有可能的词，包括覆盖岐义和交叉岐义
 */
struct OmniSegType : public OmniSegBase
{
};

/**
 * 本质上这个不是全切分而是 每次从当前位置考虑 最大+最小 切分
 */
struct OmniSegWithAmbi : public OmniSegBase
{//模拟原有全切分 "为人民办实事" 如果岐义字典里面有没有为人民， 不可以切出 人民,因为下一位置是从成词位置的下一个位置
};

/**
 * 完整的全切分
 */
struct OmniSegWithAmbiFull : public OmniSegBase
{//完整的全切分 "为人民"可以切出 为人，人民 而且单字考虑切出来的比IK多一些
};

/**
 * 完整的全切分,包括完整路径
 */
struct OmniSegWithAmbiFullPath : public OmniSegBase
{//完整的全切分 "为人民"可以切出 "为人"，"民" "为" "人民"
};

struct OmniSegWithAmbiIK : public OmniSegBase
{//完整的全切分 "为人民"可以切出 "为人"，"人民" 完全仿照IK的全切分，只是尽量保证给有意义的词

};

} //----end of namespace segment

#endif  //----end of SEG_TYPE_H_
