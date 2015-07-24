/** 
 *  ==============================================================================
 * 
 *          \file   segment_impl.h
 *
 *        \author   ChengHuige
 *          
 *          \date   2010-10-10 15:39:11.195818
 *  
 *  \Description:   TODO Ϊ�� ����� maxSegmentCH��Ҫ�ĳ� �º�����ʽ������maxSegment
 *                  maxSegment��ʵ��Ϊ�����зֵĿ�ܺ���Ӧ�á�
 *
 *            ������ͬ�Ŀ�ܣ��м�仯������ ���ƺ���ָ��
 *            ���ǲ���Ӱ���ٶ��ֲ���Ū�º�����ô��
 *            Ҫ�䶯�ĺ���������ͬ�����ƣ�����traits��ʽ���ط���
 *
 *           �º����ʺ��ⲿ�����滻��traits�����ʺ����ڲ���ͬ������ѡ��, �ȿ����Ƿ��÷º������Է���
 *           ��������漰�����ڲ���Դ�ķ��ʾͲ�̫�ʺ��÷º���
 *
 *           ���Ҫ����Ĭ�������ֻ�������ص�����ٸ���Ĭ�����д��
 *
 *           ��ǰĬ��ʵ��ʹ��SegmentorImpl_Basic ����OmniSegmentWithAmbi��֧�ֵ�ǰֻд��
 *           SegmentorImpl_Basic�ġ�
 *
 *
 * FIXME ���ڸ���seg ����ambi��Ҫ������ �������ٴ��ݵĲ���
 *  ==============================================================================
 */

#ifndef SEGMENT_IMPL_H_
#define SEGMENT_IMPL_H_
#include "seg_type.h"
#include "seg_common.h"
#include "gbk_encoder.h"
#include "datrie.h"
#include "segment_result_func.h"
namespace segment
{

class SegmentorImpl
{
protected:
    DATrie m_trie;
    Encoder m_encoder;
public:

    SegmentorImpl(const string& datrie_file, const string& encoder_file)
    : m_trie(datrie_file), m_encoder(encoder_file)
    {
    }

    SegmentorImpl()
    {

    }

    bool init(const string& datrie_file, const string& encoder_file)
    {
        if (!m_trie.load(datrie_file))
            return false;
        if (!m_encoder.load(encoder_file))
            return false;
        return true;
    }

    /**
     * �������ƥ���з����Ĵ�
     * @param out ���
     * @param code �м����
     * @param len  ���볤��
     * @param offset ���ԭʼkey��ƫ��
     * @param put   д����º���
     * @param
     */
    template<typename Container, typename RFunc>
    void segmentCH(Container& out, const short* code, int len, int offset, RFunc put, MaxSegType)
    {
        DATrie::ResultType result;
        int pos;
        int i = 0;
        int level = 0;
        while (i < len)
        {
            pos = offset + i * 2;
            if (!m_trie.searchLongest(code + i, len - i, result)) //û�гɴ�
            {
                put(out, pos, 2, level);
                i++;
            }
            else
            {
                put(out, pos, result.length * 2, level);
                i += result.length;
            }
        }
    }

    /**
     * ���ƥ�俼�Ǽ���������崦��
     */
    template<typename Container, typename RFunc>
    void segmentCH(Container& out, const short* code, int len, int offset, RFunc put, MaxSegWithAmbi)
    {
        DATrie::ResultType result;
        int pos;
        int i = 0;
        int level = 0;
        while (i < len)
        {
            pos = offset + i * 2;
            if (!m_trie.searchLongest(code + i, len - i, result, DIANYALIGUO << AMBOFFSET)) //û�гɴ�
            {
                put(out, pos, 2, level);
                i++;
            }
            else
            {
                if ((result.value & KEYTYPEBIT) == ambiguity)
                { //�������崮���ұ����ɴ� ("����Ь"����崮���Ǳ���ɴ�)
                    int ambi_info = (result.value >> AMBOFFSET);
                    assert(ambi_info);
                    int len = addAmbiMax(out, ambi_info, pos, level, put); //�����search����ȷ������DIANYALIGUO���͵�����
                    i += len;
                }
                else
                {
                    put(out, pos, result.length * 2, level);
                    i += result.length;
                }
            }
        }
    }

