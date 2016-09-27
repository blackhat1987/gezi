#ifndef WINNERTREE_LINUX_H
#define WINNERTREE_LINUX_H

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
#include <glog/logging.h>
#include "types.h"
#include "debug_help.h"


using namespace std;
template <class NODE, class CMP = std::less<NODE> >
class CWinnerTree
{
public:

    //Ĭ�Ͽ�ָ�����
    CWinnerTree(CMP CMP_ELEMENT = CMP())
    {
        M_CMP_ELEMENT = CMP_ELEMENT;
    }

    //��·�鲢�Ƿ����
    inline bool IsStopped()
    {
        return m_vecRunTracks.size() == m_nStoppedRun;
    }

    //����һ����ȫ������������ʼ����һ�Žڵ㡣
    //************************************
    // Method:    MakeTree
    // FullName:  CWinnerTree<NODE>::MakeTree
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: vector<NODE*>&vecNodePtr    �����׵�ַ����
    // Parameter: vector<NODE*>&vecNodeEndPtr ���н�����ַ���顣
    //************************************
    bool CreateTree(vector<NODE*>&vecNodePtr, vector<NODE*>&vecNodeEndPtr, vector<NODE> *pVecDest = NULL)
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
    inline void K_Merge()
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
    bool K_MergeFile(vector<FILE*> &vecTempFileHandle, FILE * fpWriteFileHandle, int nReadCnt, NODE*pOutPtr)
    {
        int nOutCnt = 0;

        while (m_vecRunTracks.size() != m_nStoppedRun)//�����ļ�û�й鲢��ȫ
        {
            pOutPtr[nOutCnt++] = *(m_vecTree[0].first);

            if (nOutCnt == nReadCnt)//д��������
            {
                __int64 nWriteCnt;
                nWriteCnt = fwrite(pOutPtr, sizeof (NODE), nOutCnt, fpWriteFileHandle);
                if (nWriteCnt == -1 || nWriteCnt != nOutCnt)
                {
                    printf("WriteFile error %d.\n", __LINE__);
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
                DWORD_ nRealReadCnt = 0;
                nRealReadCnt = fread(m_vecRunBeginPtr[nRun], sizeof (NODE), nReadCnt, vecTempFileHandle[nRun]);
                if (nRealReadCnt == -1)
                {
                    printf("ReadFile error %d.\n", __LINE__);
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
            __int64 nWriteCnt;
            nWriteCnt = fwrite(pOutPtr, sizeof (NODE), nOutCnt, fpWriteFileHandle);
            if (nWriteCnt == -1 || nWriteCnt != nOutCnt)
            {
                printf("WriteFile error %d.\n", __LINE__);
                return false;
            }
        }
        return true;
    }


public:
    ~CWinnerTree(void)
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
int K_MergeFile(const char *pchFileIn, const char *pchFileOut, CMP CMP_NODE, int nFreeMemSize)
{
    printf("\n---------------K_MergeFile---------------\n");
    //���ļ�
    FILE *fpSrc, *fpDes;
    if ((fpSrc = fopen(pchFileIn, "rb")) == NULL)
    {
        printf("Could not open file !(%d).\n", __LINE__);
        return -1;
    }
    if ((fpDes = fopen(pchFileOut, "wb")) == NULL)
    {
        printf("Could not create file !(%d).\n", __LINE__);
        return -1;
    }

    //��ô�С
    LOG(INFO) << "in file info" << "\n";
    struct stat64 stllFileSize; //FileSize
    if (stat64(pchFileIn, &stllFileSize) < 0)
    {
        printf("Execute GetFileSize  fail! (%d).\n", __LINE__);
        return -1;
    }

    __int64 nFileSize = stllFileSize.st_size;
    LOG(INFO) << Pval(sizeof(NODE)) << "\n";
    LOG(INFO) << "The file size is: " << nFileSize  << "\n";
    LOG(INFO) << "Node num is: " << nFileSize / sizeof (NODE) << "\n";
    if (nFileSize % sizeof (NODE) != 0 || !nFileSize)//�ļ���СӦ���ǽṹ���������
    {
        LOG(INFO) << "file size empty or not fileSize % sizeof (NODE) != 0 return -1" << "\n";
        return -1;
    }

    __int64 nTotalEleCnt; //�����ļ���Ԫ�ظ���
    int nEachColCnt; //ÿ���鲢��(���򻺴�)Ԫ�ظ���
    int nColCnt; //�и���
    __int64 nReadCnt, nWriteCnt; //ʵ�ʶ�ȡ����

    nTotalEleCnt = nFileSize / sizeof (NODE);
    nEachColCnt = nFreeMemSize / sizeof (NODE);
    Pval(sizeof(NODE));
    Pval(nFreeMemSize);
    printf("nEachColCnt %d\n", nEachColCnt);
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
        LOG(INFO) << "Sort all in the mem" << "\n";
        vector<NODE> vecBuf; //��������
        vecBuf.resize(nEachColCnt);

        //readfile
        nReadCnt = fread(&vecBuf[0], sizeof (NODE), nTotalEleCnt, fpSrc);
        if (nReadCnt == -1 || nReadCnt != nTotalEleCnt)
        {
            printf("ReadFile error %d.\n", __LINE__);
            return -1;
        }
        vecBuf.erase(vecBuf.begin() + nReadCnt, vecBuf.end()); //ɾ��Buffer�ж���Ŀռ�
        sort(vecBuf.begin(), vecBuf.end(), CMP_NODE); //sort

        //writefile
        nWriteCnt = fwrite(&vecBuf[0], sizeof (NODE), nTotalEleCnt, fpDes);
        if (nWriteCnt == -1 || nWriteCnt != nTotalEleCnt)
        {
            printf("WriteFile error %d.\n", __LINE__);
            return -1;
        }
    }
    else//����������
    {
        LOG(INFO) << "in mem sort begin" << "\n";
        //0.���������ֶ������ļ�
        vector<NODE> vecBuf; //��������
        vecBuf.resize(nEachColCnt);

        vector<string> vecTempFileName; //�ļ���
        vecTempFileName.resize(nColCnt, "0");

        vector<FILE*> vecTempFileHandle; //�ļ����
        vecTempFileHandle.resize(nColCnt);

        DWORD_ nWriteCnt;
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
                printf("Could not create file handle object !(%d).\n", __LINE__);
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
                printf("ReadFile error %d.\n", __LINE__);
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
                printf("WriteFile error %d.\n", __LINE__);
                return -1;
            }
            fclose(vecTempFileHandle[i]);
        }

        LOG(INFO) << "out of mem merge begin" << "\n";
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
                printf("Could not open file handle object !(%d).\n", __LINE__);
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
                printf("ReadFile error %d.\n", __LINE__);
                return -1;
            }
            vecNodeEndPtr[i] = vecNodePtr[i] + nReadCnt;
        }
        outPtrBegin = vecNodeEndPtr[nColCnt - 1];

        CWinnerTree<NODE, CMP> winnerTree(CMP_NODE);
        winnerTree.CreateTree(vecNodePtr, vecNodeEndPtr);
        winnerTree.K_MergeFile(vecTempFileHandle, fpDes, nEachMergeCnt, outPtrBegin);

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
int K_MergeFile(const char *pchFileIn, const char *pchFileOut, int nFreeMemSize = 1024 * 1024 * 1024)
{
    return K_MergeFile<NODE, std::less<NODE> >(pchFileIn, pchFileOut, std::less<NODE > (), nFreeMemSize);
}
#endif

