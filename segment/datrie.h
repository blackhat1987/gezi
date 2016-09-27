/** 
 *  ==============================================================================
 * 
 *          \file   datrie.h
 *
 *        \author   gezi  
 *          
 *          \date   2010-09-25 15:56:11.433657
 *  
 *  \Description:   一个静态建立的double array trie树,原有分词中代码提取封装
 *                  为了简单先不考虑岐义
 *                  TODO
 *                  1. 动态建立
 *                  2. 较好的支持扩展，岐义处理
 *
 *                  注意需要保证构建字典的化需要按照字典顺序排序
 * 
 *                  weight 数组 相当于 key,value中的value,注意当前定死value类型是int,存储是数组
 *                  TODO 这个需求可能变化也许需要改动，如果要使用hashmap 来存储呢，这样需要变动下代码了。。
 *                  resize, push_back 需要去掉，load save也需要变，序列化的不需要变
 *
 *                  取消了 check *-1 标示岐义，只存储weight 交给外面判断岐义
 *
 *
 *                  FIXME 如果load save的话 ValueType必须是简单类型吧
 *
 *  ==============================================================================
 */

#ifndef DATRIE_H_
#define DATRIE_H_
#include <assert.h>
#include "seg_type.h"
#include "debug_help.h"
#include "progress_bar.h"

namespace segment
{

/*
 *ElemType 是检索Key中单个元素的类型，默认对于gbk用short,也可以char
 * 这里code的概念等同于key 默认类型是basic_string<ElemType>
 *ValueType 是结果类型 默认int
 * value概念等同weight
 */
template<typename ElemType, typename KeyType, typename ValueType>
class DATrieT
{
public:
    typedef KeyType CodeType;
    //字符编码
    struct TermCode
    {
        KeyType code; //this is the key TODO use vector or string?
        ValueType weight; //this is the value

        TermCode()
        {
        }

        TermCode(KeyType code_, ValueType weight_)
        : code(code_), weight(weight_)
        {
        }

        bool operator<(const TermCode & rhs) const
        {
            return code < rhs.code;
        }
    };

    struct ResultType
    {
        int value; //对应的value
        int length; //返回查找到的词的长度

        ResultType()
        : value(-1), length(0)
        {
        }

        ResultType(int v, int l)
        : length(l), value(v)
        {

        }
    };

private:
    typedef tuple<int, uint, ValueType> DATrieNode;
    typedef ValueType ValType;


    //trie

    struct TrieNode
    {
        ValueType weight; //权重
        short wSubCnt; //孩子个数
        short wSubBeg; //第一子结点起始索引
        ElemType wData; //字序号
        bool bEnd; //可成词标志
    };

    struct PosCnt
    { //结点在TRIE中的位置信息
        int nPosInBase; //base下标
        short nPosInTrie; //Trie树中位置
        short nCnt; //子结点数

        bool operator<(const PosCnt & pc)const //优先级
        {
            return this->nCnt < pc.nCnt;
        }
    };

    typedef std::vector<std::vector<TrieNode>* > Trie;
    typedef vector<int> BaseVec;
    typedef vector<uint> CheckVec;
    typedef vector<ValueType> WeightVec;
private:
    static const short WORDCNTMAX_CH = 15; //汉语词最大字长
    static const short WORDCNTMAX_EN = 30; //非汉语词最大字长
    static const short WORDCNTMAX =
            WORDCNTMAX_CH > WORDCNTMAX_EN ? WORDCNTMAX_CH : WORDCNTMAX_EN; //用于Trie树
    static const short FRST_OFFSET = 8095; //首字区域长度

    int m_keyNum;
    //Double-Array Trie
    BaseVec m_viBase; //直接子结点转移量、是否成词
    CheckVec m_viCheck; //前驱字序号、是否为歧义串
    WeightVec m_viWeight; //相当于key,value中的value  注意如果value是int可以优化内存不需要m_viWeight
public:

    DATrieT()
    {

    }

    DATrieT(const string& fdat)
    {
        load(fdat);
    }

    bool load(const string& fdat)
    {
        std::ifstream fDat(fdat.c_str(), std::ios::binary);
        if (!fDat.is_open())
        {
            std::cerr << "Lod datrie failed."
                    << "Func(Load) error." << std::endl;
            return false;
        }

        DATrieNode dat;
        while (!fDat.eof())
        {
            fDat.read((char*) (&dat), sizeof (dat));
            m_viBase.push_back(boost::get < 0 > (dat));
            m_viCheck.push_back(boost::get < 1 > (dat));
            m_viWeight.push_back(boost::get < 2 > (dat));
        }
        fDat.close();

        shrankMem();

        LOG(INFO) << "Datrie using mem: " << memSize() << "M" << "\n";
        return true;
    }

    void shrankMem()
    {
        BaseVec(m_viBase).swap(m_viBase);
        CheckVec(m_viCheck).swap(m_viCheck);
        WeightVec(m_viWeight).swap(m_viWeight);
    }

    float memSize()
    {
        return (m_viBase.capacity() * sizeof (int) +m_viCheck.capacity() * sizeof (uint) +
                m_viWeight.capacity() * sizeof (ValueType)) / (1024.0 * 1024);
    }

    void save(const string& file)
    {
        std::ofstream fdat(file.c_str(), std::ios::binary);

        DATrieNode daTrie;
        std::vector<int>::const_reverse_iterator it = m_viBase.rbegin();
        while (it < m_viBase.rend() && !*it)
        {
            ++it;
        }
        int arrSz = (int) (m_viBase.rend() - it);
        for (int i = 0; i < arrSz; ++i)
        {
            boost::get < 0 > (daTrie) = m_viBase[i];
            boost::get < 1 > (daTrie) = m_viCheck[i];
            boost::get < 2 > (daTrie) = m_viWeight[i];
            fdat.write((char*) (&daTrie), sizeof (daTrie));
        }
    }