    /**
     * ���Ĵ���ȫ�з�
     * ��������������ȫ�з֣����ǿ��ܲ��������·��ֻ�ǰѿ��ܵĴʶ���֤����������������ĵ��ֿ��ܲ���ȡ�Ӷ��޷�ƴ������·��
     * ����IK ���ǿ��ܻ��г�����ĵ�����������֤·��
     * ���� ���� -> ������  ������  ֻ�г� ��
     */
    template<typename Container, typename RFunc>
    void segmentCH(Container& out, const short* code, int len, int offset, RFunc put, OmniSegWithAmbiFull, short level = 0)
    {
        DATrie::ResultType result;
        int pos;
        int i = 0;
        int max_len_now = 0;
        short len_vec[KEYCNTMAX];
        int val_vec[KEYCNTMAX];
        int longest_key_val, longest_key_len;
        while (i < len)
        {
            pos = offset + i * 2;
            int result_num = m_trie.searchAll(code + i, len - i, len_vec, val_vec, KEYCNTMAX);
            if (!result_num) //û�гɴ�
            {
                //                if (next_pos[i] != -1)
                if (i >= max_len_now)
                    put(out, pos, 2, level);
                i++; //next step
                if (i > max_len_now)
                    max_len_now = i;
            }
            else
            {
                longest_key_val = val_vec[result_num - 1];
                longest_key_len = len_vec[result_num - 1];

                if (longest_key_val == common || (longest_key_val >> AMBOFFSET) == DIANYALIGUO)
                {//����ͨ�ֵ��
                    bool has_longer = false;
                    for (int j = result_num - 1; j >= 0; j--)
                    {
                        if (!(val_vec[j] & KEYTYPEBIT) == ambiguity)
                        {
                            short level_ = level || has_longer;
                            put(out, pos, len_vec[j] * 2, level_);
                            has_longer = true;
                        }
                    }
                    //TODO ������Ҫѡ���Ƿ�Ҫ�и���ĵ�������ȫ·�� your choice
                    //�����MaxLen���Ǳ�׼������IK��ȫ�з֣�����׷��ƴ·��������������ʵĲ�׷���ӡ
                    //                    if (i + longest_key_len > max_len_now)
                    //                        max_len_now = i + longest_key_len;
                    if (i + len_vec[0] > max_len_now)
                        max_len_now = i + len_vec[0];
                    i++; //next step
                }
                else if (longest_key_val > KEYTYPEBIT)
                {//>0xffff������崮
                    bool is_also_key = ((longest_key_val & KEYTYPEBIT) != ambiguity);
                    if (is_also_key)
                    {//����Ҳ��common�ʵ���Ĵ�
                        put(out, pos, longest_key_len * 2, level);
                    }
                    int step = addAmbiOmni(out, longest_key_val >> AMBOFFSET, pos, level, put,
                                           is_also_key, code + i, OmniSegWithAmbiFull());
                    i += step; //next step
                    if (i > max_len_now)
                        max_len_now = i;
                }
                else if (longest_key_val == special)
                {//�ǲ���Ҫ�ڲ��зֵ������������Ʒ������
                    put(out, pos, longest_key_len * 2, level);
                    i += longest_key_len; //next step
                    if (i > max_len_now)
                        max_len_now = i;
                }
                else
                {
                    std::cout << "wrong unsupported key type in segmentCH omni " << longest_key_val << std::endl;
                    throw -1;
                }

            }
        }
    }

