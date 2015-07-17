/* 
 * File:   merge_vec.h
 * Author: chenghuige
 *
 * Created on 2010年2月25日, 下午10:17
 */

#ifndef _MERGE_VEC_H
#define	_MERGE_VEC_H

#include <vector>
#include <queue>
#include <deque>
#include <bitset>
#include "invert_table.h"

namespace adrank
{

///**合并两个vec，注意均按照广告id排序，重复的id合并其sim,合并结果到vec1*/
////FIXME 排名考虑 竞价 点击率 关键词匹配度 也要考虑广告内容和查询的匹配度??!!! FIXME
//struct AddWeight
//{
//    //asset left.m_nID == right.m_nID
//    template<typename _InvertNode>
//            inline void operator() (_InvertNode& invert_node, _InvertNode& left, _InvertNode & right)
//    {
//        invert_node.m_nID = left.m_nID;
//        invert_node.m_nWeight = left.m_nWeight + right.m_nWeight;
//    }
//};
//struct MaxWeight
//{
//    template<typename _InvertNode>
//            inline void operator() (_InvertNode& invert_node, _InvertNode& left, _InvertNode & right)
//    {
//        invert_node.m_nID = left.m_nID;
//        invert_node.m_nWeight = std::max(left.m_nWeight, right.m_nWeight);
//    }
//};
//struct MaxWeightSelectInfo
//{
//    template<typename _InvertNode>
//            inline void operator() (_InvertNode& invert_node, _InvertNode& left, _InvertNode & right)
//    {
//        if (left.m_nWeight > right.m_nWeight)
//            invert_node = left;
//        else
//            invert_node = right;
//    }
//};
//struct ChooseFirst
//{
//    template<typename _InvertNode>
//            inline void operator() (_InvertNode& invert_node, _InvertNode& left, _InvertNode & right)
//    {
//        invert_node = left;
//    }
//};
/**合并两个vec，注意均按照广告id排序，重复的id合并其sim,合并结果到vec1*/
//FIXME 排名考虑 竞价 点击率 关键词匹配度 也要考虑广告内容和查询的匹配度??!!! FIXME
struct AddWeight
{
    //asset left.m_nID == right.m_nID
    template<typename _InvertNode>
            inline _InvertNode operator() (_InvertNode& left, _InvertNode & right)
    {
        _InvertNode invert_node;
        invert_node.m_nID = left.m_nID;
        invert_node.m_nWeight = left.m_nWeight + right.m_nWeight;
        return invert_node;
    }
};
struct MaxWeight
{
    template<typename _InvertNode>
            inline _InvertNode operator() (_InvertNode& left, _InvertNode & right)
    {
        _InvertNode invert_node;
        invert_node.m_nID = left.m_nID;
        invert_node.m_nWeight = std::max(left.m_nWeight, right.m_nWeight);
        return invert_node;
    }
};
struct MaxWeightSelectInfo
{
    template<typename _InvertNode>
            inline _InvertNode operator() (_InvertNode& left, _InvertNode & right)
    {
        if (left.m_nWeight > right.m_nWeight)
            return left;
        else
            return right;
    }
};
struct ChooseFirst
{
    template<typename _InvertNode>
            inline _InvertNode operator() (_InvertNode& left, _InvertNode & right)
    {
        return left;
    }
};

///数组归并，要求vec1,ve2按照m_nID排好序
template<typename Func, typename T>
void mergeVec(T& vec1, T& vec2, Func func)
{
    int i = 0;
    int j = 0;
    T vec;
    vec.reserve(vec1.size() + vec2.size());
    //typename T::value_type invert_node;
    while (i < vec1.size() && j < vec2.size())
    {
        if (vec1[i].m_nID == vec2[j].m_nID)
        {
            //func(invert_node, vec1[i], vec2[j]);
            //vec.push_back(invert_node);
            vec.push_back(func(vec1[i], vec2[j]));
            i++;
            j++;
        }
        else if (vec1[i].m_nID < vec2[j].m_nID)
        {
            vec.push_back(vec1[i]);
            i++;
        }
        else
        {
            vec.push_back(vec2[j]);
            j++;
        }
    }

    while (j < vec2.size())
    {
        vec.push_back(vec2[j]);
        j++;
    }

    while (i < vec1.size())
    {
        vec.push_back(vec1[i]);
        i++;
    }

    vec1.swap(vec);
}
template<typename Func, typename T>
void mergeVec(T& vec1, T& vec2, T& vec, Func func)
{
    int i = 0;
    int j = 0;
    //typename T::value_type invert_node;
    while (i < vec1.size() && j < vec2.size())
    {
        if (vec1[i].m_nID == vec2[j].m_nID)
        {
            //func(invert_node, vec1[i], vec2[j]);
            //vec.push_back(invert_node);
            vec.push_back(func(vec1[i], vec2[j]));
            i++;
            j++;
        }
        else if (vec1[i].m_nID < vec2[j].m_nID)
        {
            vec.push_back(vec1[i]);
            i++;
        }
        else
        {
            vec.push_back(vec2[j]);
            j++;
        }
    }

    while (j < vec2.size())
    {
        vec.push_back(vec2[j]);
        j++;
    }

    while (i < vec1.size())
    {
        vec.push_back(vec1[i]);
        i++;
    }
}


///vec to store the final result
template<typename T>
void mergeVec_chooseFirst(T& vec1, T& vec2)
{
    int i = 0;
    int j = 0;
    T vec;
    vec.reserve(vec1.size() + vec2.size());
    //typename T::value_type invert_node;
    while (i < vec1.size() && j < vec2.size())
    {
        if (vec1[i].m_nID == vec2[j].m_nID)
        {
            //func(invert_node, vec1[i], vec2[j]);
            //vec.push_back(invert_node);
            vec.push_back(vec1[i]);
            i++;
            j++;
        }
        else if (vec1[i].m_nID < vec2[j].m_nID)
        {
            vec.push_back(vec1[i]);
            i++;
        }
        else
        {
            vec.push_back(vec2[j]);
            j++;
        }
    }

    while (j < vec2.size())
    {
        vec.push_back(vec2[j]);
        j++;
    }

    while (i < vec1.size())
    {
        vec.push_back(vec1[i]);
        i++;
    }
    vec1.swap(vec);
}
/**
 * 合并一系列的vector,返回i 则 vec[i]中保存最后的归并结果
 * 这个是简单的两两归并/形成完全二叉树   O(log(K)*n)
 *
 * 这个比一个接一个得merge快很多
 * TODO 与外排很像但是我能在内存存放所有数据
 * 1. 直接K路归并？  K = vec_size  O(log(K) * n)
 * 2. 2路归并 每次取长度最小的两个 构造最优归并树( huffman)? O(log(K)*n)
 * 3. 对于这里类别，广告归并，因为广告比较少可以用标记位，hash O(n) n为各个vector元素之和
 * 4. 考虑多线程？
 */
template<typename Func, typename T>
int mergeVecs(T vecs[], int vec_size, Func func)
{
    //you should make sure vec_size > 0
    int times = (int) ceil(log((double) vec_size) / log(2.0)); //log2
    int find = 0;
    int choose[2] = {0, 0}; //must be 0
    for (int i = 0; i < times; i++)
    {
        find = 0;
        for (size_t j = 0; j < vec_size; j++)
        {
            if (vecs[j].size() > 0)
            {
                choose[find++] = j;
                if (find == 2)
                {
                    mergeVec(vecs[choose[0]], vecs[choose[1]], func);
                    vecs[choose[1]].clear();
                    find = 0;
                }
            }
        }
    }
    return choose[0];
}

///试图降低每次归并的空间开辟代价但是不太好弄
//template<typename Func, typename T>
//int mergeVecs(T vecs[], int vec_size, Func func)
//{
//    int times = (int) ceil(log((double) vec_size) / log(2.0)); //log2
//    int find = 0;
//    T result_vec;
//    for (int i = 0; i < times; i++)
//    {
//        find = 0;
//        for (size_t j = 0; j < vec_size; j++)
//        {
//            if (vecs[j].size() > 0)
//            {
//                choose[find++] = j;
//                if (find == 2)
//                {
//                    mergeVec(vecs[choose[0]], vecs[choose[1]], result_vec, func);
//                    vecs[choose[1]].clear();
//                    find = 0;
//                }
//            }
//        }
//    }
//    vecs[0].swap(vec)
//    return 0;
//}

///利用hash，adranker专用,T必须有m_nID
///因为vecs按照下标，优先级降低，所以后面重复出现的去掉
//FIXME 多维数组写成vector a[20]这样的形式好吗
///结果存储在vecs[0]中 返回0,注意结果已经不排序了，也不要求输入时排序的，就是取并集
template<typename T, typename U>
int mergeVecs_hash(T vecs[], int vec_size, U& visited, int ad_num)
{
    //bool vistied[ad_num];
    //memset(vistied, 0, sizeof(bool)*ad_num)
    //std::bitset<ad_num> visited(0);
    //std::bitset<4 * 1024 * 1024 * 1024> visited(0);    //暂时写死，以后改用boost可变长度的bitset FIXME!
    T result_vec;
    result_vec.reserve(vecs[0].size() * vec_size / 2);

    for (int i = 0; i < vec_size; i++)
    {
        for (size_t j = 0; j < vecs[i].size(); j++)
        {
            if (!visited[vecs[i][j].m_nID])
            {
                visited[vecs[i][j].m_nID] = true;
                result_vec.push_back(vecs[i][j]);
            }
        }
        vecs[i].clear();
    }
    vecs[0].swap(result_vec);
    return 0;
}
template<typename T>
int mergeVecs_chooseFirst(T vecs[], int vec_size, int ad_num)
{
    //you should make sure vec_size > 0
    int times = (int) ceil(log((double) vec_size) / log(2.0)); //log2
    int find = 0;
    int choose[2] = {0, 0}; //must be 0
    for (int i = 0; i < times; i++)
    {
        find = 0;
        for (size_t j = 0; j < vec_size; j++)
        {
            if (vecs[j].size() > 0)
            {
                choose[find++] = j;
                if (find == 2)
                {
                    mergeVec_chooseFirst(vecs[choose[0]], vecs[choose[1]]);
                    vecs[choose[1]].clear();
                    find = 0;
                }
            }
        }
    }
    return choose[0];
}

///最优归并, (用queue实现完全二叉树归并 23MS for 4001039 用queue比较慢)
///即使是最优归并，也应该由于需要计算最小的两个而变得比较慢
template<typename T>
struct BestMergeCmper
{
    BestMergeCmper(T vecs[]) : m_vecs(vecs)
    {
    }
    bool operator() (const int index1, const int index2)
    {
        return m_vecs[index1].size() > m_vecs[index2].size();
    }
private:
    T* m_vecs;
};
template<typename Func, typename T>
int mergeVecs_bestMerge(T vecs[], int vec_size, Func func)
{
    //  typedef std::priority_queue<int, std::queue<int>, BestMergeCmper<T> >  MergeQueue;
    //  BestMergeCmper<T> cmper(vecs);
    //  MergeQueue queue(cmper);
    std::priority_queue<int> queue;
    for (int i = 0; i < vec_size; i++)
    {
        queue.push(i);
    }
    while (queue.size() != 1)
    {
        int i = queue.top();
        queue.pop();
        int j = queue.top();
        queue.pop();
        mergeVec(vecs[i], vecs[j], func);
        vecs[j].clear();
        queue.push(i);
    }
    return queue.top();
}
///合并相同entry的两个post list
inline void mergeInvertList(const std::vector<InvertNode>&vec1, const std::vector<InvertNode>& vec2,
                            int index, FILE* fp)
{
    size_t i = 0;
    size_t j = 0;
    std::vector<InvertNode> vec;
    while (i < vec1.size() && j < vec2.size())
    {
        if (vec1[i].m_nID == vec2[j].m_nID) //同时出现的以offline计算得到的sim为准
        {
            vec.push_back(vec1[i]);
            i++;
            j++;
        }
        else if (vec1[i].m_nID < vec2[j].m_nID)
        {
            vec.push_back(vec1[i]);
            i++;
        }
        else
        {
            vec.push_back(vec2[j]);
            j++;
        }
    }

    while (j < vec2.size())
    {
        vec.push_back(vec2[j]);
        j++;
    }

    while (i < vec1.size())
    {
        vec.push_back(vec1[i]);
        i++;
    }

    //按相似度从大到小排序
    std::sort(vec.begin(), vec.end(), CmpInvertNodeWeight());

    std::vector<ST_PidKidInfo> result_vec;
    result_vec.resize(vec.size());

    for (size_t i = 0; i < vec.size(); i++)
    {
        result_vec[i].setData(index, vec[i].m_nID, vec[i].m_nWeight);
    }

    fwrite(&result_vec[0], sizeof (ST_PidKidInfo), result_vec.size(), fp);
}

} //namesapce adrank


#endif	/* _MERGE_VEC_H */

