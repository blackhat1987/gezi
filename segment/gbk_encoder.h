/** 
 *  ==============================================================================
 * 
 *          \file   gbk_encoder.h
 *
 *        \author   gezi  
 *          
 *          \date   2010-09-25 16:32:02.142693
 *  
 *  \Description:   对原分词代码中gbk string 编码的提出, 该编码主要配合双数组树的使用
 *                  针对gbk字符的编码 包括中英文
 *                  由于对于扩展汉字位针对特定文本给出不同编码所以需要
 *
 *              //***********双数组字位设计************
                //设置首字区域为8000个汉字位，95个ascii码字位[32-126]，1-6768位为GB2312汉字，后面1232字位为扩展汉字字位备用
                //前6768位按GB2312内码映射后再加1作为序号，后1232位用hash存储内码，以索引+6769为序号，最后将hash存成文件
                //歧义串切分信息用int大小的二进制数记录，两低字节为0，两高字节为切分信息
 *
 *               GBKEncoder 分为两种模式 OnlineMode, OfflineMode对应不同的获取编码细节代码，因为
 *               离线可能需要对于 后1232位用hash存储内码，以索引+6769为序号 区别仅在于 getNonGB2312ChCode
 *               另外在线构造需要给定输入文件
 *
 *               注意这种编码英文在后面 那么 原有的string 排序和 转换编码的排序 对于会有不同
 *  ==============================================================================
 */

#ifndef GBK_ENCODER_H_
#define GBK_ENCODER_H_
#include <fstream>
#include <iostream>
#include "seg_type.h"
#include "gbk_string_help.h"

namespace segment {
template <typename WorkMode = OnlineMode>
        class GBKEncoderT
{
protected:
    static const short AMBOFFSET = 16; //歧义串切分存储偏移
    static const short GB2312_OFFSET = 6768; //GB2312区域长度
    static const int KEYTYPEBIT = 0xffff; //歧义串切分低字节信息位
private:
    typedef std::pair<ushort, short> KeyMap; //code,index
    HashMapUs_s m_hmCode2Idx; //GBK扩展字内码映射
public:
    ///读入离线处理好的hash构造 for online
    GBKEncoderT(const string& fmap)
    {
        load(fmap);
    }
    GBKEncoderT()
    {
    }
    bool load(const string& fmap)
    {
        std::ifstream fMap(fmap.c_str(), std::ios::binary);
        if (!fMap.is_open())
        {
            std::cerr << "Lod gbk encode map failed."
                    << "Func(Load) error. " << fmap << std::endl;
            return false;
        }
        KeyMap kmp;
        while (!fMap.eof())
        {
            fMap.read((char*) (&kmp), sizeof (kmp));
            m_hmCode2Idx.insert(std::make_pair(kmp.first, kmp.second));
        }
        return true;
    }
    ///获取非汉字的内码 online and offline both
    short getENCode(char ch) const
    {
        //get half-wild encode
        if (ch >= 32 && ch <= 126)
        {
            return (short) ch - 32 + FRST_OFFSET_CH + 1;
        }
        else
        {
            return 0;
        }
    }
    bool isENCode(short code) const
    {
        return code > FRST_OFFSET_CH;
    }
    bool isCHCode(short code) const
    {
        return code > 0 && code <= FRST_OFFSET_CH;
    }

    ///获取汉字的内码（查询）
    short getCHCode(uchar ch1, uchar ch2)
    {
        //get chinese encode
        if (isGB2312(ch1, ch2))
        {
            return (ch1 - 176) * 94 + (ch2 - 161) + 1;
        }
        else
        {
            return getNonGB2312ChCode(ch1, ch2, WorkMode());
        }
    }
    short getNonGB2312ChCode(uchar ch1, uchar ch2, OnlineMode)
    {
        unsigned short c = ch1 << 8 | ch2;
        return m_hmCode2Idx.find(c) != m_hmCode2Idx.end() ?
                (m_hmCode2Idx[c] + GB2312_OFFSET + 1) : 0;
    }
    short getNonGB2312ChCode(uchar ch1, uchar ch2, OfflineMode)
    {
        static int hashIdx = 0;
        if (ch1 > 127)
        { //扩展字
            ushort c = (ch1 << 8) | ch2;
            if (m_hmCode2Idx.find(c) == m_hmCode2Idx.end())
            {
                m_hmCode2Idx[c] = hashIdx++;
            }
            return (m_hmCode2Idx[c] + GB2312_OFFSET + 1);
        }
        else
        {
            //            std::cerr << "compose non-chinese:" << std::endl;
            return 0; //fixme
        }
    }
public:
    ///获取字符串编码,存储在v_code online and offline
    ///获取编码同时,获得每个编码位置到此的长度
    ///返回-1 编码错误, 返回1 即为全双字节中文，否则返回0
    ///英文如果切分可能会存在问题的 adidasabc 是否切出adisas abc  尤其是最小切分的时候 applied -> app
    ///所有理论上英文如果没有空格不应该切开 即使在字典中有英文词
    template<typename u16_string_>
    void getKeyCode(const string& phrase, u16_string_& v_code)
    { //汉字词非汉字词编码[必须已经过标准化]
        v_code.clear();
        short code = 0;
        for (size_t i = 0; i < phrase.size();)
        {
            if (((uchar) phrase[i]) >= 0x81
                    && ((uchar) phrase[i]) <= 0xFE && i + 1 < phrase.size())
            {
                code = getCHCode((uchar) phrase[i], (uchar) phrase[i + 1]);
                i += 2;
            }
            else
            {
                code = getENCode(phrase[i]);
                i++;
            }
            v_code.push_back(code);
        }
    }
    int getKeyCode(const string& phrase, short* v_code)
    { //汉字词非汉字词编码[必须已经过标准化]
        short code = 0;
        int num = 0;
        for (size_t i = 0; i < phrase.size();)
        {
            if (((uchar) phrase[i]) >= 0x81
                    && ((uchar) phrase[i]) <= 0xFE && i + 1 < phrase.size())
            {
                code = getCHCode((uchar) phrase[i], (uchar) phrase[i + 1]);
                i += 2;
            }
            else
            {
                code = getENCode(phrase[i]);
                i++;
            }
            v_code[num++] = code;
        }
        return num;
    }

    ///offline map 写入文件
    void save(const string& file)
    {
        std::ofstream fmap(file.c_str(), std::ios::binary);

        KeyMap key_map;
        HashMapUs_s::const_iterator hit = m_hmCode2Idx.begin();
        for (; hit != m_hmCode2Idx.end(); ++hit)
        {
            key_map.first = hit->first;
            key_map.second = hit->second;
            fmap.write((char*) (&key_map), sizeof (key_map));
        }
    }
};

typedef GBKEncoderT<OnlineMode> Encoder;
typedef GBKEncoderT<OfflineMode> EncodeTrainer;
typedef GBKEncoderT<OnlineMode> GBK_Encoder;
typedef GBKEncoderT<OfflineMode> GBK_EncodeTrainer;
}

#endif  //----end of GBK_ENCODER_H_
