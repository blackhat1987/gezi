#ifndef WINNER_TREE_H_
#define WINNER_TREE_H_

/**
 * TODO 打印命令要改用log
 */

#include <sys/stat.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>  
#include <utility>
#include <sys/types.h>   
#include <sys/stat.h>
#include <malloc.h>
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <time.h>
#include <sys/time.h>
#include <cstring>
#include <functional>
#include <vector>

#include "debug_help.h"
#include "ul_log_help.h"

using std::vector;  //TODO namespace
typedef long long int64;
template <class NODE, class CMP = std::less<NODE> >
class WinnderTreeT
{
public:
    typedef unsigned long long uint64;
    //默认空指针最大
    WinnderTreeT(CMP CMP_ELEMENT = CMP())
    {
        M_CMP_ELEMENT = CMP_ELEMENT;
    }

    //多路归并是否结束
    inline bool is_stopped()
    {
        return m_vecRunTracks.size() == m_nStoppedRun;
    }

    //构造一颗完全二叉树，并初始化第一排节点。
    //************************************
    // Method:    MakeTree
    // FullName:  WinnderTreeT<NODE>::MakeTree
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: vector<NODE*>&vecNodePtr    各列首地址数组
    // Parameter: vector<NODE*>&vecNodeEndPtr 各列结束地址数组。
    //************************************
    bool create_tree(vector<NODE*>&vecNodePtr, vector<NODE*>&vecNodeEndPtr, vector<NODE> *pVecDest = NULL)
    {
        m_nStoppedRun = 0;
        if (vecNodePtr.size() < 1)
        {
            return false;
        }
        m_vecRunTracks = vecNodePtr;
        m_vecRunEnds = vecNodeEndPtr;
        m_vecRunBeginPtr = vecNodePtr;
        m_pVecDest = pVecDest;

        m_vecStopMark.resize(vecNodePtr.size(), 0);

        MakeTree();
        return true;
    }
    void MakeTree()
    {
        for (int i = 0; i < m_vecRunTracks.size(); ++i)
        {
            if ((m_vecRunTracks[i] == NULL || m_vecRunTracks[i] == m_vecRunEnds[i]) && m_vecStopMark[i] == 0)
            {
                m_vecStopMark[i] = 1;
                ++m_nStoppedRun;
            }
        }

        int nLeftRun = m_vecRunTracks.size() - m_nStoppedRun;
        if (nLeftRun == 0)
        {
            return;
        }
        //任意节点有两颗子树，或者是叶子节点的 完全二叉树

        int i = 1;
        m_nLevel = 0;
        while (nLeftRun > i)
        {
            ++m_nLevel;
            i <<= 1;
        }

        ++m_nLevel; //完全二叉树的层数
        m_vecTree.resize(2 * nLeftRun - 1); //最后一层不满时 树节点数为 2*run-1
        m_nLastLevelBegin = m_vecTree.size() - nLeftRun;


        //填写所有叶子节点，即加入所有RUN的第一个元素
        typename vector<pair<NODE *, int> >::iterator itTree;
        itTree = m_vecTree.begin() + m_nLastLevelBegin;
        int nCnt = -1;
        m_vecRunInTreePos.clear();
        for (int i = 0; i < m_vecRunTracks.size(); ++i)
        {
            if ((m_vecRunTracks[i] != NULL && m_vecRunTracks[i] != m_vecRunEnds[i]))
            {
                (*itTree).first = m_vecRunTracks[i];
                (*itTree).second = i;
                ++itTree;
                ++nCnt;
            }
            m_vecRunInTreePos.push_back(nCnt + m_nLastLevelBegin);
        }

        if (nLeftRun <= 1)
        {
            return;
        }

        //填写其他节点
        int nR = m_vecTree.size() - 1;
        int nL = nR - 1;
        while (nL > 0)
        {
            m_vecTree[nL >> 1] = CMP_NODE(m_vecTree[nL], m_vecTree[nR]) ? m_vecTree[nL] : m_vecTree[nR]; //左节点小
            nR -= 2;
            nL -= 2;
        }
    }