    /**
     * ��ȫģ��IK��ȫ�з� ֻ�Ǳ�֤������������Ĵ�
     * Ŀǰֻ���������ȷ�ģ���Ϊ�����˶��� SHOUTIBAOENCODE �ı仯���� TODO
     */
    template<typename Container, typename RFunc>
    void segmentCH(Container& out, const short* code, int len, int offset, RFunc put, OmniSegWithAmbiIK, short level = 0)
    {
        DATrie::ResultType result;
        int pos;
        int i = 0;
        int max_len_now = 0;
        short len_vec[KEYCNTMAX];
        int val_vec[KEYCNTMAX];
        int longest_key_val, longest_key_len;
        while (i < len)
        {
            pos = offset + i * 2;
            int result_num = m_trie.searchAll(code + i, len - i, len_vec, val_vec, KEYCNTMAX);
            if (!result_num) //û�гɴ�
            {
                if (i >= max_len_now)
                    put(out, pos, 2, level);
                i++; //next step
                if (i > max_len_now)
                    max_len_now = i;
            }
            else
            {
                longest_key_val = val_vec[result_num - 1];
                longest_key_len = len_vec[result_num - 1];

                if (longest_key_val == common || (longest_key_val >> AMBOFFSET) == DIANYALIGUO)
                {//����ͨ�ֵ�ʣ����ߡ������������ѹ����������Ҫȫ�зֵ������
                    int longest_len = 0;
                    for (int j = result_num - 1; j >= 0; j--)
                    {
                        if (!(val_vec[j] & KEYTYPEBIT) == ambiguity)
                        {
                            short level_ = level || longest_len;
                            put(out, pos, len_vec[j] * 2, level_);
                            if (!longest_len)
                                longest_len = len_vec[j];
                        }
                    }
                    //TODO ������Ҫѡ���Ƿ�Ҫ�и���ĵ�������ȫ·�� your choice
                    //�����MaxLen���Ǳ�׼������IK��ȫ�з֣�����׷��ƴ·��������������ʵĲ�׷���ӡ
                    if (i + longest_len > max_len_now)
                        max_len_now = i + longest_len;
                    i++; //next step
                }
                else if (longest_key_val > KEYTYPEBIT)
                {//>0xffff������崮
                    bool is_also_key = ((longest_key_val & KEYTYPEBIT) != ambiguity);
                    if (is_also_key)
                    {//����Ҳ��common�ʵ���Ĵ�
                        put(out, pos, longest_key_len * 2, level);
                    }
                    int step = addAmbiOmni(out, longest_key_val >> AMBOFFSET, pos, level, put,
                                           is_also_key, code + i, OmniSegWithAmbiIK());
                    i += step; //next step
                    if (i > max_len_now)
                        max_len_now = i;
                }
                else if (longest_key_val == special)
                {//�ǲ���Ҫ�ڲ��зֵ������������Ʒ������
                    put(out, pos, longest_key_len * 2, level);
                    i += longest_key_len; //next step
                    if (i > max_len_now)
                        max_len_now = i;
                }
                else
                {
                    std::cout << "wrong unsupported key type in segmentCH omni: " << longest_key_val << std::endl;
                    throw -1;
                }

            }
        }
    }