    void clearTrie(Trie& trie)
    { //释放Trie树
        if (!trie.empty())
        {
            typename Trie::const_iterator it;
            for (it = trie.begin(); it != trie.end(); ++it)
            {
                delete *it;
            }
            trie.clear();
        }
    }
    //#endif

    bool build(const vector<TermCode>& vkey_code)
    {
        build(vkey_code, DefaultProgressBar()); //默认不显示进度
    }

    template<typename ProgressFunc>
    bool build(const vector<TermCode>& vkey_code, ProgressFunc progress_func)
    {
        Trie trie;
        LOG(INFO) << "Building trie first" << std::endl;
        //---------build trie
        buildTrie(vkey_code, trie);
        LOG(INFO) << "Building double array trie" << std::endl;
        //---------use trie to build DATrie
        buildDATrie(trie, progress_func);

        clearTrie(trie);
    }

    template<typename ProgressFunc>
    bool buildDATrie(const Trie& trie, ProgressFunc progress_func)
    { //双数组索引树(位置0空出)，Trie树已建好[中英文词典均适用]
        if (trie.empty())
        {
            std::cerr << "trie is empty! Func(BuildDAtrie) error." << std::endl;
            return false;
        }
        m_viBase.clear();
        m_viCheck.clear();
        m_viWeight.clear();

        int progress = 0;

        typedef std::pair<short, short> PairSS;
        std::vector<PairSS > vpWord2SubCnt; //首字序号映射子结点数
        {
            for (size_t i = 0; i < trie.size(); ++i)
            {
                if (trie[i])
                {
                    vpWord2SubCnt.push_back(
                                            PairSS((short) i, trie[i]->front().wSubCnt));
                }
            }
            sort(vpWord2SubCnt.begin(), vpWord2SubCnt.end(),
                 boost::bind(&PairSS::second, _1) > boost::bind(&PairSS::second, _2)); //按孩子个数倒排
        }
        size_t fwSize = vpWord2SubCnt.size(); //首字个数

        //生成双数组trie树。
        m_viBase.resize(std::numeric_limits<short>::max());
        m_viCheck.resize(std::numeric_limits<short>::max());
        m_viWeight.resize(std::numeric_limits<short>::max());

        std::priority_queue<PosCnt, std::vector<PosCnt> > pq; //默认大值优先
        PosCnt pc; //当前结点信息
        PosCnt pcSub; //子结点信息
        TrieNode* pNodeFrst; //首字+子树结点指针
        short wBeg, wEnd; //子结点首尾索引

        int arraySz = (int) m_viBase.size();
        int nSquence; //首字序号
        int t; //后缀字的下标
        int nBaseVal; //base值
        bool bCheck; //是否找到空位
        VEC_INT viEndTag; //中间可成词结点base下标

        for (size_t i = 0; i < fwSize; ++i) //one loop:处理一棵首字子树
        {
            nSquence = vpWord2SubCnt[i].first;
            pNodeFrst = &(trie[nSquence]->front()); //首字

            if (!pNodeFrst->wSubCnt)
            { //单字
                m_viBase[nSquence] = -nSquence;
                m_viWeight[nSquence] = pNodeFrst->weight;
            }
            else
            {
                m_viCheck[nSquence] = 0;
                pc.nCnt = pNodeFrst->wSubCnt;
                pc.nPosInTrie = 0; //首字在trie子树中位置为0
                pc.nPosInBase = nSquence;
                pq.push(pc); //首字入队

                while (!pq.empty())
                { //处理子树
                    pc = pq.top();
                    pq.pop();

                    int base = pc.nPosInBase;
                    short pos = pc.nPosInTrie;
                    short subCnt = pc.nCnt;
                    if (subCnt)
                    {
                        wBeg = pNodeFrst[pos].wSubBeg + pos; //子结点首索引
                        wEnd = wBeg + pNodeFrst[pos].wSubCnt; //子结点尾索引

                        if (pNodeFrst[pos].bEnd)
                        { //中间字
                            viEndTag.push_back(base);
                            m_viWeight[base] = pNodeFrst[pos].weight;

                            progress++;
                            progress_func(progress, m_keyNum);
                        }

                        nBaseVal = base;

                        //安置子结点，取得该结点的最终base值
                        do
                        {
                            bCheck = true;
                            for (short j = wBeg; j < wEnd; ++j)
                            {
                                short c = pNodeFrst[j].wData;
                                t = nBaseVal + c;

                                if (t <= FRST_OFFSET) //TODO chg 为什么还要依赖编码中的FRST_OFFSET首字区域长度
                                { //不占用首字空间
                                    nBaseVal = FRST_OFFSET + 1 - c;
                                    bCheck = false;
                                    break;
                                }
                                if (t >= arraySz)
                                { //空间不够
                                    m_viBase.resize(t + std::numeric_limits<short>::max());
                                    m_viCheck.resize(t + std::numeric_limits<short>::max());
                                    m_viWeight.resize(t + std::numeric_limits<short>::max());
                                    arraySz = t + std::numeric_limits<short>::max();
                                }
                                if (m_viCheck[t])
                                { //位置已占用
                                    bCheck = false;
                                    ++nBaseVal;
                                    break;
                                }
                            }

                            if (bCheck && (nBaseVal == base) &&
                                    pNodeFrst[pos].bEnd)
                            { //有后缀但可成词,偏移量不能为数组下标
                                ++nBaseVal;
                                bCheck = false;
                            }
                        }
                        while (!bCheck);

                        m_viBase[base] = nBaseVal; //父节点BASE
                        for (short j = wBeg; j < wEnd; ++j) //子节点CHECK
                        {

                            t = nBaseVal + pNodeFrst[j].wData;
                            assert(t > FRST_OFFSET);
                            m_viCheck[t] = base;

                            pcSub.nCnt = pNodeFrst[j].wSubCnt;
                            pcSub.nPosInTrie = j;
                            pcSub.nPosInBase = t;
                            pq.push(pcSub);
                        }
                    }
                    else
                    { //词结束结点
                        m_viBase[base] = -base;
                        m_viWeight[base] = pNodeFrst[pos].weight;
                        progress++;
                        progress_func(progress, m_keyNum);
                    }
                }
            }
        }

        //处理中间成词结点base值
        size_t sz = viEndTag.size();
        for (size_t i = 0; i < sz; ++i)
        {
            m_viBase[viEndTag[i]] *= -1;
        }
        return true;
    }