    //内存中的K路求并集输出到m_pVecDest中
    inline void k_merge()
    {
        while (m_vecRunTracks.size() != m_nStoppedRun)
        {
            m_pVecDest->push_back(*(m_vecTree[0].first));
            nRun = m_vecTree[0].second;
            nTrack = m_vecRunInTreePos[m_vecTree[0].second]; //跟踪计算结点

            //插入一个数到最底层
            if (++(m_vecRunTracks[nRun]) == m_vecRunEnds[nRun])//一列中止了
            {

                MakeTree(); //一列中止重新构造树
            }
            else
            {
                m_vecTree[nTrack].first = m_vecRunTracks[nRun];
                m_vecTree[nTrack].second = nRun;
                //向根方向进行比较
                while (nTrack != 0)
                {
                    if (nTrack % 2 == 0)//是偶数为右子树
                    {
                        m_vecTree[(nTrack >> 1) - 1] = CMP_NODE(m_vecTree[nTrack], m_vecTree[nTrack - 1]) ? m_vecTree[nTrack] : m_vecTree[nTrack - 1];
                        nTrack >>= 1;
                        nTrack -= 1;
                    }
                    else
                    {
                        m_vecTree[nTrack >> 1] = CMP_NODE(m_vecTree[nTrack], m_vecTree[nTrack + 1]) ? m_vecTree[nTrack] : m_vecTree[nTrack + 1];
                        //nTrack-=1;
                        nTrack >>= 1;
                    }
                }
            }
        }
    }

    //返回一个最小的节点
    //NODE*表示该节点的地址，int 表示从哪一个归并列返回的
    bool k_merge_file(vector<FILE*> &vecTempFileHandle, FILE * fpWriteFileHandle, int nReadCnt, NODE*pOutPtr)
    {
        int nOutCnt = 0;

        while (m_vecRunTracks.size() != m_nStoppedRun)//所以文件没有归并完全
        {
            pOutPtr[nOutCnt++] = *(m_vecTree[0].first);

            if (nOutCnt == nReadCnt)//写缓冲区满
            {
                uint64 nWriteCnt;
                nWriteCnt = fwrite(pOutPtr, sizeof (NODE), nOutCnt, fpWriteFileHandle);
                if (nWriteCnt == -1 || nWriteCnt != nOutCnt)
                {
                    LOG_WARNING("WriteFile error");
                    return false;
                }
                nOutCnt = 0;
            }

            nRun = m_vecTree[0].second;
            nTrack = m_vecRunInTreePos[m_vecTree[0].second]; //跟踪计算结点

            //插入一个数到最底层
            ++(m_vecRunTracks[nRun]);
            if (m_vecRunTracks[nRun] == m_vecRunEnds[nRun])//一列中止了
            {
                long long nRealReadCnt = 0;
                nRealReadCnt = fread(m_vecRunBeginPtr[nRun], sizeof (NODE), nReadCnt, vecTempFileHandle[nRun]);
                if (nRealReadCnt == -1)
                {
                    LOG_WARNING("ReadFile error");
                    return false;
                }

                if (nRealReadCnt == 0)//一列文件完毕重新构造树
                {
                    MakeTree(); //一列中止重新构造树
                    continue;
                }
                else
                {
                    m_vecRunTracks[nRun] = m_vecRunBeginPtr[nRun];
                    m_vecRunEnds[nRun] = m_vecRunTracks[nRun] + nRealReadCnt;
                }
            }

            m_vecTree[nTrack].first = m_vecRunTracks[nRun];
            m_vecTree[nTrack].second = nRun;

            //向根方向进行比较
            while (nTrack != 0)
            {
                if (nTrack % 2 == 0)//是偶数为右子树
                {
                    m_vecTree[(nTrack >> 1) - 1] = CMP_NODE(m_vecTree[nTrack], m_vecTree[nTrack - 1]) ? m_vecTree[nTrack] : m_vecTree[nTrack - 1];
                    nTrack >>= 1;
                    nTrack -= 1;
                }
                else
                {
                    m_vecTree[nTrack >> 1] = CMP_NODE(m_vecTree[nTrack], m_vecTree[nTrack + 1]) ? m_vecTree[nTrack] : m_vecTree[nTrack + 1];
                    nTrack >>= 1;
                }
            }
        }

        if (nOutCnt)//缓冲区还有没写入文件的
        {
            uint64 nWriteCnt;
            nWriteCnt = fwrite(pOutPtr, sizeof (NODE), nOutCnt, fpWriteFileHandle);
            if (nWriteCnt == -1 || nWriteCnt != nOutCnt)
            {
                LOG_WARNING("WriteFile error");
                return false;
            }
        }
        return true;
    }


public:
    ~WinnderTreeT(void)
    {
    };
private:
    //modified remove == use < >
    inline bool CMP_NODE(pair<NODE*, int> &nodeL, pair<NODE*, int>& nodeR)
    {
        return M_CMP_ELEMENT(*(nodeL.first), *(nodeR.first)) ||
                //                *(nodeL.first)==*(nodeR.first)&&nodeL.second<nodeR.second;
                (!M_CMP_ELEMENT(*(nodeR.first), *(nodeL.first)) && nodeL.second < nodeR.second); //chg modify
    }
private:
    vector<pair<NODE*, int> > m_vecTree; //完全二叉树结构
    vector<NODE*> m_vecRunBeginPtr; //保存每一列起始地址
    vector<NODE*> m_vecRunTracks; //当前跟踪到的各个Node
    vector<NODE*> m_vecRunEnds; //Run的中止指针
    vector<int> m_vecStopMark; //每个Rund的中止标准
    vector<int> m_vecRunInTreePos; //每个Run号对应的TREE中的位置。

