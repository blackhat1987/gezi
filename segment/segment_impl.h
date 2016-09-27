/** 
 *  ==============================================================================
 * 
 *          \file   segment_impl.h
 *
 *        \author   ChengHuige
 *          
 *          \date   2010-10-10 15:39:11.195818
 *  
 *  \Description:   TODO 为了 灵活性 maxSegmentCH需要改成 仿函数形式，传给maxSegment
 *                  maxSegment其实作为所有切分的框架函数应该。
 *
 *            想用相同的框架，中间变化函数命 类似函数指针
 *            但是不想影响速度又不好弄仿函数怎么办
 *            要变动的函数采用相同的名称，采用traits方式重载分配
 *
 *           仿函数适合外部操作替换，traits重载适合类内部不同方法的选择, 先考虑是否用仿函数可以方便
 *           如果函数涉及对类内部资源的访问就不太适合用仿函数
 *
 *           如果要给出默认情况，只能用重载的情况再给出默认情况写法
 *
 *           当前默认实际使用SegmentorImpl_Basic 对于OmniSegmentWithAmbi的支持当前只写了
 *           SegmentorImpl_Basic的。
 *
 *
 * FIXME 关于各个seg 处理ambi需要再斟酌 尤其是再传递的参数
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
     * 最大正向匹配切分中文串
     * @param out 输出
     * @param code 中间编码
     * @param len  编码长度
     * @param offset 相对原始key的偏移
     * @param put   写结果仿函数
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
            if (!m_trie.searchLongest(code + i, len - i, result)) //没有成词
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
     * 最大匹配考虑加入离线岐义处理
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
            if (!m_trie.searchLongest(code + i, len - i, result, DIANYALIGUO << AMBOFFSET)) //没有成词
            {
                put(out, pos, 2, level);
                i++;
            }
            else
            {
                if ((result.value & KEYTYPEBIT) == ambiguity)
                { //如果是岐义串并且本身不成词 ("篮球鞋"是岐义串但是本身成词)
                    int ambi_info = (result.value >> AMBOFFSET);
                    assert(ambi_info);
                    int len = addAmbiMax(out, ambi_info, pos, level, put); //上面的search可以确保不是DIANYALIGUO类型的歧义
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
     * 中文串的全切分
     * 这个是真正意义的全切分，但是可能不组成完整路径只是把可能的词都保证出来，不是有意义的单字可能不提取从而无法拼成完整路径
     * 类似IK 但是可能会切出更多的单字来尽量保证路径
     * 比如 军刀 -> 军，刀  而不是  只切出 刀
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
            if (!result_num) //没有成词
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
                {//是普通字典词
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
                    //TODO 这里需要选择是否要切更多的单字来补全路径 your choice
                    //如果是MaxLen则是标准的类似IK的全切分，即不追求拼路径，不是有意义词的不追求打印
                    //                    if (i + longest_key_len > max_len_now)
                    //                        max_len_now = i + longest_key_len;
                    if (i + len_vec[0] > max_len_now)
                        max_len_now = i + len_vec[0];
                    i++; //next step
                }
                else if (longest_key_val > KEYTYPEBIT)
                {//>0xffff即是岐义串
                    bool is_also_key = ((longest_key_val & KEYTYPEBIT) != ambiguity);
                    if (is_also_key)
                    {//本身也是common词典里的词
                        put(out, pos, longest_key_len * 2, level);
                    }
                    int step = addAmbiOmni(out, longest_key_val >> AMBOFFSET, pos, level, put,
                                           is_also_key, code + i, OmniSegWithAmbiFull());
                    i += step; //next step
                    if (i > max_len_now)
                        max_len_now = i;
                }
                else if (longest_key_val == special)
                {//是不需要内部切分的特殊词如人名品牌名等
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
     * 完全模拟IK的全切分 只是保证出所有有意义的词
     * 目前只有这个是正确的，因为加入了对于 SHOUTIBAOENCODE 的变化。。 TODO
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
            if (!result_num) //没有成词
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
                {//是普通字典词，或者“手提包”“电压力锅”类需要全切分的歧义词
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
                    //TODO 这里需要选择是否要切更多的单字来补全路径 your choice
                    //如果是MaxLen则是标准的类似IK的全切分，即不追求拼路径，不是有意义词的不追求打印
                    if (i + longest_len > max_len_now)
                        max_len_now = i + longest_len;
                    i++; //next step
                }
                else if (longest_key_val > KEYTYPEBIT)
                {//>0xffff即是岐义串
                    bool is_also_key = ((longest_key_val & KEYTYPEBIT) != ambiguity);
                    if (is_also_key)
                    {//本身也是common词典里的词
                        put(out, pos, longest_key_len * 2, level);
                    }
                    int step = addAmbiOmni(out, longest_key_val >> AMBOFFSET, pos, level, put,
                                           is_also_key, code + i, OmniSegWithAmbiIK());
                    i += step; //next step
                    if (i > max_len_now)
                        max_len_now = i;
                }
                else if (longest_key_val == special)
                {//是不需要内部切分的特殊词如人名品牌名等
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
     * 中文串的全切分
     * 这个是真正意义的全切分，但是可能不组成完整路径只是把可能的词都保证出来，不是有意义的单字可能不提取从而无法拼成完整路径
     * 完全达到这个目标 代价带大  暂时用这样的策略
     * 在 OmniSegWithAmbiFull 基础上  补充一些 单字， 补充的策略是 如果 该单字 前后都成词 则该单字切出来，
     * 这样能解决99.9%的问题 除了类似  A,B,C,DE   AB,C,D,E这样的情况
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
        bool has_put[len], before_is_word[len + 1]; //注意len + 1否则越界
        memset(has_put, false, len * sizeof (bool));
        memset(before_is_word, false, (len + 1) * sizeof (bool));
        before_is_word[0] = true;
        int longest_key_val, longest_key_len;
        while (i < len)
        {
            pos = offset + i * 2;
            int result_num = m_trie.searchAll(code + i, len - i, len_vec, val_vec, KEYCNTMAX);
            if (!result_num) //没有成词
            {
                if (i >= max_len_now)
                {
                    if (i > 0 && !has_put[i - 1])
                    {//先补前面的单字
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
                {//AB  BCD 这种 C要单独切出来
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
                {//先补前面的单字
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
                {//是普通字典词，或者“手提包”“电压力锅”类需要全切分的歧义词, 另外如果 “秋冬枣红色” 冬枣，那么枣属于i < max_len_now岐义被忽略
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
                    //TODO 这里需要选择是否要切更多的单字来补全路径 your choice
                    //如果是MaxLen则是标准的类似IK的全切分，即不追求拼路径，不是有意义词的不追求打印
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
                {//>0xffff即是岐义串
                    bool is_also_key = ((longest_key_val & KEYTYPEBIT) != ambiguity);
                    if (is_also_key)
                    {//本身也是common词典里的词
                        put(out, pos, longest_key_len * 2, level);
                        before_is_word[i + longest_key_len] = true;
                    }
                    int step = addAmbiOmni(out, longest_key_val >> AMBOFFSET, pos, level, put,
                                           is_also_key, code + i, OmniSegWithAmbiFullPath());
                    i += step; //next step
                    if (step < longest_key_len)
                    { //岐义 避免 “编/程序"这种 将 "编"输出两次
                        has_put[i - 1] = true;
                    }
                    before_is_word[i] = true;
                    if (i > max_len_now)
                        max_len_now = i;
                    if (i > max_len)
                        max_len = i;
                }
                else if (longest_key_val == special)
                {//是不需要内部切分的特殊词如人名品牌名等
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
        //最后的补字处理
        if (!has_put[i - 1])
        {//先补前面的单字
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
     * 忽略歧义的部分不好弄，除非单独再加一个trie树，不带任何歧义词，其实离线干脆就全切分完了。。。
     * 别训练歧义串最安全，我感觉影响也不会太大
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
        bool has_put[len], before_is_word[len + 1]; //注意len + 1否则越界
        memset(has_put, false, len * sizeof (bool));
        memset(before_is_word, false, (len + 1) * sizeof (bool));
        before_is_word[0] = true;
        int longest_key_val, longest_key_len;
        while (i < len)
        {
            pos = offset + i * 2;
            int result_num = m_trie.searchAll(code + i, len - i, len_vec, val_vec, KEYCNTMAX);
            if (!result_num) //没有成词
            {
                if (i >= max_len_now)
                {
                    if (i > 0 && !has_put[i - 1])
                    {//先补前面的单字
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
                {//先补前面的单字
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
                {//是普通字典词，或者“手提包”“电压力锅”类需要全切分的歧义词
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
                    //TODO 这里需要选择是否要切更多的单字来补全路径 your choice
                    //如果是MaxLen则是标准的类似IK的全切分，即不追求拼路径，不是有意义词的不追求打印
                    if (i + len_vec[0] > max_len_now)
                        max_len_now = i + len_vec[0];
                    if (len_vec[0] == 1)
                        has_put[i] = true;
                    i++; //next step
                }
                else if (longest_key_val == special)
                {//是不需要内部切分的特殊词如人名品牌名等
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
        //最后的补字处理
        if (!has_put[i - 1])
        {//先补前面的单字
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
     * 模仿以前算法的全切分本质是
     * 最大+最小 切分 而非全切分 需要离线尽量处理好岐义情况
     * 先不考虑seg inside
     * 不考虑level
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
            if (!result_num) //没有成词
            {
                put(out, pos, 2, level);
                i++;
            }
            else
            {
                longest_key_val = val_vec[result_num - 1];
                longest_key_len = len_vec[result_num - 1];

                if (longest_key_val == common || (longest_key_val >> AMBOFFSET) == DIANYALIGUO)
                {//是普通字典词，或者“手提包”“电压力锅”类需要全切分的歧义词
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
                {//>0xffff即是岐义串
                    bool is_also_key = ((longest_key_val & KEYTYPEBIT) != ambiguity);
                    if (is_also_key)
                    {//本身也是common词典里的词
                        put(out, pos, longest_key_len * 2, level);
                    }
                    int step = addAmbiOmni(out, longest_key_val >> AMBOFFSET, pos, level, put,
                                           is_also_key, code + i, OmniSegWithAmbi());
                    next_pos[i + step] = 1;
                    i += step;
                    continue;
                }
                else if (longest_key_val == special)
                {//是不需要内部切分的特殊词如人名品牌名等
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
    {//如果从第二个字开始内部有词那么把该词提取出来，前后切单字，否则不作为
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
            { //尾串留给下一个步骤后续处理 比如 ”浅黄,白“ ”浅黄白色“ -> ”浅黄，白色"
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
            { //如果原岐义词不是词典里的词那么尾串留给下一个步骤判断加入
                //                    put(out, pos, len, level);
                segmentCH(out, code + (pos - start) / 2, len / 2, pos, put, seg_type, level || also_key); //内部还需要判断是否还要进行一下切分
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
    //            { //如果原岐义词不是词典里的词那么尾串留给下一个步骤判断加入
    //                //                    put(out, pos, len, level);
    //                segmentCH(out, code + (pos - start) / 2, len / 2, pos, put, seg_type, level || also_key); //内部还需要判断是否还要进行一下切分
    //                pos += len;
    //            }
    //        }
    //        return (pos - start) / 2;
    //    }


};

} //----end of namespace segment

#endif  //----end of SEGMENT_IMPL_H_