    void buildTrie(const vector<TermCode>& vkey_code, Trie& trie)
    { //已按内码顺序排序且唯一的词做trie树[中英文词典均适用],注意必须排好序
        m_keyNum = vkey_code.size();
        if (!trie.empty())
        {
            typename Trie::iterator it;
            for (it = trie.begin(); it != trie.end(); ++it)
            {
                delete *it;
            }
            trie.clear();
        }
        trie.resize(FRST_OFFSET + 1); //首字最大个数，0位空

        typename vector<TermCode>::const_iterator itF; //同一个字的开始
        typename vector<TermCode>::const_iterator it;
        vector<typename vector<TermCode>::const_iterator> vecIter; //记录多字词
        typename vector<typename vector<TermCode>::const_iterator>::iterator itVecIter;
        typedef std::tr1::unordered_map<int, short> HashMap;

        short wordIndex; //字序号做trie树vector索引
        short wordFrst; //同层上个字序号
        short wordCur; //当前字序号
        short preLevelWordFrst; //上个父结点字序号
        short preLevelWordCur; //父结点字序号
        short nLevel; //当前层数
        int nPreLevelPosFrst; //父结点的位置
        int nlevelCount; //每层结点个数

        TrieNode treeNode;
        //一棵树各个字的位置映射
        //key-同一首字位置偏移*词最大字长+层数 val-vector<TrieNode>的索引
        HashMap hmTree;
        int nKey; //hmTree的key

        for (it = vkey_code.begin(); it != vkey_code.end();) //one loop:处理首字相同的词
        {
            itF = it;
            wordIndex = (ElemType) it->code[0]; //首字索引

            memset(&treeNode, 0, sizeof treeNode);
            treeNode.wData = wordIndex; //拷贝首字
            trie[wordIndex] = new std::vector<TrieNode>;
            trie[wordIndex]->push_back(treeNode);

            //处理首字相同词的首字
            while (it != vkey_code.end() && (ElemType) it->code[0] == wordIndex)
            {
                if (it->code.size() > 1)
                { //多字词
                    vecIter.push_back(it);
                }
                else
                { //单字词
                    assert(0 == (int) (it - itF));
                    nKey = (int) (it - itF) * WORDCNTMAX; //正常情况应该为0(按序且唯一)
                    hmTree.insert(std::pair<int, short>(nKey, 0)); //加入位置信息

                    trie[wordIndex]->front().bEnd = true;
                    trie[wordIndex]->front().weight = it->weight;
                }
                ++it;
            }//it指向相同首字词段尾

            //处理多字词，第2层以后
            nLevel = 1;

            while (!vecIter.empty()) //one loop:处理一层
            {
                wordFrst = 0;
                nlevelCount = 0;
                preLevelWordFrst = 0;
                nPreLevelPosFrst = -1;

                for (itVecIter = vecIter.begin(); itVecIter != vecIter.end();)
                { //处理一层中的一个字
                    preLevelWordCur = (*itVecIter)->code[nLevel - 1]; //父结点字序号
                    wordCur = (*itVecIter)->code[nLevel]; //当前结点字序号
                    //父节点在分段矩阵中的一维位置
                    nKey = (int) ((*itVecIter) - itF) * WORDCNTMAX + nLevel - 1;

                    if (preLevelWordCur != preLevelWordFrst ||
                            (preLevelWordCur == preLevelWordFrst &&
                            hmTree[nKey] != hmTree[nPreLevelPosFrst]))
                    { //新的父节点

                        (*trie[wordIndex])[hmTree[nKey]].wSubCnt = 1;
                        (*trie[wordIndex])[hmTree[nKey]].wSubBeg =
                                (short) trie[wordIndex]->size() - hmTree[nKey];

                        preLevelWordFrst = preLevelWordCur;
                        wordFrst = 0;
                    }
                    else
                    { //同一父节点
                        if (wordCur != wordFrst)
                        {
                            ++(*trie[wordIndex])[hmTree[nKey]].wSubCnt;
                        }
                    }

                    //当前节点在分段矩阵中的一维位置
                    nKey = (int) ((*itVecIter) - itF) * WORDCNTMAX + nLevel;

                    if (wordCur != wordFrst)
                    { //出现新字
                        ++nlevelCount;
                        wordFrst = wordCur;

                        memset(&treeNode, 0, sizeof treeNode);
                        treeNode.wData = wordCur; //拷贝当前字
                        //加入位置信息
                        hmTree.insert(
                                      std::pair<int, short>(nKey, (short) trie[wordIndex]->size()));
                        nPreLevelPosFrst =
                                (int) ((*itVecIter) - itF) * WORDCNTMAX + nLevel - 1; //父节点的位置

                        if ((int) (*itVecIter)->code.size() == nLevel + 1)
                        { //到本字成词
                            treeNode.bEnd = true;
                            treeNode.weight = (*itVecIter)->weight;
                            itVecIter = vecIter.erase(itVecIter); //该词处理完
                        }
                        else
                        {
                            ++itVecIter;
                        }
                        trie[wordIndex]->push_back(treeNode);
                    }
                    else
                    { //同上一字（暗示短词在先,词典一定要排好序）
                        //(不可有重复词，否则跳过，会造成溢出)
                        assert((int) (*itVecIter)->code.size() > nLevel + 1); //why will here wrong?
                        ++itVecIter;
                        //加入位置信息
                        hmTree.insert(
                                      std::pair<int, short>(nKey, (short) trie[wordIndex]->size() - 1));
                    }
                }
                ++nLevel;
            }
            hmTree.clear();
        }
    }

