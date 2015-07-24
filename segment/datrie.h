/** 
 *  ==============================================================================
 * 
 *          \file   datrie.h
 *
 *        \author   gezi  
 *          
 *          \date   2010-09-25 15:56:11.433657
 *  
 *  \Description:   һ����̬������double array trie��,ԭ�зִ��д�����ȡ��װ
 *                  Ϊ�˼��Ȳ��������
 *                  TODO
 *                  1. ��̬����
 *                  2. �Ϻõ�֧����չ����崦��
 *
 *                  ע����Ҫ��֤�����ֵ�Ļ���Ҫ�����ֵ�˳������
 * 
 *                  weight ���� �൱�� key,value�е�value,ע�⵱ǰ����value������int,�洢������
 *                  TODO ���������ܱ仯Ҳ����Ҫ�Ķ������Ҫʹ��hashmap ���洢�أ�������Ҫ�䶯�´����ˡ���
 *                  resize, push_back ��Ҫȥ����load saveҲ��Ҫ�䣬���л��Ĳ���Ҫ��
 *
 *                  ȡ���� check *-1 ��ʾ��壬ֻ�洢weight ���������ж����
 *
 *
 *                  FIXME ���load save�Ļ� ValueType�����Ǽ����Ͱ�
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
 *ElemType �Ǽ���Key�е���Ԫ�ص����ͣ�Ĭ�϶���gbk��short,Ҳ����char
 * ����code�ĸ����ͬ��key Ĭ��������basic_string<ElemType>
 *ValueType �ǽ������ Ĭ��int
 * value�����ͬweight
 */
template<typename ElemType, typename KeyType, typename ValueType>
class DATrieT
{
public:
    typedef KeyType CodeType;
    //�ַ�����
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
        int value; //��Ӧ��value
        int length; //���ز��ҵ��Ĵʵĳ���

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
        ValueType weight; //Ȩ��
        short wSubCnt; //���Ӹ���
        short wSubBeg; //��һ�ӽ����ʼ����
        ElemType wData; //�����
        bool bEnd; //�ɳɴʱ�־
    };

    struct PosCnt
    { //�����TRIE�е�λ����Ϣ
        int nPosInBase; //base�±�
        short nPosInTrie; //Trie����λ��
        short nCnt; //�ӽ����

        bool operator<(const PosCnt & pc)const //���ȼ�
        {
            return this->nCnt < pc.nCnt;
        }
    };

    typedef std::vector<std::vector<TrieNode>* > Trie;
    typedef vector<int> BaseVec;
    typedef vector<uint> CheckVec;
    typedef vector<ValueType> WeightVec;