    /**
     * ���Ĵ���ȫ�з�
     * ��������������ȫ�з֣����ǿ��ܲ��������·��ֻ�ǰѿ��ܵĴʶ���֤����������������ĵ��ֿ��ܲ���ȡ�Ӷ��޷�ƴ������·��
     * ��ȫ�ﵽ���Ŀ�� ���۴���  ��ʱ�������Ĳ���
     * �� OmniSegWithAmbiFull ������  ����һЩ ���֣� ����Ĳ����� ��� �õ��� ǰ�󶼳ɴ� ��õ����г�����
     * �����ܽ��99.9%������ ��������  A,B,C,DE   AB,C,D,E���������
     */
    template<typename Container, typename RFunc>
    void segmentCH(Container& out, const short* code, int len, int offset, RFunc put, OmniSegWithAmbiFullPath, short level = 0)
    {
        DATrie::ResultType result;
        int pos;
        int i = 0;
        int max_len_now = 0;
        int max_len = 0;
        short len_vec[KEYCNTMAX];
        int val_vec[KEYCNTMAX];
        bool has_put[len], before_is_word[len + 1]; //ע��len + 1����Խ��
        memset(has_put, false, len * sizeof (bool));
        memset(before_is_word, false, (len + 1) * sizeof (bool));
        before_is_word[0] = true;
        int longest_key_val, longest_key_len;
        while (i < len)
        {
            pos = offset + i * 2;
            int result_num = m_trie.searchAll(code + i, len - i, len_vec, val_vec, KEYCNTMAX);
            if (!result_num) //û�гɴ�
            {
                if (i >= max_len_now)
                {
                    if (i > 0 && !has_put[i - 1])
                    {//�Ȳ�ǰ��ĵ���
                        if (before_is_word[i])
                        {
                            if (before_is_word[i - 1])
                            {
                                put(out, pos - 2, 2, 1);
                                has_put[i - 1] = true;
                            }
                        }
                        else
                        {
                            int j = i - 1;
                            while (j > 0 && !has_put[j - 1] && !before_is_word[j])
                            {
                                j--;
                            }
                            for (int k = j; k < i; k++)
                            {
                                put(out, offset + k * 2, 2, 1);
                                has_put[k] = true;
                            }
                        }
                    }
                    put(out, pos, 2, level);
                    has_put[i] = true;
                }
                else
                {//AB  BCD ���� CҪ�����г���
                    if (before_is_word[i] || (i > 0 && has_put[i - 1])) //i >0 no need
                    {
                        put(out, pos, 2, level);
                        has_put[i] = true;
                    }
                }
                i++; //next step
                if (i > max_len_now)
                    max_len_now = i;
                if (i > max_len)
                    max_len = i;
            }
            else
            {
                if (i > 0 && !has_put[i - 1])
                {//�Ȳ�ǰ��ĵ���
                    if (before_is_word[i])
                    {
                        if (before_is_word[i - 1])
                        {
                            put(out, pos - 2, 2, 1);
                            has_put[i - 1] = true;
                        }
                    }
                    else
                    {
                        int j = i - 1;
                        while (j > 0 && !has_put[j - 1] && !before_is_word[j])
                        {
                            j--;
                        }
                        for (int k = j; k < i; k++)
                        {
                            put(out, offset + k * 2, 2, 1);
                            has_put[k] = true;
                        }
                    }
                }
                longest_key_val = val_vec[result_num - 1];
                longest_key_len = len_vec[result_num - 1];

                if (longest_key_val == common || (longest_key_val >> AMBOFFSET) == DIANYALIGUO || i < max_len)
                {//����ͨ�ֵ�ʣ����ߡ������������ѹ����������Ҫȫ�зֵ������, ������� ���ﶬ���ɫ�� ���棬��ô������i < max_len_now��屻����
                    int longest_len = 0;
                    for (int j = result_num - 1; j >= 0; j--)
                    {
                        if (!(val_vec[j] & KEYTYPEBIT) == ambiguity)
                        {
                            short level_ = level || longest_len;
                            put(out, pos, len_vec[j] * 2, level_);
                            before_is_word[i + len_vec[j]] = true;
                            if (!longest_len)
                                longest_len = len_vec[j];
                        }
                    }
                    //                    if ((longest_key_val >> AMBOFFSET) == DIANYALIGUO)
                    //                    {
                    //                        segmentCH_(out, code + i + 1, len - i - 1, offset + (i + 1) * 2, put, OmniSegWithAmbiFullPath(), level);
                    //                        i += longest_key_len;
                    //                        before_is_word[i] = true;
                    //                        if (i > max_len_now)
                    //                            max_len_now = i;
                    //                    }
                    //                    else
                    //                    {
                    //TODO ������Ҫѡ���Ƿ�Ҫ�и���ĵ�������ȫ·�� your choice
                    //�����MaxLen���Ǳ�׼������IK��ȫ�з֣�����׷��ƴ·��������������ʵĲ�׷���ӡ
                    if (i + len_vec[0] > max_len_now)
                        max_len_now = i + len_vec[0];
                    if (i + len_vec[result_num - 1] > max_len)
                        max_len = i + len_vec[result_num - 1];
                    if (len_vec[0] == 1)
                        has_put[i] = true;
                    i++; //next step
                    //                    }
                }
                    //                else if ((longest_key_val >> AMBOFFSET) == DIANYALIGUO)
                    //                {
                    //                    segmentCH_(out, code + i, len - i, offset, put, OmniSegWithAmbiFullPath(), level);
                    //                    i += longest_key_len;
                    //                    before_is_word[i] = true;
                    //                    if (i > max_len_now)
                    //                        max_len_now = i;
                    //                }
                else if (longest_key_val > KEYTYPEBIT)
                {//>0xffff������崮
                    bool is_also_key = ((longest_key_val & KEYTYPEBIT) != ambiguity);
                    if (is_also_key)
                    {//����Ҳ��common�ʵ���Ĵ�
                        put(out, pos, longest_key_len * 2, level);
                        before_is_word[i + longest_key_len] = true;
                    }
                    int step = addAmbiOmni(out, longest_key_val >> AMBOFFSET, pos, level, put,
                                           is_also_key, code + i, OmniSegWithAmbiFullPath());
                    i += step; //next step
                    if (step < longest_key_len)
                    { //��� ���� ����/����"���� �� "��"�������
                        has_put[i - 1] = true;
                    }
                    before_is_word[i] = true;
                    if (i > max_len_now)
                        max_len_now = i;
                    if (i > max_len)
                        max_len = i;
                }
                else if (longest_key_val == special)
                {//�ǲ���Ҫ�ڲ��зֵ������������Ʒ������
                    put(out, pos, longest_key_len * 2, level);
                    i += longest_key_len; //next step
                    before_is_word[i] = true;
                    if (i > max_len_now)
                        max_len_now = i;
                    if (i > max_len)
                        max_len = i;
                }
                else
                {
                    std::cout << "wrong unsupported key type in segmentCH omni: " << longest_key_val << std::endl;
                    throw -1;
                }

            }
        }
        //���Ĳ��ִ���
        if (!has_put[i - 1])
        {//�Ȳ�ǰ��ĵ���
            if (before_is_word[i])
            {
                if (before_is_word[i - 1])
                {
                    put(out, offset + (i - 1) * 2, 2, 1);
                    has_put[i - 1] = true;
                }
            }
            else
            {
                int j = i - 1;
                while (j > 0 && !has_put[j - 1] && !before_is_word[j])
                {
                    j--;
                }
                for (int k = j; k < i; k++)
                {
                    put(out, offset + k * 2, 2, 1);
                    has_put[k] = true;
                }
            }
        }
    }