    /**
     * 精确查询一个编码串是否在trie树中，在返回true,否则返回false
     * 如果成功result记录对应的value, 注意key的长度如果len = 0 即key.size() 否则按len的长度
     * node_pos 起始查询的位置  暂时的构造不需要提供 bool search(const T& key, ValueType& result, size_t len = 0, size_t node_pos = 0)
     * 因为这里的构造是单独先处理一下首字母
     *
     * 注意
     *  * 这里构造的trie树是优先分配首字母的，首字母的编码为a 则 首字母状态位置是a, base[a] == 0 表示首字母不在
     *    也可以这样，-1表示原始头状态，base[-1] = 0 , 然后状态转移 base[0] + a = a,这样的话，需要check[a] 判断是否 = -1 一个思路
     *    这里就是首字母分别处理了，而不是由一个统一状态开始
     *
     * *从第二个字开始
     * 1.是否状态在trie中  check[now] = pre则在 check[now]存储上一个状态的位置index即pre,
     * 2.如果状态在trie中 它是否成词  base[now] < 0 则成词 否则 base[now]是下一个转移基础
     * 3.如果成词那么有两种情况
     *   1. 该词往下没有词了                    base[now] = -now
     *   2. 该词是词而且往下还有其它更长的成词     base[now] != -now  -base[now] 是下一个转移基础，参考 "阿根廷“那个图
     *   是trie中状态如果不成词一定有后继的状态
     *
     *  TODO searchExact
     *  与别的查询不同 它强调的是走完key的所有字看最后一个字的状态，如果中间有问题返回false
     */
    template<typename T>
    bool search(const T& key, ValueType& result) const
    {
        if (key.empty())
            return false;
        int len = key.size(); //------至少有一个字
        int p = (ElemType) key[0]; //-----p第一个字的状态位置，b第二个字的状态base
        if (!m_viBase[p] || (m_viBase[p] == -p && len > 1)) //-------首字母不在字典中,或者首字母是已最长词了而查询词更长属于提前由于成词但是没有后续状态的
            return false;

        //首字母是有效状态，且不是最终词，或者是最终词但是查询词长度也为1

        int b = abs(m_viBase[p]);
        int pre; //记录上一个状态位置
        //--------遍历从第二个字开始的状态
        size_t i = 1;
        for (; i < len; i++)
        {
            pre = p;
            p = b + (ElemType) key[i]; //-------p当前字状态位置
            if (pre == m_viCheck[p]) //-------当前字状态在字典中,check[p]存储了上一个状态位置pre
            {
                if (m_viBase[p] != -p) //-----该状态不是终点状态还有更长成词
                    b = abs(m_viBase[p]); //---转移到下一个字状态base,注意后面循环abs
                else //---成词而且没有后续状态跳出
                {
                    i++;
                    break;
                }
            }
            else
            {
                return false; //中间找不到后继状态的情况
            }
        }
        if (i < len) //提前由于成词但是没有后续状态而跳出
            return false;
        //---------如果所有字都遍历到了，即都是trie中的状态，判断最后一个字的状态是否是成词状态
        if (m_viBase[p] < 0) //--最后的字状态成词
        {
            result = m_viWeight[p];
            return true;
        }
        return false;
    }

    /*
     * 只查询是否在 TODO 代码重复
     */
    template<typename T>
    bool search(const T& key) const
    {
        if (key.empty())
            return false;
        int len = key.size(); //------至少有一个字
        int p = (ElemType) key[0]; //-----p第一个字的状态位置，b第二个字的状态base
        if (!m_viBase[p] || (m_viBase[p] == -p && len > 1)) //-------首字母不在字典中,或者首字母是已最长词了而查询词更长
            return false;
        int b = abs(m_viBase[p]);
        int pre; //记录上一个状态位置
        //--------遍历从第二个字开始的状态
        size_t i = 1;
        for (; i < len; i++)
        {
            pre = p;
            p = b + (ElemType) key[i]; //-------p当前字状态位置
            if (pre == m_viCheck[p]) //-------当前字状态在字典中,check[p]存储了上一个状态位置pre
            {
                if (m_viBase[p] != -p) //-----该状态不是终点状态还有更长成词
                    b = abs(m_viBase[p]); //---转移到下一个字状态base,注意后面循环abs
                else //---成词而且没有后续状态跳出
                {
                    i++;
                    break;
                }
            }
            else
            {
                return false;
            }
        }
        if (i < len) //提前由于成词但是没有后续状态而跳出
            return false;
        //---------如果所有字都遍历到了，即都是trie中的状态，判断最后一个字的状态是否是成词状态
        if (m_viBase[p] < 0) //--最后的字状态成词
            return true;
        return false;
    }