private:
    static const short WORDCNTMAX_CH = 15; //���������ֳ�
    static const short WORDCNTMAX_EN = 30; //�Ǻ��������ֳ�
    static const short WORDCNTMAX =
            WORDCNTMAX_CH > WORDCNTMAX_EN ? WORDCNTMAX_CH : WORDCNTMAX_EN; //����Trie��
    static const short FRST_OFFSET = 8095; //�������򳤶�

    int m_keyNum;
    //Double-Array Trie
    BaseVec m_viBase; //ֱ���ӽ��ת�������Ƿ�ɴ�
    CheckVec m_viCheck; //ǰ������š��Ƿ�Ϊ���崮
    WeightVec m_viWeight; //�൱��key,value�е�value  ע�����value��int�����Ż��ڴ治��Ҫm_viWeight
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
    { //�ͷ�Trie��
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
        build(vkey_code, DefaultProgressBar()); //Ĭ�ϲ���ʾ����
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
    { //˫����������(λ��0�ճ�)��Trie���ѽ���[��Ӣ�Ĵʵ������]
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
        std::vector<PairSS > vpWord2SubCnt; //�������ӳ���ӽ����
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
                 boost::bind(&PairSS::second, _1) > boost::bind(&PairSS::second, _2)); //�����Ӹ�������
        }
        size_t fwSize = vpWord2SubCnt.size(); //���ָ���

        //����˫����trie����
        m_viBase.resize(std::numeric_limits<short>::max());
        m_viCheck.resize(std::numeric_limits<short>::max());
        m_viWeight.resize(std::numeric_limits<short>::max());

        std::priority_queue<PosCnt, std::vector<PosCnt> > pq; //Ĭ�ϴ�ֵ����
        PosCnt pc; //��ǰ�����Ϣ
        PosCnt pcSub; //�ӽ����Ϣ
        TrieNode* pNodeFrst; //����+�������ָ��
        short wBeg, wEnd; //�ӽ����β����

        int arraySz = (int) m_viBase.size();
        int nSquence; //�������
        int t; //��׺�ֵ��±�
        int nBaseVal; //baseֵ
        bool bCheck; //�Ƿ��ҵ���λ
        VEC_INT viEndTag; //�м�ɳɴʽ��base�±�

        for (size_t i = 0; i < fwSize; ++i) //one loop:����һ����������
        {
            nSquence = vpWord2SubCnt[i].first;
            pNodeFrst = &(trie[nSquence]->front()); //����

            if (!pNodeFrst->wSubCnt)
            { //����
                m_viBase[nSquence] = -nSquence;
                m_viWeight[nSquence] = pNodeFrst->weight;
            }
            else
            {
                m_viCheck[nSquence] = 0;
                pc.nCnt = pNodeFrst->wSubCnt;
                pc.nPosInTrie = 0; //������trie������λ��Ϊ0
                pc.nPosInBase = nSquence;
                pq.push(pc); //�������

                while (!pq.empty())
                { //��������
                    pc = pq.top();
                    pq.pop();

                    int base = pc.nPosInBase;
                    short pos = pc.nPosInTrie;
                    short subCnt = pc.nCnt;
                    if (subCnt)
                    {
                        wBeg = pNodeFrst[pos].wSubBeg + pos; //�ӽ��������
                        wEnd = wBeg + pNodeFrst[pos].wSubCnt; //�ӽ��β����

                        if (pNodeFrst[pos].bEnd)
                        { //�м���
                            viEndTag.push_back(base);
                            m_viWeight[base] = pNodeFrst[pos].weight;

                            progress++;
                            progress_func(progress, m_keyNum);
                        }

                        nBaseVal = base;

                        //�����ӽ�㣬ȡ�øý�������baseֵ
                        do
                        {
                            bCheck = true;
                            for (short j = wBeg; j < wEnd; ++j)
                            {
                                short c = pNodeFrst[j].wData;
                                t = nBaseVal + c;

                                if (t <= FRST_OFFSET) //TODO chg Ϊʲô��Ҫ���������е�FRST_OFFSET�������򳤶�
                                { //��ռ�����ֿռ�
                                    nBaseVal = FRST_OFFSET + 1 - c;
                                    bCheck = false;
                                    break;
                                }
                                if (t >= arraySz)
                                { //�ռ䲻��
                                    m_viBase.resize(t + std::numeric_limits<short>::max());
                                    m_viCheck.resize(t + std::numeric_limits<short>::max());
                                    m_viWeight.resize(t + std::numeric_limits<short>::max());
                                    arraySz = t + std::numeric_limits<short>::max();
                                }
                                if (m_viCheck[t])
                                { //λ����ռ��
                                    bCheck = false;
                                    ++nBaseVal;
                                    break;
                                }
                            }

                            if (bCheck && (nBaseVal == base) &&
                                    pNodeFrst[pos].bEnd)
                            { //�к�׺���ɳɴ�,ƫ��������Ϊ�����±�
                                ++nBaseVal;
                                bCheck = false;
                            }
                        }
                        while (!bCheck);

                        m_viBase[base] = nBaseVal; //���ڵ�BASE
                        for (short j = wBeg; j < wEnd; ++j) //�ӽڵ�CHECK
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
                    { //�ʽ������
                        m_viBase[base] = -base;
                        m_viWeight[base] = pNodeFrst[pos].weight;
                        progress++;
                        progress_func(progress, m_keyNum);
                    }
                }
            }
        }

        //�����м�ɴʽ��baseֵ
        size_t sz = viEndTag.size();
        for (size_t i = 0; i < sz; ++i)
        {
            m_viBase[viEndTag[i]] *= -1;
        }
        return true;
    }

    void buildTrie(const vector<TermCode>& vkey_code, Trie& trie)
    { //�Ѱ�����˳��������Ψһ�Ĵ���trie��[��Ӣ�Ĵʵ������],ע������ź���
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
        trie.resize(FRST_OFFSET + 1); //������������0λ��

        typename vector<TermCode>::const_iterator itF; //ͬһ���ֵĿ�ʼ
        typename vector<TermCode>::const_iterator it;
        vector<typename vector<TermCode>::const_iterator> vecIter; //��¼���ִ�
        typename vector<typename vector<TermCode>::const_iterator>::iterator itVecIter;
        typedef std::tr1::unordered_map<int, short> HashMap;

        short wordIndex; //�������trie��vector����
        short wordFrst; //ͬ���ϸ������
        short wordCur; //��ǰ�����
        short preLevelWordFrst; //�ϸ�����������
        short preLevelWordCur; //����������
        short nLevel; //��ǰ����
        int nPreLevelPosFrst; //������λ��
        int nlevelCount; //ÿ�������

        TrieNode treeNode;
        //һ���������ֵ�λ��ӳ��
        //key-ͬһ����λ��ƫ��*������ֳ�+���� val-vector<TrieNode>������
        HashMap hmTree;
        int nKey; //hmTree��key

        for (it = vkey_code.begin(); it != vkey_code.end();) //one loop:����������ͬ�Ĵ�
        {
            itF = it;
            wordIndex = (ElemType) it->code[0]; //��������

            memset(&treeNode, 0, sizeof treeNode);
            treeNode.wData = wordIndex; //��������
            trie[wordIndex] = new std::vector<TrieNode>;
            trie[wordIndex]->push_back(treeNode);

            //����������ͬ�ʵ�����
            while (it != vkey_code.end() && (ElemType) it->code[0] == wordIndex)
            {
                if (it->code.size() > 1)
                { //���ִ�
                    vecIter.push_back(it);
                }
                else
                { //���ִ�
                    assert(0 == (int) (it - itF));
                    nKey = (int) (it - itF) * WORDCNTMAX; //�������Ӧ��Ϊ0(������Ψһ)
                    hmTree.insert(std::pair<int, short>(nKey, 0)); //����λ����Ϣ

                    trie[wordIndex]->front().bEnd = true;
                    trie[wordIndex]->front().weight = it->weight;
                }
                ++it;
            }//itָ����ͬ���ִʶ�β

            //������ִʣ���2���Ժ�
            nLevel = 1;

            while (!vecIter.empty()) //one loop:����һ��
            {
                wordFrst = 0;
                nlevelCount = 0;
                preLevelWordFrst = 0;
                nPreLevelPosFrst = -1;

                for (itVecIter = vecIter.begin(); itVecIter != vecIter.end();)
                { //����һ���е�һ����
                    preLevelWordCur = (*itVecIter)->code[nLevel - 1]; //����������
                    wordCur = (*itVecIter)->code[nLevel]; //��ǰ��������
                    //���ڵ��ڷֶξ����е�һάλ��
                    nKey = (int) ((*itVecIter) - itF) * WORDCNTMAX + nLevel - 1;

                    if (preLevelWordCur != preLevelWordFrst ||
                            (preLevelWordCur == preLevelWordFrst &&
                            hmTree[nKey] != hmTree[nPreLevelPosFrst]))
                    { //�µĸ��ڵ�

                        (*trie[wordIndex])[hmTree[nKey]].wSubCnt = 1;
                        (*trie[wordIndex])[hmTree[nKey]].wSubBeg =
                                (short) trie[wordIndex]->size() - hmTree[nKey];

                        preLevelWordFrst = preLevelWordCur;
                        wordFrst = 0;
                    }
                    else
                    { //ͬһ���ڵ�
                        if (wordCur != wordFrst)
                        {
                            ++(*trie[wordIndex])[hmTree[nKey]].wSubCnt;
                        }
                    }

                    //��ǰ�ڵ��ڷֶξ����е�һάλ��
                    nKey = (int) ((*itVecIter) - itF) * WORDCNTMAX + nLevel;

                    if (wordCur != wordFrst)
                    { //��������
                        ++nlevelCount;
                        wordFrst = wordCur;

                        memset(&treeNode, 0, sizeof treeNode);
                        treeNode.wData = wordCur; //������ǰ��
                        //����λ����Ϣ
                        hmTree.insert(
                                      std::pair<int, short>(nKey, (short) trie[wordIndex]->size()));
                        nPreLevelPosFrst =
                                (int) ((*itVecIter) - itF) * WORDCNTMAX + nLevel - 1; //���ڵ��λ��

                        if ((int) (*itVecIter)->code.size() == nLevel + 1)
                        { //�����ֳɴ�
                            treeNode.bEnd = true;
                            treeNode.weight = (*itVecIter)->weight;
                            itVecIter = vecIter.erase(itVecIter); //�ôʴ�����
                        }
                        else
                        {
                            ++itVecIter;
                        }
                        trie[wordIndex]->push_back(treeNode);
                    }
                    else
                    { //ͬ��һ�֣���ʾ�̴�����,�ʵ�һ��Ҫ�ź���
                        //(�������ظ��ʣ�������������������)
                        assert((int) (*itVecIter)->code.size() > nLevel + 1); //why will here wrong?
                        ++itVecIter;
                        //����λ����Ϣ
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
     * ��ȷ��ѯһ�����봮�Ƿ���trie���У��ڷ���true,���򷵻�false
     * ����ɹ�result��¼��Ӧ��value, ע��key�ĳ������len = 0 ��key.size() ����len�ĳ���
     * node_pos ��ʼ��ѯ��λ��  ��ʱ�Ĺ��첻��Ҫ�ṩ bool search(const T& key, ValueType& result, size_t len = 0, size_t node_pos = 0)
     * ��Ϊ����Ĺ����ǵ����ȴ���һ������ĸ
     *
     * ע��
     *  * ���ﹹ���trie�������ȷ�������ĸ�ģ�����ĸ�ı���Ϊa �� ����ĸ״̬λ����a, base[a] == 0 ��ʾ����ĸ����
     *    Ҳ����������-1��ʾԭʼͷ״̬��base[-1] = 0 , Ȼ��״̬ת�� base[0] + a = a,�����Ļ�����Ҫcheck[a] �ж��Ƿ� = -1 һ��˼·
     *    �����������ĸ�ֱ����ˣ���������һ��ͳһ״̬��ʼ
     *
     * *�ӵڶ����ֿ�ʼ
     * 1.�Ƿ�״̬��trie��  check[now] = pre���� check[now]�洢��һ��״̬��λ��index��pre,
     * 2.���״̬��trie�� ���Ƿ�ɴ�  base[now] < 0 ��ɴ� ���� base[now]����һ��ת�ƻ���
     * 3.����ɴ���ô���������
     *   1. �ô�����û�д���                    base[now] = -now
     *   2. �ô��Ǵʶ������»������������ĳɴ�     base[now] != -now  -base[now] ����һ��ת�ƻ������ο� "����͢���Ǹ�ͼ
     *   ��trie��״̬������ɴ�һ���к�̵�״̬
     *
     *  TODO searchExact
     *  ���Ĳ�ѯ��ͬ ��ǿ����������key�������ֿ����һ���ֵ�״̬������м������ⷵ��false
     */
    template<typename T>
    bool search(const T& key, ValueType& result) const
    {
        if (key.empty())
            return false;
        int len = key.size(); //------������һ����
        int p = (ElemType) key[0]; //-----p��һ���ֵ�״̬λ�ã�b�ڶ����ֵ�״̬base
        if (!m_viBase[p] || (m_viBase[p] == -p && len > 1)) //-------����ĸ�����ֵ���,��������ĸ��������˶���ѯ�ʸ���������ǰ���ڳɴʵ���û�к���״̬��
            return false;

        //����ĸ����Ч״̬���Ҳ������մʣ����������մʵ��ǲ�ѯ�ʳ���ҲΪ1

        int b = abs(m_viBase[p]);
        int pre; //��¼��һ��״̬λ��
        //--------�����ӵڶ����ֿ�ʼ��״̬
        size_t i = 1;
        for (; i < len; i++)
        {
            pre = p;
            p = b + (ElemType) key[i]; //-------p��ǰ��״̬λ��
            if (pre == m_viCheck[p]) //-------��ǰ��״̬���ֵ���,check[p]�洢����һ��״̬λ��pre
            {
                if (m_viBase[p] != -p) //-----��״̬�����յ�״̬���и����ɴ�
                    b = abs(m_viBase[p]); //---ת�Ƶ���һ����״̬base,ע�����ѭ��abs
                else //---�ɴʶ���û�к���״̬����
                {
                    i++;
                    break;
                }
            }
            else
            {
                return false; //�м��Ҳ������״̬�����
            }
        }
        if (i < len) //��ǰ���ڳɴʵ���û�к���״̬������
            return false;
        //---------��������ֶ��������ˣ�������trie�е�״̬���ж����һ���ֵ�״̬�Ƿ��ǳɴ�״̬
        if (m_viBase[p] < 0) //--������״̬�ɴ�
        {
            result = m_viWeight[p];
            return true;
        }
        return false;
    }

    /*
     * ֻ��ѯ�Ƿ��� TODO �����ظ�
     */
    template<typename T>
    bool search(const T& key) const
    {
        if (key.empty())
            return false;
        int len = key.size(); //------������һ����
        int p = (ElemType) key[0]; //-----p��һ���ֵ�״̬λ�ã�b�ڶ����ֵ�״̬base
        if (!m_viBase[p] || (m_viBase[p] == -p && len > 1)) //-------����ĸ�����ֵ���,��������ĸ��������˶���ѯ�ʸ���
            return false;
        int b = abs(m_viBase[p]);
        int pre; //��¼��һ��״̬λ��
        //--------�����ӵڶ����ֿ�ʼ��״̬
        size_t i = 1;
        for (; i < len; i++)
        {
            pre = p;
            p = b + (ElemType) key[i]; //-------p��ǰ��״̬λ��
            if (pre == m_viCheck[p]) //-------��ǰ��״̬���ֵ���,check[p]�洢����һ��״̬λ��pre
            {
                if (m_viBase[p] != -p) //-----��״̬�����յ�״̬���и����ɴ�
                    b = abs(m_viBase[p]); //---ת�Ƶ���һ����״̬base,ע�����ѭ��abs
                else //---�ɴʶ���û�к���״̬����
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
        if (i < len) //��ǰ���ڳɴʵ���û�к���״̬������
            return false;
        //---------��������ֶ��������ˣ�������trie�е�״̬���ж����һ���ֵ�״̬�Ƿ��ǳɴ�״̬
        if (m_viBase[p] < 0) //--������״̬�ɴ�
            return true;
        return false;
    }

    template<typename T>
    bool search_(const T& key, int len) const
    {//ע���е��ⲿ�������search��Ҫfix
        if (len == 0)
            return false;
        int p = (ElemType) key[0]; //-----p��һ���ֵ�״̬λ�ã�b�ڶ����ֵ�״̬base
        if (!m_viBase[p] || (m_viBase[p] == -p && len > 1)) //-------����ĸ�����ֵ���,��������ĸ��������˶���ѯ�ʸ���
            return false;
        int b = abs(m_viBase[p]);
        int pre; //��¼��һ��״̬λ��
        //--------�����ӵڶ����ֿ�ʼ��״̬
        size_t i = 1;
        for (; i < len; i++)
        {
            pre = p;
            p = b + (ElemType) key[i]; //-------p��ǰ��״̬λ��
            if (pre == m_viCheck[p]) //-------��ǰ��״̬���ֵ���,check[p]�洢����һ��״̬λ��pre
            {
                if (m_viBase[p] != -p) //-----��״̬�����յ�״̬���и����ɴ�
                    b = abs(m_viBase[p]); //---ת�Ƶ���һ����״̬base,ע�����ѭ��abs
                else //---�ɴʶ���û�к���״̬����
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
        if (i < len) //��ǰ���ڳɴʵ���û�к���״̬������
            return false;
        //---------��������ֶ��������ˣ�������trie�е�״̬���ж����һ���ֵ�״̬�Ƿ��ǳɴ�״̬
        if (m_viBase[p] < 0) //--������״̬�ɴ�
            return true;
        return false;
    }

    /**
     * ���Ҵ����õ���һ��ƥ���<λ�ã�value>
     * û���κ�ƥ�䷵��false
     */
    template<typename T>
    bool searchFirst(const T& key, ResultType& result) const
    {
        if (key.empty())
            return false;
        int len = key.size(); //------������һ����
        int p = (ElemType) key[0];

        if (!m_viBase[p]) //-------����ĸ�����ֵ���
            return false;

        if (m_viBase[p] < 0) //���ֳɴ�,�򷵻�
        {
            result.length = 1;
            result.value = m_viWeight[p];
            return true;
        }

        int b = abs(m_viBase[p]);
        int pre; //��¼��һ��״̬λ��
        //--------�����ӵڶ����ֿ�ʼ��״̬
        for (size_t i = 1; i < len; i++)
        {
            pre = p;
            p = b + (ElemType) key[i]; //-------p��ǰ��״̬λ��
            if (pre == m_viCheck[p]) //-------��ǰ��״̬���ֵ���,check[p]�洢����һ��״̬λ��pre
            {
                if (m_viBase[p] < 0) //��״̬�ɴ�
                {
                    result.length = i + 1;
                    result.value = m_viWeight[p];
                    return true;
                }
                else
                    b = m_viBase[p]; //--����һ״̬��base
            }
            else //����һ״̬ ��Ϊǰ��ֻҪ�гɴʾ��Ѿ��˳����Ե�����Ч״̬��ζ��֮ǰû���ҵ��κδ�
            {
                return false;
            }
        }

        //---------��������ֶ��������ˣ�������trie�е�״̬,����û���ҵ��ɴ�
        return false;
    }

    template<typename T>
    bool searchFirst(const T& key, int len, ResultType& result) const
    {
        if (!len)
            return false;
        int p = (ElemType) key[0];

        if (!m_viBase[p]) //-------����ĸ�����ֵ���
            return false;

        if (m_viBase[p] < 0) //���ֳɴ�,�򷵻�
        {
            result.length = 1;
            result.value = m_viWeight[p];
            return true;
        }

        int b = abs(m_viBase[p]);
        int pre; //��¼��һ��״̬λ��
        //--------�����ӵڶ����ֿ�ʼ��״̬
        for (size_t i = 1; i < len; i++)
        {
            pre = p;
            p = b + (ElemType) key[i]; //-------p��ǰ��״̬λ��
            if (pre == m_viCheck[p]) //-------��ǰ��״̬���ֵ���,check[p]�洢����һ��״̬λ��pre
            {
                if (m_viBase[p] < 0) //��״̬�ɴ�
                {
                    result.length = i + 1;
                    result.value = m_viWeight[p];
                    return true;
                }
                else
                    b = m_viBase[p]; //--����һ״̬��base
            }
            else //����һ״̬ ��Ϊǰ��ֻҪ�гɴʾ��Ѿ��˳����Ե�����Ч״̬��ζ��֮ǰû���ҵ��κδ�
            {
                return false;
            }
        }

        //---------��������ֶ��������ˣ�������trie�е�״̬,����û���ҵ��ɴ�
        return false;
    }

    /**
     * ����������̵ķǵ��ִ�
     * ����Ҳ������Ƿ��ص��֣�
     * �������Ҳ�Ҳ�������false
     */
    template<typename T>
    bool searchFirstNonSingle(const T& key, ResultType& result) const
    {
        if (key.empty())
            return false;
        int len = key.size(); //------������һ����
        int p = (ElemType) key[0];

        if (!m_viBase[p]) //-------����ĸ�����ֵ���
            return false;

        bool has_first = false;
        if (m_viBase[p] < 0) //���ֳɴ�,�򷵻�
        {
            result.length = 1;
            result.value = m_viWeight[p];
            has_first = true;
        }

        int b = abs(m_viBase[p]);
        int pre; //��¼��һ��״̬λ��
        //--------�����ӵڶ����ֿ�ʼ��״̬
        for (size_t i = 1; i < len; i++)
        {
            pre = p;
            p = b + (ElemType) key[i]; //-------p��ǰ��״̬λ��
            if (pre == m_viCheck[p]) //-------��ǰ��״̬���ֵ���,check[p]�洢����һ��״̬λ��pre
            {
                if (m_viBase[p] < 0) //��״̬�ɴ�
                {
                    result.length = i + 1;
                    result.value = m_viWeight[p];
                    return true;
                }
                else
                    b = m_viBase[p]; //--����һ״̬��base
            }
            else //����һ״̬ ��Ϊǰ��ֻҪ�гɴʾ��Ѿ��˳����Ե�����Ч״̬��ζ��֮ǰû���ҵ��κδ�
            {
                return has_first;
            }
        }

        //---------��������ֶ��������ˣ�������trie�е�״̬,����û���ҵ��ɴ�

        return has_first;
    }

    template<typename T>
    bool searchFirstNonSingle(const T& key, int len, ResultType& result) const
    {
        if (!len)
            return false;
        int p = (ElemType) key[0];

        if (!m_viBase[p]) //-------����ĸ�����ֵ���
            return false;

        bool has_first = false;
        if (m_viBase[p] < 0) //���ֳɴ�,�򷵻�
        {
            result.length = 1;
            result.value = m_viWeight[p];
            has_first = true;
        }

        int b = abs(m_viBase[p]);
        int pre; //��¼��һ��״̬λ��
        //--------�����ӵڶ����ֿ�ʼ��״̬
        for (size_t i = 1; i < len; i++)
        {
            pre = p;
            p = b + (ElemType) key[i]; //-------p��ǰ��״̬λ��
            if (pre == m_viCheck[p]) //-------��ǰ��״̬���ֵ���,check[p]�洢����һ��״̬λ��pre
            {
                if (m_viBase[p] < 0) //��״̬�ɴ�
                {
                    result.length = i + 1;
                    result.value = m_viWeight[p];
                    return true;
                }
                else
                    b = m_viBase[p]; //--����һ״̬��base
            }
            else //����һ״̬ ��Ϊǰ��ֻҪ�гɴʾ��Ѿ��˳����Ե�����Ч״̬��ζ��֮ǰû���ҵ��κδ�
            {
                return has_first;
            }
        }

        //---------��������ֶ��������ˣ�������trie�е�״̬,����û���ҵ��ɴ�

        return has_first;
    }

    /**
     * ����̳ɴʷ��س��ȣ����û�ҵ�����0
     */
    template<typename T>
    int matchFirst(const T& key, int len) const
    {
        if (!len)
            return 0;
        int p = (ElemType) key[0];

        if (!m_viBase[p]) //-------����ĸ�����ֵ���
            return 0;

        int has_first = 0;
        if (m_viBase[p] < 0) //���ֳɴ�,�򷵻�
        {
            return 1; //����ǵ���
        }

        int b = abs(m_viBase[p]);
        int pre; //��¼��һ��״̬λ��
        //--------�����ӵڶ����ֿ�ʼ��״̬
        for (size_t i = 1; i < len; i++)
        {
            pre = p;
            p = b + (ElemType) key[i]; //-------p��ǰ��״̬λ��
            if (pre == m_viCheck[p]) //-------��ǰ��״̬���ֵ���,check[p]�洢����һ��״̬λ��pre
            {
                if (m_viBase[p] < 0) //��״̬�ɴ�
                {
                    return i + 1;
                }
                else
                    b = m_viBase[p]; //--����һ״̬��base
            }
            else //����һ״̬ ��Ϊǰ��ֻҪ�гɴʾ��Ѿ��˳����Ե�����Ч״̬��ζ��֮ǰû���ҵ��κδ�
            {
                return 0;
            }
        }

        //---------��������ֶ��������ˣ�������trie�е�״̬,����û���ҵ��ɴ�
        return 0;
    }

    template<typename T>
    int matchFirstNonSingle(const T& key, int len) const
    {
        if (!len)
            return 0;
        int p = (ElemType) key[0];

        if (!m_viBase[p]) //-------����ĸ�����ֵ���
            return 0;

        int has_first = 0;
        if (m_viBase[p] < 0) //���ֳɴ�,�򷵻�
        {
            has_first = 1;
        }

        int b = abs(m_viBase[p]);
        int pre; //��¼��һ��״̬λ��
        //--------�����ӵڶ����ֿ�ʼ��״̬
        for (size_t i = 1; i < len; i++)
        {
            pre = p;
            p = b + (ElemType) key[i]; //-------p��ǰ��״̬λ��
            if (pre == m_viCheck[p]) //-------��ǰ��״̬���ֵ���,check[p]�洢����һ��״̬λ��pre
            {
                if (m_viBase[p] < 0) //��״̬�ɴ�
                {
                    return i + 1;
                }
                else
                    b = m_viBase[p]; //--����һ״̬��base
            }
            else //����һ״̬ ��Ϊǰ��ֻҪ�гɴʾ��Ѿ��˳����Ե�����Ч״̬��ζ��֮ǰû���ҵ��κδ�
            {
                return has_first;
            }
        }

        //---------��������ֶ��������ˣ�������trie�е�״̬,����û���ҵ��ɴ�

        return has_first;
    }

    /**
     * ���Ҵ����õ����ƥ���<λ�ã�value>
     * û���κ�ƥ�䷵��false
     *
     * ע���ֵ����� abc abcdef
     * �� abcdeƥ�䵽abc��һ��������ǲ��Ǵʵ�����ģ�����ƥ����abcde�󷵻ػ���abc,
     * ���������ҵ������
     */
    template<typename T>
    bool searchLongest(const T& key, int len, ResultType& result) const
    {
        result.length = 0; //���û��length = 0
        if (!len)
            return false;
        int p = (ElemType) key[0]; //-----p��һ���ֵ�״̬λ�ã�b�ڶ����ֵ�״̬base
        if (!m_viBase[p]) //-------����ĸ�����ֵ���
            return false;

        if (m_viBase[p] < 0) //���ֳɴ�
        {
            result.length = 1;
            result.value = m_viWeight[p];
            if (m_viBase[p] == -p || len == 1) //----��������
                return true;
        }

        //���ֲ�����ɴ�,����
        int b = abs(m_viBase[p]);
        int pre; //��¼��һ��״̬λ��
        //--------�����ӵڶ����ֿ�ʼ��״̬
        for (size_t i = 1; i < len; i++)
        {
            pre = p;
            p = b + (ElemType) key[i]; //-------p��ǰ��״̬λ��
            if (pre == m_viCheck[p]) //-------��ǰ��״̬���ֵ���,check[p]�洢����һ��״̬λ��pre
            {
                if (m_viBase[p] < 0) //��״̬�ɴ�
                {
                    result.length = i + 1;
                    result.value = m_viWeight[p];
                    if (m_viBase[p] == -p)
                        return true;
                }
                b = abs(m_viBase[p]); //--����һ״̬��base
            }
            else
                return (result.length); //������޸Ĺ����н��
        }
        return (result.length);
    }

    template<typename T>
    bool searchLongest(const T& key, int len, ResultType& result, int stop_value) const
    {
        result.length = 0; //���û��length = 0
        if (!len)
            return false;
        int p = (ElemType) key[0]; //-----p��һ���ֵ�״̬λ�ã�b�ڶ����ֵ�״̬base
        if (!m_viBase[p]) //-------����ĸ�����ֵ���
            return false;

        if (m_viBase[p] < 0) //���ֳɴ�
        {
            result.length = 1;
            result.value = m_viWeight[p];
            if (m_viBase[p] == -p || len == 1) //----��������
                return true;
        }

        //���ֲ�����ɴ�,����
        int b = abs(m_viBase[p]);
        int pre; //��¼��һ��״̬λ��
        //--------�����ӵڶ����ֿ�ʼ��״̬
        for (size_t i = 1; i < len; i++)
        {
            pre = p;
            p = b + (ElemType) key[i]; //-------p��ǰ��״̬λ��
            if (pre == m_viCheck[p]) //-------��ǰ��״̬���ֵ���,check[p]�洢����һ��״̬λ��pre
            {
                if (m_viBase[p] < 0) //��״̬�ɴ�
                {
                    if (m_viWeight[p] != stop_value) //�����������"��ѹ����"�����Ĵ���Ҫֱ�ӷ���ǰ��Ľ��
                    {
                        result.length = i + 1;
                        result.value = m_viWeight[p];
                    }
                    if (m_viBase[p] == -p)
                        return true;
                }
                b = abs(m_viBase[p]); //--����һ״̬��base
            }
            else
                return (result.length); //������޸Ĺ����н��
        }
        return (result.length);
    }

    template<typename T>
    bool searchLongest(const T& key, ResultType& result) const
    {
        result.length = 0; //���û��length = 0
        int len = key.size();
        if (!len)
            return false;
        int p = (ElemType) key[0]; //-----p��һ���ֵ�״̬λ�ã�b�ڶ����ֵ�״̬base
        if (!m_viBase[p]) //-------����ĸ�����ֵ���
            return false;

        if (m_viBase[p] < 0) //���ֳɴ�
        {
            result.length = 1;
            result.value = m_viWeight[p];
            if (m_viBase[p] == -p || len == 1) //----��������
                return true;
        }

        //���ֲ�����ɴ�,����
        int b = abs(m_viBase[p]);
        int pre; //��¼��һ��״̬λ��
        //--------�����ӵڶ����ֿ�ʼ��״̬
        for (size_t i = 1; i < len; i++)
        {
            pre = p;
            p = b + (ElemType) key[i]; //-------p��ǰ��״̬λ��
            if (pre == m_viCheck[p]) //-------��ǰ��״̬���ֵ���,check[p]�洢����һ��״̬λ��pre
            {
                if (m_viBase[p] < 0) //��״̬�ɴ�
                {
                    result.length = i + 1;
                    result.value = m_viWeight[p];
                    if (m_viBase[p] == -p)
                        return true;
                }
                b = abs(m_viBase[p]); //--����һ״̬��base
            }
            else
                return (result.length); //������޸Ĺ����н��
        }
        return (result.length);
    }

    template<typename T>
    int matchLongest(const T& key, int len) const
    {
        if (!len)
            return 0;
        int p = (ElemType) key[0]; //-----p��һ���ֵ�״̬λ�ã�b�ڶ����ֵ�״̬base
        if (!m_viBase[p]) //-------����ĸ�����ֵ���
            return 0;

        int length = 0;
        if (m_viBase[p] < 0) //���ֳɴ�
        {
            length = 1;
            if (m_viBase[p] == -p || len == 1) //----��������
                return length;
        }

        //���ֲ�����ɴ�,����
        int b = abs(m_viBase[p]);
        int pre; //��¼��һ��״̬λ��
        //--------�����ӵڶ����ֿ�ʼ��״̬
        for (size_t i = 1; i < len; i++)
        {
            pre = p;
            p = b + (ElemType) key[i]; //-------p��ǰ��״̬λ��
            if (pre == m_viCheck[p]) //-------��ǰ��״̬���ֵ���,check[p]�洢����һ��״̬λ��pre
            {
                if (m_viBase[p] < 0) //��״̬�ɴ�
                {
                    length = i + 1;
                    if (m_viBase[p] == -p)
                        return length;
                }
                b = abs(m_viBase[p]); //--����һ״̬��base
            }
            else
                return length; //������޸Ĺ����н��
        }
        return length;
    }

    /**
     * ���Ҵ����õ����п��ܵ�ƥ���<λ�ã�value>
     * û���κ�ƥ�䷵��false
     */
    template<typename T>
    bool searchAll(const T& key, vector<ResultType>& result_vec) const
    {
        result_vec.clear();
        if (key.empty())
            return false;
        int len = key.size(); //------������һ����
        int p = (ElemType) key[0]; //-----p��һ���ֵ�״̬λ�ã�b�ڶ����ֵ�״̬base
        if (!m_viBase[p]) //-------����ĸ�����ֵ���
            return false;
        ResultType result;
        if (m_viBase[p] < 0) //���ֳɴ�
        {
            result.length = 1;
            result.value = m_viWeight[p];
            result_vec.push_back(result);
            if (m_viBase[p] == -p || len == 1) //----��������
                return true;
        }
        int b = abs(m_viBase[p]);
        int pre; //��¼��һ��״̬λ��
        //--------�����ӵڶ����ֿ�ʼ��״̬
        for (size_t i = 1; i < len; i++)
        {
            pre = p;
            p = b + (ElemType) key[i]; //-------p��ǰ��״̬λ��
            if (pre == m_viCheck[p]) //-------��ǰ��״̬���ֵ���,check[p]�洢����һ��״̬λ��pre
            {
                if (m_viBase[p] < 0) //��״̬�ɴ�
                {
                    result.length = i + 1;
                    result.value = m_viWeight[p];
                    result_vec.push_back(result);
                    if (m_viBase[p] == -p)
                        return true;
                }
                b = abs(m_viBase[p]); //--����һ״̬��base
            }
            else
                return !result_vec.empty();
        }
        return !result_vec.empty(); //������������abcde��Ȼû�дﵽ�ֵ�������״̬
    }

    template<typename T>
    bool searchAll(const T& key, int len, vector<ResultType>& result_vec) const
    {
        if (!len)
            return false;
        result_vec.clear();
        result_vec.reserve(len);
        int p = (ElemType) key[0]; //-----p��һ���ֵ�״̬λ�ã�b�ڶ����ֵ�״̬base
        if (!m_viBase[p]) //-------����ĸ�����ֵ���
            return false;
        ResultType result;
        if (m_viBase[p] < 0) //���ֳɴ�
        {
            result.length = 1;
            result.value = m_viWeight[p];
            result_vec.push_back(result);
            if (m_viBase[p] == -p || len == 1) //----��������
                return true;
        }
        int b = abs(m_viBase[p]);
        int pre; //��¼��һ��״̬λ��
        //--------�����ӵڶ����ֿ�ʼ��״̬
        for (size_t i = 1; i < len; i++)
        {
            pre = p;
            p = b + (ElemType) key[i]; //-------p��ǰ��״̬λ��
            if (pre == m_viCheck[p]) //-------��ǰ��״̬���ֵ���,check[p]�洢����һ��״̬λ��pre
            {
                if (m_viBase[p] < 0) //��״̬�ɴ�
                {
                    result.length = i + 1;
                    result.value = m_viWeight[p];
                    result_vec.push_back(result);
                    if (m_viBase[p] == -p)
                        return true;
                }
                b = abs(m_viBase[p]); //--����һ״̬��base
            }
            else
                return !result_vec.empty();
        }
        return !result_vec.empty(); //������������abcde��Ȼû�дﵽ�ֵ�������״̬
    }

    template<typename T>
    int searchAll(const T& key, int len, ElemType* len_vec, ValueType* val_vec, int max_len = 8) const
    {
        if (!len)
            return 0;
        int result_num = 0;
        int p = (ElemType) key[0]; //-----p��һ���ֵ�״̬λ�ã�b�ڶ����ֵ�״̬base
        if (!m_viBase[p]) //-------����ĸ�����ֵ���
            return 0;
        if (m_viBase[p] < 0) //���ֳɴ�
        {
            len_vec[result_num] = 1;
            val_vec[result_num++] = m_viWeight[p];
            if (m_viBase[p] == -p || len == 1) //----��������
                return result_num;
        }
        int b = abs(m_viBase[p]);
        int pre; //��¼��һ��״̬λ��
        //--------�����ӵڶ����ֿ�ʼ��״̬
        for (size_t i = 1; i < len && result_num < max_len; i++)
        {
            pre = p;
            p = b + (ElemType) key[i]; //-------p��ǰ��״̬λ��
            if (pre == m_viCheck[p]) //-------��ǰ��״̬���ֵ���,check[p]�洢����һ��״̬λ��pre
            {
                if (m_viBase[p] < 0) //��״̬�ɴ�
                {
                    len_vec[result_num] = i + 1;
                    val_vec[result_num++] = m_viWeight[p];
                    if (m_viBase[p] == -p)
                        return result_num;
                }
                b = abs(m_viBase[p]); //--����һ״̬��base
            }
            else
                return result_num;
        }
        return result_num; //������������abcde��Ȼû�дﵽ�ֵ�������״̬
    }

    template<typename T>
    bool searchAll2(const T& key, int len, vector<ResultType>& result_vec) const
    { //����¼���ֳɴʵ����
        if (!len)
            return false;
        result_vec.clear();
        result_vec.reserve(len);
        int p = (ElemType) key[0]; //-----p��һ���ֵ�״̬λ�ã�b�ڶ����ֵ�״̬base
        if (!m_viBase[p]) //-------����ĸ�����ֵ���
            return false;
        ResultType result;
        int b = abs(m_viBase[p]);
        int pre; //��¼��һ��״̬λ��
        //--------�����ӵڶ����ֿ�ʼ��״̬
        for (size_t i = 1; i < len; i++)
        {
            pre = p;
            p = b + (ElemType) key[i]; //-------p��ǰ��״̬λ��
            if (pre == m_viCheck[p]) //-------��ǰ��״̬���ֵ���,check[p]�洢����һ��״̬λ��pre
            {
                if (m_viBase[p] < 0) //��״̬�ɴ�
                {
                    result.length = i + 1;
                    result.value = m_viWeight[p];
                    result_vec.push_back(result);
                    if (m_viBase[p] == -p)
                        return true;
                }
                b = abs(m_viBase[p]); //--����һ״̬��base
            }
            else
                return !result_vec.empty();
        }
        return !result_vec.empty(); //������������abcde��Ȼû�дﵽ�ֵ�������״̬
    }

    /*
     * ����¼���ֳɴʵ����
     * 12.07 �ĳɴ洢length
     * �����������Ǵ���������Ŀ��max_len һ����������ҵ�8���ʾ�ֹͣ
     */
    template<typename T>
    int searchAll2(const T& key, int len, ElemType* result_vec, int max_len = 8) const
    {
        if (!len)
            return 0;
        int result_num = 0;
        int p = (ElemType) key[0]; //-----p��һ���ֵ�״̬λ�ã�b�ڶ����ֵ�״̬base
        int b = abs(m_viBase[p]);
        int pre; //��¼��һ��״̬λ��
        //--------�����ӵڶ����ֿ�ʼ��״̬
        for (size_t i = 1; i < len && result_num < max_len; i++)
        {
            pre = p;
            p = b + (ElemType) key[i]; //-------p��ǰ��״̬λ��
            if (pre == m_viCheck[p]) //-------��ǰ��״̬���ֵ���,check[p]�洢����һ��״̬λ��pre
            {
                if (m_viBase[p] < 0) //��״̬�ɴ�
                {
                    result_vec[result_num++] = i + 1;
                    if (m_viBase[p] == -p)
                        return result_num;
                }
                b = abs(m_viBase[p]); //--����һ״̬��base
            }
            else
                return result_num;
        }
        return result_num; //������������abcde��Ȼû�дﵽ�ֵ�������״̬
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