    /**
     * ��������Ĳ��ֲ���Ū�����ǵ����ټ�һ��trie���������κ�����ʣ���ʵ���߸ɴ��ȫ�з����ˡ�����
     * ��ѵ�����崮�ȫ���Ҹо�Ӱ��Ҳ����̫��
     * NOT USED!!
     */
    template<typename Container, typename RFunc>
    void segmentCH_(Container& out, const short* code, int len, int offset, RFunc put, OmniSegWithAmbiFullPath, short level = 0)
    {
        DATrie::ResultType result;
        int pos;
        int i = 0;
        int max_len_now = 0;
        short len_vec[KEYCNTMAX];
        int val_vec[KEYCNTMAX];
        bool has_put[len], before_is_word[len + 1]; //ע��len + 1����Խ��
        memset(has_put, false, len * sizeof (bool));
        memset(before_is_word, false, (len + 1) * sizeof (bool));
        before_is_word[0] = true;
        int longest_key_val, longest_key_len;
        while (i < len)
        {
            pos = offset + i * 2;
            int result_num = m_trie.searchAll(code + i, len - i, len_vec, val_vec, KEYCNTMAX);
            if (!result_num) //û�гɴ�
            {
                if (i >= max_len_now)
                {
                    if (i > 0 && !has_put[i - 1])
                    {//�Ȳ�ǰ��ĵ���
                        if (before_is_word[i])
                        {
                            if (before_is_word[i - 1])
                            {
                                put(out, pos - 2, 2, 1);
                                has_put[i - 1] = true;
                            }
                        }
                        else
                        {
                            int j = i - 1;
                            while (j > 0 && !has_put[j - 1] && !before_is_word[j])
                            {
                                j--;
                            }
                            for (int k = j; k < i; k++)
                            {
                                put(out, offset + k * 2, 2, 1);
                                has_put[k] = true;
                            }
                        }
                    }
                    put(out, pos, 2, level);
                    has_put[i] = true;
                }
                i++; //next step
                if (i > max_len_now)
                    max_len_now = i;
            }
            else
            {
                if (i > 0 && !has_put[i - 1])
                {//�Ȳ�ǰ��ĵ���
                    if (before_is_word[i])
                    {
                        if (before_is_word[i - 1])
                        {
                            put(out, pos - 2, 2, 1);
                            has_put[i - 1] = true;
                        }
                    }
                    else
                    {
                        int j = i - 1;
                        while (j > 0 && !has_put[j - 1] && !before_is_word[j])
                        {
                            j--;
                        }
                        for (int k = j; k < i; k++)
                        {
                            put(out, offset + k * 2, 2, 1);
                            has_put[k] = true;
                        }
                    }
                }
                longest_key_val = val_vec[result_num - 1];
                longest_key_len = len_vec[result_num - 1];

                if (longest_key_val == common || longest_key_val > KEYTYPEBIT)
                {//����ͨ�ֵ�ʣ����ߡ������������ѹ����������Ҫȫ�зֵ������
                    int longest_len = 0;
                    for (int j = result_num - 1; j >= 0; j--)
                    {
                        if (!(val_vec[j] & KEYTYPEBIT) == ambiguity)
                        {
                            short level_ = level || longest_len;
                            put(out, pos, len_vec[j] * 2, level_);
                            before_is_word[i + len_vec[j]] = true;
                            if (!longest_len)
                                longest_len = len_vec[j];
                        }
                    }
                    //TODO ������Ҫѡ���Ƿ�Ҫ�и���ĵ�������ȫ·�� your choice
                    //�����MaxLen���Ǳ�׼������IK��ȫ�з֣�����׷��ƴ·��������������ʵĲ�׷���ӡ
                    if (i + len_vec[0] > max_len_now)
                        max_len_now = i + len_vec[0];
                    if (len_vec[0] == 1)
                        has_put[i] = true;
                    i++; //next step
                }
                else if (longest_key_val == special)
                {//�ǲ���Ҫ�ڲ��зֵ������������Ʒ������
                    put(out, pos, longest_key_len * 2, level);
                    i += longest_key_len; //next step
                    before_is_word[i] = true;
                    if (i > max_len_now)
                        max_len_now = i;
                }
                else
                {
                    std::cout << "wrong unsupported key type in segmentCH omni: " << longest_key_val << std::endl;
                    throw -1;
                }

            }
        }
        //���Ĳ��ִ���
        if (!has_put[i - 1])
        {//�Ȳ�ǰ��ĵ���
            if (before_is_word[i])
            {
                if (before_is_word[i - 1])
                {
                    put(out, offset + (i - 1) * 2, 2, 1);
                    has_put[i - 1] = true;
                }
            }
            else
            {
                int j = i - 1;
                while (j > 0 && !has_put[j - 1] && !before_is_word[j])
                {
                    j--;
                }
                for (int k = j; k < i; k++)
                {
                    put(out, offset + k * 2, 2, 1);
                    has_put[k] = true;
                }
            }
        }
    }