    template<typename T>
    bool search_(const T& key, int len) const
    {//注意有的外部代码调用search需要fix
        if (len == 0)
            return false;
        int p = (ElemType) key[0]; //-----p第一个字的状态位置，b第二个字的状态base
        if (!m_viBase[p] || (m_viBase[p] == -p && len > 1)) //-------首字母不在字典中,或者首字母是已最长词了而查询词更长
            return false;
        int b = abs(m_viBase[p]);
        int pre; //记录上一个状态位置
        //--------遍历从第二个字开始的状态
        size_t i = 1;
        for (; i < len; i++)
        {
            pre = p;
            p = b + (ElemType) key[i]; //-------p当前字状态位置
            if (pre == m_viCheck[p]) //-------当前字状态在字典中,check[p]存储了上一个状态位置pre
            {
                if (m_viBase[p] != -p) //-----该状态不是终点状态还有更长成词
                    b = abs(m_viBase[p]); //---转移到下一个字状态base,注意后面循环abs
                else //---成词而且没有后续状态跳出
                {
                    i++;
                    break;
                }
            }
            else
            {
                return false;
            }
        }
        if (i < len) //提前由于成词但是没有后续状态而跳出
            return false;
        //---------如果所有字都遍历到了，即都是trie中的状态，判断最后一个字的状态是否是成词状态
        if (m_viBase[p] < 0) //--最后的字状态成词
            return true;
        return false;
    }

    /**
     * 查找串，得到第一个匹配的<位置，value>
     * 没有任何匹配返回false
     */
    template<typename T>
    bool searchFirst(const T& key, ResultType& result) const
    {
        if (key.empty())
            return false;
        int len = key.size(); //------至少有一个字
        int p = (ElemType) key[0];

        if (!m_viBase[p]) //-------首字母不在字典中
            return false;

        if (m_viBase[p] < 0) //首字成词,则返回
        {
            result.length = 1;
            result.value = m_viWeight[p];
            return true;
        }

        int b = abs(m_viBase[p]);
        int pre; //记录上一个状态位置
        //--------遍历从第二个字开始的状态
        for (size_t i = 1; i < len; i++)
        {
            pre = p;
            p = b + (ElemType) key[i]; //-------p当前字状态位置
            if (pre == m_viCheck[p]) //-------当前字状态在字典中,check[p]存储了上一个状态位置pre
            {
                if (m_viBase[p] < 0) //该状态成词
                {
                    result.length = i + 1;
                    result.value = m_viWeight[p];
                    return true;
                }
                else
                    b = m_viBase[p]; //--到下一状态的base
            }
            else //无下一状态 因为前面只要有成词就已经退出所以到达无效状态意味着之前没有找到任何词
            {
                return false;
            }
        }

        //---------如果所有字都遍历到了，即都是trie中的状态,但是没有找到成词
        return false;
    }

    template<typename T>
    bool searchFirst(const T& key, int len, ResultType& result) const
    {
        if (!len)
            return false;
        int p = (ElemType) key[0];

        if (!m_viBase[p]) //-------首字母不在字典中
            return false;

        if (m_viBase[p] < 0) //首字成词,则返回
        {
            result.length = 1;
            result.value = m_viWeight[p];
            return true;
        }

        int b = abs(m_viBase[p]);
        int pre; //记录上一个状态位置
        //--------遍历从第二个字开始的状态
        for (size_t i = 1; i < len; i++)
        {
            pre = p;
            p = b + (ElemType) key[i]; //-------p当前字状态位置
            if (pre == m_viCheck[p]) //-------当前字状态在字典中,check[p]存储了上一个状态位置pre
            {
                if (m_viBase[p] < 0) //该状态成词
                {
                    result.length = i + 1;
                    result.value = m_viWeight[p];
                    return true;
                }
                else
                    b = m_viBase[p]; //--到下一状态的base
            }
            else //无下一状态 因为前面只要有成词就已经退出所以到达无效状态意味着之前没有找到任何词
            {
                return false;
            }
        }

        //---------如果所有字都遍历到了，即都是trie中的状态,但是没有找到成词
        return false;
    }

    /**
     * 尽量查找最短的非单字词
     * 如果找不到还是返回单字，
     * 如果单字也找不到返回false
     */
    template<typename T>
    bool searchFirstNonSingle(const T& key, ResultType& result) const
    {
        if (key.empty())
            return false;
        int len = key.size(); //------至少有一个字
        int p = (ElemType) key[0];

        if (!m_viBase[p]) //-------首字母不在字典中
            return false;

        bool has_first = false;
        if (m_viBase[p] < 0) //首字成词,则返回
        {
            result.length = 1;
            result.value = m_viWeight[p];
            has_first = true;
        }

        int b = abs(m_viBase[p]);
        int pre; //记录上一个状态位置
        //--------遍历从第二个字开始的状态
        for (size_t i = 1; i < len; i++)
        {
            pre = p;
            p = b + (ElemType) key[i]; //-------p当前字状态位置
            if (pre == m_viCheck[p]) //-------当前字状态在字典中,check[p]存储了上一个状态位置pre
            {
                if (m_viBase[p] < 0) //该状态成词
                {
                    result.length = i + 1;
                    result.value = m_viWeight[p];
                    return true;
                }
                else
                    b = m_viBase[p]; //--到下一状态的base
            }
            else //无下一状态 因为前面只要有成词就已经退出所以到达无效状态意味着之前没有找到任何词
            {
                return has_first;
            }
        }

        //---------如果所有字都遍历到了，即都是trie中的状态,但是没有找到成词

        return has_first;
    }