    vector<NODE> *m_pVecDest; //存放归并结果的地方；

    //	NODE *m_pMaxNodePtr//;
    int m_nLevel; //层数
    int m_nLastLevelBegin; //最后一层节点起始号

    int m_nStoppedRun; //归并完停止的列数

private:
    //临时计算变量，速度起见
    //pair<NODE*,int> resPair;
    int nRun;
    int nTrack; //跟踪计算结点

    CMP M_CMP_ELEMENT;
};

//文件归并排序
template <class NODE, class CMP>
int k_merge_file(const char *pchFileIn, const char *pchFileOut, CMP CMP_NODE, int64 nFreeMemSize)
{
    typedef unsigned long long uint64;
    LOG_TRACE("\n---------------k_merge_file---------------\n");
    //打开文件
    FILE *fpSrc, *fpDes;
    if ((fpSrc = fopen(pchFileIn, "rb")) == NULL)
    {
        LOG_WARNING("Could not open file");
        return -1;
    }
    if ((fpDes = fopen(pchFileOut, "wb")) == NULL)
    {
        LOG_WARNING("Could not create file.\n");
        return -1;
    }

    //获得大小
    struct stat64 stllFileSize; //FileSize
    if (stat64(pchFileIn, &stllFileSize) < 0)
    {
        LOG_WARNING("Execute GetFileSize  fail!.\n");
        return -1;
    }

    uint64 nFileSize = stllFileSize.st_size;

    if (nFileSize % sizeof (NODE) != 0 || !nFileSize)//文件大小应该是结构体的整数倍
    {
        LOG_FATAL("File size empty or not fileSize % sizeof (NODE) != 0 return -1");
        return -1;
    }

    uint64 nTotalEleCnt; //整个文件的元素个数
    int64 nEachColCnt; //每个归并列(排序缓存)元素个数
    int64 nColCnt; //列个数
    uint64 nReadCnt, nWriteCnt; //实际读取个数

    nTotalEleCnt = nFileSize / sizeof (NODE);
    nEachColCnt = nFreeMemSize / sizeof (NODE);
    Pval(sizeof(NODE));
    Pval(nFreeMemSize);
    LOG_INFO("nEachColCnt %d\n", nEachColCnt);
    if (nTotalEleCnt % nEachColCnt == 0)
    {
        nColCnt = nTotalEleCnt / nEachColCnt;
    }
    else
    {
        nColCnt = nTotalEleCnt / nEachColCnt + 1;
    }

    

    int i;
    if (nColCnt == 1)//内存能放下该文件
    {
        LOG_INFO("Sort all in the mem");
        vector<NODE> vecBuf; //向量缓冲
        vecBuf.resize(nEachColCnt);

        //readfile
        nReadCnt = fread(&vecBuf[0], sizeof (NODE), nTotalEleCnt, fpSrc);
        if (nReadCnt == -1 || nReadCnt != nTotalEleCnt)
        {
            LOG_WARNING("ReadFile error.\n");
            return -1;
        }
        vecBuf.erase(vecBuf.begin() + nReadCnt, vecBuf.end()); //删除Buffer中多余的空间
        sort(vecBuf.begin(), vecBuf.end(), CMP_NODE); //sort

        //writefile
        nWriteCnt = fwrite(&vecBuf[0], sizeof (NODE), nTotalEleCnt, fpDes);
        if (nWriteCnt == -1 || nWriteCnt != nTotalEleCnt)
        {
            LOG_WARNING("WriteFile error.\n");
            return -1;
        }
    }
    else//采用外排序法
    {
        LOG_INFO("in mem sort begin");
        //0.创建各个分段排序文件
        vector<NODE> vecBuf; //向量缓冲
        vecBuf.resize(nEachColCnt);

        vector<string> vecTempFileName; //文件名
        vecTempFileName.resize(nColCnt, "0");

        vector<FILE*> vecTempFileHandle; //文件句柄
        vecTempFileHandle.resize(nColCnt);

        long long nWriteCnt;
        char chBuf[1024];

        cout << "use " << nColCnt << "-merge" << endl; //临时文件个数
        cout << "every group have element: " << nEachColCnt << endl; //每个临时文件的大小

        FILE *fpBuf;
        for (i = 0; i < nColCnt; ++i)
        {
            sprintf(chBuf, "%d", i);
            
            vecTempFileName[i] = chBuf; //产生文件名字

            if ((fpBuf = fopen(vecTempFileName[i].c_str(), "wb")) == NULL)
            {
                LOG_WARNING("Could not create file handle object.\n");
                return -1;
            }
            vecTempFileHandle[i] = fpBuf;
        }

        //1读取缓冲区 写临时分段文件
        for (i = 0; i < nColCnt; ++i)
        {
            //readfile
            nReadCnt = fread(&vecBuf[0], sizeof (NODE), nEachColCnt, fpSrc);
            if (nReadCnt == -1 || (i != nColCnt - 1 && nReadCnt != nEachColCnt))
            {
                LOG_WARNING("ReadFile error.\n");
                return -1;
            }

            if (i == nColCnt - 1)//最后一列可能读取的比较前面的列少
            {
                vecBuf.erase(vecBuf.begin() + nReadCnt, vecBuf.end());
            }

            sort(vecBuf.begin(), vecBuf.end(), CMP_NODE);

            nWriteCnt = fwrite(&vecBuf[0], sizeof (NODE), nReadCnt, vecTempFileHandle[i]);
            if (nWriteCnt == -1 || nWriteCnt != nReadCnt)
            {
                LOG_WARNING("WriteFile error\n");
                return -1;
            }
            fclose(vecTempFileHandle[i]);
        }

        LOG_TRACE("out of mem merge begin");
        //准备归并
        int nEachMergeCnt = nEachColCnt / (nColCnt + 1); //归并所用的每个缓冲区元素个数
        vecBuf.resize(nEachColCnt);

        NODE* outPtrBegin; //输出缓冲区起始位置

        vector<NODE*> vecNodePtr;
        vector<NODE*> vecNodeEndPtr;
        vecNodePtr.resize(nColCnt);
        vecNodeEndPtr.resize(nColCnt);

        //打开每个临时文件，存贮句柄
        vecTempFileHandle.resize(nColCnt);
        for (i = 0; i < nColCnt; ++i)
        {
            if ((fpBuf = fopen(vecTempFileName[i].c_str(), "rb")) == NULL)
            {
                LOG_WARNING("Could not open file handle object .\n");
                return -1;
            }
            vecTempFileHandle[i] = fpBuf;
        }

        //遍历归并
        for (i = 0; i < nColCnt; ++i)
        {
            vecNodePtr[i] = &vecBuf[0] + i*nEachMergeCnt;
            fseek(vecTempFileHandle[i], 0, 0);
            nReadCnt = fread(vecNodePtr[i], sizeof (NODE), nEachMergeCnt, vecTempFileHandle[i]);
            if (nReadCnt == -1)
            {
                LOG_WARNING("ReadFile error");
                return -1;
            }
            vecNodeEndPtr[i] = vecNodePtr[i] + nReadCnt;
        }
        outPtrBegin = vecNodeEndPtr[nColCnt - 1];

        WinnderTreeT<NODE, CMP> winnerTree(CMP_NODE);
        winnerTree.create_tree(vecNodePtr, vecNodeEndPtr);
        winnerTree.k_merge_file(vecTempFileHandle, fpDes, nEachMergeCnt, outPtrBegin);

        for (i = 0; i < nColCnt; ++i)
        {
            fclose(vecTempFileHandle[i]);
            remove(vecTempFileName[i].c_str());
        }
    }

    fclose(fpSrc);
    fclose(fpDes);

    return 0;
}
template <class NODE>
int k_merge_file(const char *pchFileIn, const char *pchFileOut, int64 nFreeMemSize = 1024 * 1024 * 1024)
{
    return k_merge_file<NODE, std::less<NODE> >(pchFileIn, pchFileOut, std::less<NODE > (), nFreeMemSize);
}
#endif

