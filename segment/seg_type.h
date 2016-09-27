/** 
 *  ==============================================================================
 * 
 *          \file   seg_type.h
 *
 *        \author   gezi  
 *          
 *          \date   2010-09-25 22:06:50.832098
 *  
 *  \Description: seg�����͵Ķ���
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
///Ϊ��encoder�Լ��ִʹ��õ�һ���ֳ�������
static const short FRST_OFFSET_CH = 8000; ///���ֲ����������򳤶�
static const short KEYCNTMAX = 15; ///�����������Ŀ
static const short AMBOFFSET = 16; ///���崮�зִ洢ƫ��
static const int KEYTYPEBIT = 0xffff; //���崮�зֵ��ֽ���Ϣλ
static const short DIANYALIGUO = 0x7fff; //"��ѹ����"���͵���崮����, ��ʾ��Ҫ��ȫ�з֣�������Ҫȥ������֧�֣����Ӽ���ȫ�з� TODO
const static int kMaxAmbiLen = 15; //��ǰ���������崮>=16��Ϊ ���Ǵ洢��ʱ��ֻ��ռ��16��λ��,ע�������ģ�ͱ���һ��
const static double threshold = 0.98; //���ʷִʸ�����ֵ

enum LexType
{
    ambiguity, common, special, english, unknown
}; //�ʵ����ͣ�����/����/��ר/Ӣר
static const char* const LexTypeStr[] = {"ambiguity", "common", "special", "english", "unknown"};

//typedef vector<short> u16_string;
///-------tag for gbk_encoderȷ��������ģʽ��������ѵ��ģʽ

/***online serving*/
struct OnlineMode
{
};

/**offline training*/
struct OfflineMode
{
};
#ifndef WorkWithOldSeg
///�ִʽ���Ĵ洢

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
///-------------�з�����

struct MaxSegBase
{
};

struct OmniSegBase
{
};

/**����з�*/
struct MaxSegType : public MaxSegBase
{
};

struct MaxProbSeg : public MaxSegBase
{
};

/**�����������Ԥ���������з�*/
struct MaxSegWithAmbi : public MaxSegBase
{
};

/**�зֽ���洢�ʱ�ŵ����/�����з�*/
struct MaxSegWithIdentifer : public MaxSegBase
{
    
};

/**
 * ȫ�з֣��洢���п��ܵĴʣ������������ͽ������
 */
struct OmniSegType : public OmniSegBase
{
};

/**
 * �������������ȫ�зֶ��� ÿ�δӵ�ǰλ�ÿ��� ���+��С �з�
 */
struct OmniSegWithAmbi : public OmniSegBase
{//ģ��ԭ��ȫ�з� "Ϊ�����ʵ��" �������ֵ�������û��Ϊ���� �������г� ����,��Ϊ��һλ���Ǵӳɴ�λ�õ���һ��λ��
};

/**
 * ������ȫ�з�
 */
struct OmniSegWithAmbiFull : public OmniSegBase
{//������ȫ�з� "Ϊ����"�����г� Ϊ�ˣ����� ���ҵ��ֿ����г����ı�IK��һЩ
};

/**
 * ������ȫ�з�,��������·��
 */
struct OmniSegWithAmbiFullPath : public OmniSegBase
{//������ȫ�з� "Ϊ����"�����г� "Ϊ��"��"��" "Ϊ" "����"
};

struct OmniSegWithAmbiIK : public OmniSegBase
{//������ȫ�з� "Ϊ����"�����г� "Ϊ��"��"����" ��ȫ����IK��ȫ�з֣�ֻ�Ǿ�����֤��������Ĵ�

};

} //----end of namespace segment

#endif  //----end of SEG_TYPE_H_