    template<typename T>
    bool searchFirstNonSingle(const T& key, int len, ResultType& result) const
    {
        if (!len)
            return false;
        int p = (ElemType) key[0];

        if (!m_viBase[p]) //-------首字母不在字典中
            return false;

        bool has_first = false;
        if (m_viBase[p] < 0) //首字成词,则返回
        {
            result.length = 1;
            result.value = m_viWeight[p];
            has_first = true;
        }

        int b = abs(m_viBase[p]);
        int pre; //记录上一个状态位置
        //--------遍历从第二个字开始的状态
        for (size_t i = 1; i < len; i++)
        {
            pre = p;
            p = b + (ElemType) key[i]; //-------p当前字状态位置
            if (pre == m_viCheck[p]) //-------当前字状态在字典中,check[p]存储了上一个状态位置pre
            {
                if (m_viBase[p] < 0) //该状态成词
                {
                    result.length = i + 1;
                    result.value = m_viWeight[p];
                    return true;
                }
                else
                    b = m_viBase[p]; //--到下一状态的base
            }
            else //无下一状态 因为前面只要有成词就已经退出所以到达无效状态意味着之前没有找到任何词
            {
                return has_first;
            }
        }

        //---------如果所有字都遍历到了，即都是trie中的状态,但是没有找到成词

        return has_first;
    }

    /**
     * 找最短成词返回长度，如果没找到返回0
     */
    template<typename T>
    int matchFirst(const T& key, int len) const
    {
        if (!len)
            return 0;
        int p = (ElemType) key[0];

        if (!m_viBase[p]) //-------首字母不在字典中
            return 0;

        int has_first = 0;
        if (m_viBase[p] < 0) //首字成词,则返回
        {
            return 1; //最短是单字
        }

        int b = abs(m_viBase[p]);
        int pre; //记录上一个状态位置
        //--------遍历从第二个字开始的状态
        for (size_t i = 1; i < len; i++)
        {
            pre = p;
            p = b + (ElemType) key[i]; //-------p当前字状态位置
            if (pre == m_viCheck[p]) //-------当前字状态在字典中,check[p]存储了上一个状态位置pre
            {
                if (m_viBase[p] < 0) //该状态成词
                {
                    return i + 1;
                }
                else
                    b = m_viBase[p]; //--到下一状态的base
            }
            else //无下一状态 因为前面只要有成词就已经退出所以到达无效状态意味着之前没有找到任何词
            {
                return 0;
            }
        }

        //---------如果所有字都遍历到了，即都是trie中的状态,但是没有找到成词
        return 0;
    }

    template<typename T>
    int matchFirstNonSingle(const T& key, int len) const
    {
        if (!len)
            return 0;
        int p = (ElemType) key[0];

        if (!m_viBase[p]) //-------首字母不在字典中
            return 0;

        int has_first = 0;
        if (m_viBase[p] < 0) //首字成词,则返回
        {
            has_first = 1;
        }

        int b = abs(m_viBase[p]);
        int pre; //记录上一个状态位置
        //--------遍历从第二个字开始的状态
        for (size_t i = 1; i < len; i++)
        {
            pre = p;
            p = b + (ElemType) key[i]; //-------p当前字状态位置
            if (pre == m_viCheck[p]) //-------当前字状态在字典中,check[p]存储了上一个状态位置pre
            {
                if (m_viBase[p] < 0) //该状态成词
                {
                    return i + 1;
                }
                else
                    b = m_viBase[p]; //--到下一状态的base
            }
            else //无下一状态 因为前面只要有成词就已经退出所以到达无效状态意味着之前没有找到任何词
            {
                return has_first;
            }
        }

        //---------如果所有字都遍历到了，即都是trie中的状态,但是没有找到成词

        return has_first;
    }

    /**
     * 查找串，得到最长的匹配的<位置，value>
     * 没有任何匹配返回false
     *
     * 注意字典里面 abc abcdef
     * 串 abcde匹配到abc是一个结果但是不是词典中最长的，尝试匹配完abcde后返回还是abc,
     * 串中所能找到的最长的
     */
    template<typename T>
    bool searchLongest(const T& key, int len, ResultType& result) const
    {
        result.length = 0; //如果没有length = 0
        if (!len)
            return false;
        int p = (ElemType) key[0]; //-----p第一个字的状态位置，b第二个字的状态base
        if (!m_viBase[p]) //-------首字母不在字典中
            return false;

        if (m_viBase[p] < 0) //首字成词
        {
            result.length = 1;
            result.value = m_viWeight[p];
            if (m_viBase[p] == -p || len == 1) //----如果已是最长
                return true;
        }

        //首字不是最长成词,继续
        int b = abs(m_viBase[p]);
        int pre; //记录上一个状态位置
        //--------遍历从第二个字开始的状态
        for (size_t i = 1; i < len; i++)
        {
            pre = p;
            p = b + (ElemType) key[i]; //-------p当前字状态位置
            if (pre == m_viCheck[p]) //-------当前字状态在字典中,check[p]存储了上一个状态位置pre
            {
                if (m_viBase[p] < 0) //该状态成词
                {
                    result.length = i + 1;
                    result.value = m_viWeight[p];
                    if (m_viBase[p] == -p)
                        return true;
                }
                b = abs(m_viBase[p]); //--到下一状态的base
            }
            else
                return (result.length); //如果被修改过则有结果
        }
        return (result.length);
    }

