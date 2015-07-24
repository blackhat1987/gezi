/** 
 *  ==============================================================================
 * 
 *          \file   gbk_encoder.h
 *
 *        \author   gezi  
 *          
 *          \date   2010-09-25 16:32:02.142693
 *  
 *  \Description:   ��ԭ�ִʴ�����gbk string ��������, �ñ�����Ҫ���˫��������ʹ��
 *                  ���gbk�ַ��ı��� ������Ӣ��
 *                  ���ڶ�����չ����λ����ض��ı�������ͬ����������Ҫ
 *
 *              //***********˫������λ���************
                //������������Ϊ8000������λ��95��ascii����λ[32-126]��1-6768λΪGB2312���֣�����1232��λΪ��չ������λ����
                //ǰ6768λ��GB2312����ӳ����ټ�1��Ϊ��ţ���1232λ��hash�洢���룬������+6769Ϊ��ţ����hash����ļ�
                //���崮�з���Ϣ��int��С�Ķ���������¼�������ֽ�Ϊ0�������ֽ�Ϊ�з���Ϣ
 *
 *               GBKEncoder ��Ϊ����ģʽ OnlineMode, OfflineMode��Ӧ��ͬ�Ļ�ȡ����ϸ�ڴ��룬��Ϊ
 *               ���߿�����Ҫ���� ��1232λ��hash�洢���룬������+6769Ϊ��� ��������� getNonGB2312ChCode
 *               �������߹�����Ҫ���������ļ�
 *
 *               ע�����ֱ���Ӣ���ں��� ��ô ԭ�е�string ����� ת����������� ���ڻ��в�ͬ
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
    static const short AMBOFFSET = 16; //���崮�зִ洢ƫ��
    static const short GB2312_OFFSET = 6768; //GB2312���򳤶�
    static const int KEYTYPEBIT = 0xffff; //���崮�зֵ��ֽ���Ϣλ
private:
    typedef std::pair<ushort, short> KeyMap; //code,index
    HashMapUs_s m_hmCode2Idx; //GBK��չ������ӳ��
public:
    ///�������ߴ���õ�hash���� for online
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
    ///��ȡ�Ǻ��ֵ����� online and offline both
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

    ///��ȡ���ֵ����루��ѯ��
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
        { //��չ��
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
    ///��ȡ�ַ�������,�洢��v_code online and offline
    ///��ȡ����ͬʱ,���ÿ������λ�õ��˵ĳ���
    ///����-1 �������, ����1 ��Ϊȫ˫�ֽ����ģ����򷵻�0
    ///Ӣ������зֿ��ܻ��������� adidasabc �Ƿ��г�adisas abc  ��������С�зֵ�ʱ�� applied -> app
    ///����������Ӣ�����û�пո�Ӧ���п� ��ʹ���ֵ�����Ӣ�Ĵ�
    template<typename u16_string_>
    void getKeyCode(const string& phrase, u16_string_& v_code)
    { //���ִʷǺ��ִʱ���[�����Ѿ�����׼��]
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
    { //���ִʷǺ��ִʱ���[�����Ѿ�����׼��]
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

    ///offline map д���ļ�
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