    /**
     * ģ����ǰ�㷨��ȫ�зֱ�����
     * ���+��С �з� ����ȫ�з� ��Ҫ���߾��������������
     * �Ȳ�����seg inside
     * ������level
     */
    template<typename Container, typename RFunc>
    void segmentCH(Container& out, const short* code, int len, int offset, RFunc put, OmniSegWithAmbi, short level = 0)
    {
        DATrie::ResultType result;
        int pos;
        int i = 0;
        int next_pos[len + 1];
        memset(next_pos, 0, (len + 1) * sizeof (int));
        short len_vec[KEYCNTMAX];
        int val_vec[KEYCNTMAX];
        int longest_key_val, longest_key_len;
        while (i < len)
        {
            pos = offset + i * 2;
            int result_num = m_trie.searchAll(code + i, len - i, len_vec, val_vec, KEYCNTMAX);
            if (!result_num) //û�гɴ�
            {
                put(out, pos, 2, level);
                i++;
            }
            else
            {
                longest_key_val = val_vec[result_num - 1];
                longest_key_len = len_vec[result_num - 1];

                if (longest_key_val == common || (longest_key_val >> AMBOFFSET) == DIANYALIGUO)
                {//����ͨ�ֵ�ʣ����ߡ������������ѹ����������Ҫȫ�зֵ������
                    bool has_longer = false;
                    int min_j = -1;
                    for (int j = result_num - 1; j >= 0; j--)
                    {
                        if (!(val_vec[j] & KEYTYPEBIT) == ambiguity)
                        {
                            short level_ = level || has_longer;
                            put(out, pos, len_vec[j] * 2, level_);
                            has_longer = true;
                            min_j = j;
                            next_pos[i + len_vec[j]] = 1;
                        }
                    }
                    if (min_j >= 0)
                    {
                        segInside(out, code + i, len_vec[min_j], pos, put);
                        next_pos[i + len_vec[min_j]] = 1;
                    }
                }
                else if (longest_key_val > KEYTYPEBIT)
                {//>0xffff������崮
                    bool is_also_key = ((longest_key_val & KEYTYPEBIT) != ambiguity);
                    if (is_also_key)
                    {//����Ҳ��common�ʵ���Ĵ�
                        put(out, pos, longest_key_len * 2, level);
                    }
                    int step = addAmbiOmni(out, longest_key_val >> AMBOFFSET, pos, level, put,
                                           is_also_key, code + i, OmniSegWithAmbi());
                    next_pos[i + step] = 1;
                    i += step;
                    continue;
                }
                else if (longest_key_val == special)
                {//�ǲ���Ҫ�ڲ��зֵ������������Ʒ������
                    put(out, pos, longest_key_len * 2, level);
                    next_pos[i + longest_key_len] = 1;
                }
                else
                {
                    std::cout << "wrong unsupported key type in segmentCH omni " << longest_key_val << std::endl;
                    throw -1;
                }
                i++;
                while (i <= len && next_pos[i] == 0)
                    i++;
            }
        }
    }

protected:

    template<typename Container, typename RFunc>
    void segInside(Container& out, const short* code, int len, int offset, RFunc put)
    {//����ӵڶ����ֿ�ʼ�ڲ��д���ô�Ѹô���ȡ������ǰ���е��֣�������Ϊ
        DATrie::ResultType result;
        short level = 1;
        for (int i = 1; i < len; i++)
        {
            if (m_trie.searchFirst(code + i, len - i, result) && result.value == common)
            {
                for (int cur = 0; cur < i; cur++)
                {
                    put(out, cur * 2 + offset, 2, level);
                }
                put(out, i * 2 + offset, result.length * 2, level);
                for (int cur = i + result.length; cur < len; cur++)
                {
                    put(out, cur * 2 + offset, 2, level);
                }
                break;
            }
        }
    }

    template<typename Container, typename RFunc>
    void fullOmniSeg(Container& out, const short* code, int len, int offset, RFunc put)
    {
        int level = 1;
        put(out, offset, len * 2, level);
    }

    template<typename Container, typename RFunc>
    int addAmbiMax(Container& out, int ambi_info, int pos, int level, RFunc put)
    {
        int start = pos;
        short len = 0;
        while (ambi_info)
        {
            len = 2;
            while ((ambi_info & 1) == 0)
            {
                ambi_info >>= 1;
                len += 2;
            }
            ambi_info >>= 1;
            if (ambi_info)
            { //β��������һ������������� ���� ��ǳ��,�ס� ��ǳ�ư�ɫ�� -> ��ǳ�ƣ���ɫ"
                put(out, pos, len, level);
                pos += len;
            }
        }
        return (pos - start) / 2;
    }

    template<typename Container, typename RFunc, typename SegType>
    int addAmbiOmni(Container& out, int ambi_info, int pos, short level, RFunc put, bool also_key,
                    const short* code, SegType seg_type)
    {
        short len = 0;
        int start = pos;
        while (ambi_info)
        {
            len = 2;
            while ((ambi_info & 1) == 0)
            {
                ambi_info >>= 1;
                len += 2;
            }
            ambi_info >>= 1;
            if (also_key || ambi_info)
            { //���ԭ���ʲ��Ǵʵ���Ĵ���ôβ��������һ�������жϼ���
                //                    put(out, pos, len, level);
                segmentCH(out, code + (pos - start) / 2, len / 2, pos, put, seg_type, level || also_key); //�ڲ�����Ҫ�ж��Ƿ�Ҫ����һ���з�
                pos += len;
            }
        }
        return (pos - start) / 2;
    }


    //    template<typename Container, typename RFunc, typename SegType>
    //    int addAmbiOmni(Container& out, int ambi_info, int pos, short level, RFunc put, bool also_key,
    //                    const short* code, SegType seg_type)
    //    {
    //        short len = 0;
    //        int start = pos;
    //        while (ambi_info)
    //        {
    //            len = 2;
    //            while ((ambi_info & 1) == 0)
    //            {
    //                ambi_info >>= 1;
    //                len += 2;
    //            }
    //            ambi_info >>= 1;
    //            if (also_key || ambi_info)
    //            { //���ԭ���ʲ��Ǵʵ���Ĵ���ôβ��������һ�������жϼ���
    //                //                    put(out, pos, len, level);
    //                segmentCH(out, code + (pos - start) / 2, len / 2, pos, put, seg_type, level || also_key); //�ڲ�����Ҫ�ж��Ƿ�Ҫ����һ���з�
    //                pos += len;
    //            }
    //        }
    //        return (pos - start) / 2;
    //    }


};

} //----end of namespace segment

#endif  //----end of SEGMENT_IMPL_H_