    template<typename T>
    bool searchLongest(const T& key, int len, ResultType& result, int stop_value) const
    {
        result.length = 0; //如果没有length = 0
        if (!len)
            return false;
        int p = (ElemType) key[0]; //-----p第一个字的状态位置，b第二个字的状态base
        if (!m_viBase[p]) //-------首字母不在字典中
            return false;

        if (m_viBase[p] < 0) //首字成词
        {
            result.length = 1;
            result.value = m_viWeight[p];
            if (m_viBase[p] == -p || len == 1) //----如果已是最长
                return true;
        }

        //首字不是最长成词,继续
        int b = abs(m_viBase[p]);
        int pre; //记录上一个状态位置
        //--------遍历从第二个字开始的状态
        for (size_t i = 1; i < len; i++)
        {
            pre = p;
            p = b + (ElemType) key[i]; //-------p当前字状态位置
            if (pre == m_viCheck[p]) //-------当前字状态在字典中,check[p]存储了上一个状态位置pre
            {
                if (m_viBase[p] < 0) //该状态成词
                {
                    if (m_viWeight[p] != stop_value) //如果遇到类似"电压力锅"这样的词需要直接返回前面的结果
                    {
                        result.length = i + 1;
                        result.value = m_viWeight[p];
                    }
                    if (m_viBase[p] == -p)
                        return true;
                }
                b = abs(m_viBase[p]); //--到下一状态的base
            }
            else
                return (result.length); //如果被修改过则有结果
        }
        return (result.length);
    }

    template<typename T>
    bool searchLongest(const T& key, ResultType& result) const
    {
        result.length = 0; //如果没有length = 0
        int len = key.size();
        if (!len)
            return false;
        int p = (ElemType) key[0]; //-----p第一个字的状态位置，b第二个字的状态base
        if (!m_viBase[p]) //-------首字母不在字典中
            return false;

        if (m_viBase[p] < 0) //首字成词
        {
            result.length = 1;
            result.value = m_viWeight[p];
            if (m_viBase[p] == -p || len == 1) //----如果已是最长
                return true;
        }

        //首字不是最长成词,继续
        int b = abs(m_viBase[p]);
        int pre; //记录上一个状态位置
        //--------遍历从第二个字开始的状态
        for (size_t i = 1; i < len; i++)
        {
            pre = p;
            p = b + (ElemType) key[i]; //-------p当前字状态位置
            if (pre == m_viCheck[p]) //-------当前字状态在字典中,check[p]存储了上一个状态位置pre
            {
                if (m_viBase[p] < 0) //该状态成词
                {
                    result.length = i + 1;
                    result.value = m_viWeight[p];
                    if (m_viBase[p] == -p)
                        return true;
                }
                b = abs(m_viBase[p]); //--到下一状态的base
            }
            else
                return (result.length); //如果被修改过则有结果
        }
        return (result.length);
    }

    template<typename T>
    int matchLongest(const T& key, int len) const
    {
        if (!len)
            return 0;
        int p = (ElemType) key[0]; //-----p第一个字的状态位置，b第二个字的状态base
        if (!m_viBase[p]) //-------首字母不在字典中
            return 0;

        int length = 0;
        if (m_viBase[p] < 0) //首字成词
        {
            length = 1;
            if (m_viBase[p] == -p || len == 1) //----如果已是最长
                return length;
        }

        //首字不是最长成词,继续
        int b = abs(m_viBase[p]);
        int pre; //记录上一个状态位置
        //--------遍历从第二个字开始的状态
        for (size_t i = 1; i < len; i++)
        {
            pre = p;
            p = b + (ElemType) key[i]; //-------p当前字状态位置
            if (pre == m_viCheck[p]) //-------当前字状态在字典中,check[p]存储了上一个状态位置pre
            {
                if (m_viBase[p] < 0) //该状态成词
                {
                    length = i + 1;
                    if (m_viBase[p] == -p)
                        return length;
                }
                b = abs(m_viBase[p]); //--到下一状态的base
            }
            else
                return length; //如果被修改过则有结果
        }
        return length;
    }

    /**
     * 查找串，得到所有可能的匹配的<位置，value>
     * 没有任何匹配返回false
     */
    template<typename T>
    bool searchAll(const T& key, vector<ResultType>& result_vec) const
    {
        result_vec.clear();
        if (key.empty())
            return false;
        int len = key.size(); //------至少有一个字
        int p = (ElemType) key[0]; //-----p第一个字的状态位置，b第二个字的状态base
        if (!m_viBase[p]) //-------首字母不在字典中
            return false;
        ResultType result;
        if (m_viBase[p] < 0) //首字成词
        {
            result.length = 1;
            result.value = m_viWeight[p];
            result_vec.push_back(result);
            if (m_viBase[p] == -p || len == 1) //----如果已是最长
                return true;
        }
        int b = abs(m_viBase[p]);
        int pre; //记录上一个状态位置
        //--------遍历从第二个字开始的状态
        for (size_t i = 1; i < len; i++)
        {
            pre = p;
            p = b + (ElemType) key[i]; //-------p当前字状态位置
            if (pre == m_viCheck[p]) //-------当前字状态在字典中,check[p]存储了上一个状态位置pre
            {
                if (m_viBase[p] < 0) //该状态成词
                {
                    result.length = i + 1;
                    result.value = m_viWeight[p];
                    result_vec.push_back(result);
                    if (m_viBase[p] == -p)
                        return true;
                }
                b = abs(m_viBase[p]); //--到下一状态的base
            }
            else
                return !result_vec.empty();
        }
        return !result_vec.empty(); //可能是走完了abcde仍然没有达到字典中最终状态
    }

