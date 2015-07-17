#ifndef WINNER_TREE_H_
#define WINNER_TREE_H_

/**
 * TODO ��ӡ����Ҫ����log
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
    //Ĭ�Ͽ�ָ�����
    WinnderTreeT(CMP CMP_ELEMENT = CMP())
    {
        M_CMP_ELEMENT = CMP_ELEMENT;
    }

    //��·�鲢�Ƿ����
    inline bool is_stopped()
    {
        return m_vecRunTracks.size() == m_nStoppedRun;
    }

    //����һ����ȫ������������ʼ����һ�Žڵ㡣
    //************************************
    // Method:    MakeTree
    // FullName:  WinnderTreeT<NODE>::MakeTree
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: vector<NODE*>&vecNodePtr    �����׵�ַ����
    // Parameter: vector<NODE*>&vecNodeEndPtr ���н�����ַ���顣
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
        //����ڵ�������������������Ҷ�ӽڵ�� ��ȫ������

        int i = 1;
        m_nLevel = 0;
        while (nLeftRun > i)
        {
            ++m_nLevel;
            i <<= 1;
        }

        ++m_nLevel; //��ȫ�������Ĳ���
        m_vecTree.resize(2 * nLeftRun - 1); //���һ�㲻��ʱ ���ڵ���Ϊ 2*run-1
        m_nLastLevelBegin = m_vecTree.size() - nLeftRun;


        //��д����Ҷ�ӽڵ㣬����������RUN�ĵ�һ��Ԫ��
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

        //��д�����ڵ�
        int nR = m_vecTree.size() - 1;
        int nL = nR - 1;
        while (nL > 0)
        {
            m_vecTree[nL >> 1] = CMP_NODE(m_vecTree[nL], m_vecTree[nR]) ? m_vecTree[nL] : m_vecTree[nR]; //��ڵ�С
            nR -= 2;
            nL -= 2;
        }
    }

    //�ڴ��е�K·�󲢼������m_pVecDest��
    inline void k_merge()
    {
        while (m_vecRunTracks.size() != m_nStoppedRun)
        {
            m_pVecDest->push_back(*(m_vecTree[0].first));
            nRun = m_vecTree[0].second;
            nTrack = m_vecRunInTreePos[m_vecTree[0].second]; //���ټ�����

            //����һ��������ײ�
            if (++(m_vecRunTracks[nRun]) == m_vecRunEnds[nRun])//һ����ֹ��
            {

                MakeTree(); //һ����ֹ���¹�����
            }
            else
            {
                m_vecTree[nTrack].first = m_vecRunTracks[nRun];
                m_vecTree[nTrack].second = nRun;
                //���������бȽ�
                while (nTrack != 0)
                {
                    if (nTrack % 2 == 0)//��ż��Ϊ������
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

    //����һ����С�Ľڵ�
    //NODE*��ʾ�ýڵ�ĵ�ַ��int ��ʾ����һ���鲢�з��ص�
    bool k_merge_file(vector<FILE*> &vecTempFileHandle, FILE * fpWriteFileHandle, int nReadCnt, NODE*pOutPtr)
    {
        int nOutCnt = 0;

        while (m_vecRunTracks.size() != m_nStoppedRun)//�����ļ�û�й鲢��ȫ
        {
            pOutPtr[nOutCnt++] = *(m_vecTree[0].first);

            if (nOutCnt == nReadCnt)//д��������
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
            nTrack = m_vecRunInTreePos[m_vecTree[0].second]; //���ټ�����

            //����һ��������ײ�
            ++(m_vecRunTracks[nRun]);
            if (m_vecRunTracks[nRun] == m_vecRunEnds[nRun])//һ����ֹ��
            {
                long long nRealReadCnt = 0;
                nRealReadCnt = fread(m_vecRunBeginPtr[nRun], sizeof (NODE), nReadCnt, vecTempFileHandle[nRun]);
                if (nRealReadCnt == -1)
                {
                    LOG_WARNING("ReadFile error");
                    return false;
                }

                if (nRealReadCnt == 0)//һ���ļ�������¹�����
                {
                    MakeTree(); //һ����ֹ���¹�����
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

            //���������бȽ�
            while (nTrack != 0)
            {
                if (nTrack % 2 == 0)//��ż��Ϊ������
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

        if (nOutCnt)//����������ûд���ļ���
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
    vector<pair<NODE*, int> > m_vecTree; //��ȫ�������ṹ
    vector<NODE*> m_vecRunBeginPtr; //����ÿһ����ʼ��ַ
    vector<NODE*> m_vecRunTracks; //��ǰ���ٵ��ĸ���Node
    vector<NODE*> m_vecRunEnds; //Run����ָֹ��
    vector<int> m_vecStopMark; //ÿ��Rund����ֹ��׼
    vector<int> m_vecRunInTreePos; //ÿ��Run�Ŷ�Ӧ��TREE�е�λ�á�

    vector<NODE> *m_pVecDest; //��Ź鲢����ĵط���

    //	NODE *m_pMaxNodePtr//;
    int m_nLevel; //����
    int m_nLastLevelBegin; //���һ��ڵ���ʼ��

    int m_nStoppedRun; //�鲢��ֹͣ������

private:
    //��ʱ����������ٶ����
    //pair<NODE*,int> resPair;
    int nRun;
    int nTrack; //���ټ�����

    CMP M_CMP_ELEMENT;
};

//�ļ��鲢����
template <class NODE, class CMP>
int k_merge_file(const char *pchFileIn, const char *pchFileOut, CMP CMP_NODE, int64 nFreeMemSize)
{
    typedef unsigned long long uint64;
    LOG_TRACE("\n---------------k_merge_file---------------\n");
    //���ļ�
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

    //��ô�С
    struct stat64 stllFileSize; //FileSize
    if (stat64(pchFileIn, &stllFileSize) < 0)
    {
        LOG_WARNING("Execute GetFileSize  fail!.\n");
        return -1;
    }

    uint64 nFileSize = stllFileSize.st_size;

    if (nFileSize % sizeof (NODE) != 0 || !nFileSize)//�ļ���СӦ���ǽṹ���������
    {
        LOG_FATAL("File size empty or not fileSize % sizeof (NODE) != 0 return -1");
        return -1;
    }

    uint64 nTotalEleCnt; //�����ļ���Ԫ�ظ���
    int64 nEachColCnt; //ÿ���鲢��(���򻺴�)Ԫ�ظ���
    int64 nColCnt; //�и���
    uint64 nReadCnt, nWriteCnt; //ʵ�ʶ�ȡ����

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
    if (nColCnt == 1)//�ڴ��ܷ��¸��ļ�
    {
        LOG_INFO("Sort all in the mem");
        vector<NODE> vecBuf; //��������
        vecBuf.resize(nEachColCnt);

        //readfile
        nReadCnt = fread(&vecBuf[0], sizeof (NODE), nTotalEleCnt, fpSrc);
        if (nReadCnt == -1 || nReadCnt != nTotalEleCnt)
        {
            LOG_WARNING("ReadFile error.\n");
            return -1;
        }
        vecBuf.erase(vecBuf.begin() + nReadCnt, vecBuf.end()); //ɾ��Buffer�ж���Ŀռ�
        sort(vecBuf.begin(), vecBuf.end(), CMP_NODE); //sort

        //writefile
        nWriteCnt = fwrite(&vecBuf[0], sizeof (NODE), nTotalEleCnt, fpDes);
        if (nWriteCnt == -1 || nWriteCnt != nTotalEleCnt)
        {
            LOG_WARNING("WriteFile error.\n");
            return -1;
        }
    }
    else//����������
    {
        LOG_INFO("in mem sort begin");
        //0.���������ֶ������ļ�
        vector<NODE> vecBuf; //��������
        vecBuf.resize(nEachColCnt);

        vector<string> vecTempFileName; //�ļ���
        vecTempFileName.resize(nColCnt, "0");

        vector<FILE*> vecTempFileHandle; //�ļ����
        vecTempFileHandle.resize(nColCnt);

        long long nWriteCnt;
        char chBuf[1024];

        cout << "use " << nColCnt << "-merge" << endl; //��ʱ�ļ�����
        cout << "every group have element: " << nEachColCnt << endl; //ÿ����ʱ�ļ��Ĵ�С

        FILE *fpBuf;
        for (i = 0; i < nColCnt; ++i)
        {
            sprintf(chBuf, "%d", i);
            
            vecTempFileName[i] = chBuf; //�����ļ�����

            if ((fpBuf = fopen(vecTempFileName[i].c_str(), "wb")) == NULL)
            {
                LOG_WARNING("Could not create file handle object.\n");
                return -1;
            }
            vecTempFileHandle[i] = fpBuf;
        }

        //1��ȡ������ д��ʱ�ֶ��ļ�
        for (i = 0; i < nColCnt; ++i)
        {
            //readfile
            nReadCnt = fread(&vecBuf[0], sizeof (NODE), nEachColCnt, fpSrc);
            if (nReadCnt == -1 || (i != nColCnt - 1 && nReadCnt != nEachColCnt))
            {
                LOG_WARNING("ReadFile error.\n");
                return -1;
            }

            if (i == nColCnt - 1)//���һ�п��ܶ�ȡ�ıȽ�ǰ�������
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
        //׼���鲢
        int nEachMergeCnt = nEachColCnt / (nColCnt + 1); //�鲢���õ�ÿ��������Ԫ�ظ���
        vecBuf.resize(nEachColCnt);

        NODE* outPtrBegin; //�����������ʼλ��

        vector<NODE*> vecNodePtr;
        vector<NODE*> vecNodeEndPtr;
        vecNodePtr.resize(nColCnt);
        vecNodeEndPtr.resize(nColCnt);

        //��ÿ����ʱ�ļ����������
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

        //�����鲢
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