    template<typename T>
    bool searchAll(const T& key, int len, vector<ResultType>& result_vec) const
    {
        if (!len)
            return false;
        result_vec.clear();
        result_vec.reserve(len);
        int p = (ElemType) key[0]; //-----p第一个字的状态位置，b第二个字的状态base
        if (!m_viBase[p]) //-------首字母不在字典中
            return false;
        ResultType result;
        if (m_viBase[p] < 0) //首字成词
        {
            result.length = 1;
            result.value = m_viWeight[p];
            result_vec.push_back(result);
            if (m_viBase[p] == -p || len == 1) //----如果已是最长
                return true;
        }
        int b = abs(m_viBase[p]);
        int pre; //记录上一个状态位置
        //--------遍历从第二个字开始的状态
        for (size_t i = 1; i < len; i++)
        {
            pre = p;
            p = b + (ElemType) key[i]; //-------p当前字状态位置
            if (pre == m_viCheck[p]) //-------当前字状态在字典中,check[p]存储了上一个状态位置pre
            {
                if (m_viBase[p] < 0) //该状态成词
                {
                    result.length = i + 1;
                    result.value = m_viWeight[p];
                    result_vec.push_back(result);
                    if (m_viBase[p] == -p)
                        return true;
                }
                b = abs(m_viBase[p]); //--到下一状态的base
            }
            else
                return !result_vec.empty();
        }
        return !result_vec.empty(); //可能是走完了abcde仍然没有达到字典中最终状态
    }

    template<typename T>
    int searchAll(const T& key, int len, ElemType* len_vec, ValueType* val_vec, int max_len = 8) const
    {
        if (!len)
            return 0;
        int result_num = 0;
        int p = (ElemType) key[0]; //-----p第一个字的状态位置，b第二个字的状态base
        if (!m_viBase[p]) //-------首字母不在字典中
            return 0;
        if (m_viBase[p] < 0) //首字成词
        {
            len_vec[result_num] = 1;
            val_vec[result_num++] = m_viWeight[p];
            if (m_viBase[p] == -p || len == 1) //----如果已是最长
                return result_num;
        }
        int b = abs(m_viBase[p]);
        int pre; //记录上一个状态位置
        //--------遍历从第二个字开始的状态
        for (size_t i = 1; i < len && result_num < max_len; i++)
        {
            pre = p;
            p = b + (ElemType) key[i]; //-------p当前字状态位置
            if (pre == m_viCheck[p]) //-------当前字状态在字典中,check[p]存储了上一个状态位置pre
            {
                if (m_viBase[p] < 0) //该状态成词
                {
                    len_vec[result_num] = i + 1;
                    val_vec[result_num++] = m_viWeight[p];
                    if (m_viBase[p] == -p)
                        return result_num;
                }
                b = abs(m_viBase[p]); //--到下一状态的base
            }
            else
                return result_num;
        }
        return result_num; //可能是走完了abcde仍然没有达到字典中最终状态
    }

    template<typename T>
    bool searchAll2(const T& key, int len, vector<ResultType>& result_vec) const
    { //不记录首字成词的情况
        if (!len)
            return false;
        result_vec.clear();
        result_vec.reserve(len);
        int p = (ElemType) key[0]; //-----p第一个字的状态位置，b第二个字的状态base
        if (!m_viBase[p]) //-------首字母不在字典中
            return false;
        ResultType result;
        int b = abs(m_viBase[p]);
        int pre; //记录上一个状态位置
        //--------遍历从第二个字开始的状态
        for (size_t i = 1; i < len; i++)
        {
            pre = p;
            p = b + (ElemType) key[i]; //-------p当前字状态位置
            if (pre == m_viCheck[p]) //-------当前字状态在字典中,check[p]存储了上一个状态位置pre
            {
                if (m_viBase[p] < 0) //该状态成词
                {
                    result.length = i + 1;
                    result.value = m_viWeight[p];
                    result_vec.push_back(result);
                    if (m_viBase[p] == -p)
                        return true;
                }
                b = abs(m_viBase[p]); //--到下一状态的base
            }
            else
                return !result_vec.empty();
        }
        return !result_vec.empty(); //可能是走完了abcde仍然没有达到字典中最终状态
    }

    /*
     * 不记录首字成词的情况
     * 12.07 改成存储length
     * 下面两个都是带有限制数目的max_len 一般限制最多找到8个词就停止
     */
    template<typename T>
    int searchAll2(const T& key, int len, ElemType* result_vec, int max_len = 8) const
    {
        if (!len)
            return 0;
        int result_num = 0;
        int p = (ElemType) key[0]; //-----p第一个字的状态位置，b第二个字的状态base
        int b = abs(m_viBase[p]);
        int pre; //记录上一个状态位置
        //--------遍历从第二个字开始的状态
        for (size_t i = 1; i < len && result_num < max_len; i++)
        {
            pre = p;
            p = b + (ElemType) key[i]; //-------p当前字状态位置
            if (pre == m_viCheck[p]) //-------当前字状态在字典中,check[p]存储了上一个状态位置pre
            {
                if (m_viBase[p] < 0) //该状态成词
                {
                    result_vec[result_num++] = i + 1;
                    if (m_viBase[p] == -p)
                        return result_num;
                }
                b = abs(m_viBase[p]); //--到下一状态的base
            }
            else
                return result_num;
        }
        return result_num; //可能是走完了abcde仍然没有达到字典中最终状态
    }

    bool canSearch(ElemType s) const
    {
        int base = m_viBase[s];
        if (base && base != -s)
            return true;
        else
            return false;
    }
};

typedef DATrieT<short, vector<short>, int> DATrie; //TODO basic_string<short> or vector<short>
//typedef DATrieT<unsigned char, string, int> DATrie;
}

#endif  //----end of DATRIE_H_
