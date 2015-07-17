/** 
 *  ==============================================================================
 * 
 *          \file      inverted_index.h
 *
 *        \author   chenghuige 
 *          
 *          \date     2010-01-31 13:53:58.446039
 *  
 *  \Description: 支持简单的倒排索引，不负责编号映射
 *  可以用std::pair 替代  InvertNode 不过当前保证都是 first second名字就行了
 *
 *  TODO IndexVec IndexCacheVec可以修改 只用一个bool vec标记索引对应的倒排是否在内存中即可,
 *   然后只保留一个IndexVec
 *
 * 注意不要拷贝，否则由于FILE* fp指向相同的文件，会造成尝试两次关闭，也没有必要使用拷贝！
 *
 * TODO 单独提出一个简单的inverted_index 不计算l1norm l2norm ,计算的继承整个简单的
 *  ==============================================================================
 */

#ifndef INVERTED_INDEX_H_
#define INVERTED_INDEX_H_

#include "winner_tree.h"
#include "inverted_node_types.h"
#include "inverted_node_old_compat.h"
#include "inverted_default_value.h"
#include "ul_log_help.h"
#include "common_help.h"


namespace inverted {
struct OIFVisitor_Default
{//IF means one invert finish
    template<typename _Node, typename _CacheNode>
            void operator () (_Node& node, _CacheNode & cache_node) const
    {

    }
};
/**
 * 倒排表
 */
template <typename _ValueType = float,
        template <typename ELEM> class _IndexNode = IndexNode,
        template <typename _T1, typename _T2> class _InvertNode = std::pair,
        typename _KeyType = int, typename _IndexType = int,
        typename _OIFVisitor = OIFVisitor_Default
        >
        class InvertedIndex
{
public:
    typedef _ValueType ValueType;
    typedef _KeyType KeyType;
    typedef _IndexType IndexType;
    typedef typename NormTypeTraits<ValueType>::L1NormType L1NormType;
    typedef typename NormTypeTraits<ValueType>::L2NormType L2NormType; //L2NormType
    typedef _InvertNode<_KeyType, _ValueType> Pair;
    typedef Pair Node;
    typedef Pair InvertNode;
    typedef Pair InvertNodeType;
    typedef _IndexNode<ValueType> IndexNodeType;
    typedef IndexNode_Cache<ValueType> OldNodeType; //for old compat
    typedef SortNode<IndexType, KeyType, ValueType> SortNodeType;
    typedef typename IndexNodeType::L1Norm L1Norm;
    typedef typename IndexNodeType::L2Norm L2Norm;
    typedef InvertNodeType* iterator;
    typedef std::pair<iterator, iterator> Range;

public:
    InvertedIndex(const _OIFVisitor& visitor = _OIFVisitor())
    : m_fpInvert(NULL), m_entryNum(0), m_bAllInMem(false), m_bNeedCache(true),
    m_sortMethod(UNKNOWN_ORDER), m_bPersitant(true), m_invertSize(0),
    m_infileName(""), m_sortedfileName(""), m_indexfileName(""),
    m_invertfileName(""), m_oifVisitor(visitor), m_tempIndex(-1)
    {
        init_default_null_value(m_nullWeight);
    }
    explicit InvertedIndex(IndexType entry_num)
    : m_fpInvert(NULL), m_entryNum(entry_num), m_bAllInMem(false), m_bNeedCache(true),
    m_sortMethod(UNKNOWN_ORDER), m_bPersitant(true), m_invertSize(0),
    m_infileName(""), m_sortedfileName(""), m_indexfileName(""), m_invertfileName(""),
    m_tempIndex(-1)
    {
        init_default_null_value(m_nullWeight);
    }
    ~InvertedIndex()
    {
        clear_all();
    }
    void set_null_weight(ValueType null_weight)
    {
        m_nullWeight = null_weight;
    }
    void set_nonpersistant()
    {
        m_bPersitant = false;
    }
    void set_persistant(bool status)
    {
        m_bPersitant = status;
    }
    bool is_persistant() const
    {
        return m_bPersitant;
    }
    void set_need_cache(bool status)
    {
        m_bNeedCache = status;
    }
    bool is_need_cache() const
    {
        return m_bNeedCache;
    }
    void clear_cache()
    {
        if (m_fpInvert)
        { //注意如果有拷贝存在 这里一个关闭了 另外一个invert也还是会尝试关闭因为它的m_fpInvert还不是NULL所以会出错
            fclose(m_fpInvert);
            m_fpInvert = NULL;
        }
        m_indexVec.clear();
        m_indexCacheVec.clear();
        m_invertCacheVec.clear();
        m_entryNum = 0;
    }
    void clear()
    {
        clear_cache();
        //删除不需要的文件
        if (!m_infileName.empty())
        {
            LOG_TRACE("Delete %s", m_infileName.c_str());
            bf::remove(bf::path(m_infileName));
        }
        if (!m_sortedfileName.empty())
        {
            LOG_TRACE("Delete %s", m_sortedfileName.c_str());
            bf::remove(bf::path(m_sortedfileName));
        }
    }
    void clear_all()
    {
        clear();
        if (!is_persistant())
            clear_disk();
    }
    void clear_disk()
    {
        if (m_dir.empty())
        {
            bf::remove(bf::path(m_indexfileName));
            bf::remove(bf::path(m_invertfileName));
        }
        else
        {
            bf::remove_all(bf::path(m_dir));
        }
    }
    /**设定倒排表所需要的文件名，两个必须的，倒排索引文件名和倒排文件名*/
    void set_file(const char* index_file, const char* invert_file)
    {
        m_indexfileName = index_file;
        m_invertfileName = invert_file;
    }
    void set_dir(const string& dir)
    {
        m_dir = dir;
        if (!bf::exists(dir))
        {
            LOG_WARNING("%s not exist, will create first", dir.c_str());
            bf::create_directories(dir);
        }
        string indexfile_name = m_dir + "/index.idx";
        string invertfile_name = m_dir + "/invert.idx";
        set_file(indexfile_name.c_str(), invertfile_name.c_str());
    }
    void set_entry_num(int entry_num)
    {
        m_entryNum = entry_num;
    }

    ///读取倒排文件
    template<class IndexType, class InvertType>
    static bool read_invert(FILE *fp, const IndexType& strIndexNode, vector<InvertType>& vecInvert, int nReadSize)
    {
        uint64 nAddr = strIndexNode.addr;
        int nCount = strIndexNode.count;

        if (fseek(fp, nAddr, 0) == -1)
            return false;

        int nSize = std::min(nReadSize, nCount);

        vecInvert.resize(nSize);
        int nReadCnt = fread(&vecInvert[0], sizeof (InvertType), nSize, fp);
        if (nReadCnt == -1 || nReadCnt != nSize)
            return false;
        return true;
    }
    /**
     * 待排序的文件作为输入，建立倒排表，Node表示文件排序元素类型如
     *<phrase,ad> 或者<phrase, phrase , weight>
     *按照GETPID中排序WinnerTree_Linux.h中的要求，需要提供排序函数Cmp，Node中未提供
     * 同时提供indexfile,invertfile,sorted_file的命名
     */

    template<class CMP_NODE>
    void create(const char *infile_name, const char * sortedfile_name,
    const char *indexfile_name, const char* invertfile_name,
    CMP_NODE cmp_node,
    int64 nFreeMemSize = SortCacheSize)
    {
        clear();
        m_infileName = infile_name;
        m_indexfileName = indexfile_name;
        m_invertfileName = invertfile_name;

        if (k_merge_file<SortNodeType, CMP_NODE > (infile_name, sortedfile_name,
                cmp_node, nFreeMemSize) == -1)
        {
            //LOG(FATAL) << "Sorting file " << infile_name << " FATAL" << endl;
        }
        m_sortedfileName = sortedfile_name;

        create_inverted_index();
    }
    /**
     *
     * @param dir    给定的索引路径，这种创建默认相关文件的名字
     * @param cmp_node
     * @param nFreeMemSize
     * @return
     */
    template<class CMP_NODE>
    void create(const char *dir, CMP_NODE cmp_node, int64 nFreeMemSize = SortCacheSize)
    {
        clear();
        m_dir = dir;
        m_infileName = m_dir + "/ini.idx";
        m_indexfileName = m_dir + "/index.idx";
        m_invertfileName = m_dir + "/invert.idx";
        m_sortedfileName = m_dir + "/sorted.idx";

        if (k_merge_file<SortNodeType, CMP_NODE > (m_infileName.c_str(), m_sortedfileName.c_str(),
                cmp_node, nFreeMemSize) == -1)
        {
            //LOG(FATAL) << "Sorting file " << m_infileName << " FATAL" << endl;
        }

        create_inverted_index();
    }
    ///上面函数的默认排序方法
    void create(const char *infile_name, const char * sortedfile_name,
            const char *indexfile_name, const char* invertfile_name,
            int64 nFreeMemSize = SortCacheSize)
    {
        clear();
        m_infileName = infile_name;
        m_indexfileName = indexfile_name;
        m_invertfileName = invertfile_name;

        if (k_merge_file<SortNodeType > (infile_name, sortedfile_name,
                CmpSTNodeID(), nFreeMemSize) == -1)
        {
            //LOG(FATAL) << "Sorting file " << infile_name << " FATAL" << endl;
        }
        m_sortedfileName = sortedfile_name;

        create_inverted_index();
    }
    void create(const char *dir, int64 nFreeMemSize = SortCacheSize)
    {
        clear();
        m_dir = dir;
        m_infileName = m_dir + "/ini.idx";
        m_indexfileName = m_dir + "/index.idx";
        m_invertfileName = m_dir + "/invert.idx";
        m_sortedfileName = m_dir + "/sorted.idx";
        if (k_merge_file<SortNodeType > (m_infileName.c_str(), m_sortedfileName.c_str(),
                CmpSTNodeID(), nFreeMemSize) == -1)
        {
            //LOG(FATAL) << "Sorting file " << m_infileName << " FATAL" << endl;
        }

        create_inverted_index();
    }

    ///从已经排好序的文件中建立倒排索引
    void create(const char * sortedfile_name, const char *indexfile_name, const char* invertfile_name)
    {
        clear();
        m_indexfileName = indexfile_name;
        m_invertfileName = invertfile_name;
        m_sortedfileName = sortedfile_name;

        //do real work here
        create_inverted_index();
    }
    ///重命名为了避免 void create(const char *dir, int nFreeMemSize = SortCacheSize) 重复
    void create2(const char* dir)
    {
        clear();
        m_dir = dir;
        m_indexfileName = m_dir + "/index.idx";
        m_invertfileName = m_dir + "/invert.idx";
        m_sortedfileName = m_dir + "/sorted.idx";

        create_inverted_index();
    }

    ///基于内存的倒排索引建立
    void create(std::vector<SortNodeType>& vec, const char *indexfile_name, const char* invertfile_name)
    {
        set_file(indexfile_name, invertfile_name);
        create_inverted_index(vec);
    }
    void create(std::vector<SortNodeType>& vec, const char *dir)
    {
        m_dir = dir;
        string indexfile_name = m_dir + "/index.idx";
        string invertfile_name = m_dir + "/invert.idx";
        set_file(indexfile_name.c_str(), invertfile_name.c_str());
        create_inverted_index(vec);
    }
    /*
     * FIXME TEMPLY rmove const
     */
    template<typename Vector>
    void create_bigVec(Vector& vec, const char *dir)
    {
        m_dir = dir;
        string indexfile_name = m_dir + "/index.idx";
        string invertfile_name = m_dir + "/invert.idx";
        set_file(indexfile_name.c_str(), invertfile_name.c_str());
        create_inverted_index_bigvec(vec);
    }
    /**
     * 如果倒排结构已经建立好存储在文件中则读取索引和倒排文件
     * 建立倒排表
     */
    bool load(const char *indexfile_name, const char *invertfile_name, const char *sortedfile_name = "")
    {
        return load<IndexNodeType > (indexfile_name, invertfile_name, sortedfile_name);
    }
    bool load(const string& dir)
    {
        return load<IndexNodeType > (dir);
    }
    bool load_old(const string& dir)
    {
        return load<OldNodeType > (dir);
    }
    template <typename _IndexNodeType>
    bool load(const string& dir)
    {
        m_dir = dir;
        string indexfile_name = m_dir + "/index.idx";
        string invertfile_name = m_dir + "/invert.idx";
        return load<_IndexNodeType > (indexfile_name.c_str(), invertfile_name.c_str());
    }
    template <typename _IndexNodeType>
    bool load(const char *indexfile_name, const char *invertfile_name, const char *sortedfile_name = "")
    {
        clear();
        LOG_INFO("----Begin loading inverted index: %s", m_dir.c_str());
        //        LOG_INFO("The invert's max cahce size can use is %f G", InvertCacheSize / float(1 << 30));
        m_indexfileName = indexfile_name;
        m_invertfileName = invertfile_name;
        if (sortedfile_name != "")
            m_sortedfileName = sortedfile_name;

        //打开倒排文件
        if ((m_fpInvert = fopen(m_invertfileName.c_str(), "rb")) == NULL)
        {
            LOG_ERROR("Fail to open invert file %s", m_invertfileName.c_str());
            return false;
        }

        load_inverted_index<_IndexNodeType > ();

        //内存中缓存cache
        make_inverted_cache();

        LOG_INFO("----Sucessfully load the inverted index: %s", m_dir.c_str());
        return true;
    }
    template <typename _IndexNodeType>
    bool load_no_sequence(const char *indexfile_name, const char *invertfile_name, const char *sortedfile_name = "")
    {
        clear();
        m_indexfileName = indexfile_name;
        m_invertfileName = invertfile_name;
        if (sortedfile_name != "")
            m_sortedfileName = sortedfile_name;

        //打开倒排文件
        if ((m_fpInvert = fopen(m_invertfileName.c_str(), "rb")) == NULL)
        {
            LOG_WARNING("Open %s failed", m_invertfileName.c_str());
            return false;
        }

        load_inverted_index_nosequence<_IndexNodeType > ();

        //内存中缓存cache
        make_inverted_cache();
        return true;
    }


    ///将索引结构写入文件
    bool write_index()
    {
        LOG_INFO("The index size is : %d %d The index file is %s", m_indexVec.size(), m_indexCacheVec.size(), m_indexfileName.c_str());
        FILE* fpIndex = fopen(m_indexfileName.c_str(), "wb");
        if (!fpIndex)
        {
            LOG_WARNING("Open %s fail", m_indexfileName.c_str());
            return false;
        }
        LOG_INFO("The index size is : %d %d The index file is %s", m_indexVec.size(), m_indexCacheVec.size(), m_indexfileName.c_str());
        size_t ret = fwrite(&m_indexCacheVec[0], sizeof (IndexNodeType), m_indexVec.size(), fpIndex);
        LOG_INFO("Write %d", ret);
        if (fpIndex)
        {
            fclose(fpIndex);
            fpIndex = NULL;
        }

        //        write_vec(m_indexCacheVec, "web_dawei/freq_invert/index2.idx");
        return true;
    }

    ///重新排序，再建立倒排,其实这个时候整个再排序是不划算的，因为其实已经按照id排序了,不过如果内存存不下的情况暂时只能这样比较好了
    template<class CMP_NODE>
    void recreate(CMP_NODE cmp_node,
    int nFreeMemSize = SortCacheSize)
    {
        clear();
        std::string tempfileName("temp.idx");
        if (k_merge_file<SortNodeType, CMP_NODE > (m_sortedfileName.c_str(), tempfileName.c_str(),
                cmp_node, SortCacheSize) == -1)
        {
            LOG_FATAL("Sorting file fail");
        }


        bf::rename(bf::path(tempfileName), bf::path(m_sortedfileName));

        create_inverted_index();
    }
    /**
     * 假设都在内存的话 这样应该比较快
     * 暂时这样的话 那么如果是有外存的 那么只是temp数组变化了，没有写回索引文件，TODO
     */
    template<class CMP>
    void sort(CMP cmp)
    {
        Range range;
        for (IndexType i = 0; i < m_entryNum; i++)
        {
            range = posting(i);
            std::sort(range.first, range.second, cmp);
        }
    }
    void sort(SortMethod sort_method)
    {
        switch (sort_method)
        {
            case BY_ID:
                sort(CmpNodeByID());
                break;
            case BY_VALUE:
                sort(CmpNodeByValue());
                break;
            case BY_VALUE_REVERSE:
                sort(CmpNodeByValue_Reverse());
                break;
            default:
                break;
        }
    }

    ///倒排表(建好后)有多少个入口，即多少个post list
    IndexType entry_num() const
    {
        return m_entryNum;
    }
    ///最好调用size
    IndexType size() const
    {
        return m_entryNum;
    }
    /**
     * 读取某个索引对应的倒排的begin()
     * 注意默认所有的索引都是int编号的（通过映射,从0到elem_num -1)
     * 外部需要提供一个空vector,因为有可能倒排list不在内存cache中，这时候需要读到这个vector中
     * 返回外部需要开始读的起始位置和要读的倒排list元素数目,如果不在cache 中start == &(vec[0])
     *
     * usage:
     *  std::vector<InvertNodeType> temp_vec;
     *  InvertNodeType* post_start = NULL;
     *   int post_num = 0;
     *
     *  getPostList (index, temp_vec, post_start,  post_num);
     *
     *  for ( int i = 0; i < num; i++)
     * {
     *      cout << *(post_start++).first << endl;
     * }
     * -1 表示查找失败
     * 正常 >= 0 返回查到的数目
     */
    int get_post(IndexType index, std::vector<InvertNodeType>& temp_vec, InvertNodeType*& post_start) const
    {
        //检查索引坐标的有效性
        if (index < 0 || index >= m_entryNum)
        {
            post_start = NULL;
            return -1;
        }

        uint64 nAddr;
        bool bRt;
        int post_num = 0;
        //查找缓存中是否有
        if (m_indexCacheVec[index].addr != -1)
        {
            //cout << "reading from cache" << endl;
            //索引信息
            post_num = m_indexCacheVec[index].count;
            nAddr = m_indexCacheVec[index].addr;
            post_start = &(m_invertCacheVec[nAddr]);
        }
        else//从磁盘中读取
        {
            //            LOG_WARNING("read post from file");
            temp_vec.clear();
            //            cout << "reading from file" << endl;
            //索引信息
            post_num = m_indexVec[index].count;

            //file read
            bRt = read_invert(m_fpInvert, m_indexVec[index], temp_vec, post_num);
            if (!bRt) return -1;

            post_start = &(temp_vec[0]);
        }
        return post_num;
    }
    /**
     * 即使倒排信息在内存中也复制到result vec
     * return false 表示查找失败
     * 外部确保result_vec为空
     */
    bool get_post(IndexType index, std::vector<InvertNodeType>& result_vec) const
    {
        //检查索引坐标的有效
        if (index < 0 || index >= m_entryNum)
            return false;

        int post_num;
        uint64 nAddr;
        bool bRt;
        //查找缓存中是否有
        if (m_indexCacheVec[index].addr != -1)
        {
            //cout << "reading from cache" << endl;
            //索引信息
            post_num = m_indexCacheVec[index].count;
            nAddr = m_indexCacheVec[index].addr;

            for (int i = nAddr; i < nAddr + post_num; i++)
            {
                result_vec.push_back(m_invertCacheVec[i]);
            }
        }
        else//从磁盘中读取
        {
            //            LOG_WARNING("read post from file");
            //索引信息
            post_num = m_indexVec[index].count;
            //file read
            bRt = read_invert(m_fpInvert, m_indexVec[index], result_vec, post_num);
            if (!bRt) return false;
        }
        return true;
    }
    bool get_post(IndexType index, std::vector<InvertNodeType>& result_vec, int max_len) const
    {
        //检查索引坐标的有效
        if (index < 0 || index >= m_entryNum)
            return false;

        int post_num;
        uint64 nAddr;
        bool bRt;
        //查找缓存中是否有
        if (m_indexCacheVec[index].addr != -1)
        {
            //cout << "reading from cache" << endl;
            //索引信息
            post_num = m_indexCacheVec[index].count;
            post_num = std::min(post_num, max_len);
            nAddr = m_indexCacheVec[index].addr;
            for (int i = nAddr; i < nAddr + post_num; i++)
            {
                result_vec.push_back(m_invertCacheVec[i]);
            }
        }
        else//从磁盘中读取
        {
            //            LOG_WARNING("read post from file");
            //索引信息
            post_num = m_indexVec[index].count;
            post_num = std::min(post_num, max_len);
            //file read
            bRt = read_invert(m_fpInvert, m_indexVec[index], result_vec, post_num);
            if (!bRt) return false;
        }
        return true;
    }
    /**
     *  查找某个索引节点的倒排，用法,注意多线程不安全
     *  Range range = invert.post(i);
     * for (InvertNodeType* cur = range.first; cur != range.second; ++cur)
     * {
     *      cur->first
     *      cur->second
     * }
     */
    Range posting(IndexType index)
    {
        //检查索引坐标的有效性
        if (index < 0 || index >= m_entryNum)
        {
            return Range(NULL, NULL);
        }
        InvertNodeType* post_start = NULL;
        InvertNodeType* post_end = NULL;
        uint64 nAddr;
        bool bRt;
        int post_num = 0;
        //查找缓存中是否有
        if (m_indexCacheVec[index].addr != -1)
        {
            //索引信息
            post_num = m_indexCacheVec[index].count;
            nAddr = m_indexCacheVec[index].addr;
            post_start = &(m_invertCacheVec[nAddr]);
        }
        else//从磁盘中读取
        {
            if (m_tempIndex == index)
            {
                post_start = &(m_tempVec[0]);
                return Range(post_start, post_start + m_tempVec.size());
            }
            m_tempVec.clear();
            //索引信息
            post_num = m_indexVec[index].count;

            //file read
            bRt = read_invert(m_fpInvert, m_indexVec[index], m_tempVec, post_num);
            if (!bRt)
                return Range(NULL, NULL);
            m_tempIndex = index;

            post_start = &(m_tempVec[0]);
        }
        return Range(post_start, post_start + post_num);
    }
    Range range(IndexType index)
    {
        //检查索引坐标的有效性
        if (index < 0 || index >= m_entryNum)
        {
            return Range(NULL, NULL);
        }
        InvertNodeType* post_start = NULL;
        InvertNodeType* post_end = NULL;
        uint64 nAddr;
        bool bRt = false;
        int post_num = 0;
        //查找缓存中是否有
        if (m_indexCacheVec[index].addr != -1)
        {
            //索引信息
            post_num = m_indexCacheVec[index].count;
            nAddr = m_indexCacheVec[index].addr;
            post_start = &(m_invertCacheVec[nAddr]);
        }
        else//从磁盘中读取
        {
            if (m_tempIndex == index)
            {
                post_start = &(m_tempVec[0]);
                return Range(post_start, post_start + m_tempVec.size());
            }
            m_tempVec.clear();
            //索引信息
            post_num = m_indexVec[index].count;

            //file read
            if (m_fpInvert)
            {
                bRt = read_invert(m_fpInvert, m_indexVec[index], m_tempVec, post_num);
            }
            else
            {
                LOG_ERROR("Read from disk fail ,file is not open");
            }
            if (!bRt)
                return Range(NULL, NULL);
            m_tempIndex = index;

            post_start = &(m_tempVec[0]);
        }
        return Range(post_start, post_start + post_num);
    }
    /**
     * 同上，不做下标检查
     */
    Range operator[](IndexType index)
    {
        InvertNodeType* post_start = NULL;
        InvertNodeType* post_end = NULL;
        uint64 nAddr;
        bool bRt;
        int post_num = 0;
        //查找缓存中是否有
        if (m_indexCacheVec[index].addr != -1)
        {
            //索引信息
            post_num = m_indexCacheVec[index].count;
            nAddr = m_indexCacheVec[index].addr;
            post_start = &(m_invertCacheVec[nAddr]);
        }
        else//从磁盘中读取
        {
            if (m_tempIndex == index)
            {
                post_start = &(m_tempVec[0]);
                return Range(post_start, post_start + m_tempVec.size());
            }
            m_tempVec.clear();
            //索引信息
            post_num = m_indexVec[index].count;

            //file read
            bRt = read_invert(m_fpInvert, m_indexVec[index], m_tempVec, post_num);
            if (!bRt)
                return Range(NULL, NULL);

            post_start = &(m_tempVec[0]);
        }
        return Range(post_start, post_start + post_num);
    }
    /**
     * 同上，外部提供可能的备用空间，多线程安全
     */
    Range posting(IndexType index, std::vector<InvertNodeType>& temp_vec) const
    {
        //检查索引坐标的有效性
        if (index < 0 || index >= m_entryNum)
        {
            return Range(NULL, NULL);
        }
        InvertNodeType* post_start = NULL;
        InvertNodeType* post_end = NULL;
        uint64 nAddr;
        bool bRt;
        int post_num = 0;
        //查找缓存中是否有
        if (m_indexCacheVec[index].addr != -1)
        {
            //索引信息
            post_num = m_indexCacheVec[index].count;
            nAddr = m_indexCacheVec[index].addr;
            post_start = &(m_invertCacheVec[nAddr]);
        }
        else//从磁盘中读取
        {
            temp_vec.clear();
            //索引信息
            post_num = m_indexVec[index].count;

            //file read
            bRt = read_invert(m_fpInvert, m_indexVec[index], temp_vec, post_num);
            if (!bRt)
                return Range(NULL, NULL);

            post_start = &(temp_vec[0]);
        }
        return Range(post_start, post_start + post_num);
    }
    Range range(IndexType index, std::vector<InvertNodeType>& temp_vec) const
    {
        //检查索引坐标的有效性
        if (index < 0 || index >= m_entryNum)
        {
            return Range(NULL, NULL);
        }
        InvertNodeType* post_start = NULL;
        InvertNodeType* post_end = NULL;
        uint64 nAddr;
        bool bRt;
        int post_num = 0;
        //查找缓存中是否有
        if (m_indexCacheVec[index].addr != -1)
        {
            //索引信息
            post_num = m_indexCacheVec[index].count;
            nAddr = m_indexCacheVec[index].addr;
            post_start = &(m_invertCacheVec[nAddr]);
        }
        else//从磁盘中读取
        {
            temp_vec.clear();
            //索引信息
            post_num = m_indexVec[index].count;

            //file read
            bRt = read_invert(m_fpInvert, m_indexVec[index], temp_vec, post_num);
            if (!bRt)
                return Range(NULL, NULL);

            post_start = &(temp_vec[0]);
        }
        return Range(post_start, post_start + post_num);
    }
    /**
     * 查询id1倒排中id2对应的weight,如果找不到返回空
     * 这个就是顺序查找,如果二分请使用下面的M(i, j)
     */
    optional<ValueType> get_val(IndexType id1, KeyType id2) const
    {
        std::vector<InvertNodeType> temp_vec;
        InvertNodeType* post_start = NULL;
        int num = get_post(id1, temp_vec, post_start);
        if (num <= 0)
            return optional<ValueType > ();
        if (m_sortMethod != BY_ID || num < 5)
        {//顺序查找
            for (int i = 0; i < num; i++, post_start++)
            {
                if (id2 == post_start->first)
                    return optional<ValueType > (post_start->second);
            }
        }
        else
        {//二分查找
            int begin = 0;
            int end = num - 1;
            int middle, id;
            while (begin <= end)
            {
                middle = (begin + end) / 2;
                id = (post_start + middle)->first;
                if (id2 == id)
                {
                    return optional<ValueType > ((post_start + middle)->second);
                }
                else if (id2 < id)
                {
                    end = middle - 1;
                }
                else
                {
                    begin = middle + 1;
                }
            }
        }
        return optional<ValueType > ();
    }
    /**
     * 类似稀疏矩阵格式，用于查找 M(i,j),这个应该就是默认按照id
     * 排序的了！二分查找
     * 为了速度最优，默认有null weight
     */
    ValueType operator() (IndexType id1, KeyType id2)
    {
        std::vector<InvertNodeType> temp_vec;
        InvertNodeType* post_start = NULL;
        int num = get_post(id1, temp_vec, post_start);
        if (num <= 0)
            return m_nullWeight;
        if (num < 5)
        {
            for (int i = 0; i < num; i++, post_start++)
            {
                if (id2 == post_start->first)
                    return post_start->second;
            }
        }
        else
        {
            int begin = 0;
            int end = num - 1;
            int middle, id;
            while (begin <= end)
            {
                middle = (begin + end) / 2;
                id = (post_start + middle)->first;
                if (id2 == id)
                {
                    return (post_start + middle)->second;
                }
                else if (id2 < id)
                {
                    end = middle - 1;
                }
                else
                {
                    begin = middle + 1;
                }
            }
        }
        return m_nullWeight;
    }
    void modify(IndexType id1, KeyType id2, ValueType val)
    {
        std::vector<InvertNodeType> temp_vec;
        InvertNodeType* post_start = NULL;
        int num = get_post(id1, temp_vec, post_start);
        if (num <= 0)
            return;
        if (num < 5)
        {
            for (int i = 0; i < num; i++, post_start++)
            {
                if (id2 == post_start->first)
                    post_start->second = val;
            }
        }
        else
        {
            int begin = 0;
            int end = num - 1; //[]
            int middle, id;
            while (begin <= end)
            {
                middle = (begin + end) / 2;
                id = (post_start + middle)->first;
                if (id2 == id)
                {
                    (post_start + middle)->second = val;
                }
                else if (id2 < id)
                {
                    end = middle - 1;
                }
                else
                {
                    begin = middle + 1;
                }
            }
        }
    }
    KeyType get_index_id(IndexType index) const
    {
        return m_indexVec[index].first;
    }
    int get_posting_len(IndexType index) const
    {
        //检查索引坐标的有效性
        if (index < 0 || index >= m_entryNum)
            return 0;

        if (m_indexCacheVec[index].addr != -1)
            return m_indexCacheVec[index].count;
        else
            return m_indexVec[index].count;
    }
    L2Norm l2norm(IndexType index) const
    {
        if (index < 0 || index >= m_entryNum)
            return -1;

        if (m_indexCacheVec[index].addr != -1)
            return m_indexCacheVec[index].l2norm;
        else
            return m_indexVec[index].l2norm;
    }
    L1Norm l1norm(IndexType index) const
    {
        if (index < 0 || index >= m_entryNum)
            return -1;

        if (m_indexCacheVec[index].addr != -1)
            return m_indexCacheVec[index].l1norm;
        else
            return m_indexVec[index].l1norm;
    }
    std::string get_invert_filename() const
    {
        return m_invertfileName;
    }
    /**
     * 这个应该是内部调用的,只提供给类似sim_calc.h用，需要逐个加入索引
     * 返回下个add_index 需要输入的写入倒排文件地址。add_index 不涉及缓存make cache.
     *
     * 例如在 sim_calc.h中，建立相似词的索引，我们是逐个的到每个词的相似词存在一个词组中的
     *  invert.set_dir("my_index");
     *  
     * 1. invert.set_file(indexfile, invertfile)   //确定倒排索引和倒排文件的名字
     * 2. File* fp_invert = fopen(invert.get_invert_filename(), "wb"))
     *     from = 0;
     * 3  foreach phrase_id
     *           get similar phrase to post_vec
     *           from = invert.add_posting(post_vec, phrase_id, from, fp_invert, max_num)  //from是相对位置，倒排文件中的
     *     fclose(fp_invert)
     * 4. invert.write_index()  //写索引文件，倒排文件已经在add_index过程中写好了
     *
     *  TODO remove File*?
     */
    bool add_posting_init(const string& dir)
    {
        set_dir(dir);
        m_fpInvert = NULL;
        if (m_bPersitant)
        {
            m_fpInvert = fopen(m_invertfileName.c_str(), "wb");
            if (!m_fpInvert)
            {
                LOG_ERROR("Open %s fail", m_invertfileName.c_str());
                return false;
            }
        }
        return true;
    }
    bool add_posting_finalize()
    {
        bool ret = true;
        m_entryNum = m_indexVec.size(); //do not forget this!
        if (m_bNeedCache)
        {
            make_inverted_cache(); //need m_fpInvert
        }
        if (m_bPersitant)
        {//如果持久化，则写索引
            ret = write_index();
        }
        if (m_fpInvert)
        {
            fclose(m_fpInvert);
            m_fpInvert = NULL;
        }
        return ret;
    }
    /**
     * 注意外部调用者需要保证顺序写。。。 index 0,1, 2....
     */
    template<typename _Iter>
    void add_posting(IndexType index, _Iter biter, _Iter eiter)
    {
        static uint64 from = 0;
        static IndexType now_pos = 0; //现在本应该处理的index 下标
        IndexNodeType strIndexNode; //内存中的MapID索引节点
        IndexNodeType strIndexNode_Cache; //缓存索引节点
        InvertNodeType strInvertNode; //购买记录节点
        L2NormType nTotalWeight = 0;
        L1NormType l1norm = 0;
        int post_size = eiter - biter;
        for (_Iter iter = biter; iter != eiter; ++iter)
        {
            nTotalWeight += iter->second * iter->second;
            l1norm += iter->second;
        }

        for (; now_pos < index; now_pos++)
        {
            strIndexNode.addr = from * sizeof (InvertNodeType);
            strIndexNode.count = 0;
            strIndexNode.l2norm = 0;
            strIndexNode.l1norm = 0;

            strIndexNode_Cache.first = now_pos;
            strIndexNode_Cache.addr = -1;
            strIndexNode_Cache.count = strIndexNode.count;
            strIndexNode_Cache.l2norm = strIndexNode.l2norm;
            strIndexNode_Cache.l1norm = strIndexNode.l1norm;

            m_oifVisitor(strIndexNode, strIndexNode_Cache);
            m_indexVec.push_back(strIndexNode);
            m_indexCacheVec.push_back(strIndexNode_Cache);
        }

        strIndexNode.addr = from * sizeof (InvertNodeType); //ADDR
        strIndexNode.count = post_size; //购买的商品个数
        strIndexNode.l2norm = (DP) (sqrt(nTotalWeight));
        strIndexNode.l1norm = l1norm;

        //cache
        strIndexNode_Cache.first = index;
        strIndexNode_Cache.addr = -1;
        strIndexNode_Cache.count = strIndexNode.count;
        strIndexNode_Cache.l2norm = strIndexNode.l2norm;
        strIndexNode_Cache.l1norm = strIndexNode.l1norm;

        m_oifVisitor(strIndexNode, strIndexNode_Cache);
        m_indexVec.push_back(strIndexNode);
        m_indexCacheVec.push_back(strIndexNode_Cache);

        //写倒排文件
        if (m_bPersitant)
        {
            fwrite(&(*biter), sizeof (InvertNodeType), strIndexNode.count, m_fpInvert);
        }
        if (m_bNeedCache) //一般是 need cache and persistant 不可能不是persitant不用写文件，同时不写内存那神马也不做
        {//如果仅仅为了存到硬盘 不需要内存cache,这里为了逻辑简单，默认都会内存缓存，可控制的是是否写硬盘索引 TODO!是否内存缓存加开关 FIXME
            //注意如果你设定了不写倒排文件，那么你要自己保证内存中完全能装下，你设定的invert可用的内存限制大小就不起限制作用了
            //内存中保留 如果没有超过cache
            if ((m_invertCacheVec.size() + strIndexNode.count) * sizeof (InvertNodeType) <= InvertCacheSize)
            {
                m_indexCacheVec[m_indexCacheVec.size() - 1].addr = m_invertCacheVec.size(); //支持实时内存索引,注意和后面的make_inverted_cache重复了TODO
                std::copy(biter, eiter, std::back_inserter(m_invertCacheVec));
            }
        }

        from += strIndexNode.count;
        now_pos++; //advace you pos ,do not forget
    }
    /**
     * 本函数废弃
     */
    uint64 add_posting(const std::vector<InvertNodeType>& post_vec, IndexType index, uint64 from, FILE* fp_invert,
            size_t max_num = std::numeric_limits<size_t>::max())
    {
        IndexNodeType strIndexNode; //内存中的MapID索引节点
        IndexNodeType strIndexNode_Cache; //缓存索引节点
        InvertNodeType strInvertNode; //购买记录节点

        int post_size = std::min(post_vec.size(), max_num);

        typedef typename InvertNodeType::L2NormType L2NormType;
        L2NormType nTotalWeight = 0;
        L1NormType l1norm = 0;
        for (size_t i = 0; i < post_size; i++)
        {
            nTotalWeight += post_vec[i].second * post_vec[i].second;
            l1norm += post_vec[i].second;
        }
        nTotalWeight = (DP) (sqrt(nTotalWeight));

        strIndexNode.addr = from * sizeof (InvertNodeType); //ADDR
        strIndexNode.count = post_size; //购买的商品个数
        strIndexNode.l2norm = nTotalWeight;
        strIndexNode.l1norm = l1norm;

        m_indexVec.push_back(strIndexNode);

        //cache
        strIndexNode_Cache.first = index;
        strIndexNode_Cache.addr = -1;
        strIndexNode_Cache.count = strIndexNode.count;
        strIndexNode_Cache.l2norm = strIndexNode.l2norm;
        strIndexNode_Cache.l1norm = strIndexNode.l1norm;

        m_indexCacheVec.push_back(strIndexNode_Cache);

        //写倒排文件
        if (m_bPersitant)
        {
            if (post_size > 0)
                fwrite(&post_vec[0], sizeof (InvertNodeType), strIndexNode.count, fp_invert);
        }

        from += strIndexNode.count;
        return from;
    }

    //    //private:
    //public:
    ///载入索引,gcc4.1.4还不支持默认函数模板参数（如果支持template <typename IndexType = IndexNodeType>)
    ///采用模板为了适应别的程序写好的索引可能参数顺序或者个数不同
    ///但是都有id和count
    ///load之前请确保索引结构不存在或者被清空
    template <typename _IndexNodeType>
    bool load_inverted_index()
    {
        m_indexVec.reserve(m_entryNum); //为C2P索引分配内存
        m_indexCacheVec.reserve(m_entryNum);
        vector<_IndexNodeType> tempinfo;
        //index可以全部读到内存
        if (!read_vec(m_indexfileName, tempinfo))
        {
            LOG_ERROR("Can not open index file %s", m_indexfileName.c_str());
            return false;
        }
        //cout << "new mem using " << timer.elapsed() << " " << cache_size << endl;
        //实验结果40M好像直接堆栈溢出了，只能动态开辟，一次从文件读出到缓存用上面的毕用下面的
        //vector快很多
        //_IndexNodeType tempinfo[cache_size];  //notice for speed may be wrong for big! FIXME
        //std::vector<_IndexNodeType> tempinfo;
        //tempinfo.resize(cache_size);
        IndexNodeType strIndexNode; //内存中的MapID索引节点
        IndexNodeType strIndexNode_Cache; //缓存索引节点

        int num = (int) tempinfo.size();
        uint64 from = 0;
        int nPid = 0;

        for (int i = 0; i < num; i++)
        {
            //不存在,标记为空
            if (nPid != tempinfo[i].first)
            {
                //cout << "This really happens?  no postlist for " << nPid << endl;
                for (int j = 0; j < tempinfo[i].first - nPid; j++)
                {
                    strIndexNode.addr = from * sizeof (InvertNodeType);
                    strIndexNode.count = 0;
                    strIndexNode.l2norm = 0;
                    strIndexNode.l1norm = 0;
                    m_indexVec.push_back(strIndexNode);

                    strIndexNode_Cache.first = nPid + j;
                    strIndexNode_Cache.addr = -1;
                    strIndexNode_Cache.count = strIndexNode.count;
                    strIndexNode_Cache.l2norm = strIndexNode.l2norm;
                    strIndexNode_Cache.l1norm = strIndexNode.l1norm;
                    m_indexCacheVec.push_back(strIndexNode_Cache);
                }
            }
            nPid = tempinfo[i].first;

            strIndexNode.addr = from * sizeof (InvertNodeType);
            strIndexNode.count = tempinfo[i].count;
            strIndexNode.l2norm = tempinfo[i].l2norm;
            strIndexNode.l1norm = tempinfo[i].l1norm;
            m_indexVec.push_back(strIndexNode);
            from += strIndexNode.count; //from advance

            //cache
            strIndexNode_Cache.first = nPid;
            strIndexNode_Cache.addr = -1;
            strIndexNode_Cache.count = strIndexNode.count;
            strIndexNode_Cache.l2norm = strIndexNode.l2norm;
            strIndexNode_Cache.l1norm = strIndexNode.l1norm;
            m_indexCacheVec.push_back(strIndexNode_Cache);

            nPid++; //nPid advance
        }
        m_entryNum = m_indexVec.size();

        return true;
    }
    ///不要求对于index从0开始顺序编号
    template <typename _IndexNodeType>
    bool load_inverted_index_nosequence()
    {
        FILE* fpIndex = fopen(m_indexfileName.c_str(), "rb");
        if (!fpIndex)
        {
            cout << "Open " << m_indexfileName << " failed" << endl;
            throw new int(3);
        }

        ///TODO make easy if we use the same _IndexNodeType write than read?
        //fread(&m_indexCacheVec[0], sizeof (IndexNodeType), m_indexVec.size(), fpIndex);

        m_indexVec.reserve(m_entryNum); //为C2P索引分配内存
        m_indexCacheVec.reserve(m_entryNum);

        const int cache_size = 4 * 1024;
        _IndexNodeType tempinfo[cache_size];
        // _IndexNodeType *tempinfo = new _IndexNodeType[cache_size];
        IndexNodeType strIndexNode; //内存中的MapID索引节点
        IndexNodeType strIndexNode_Cache; //缓存索引节点

        int num;
        uint64 from = 0;
        int nPid = 0;

        while (!feof(fpIndex))
        {
            num = fread(tempinfo, sizeof (_IndexNodeType), cache_size, fpIndex);
            for (int i = 0; i < num; i++)
            {

                //nPid = tempinfo[i].first;
                strIndexNode.first = tempinfo[i].first;
                strIndexNode.addr = from * sizeof (InvertNodeType);
                strIndexNode.count = tempinfo[i].count;
                strIndexNode.l2norm = tempinfo[i].l2norm;
                strIndexNode.l1norm = tempinfo[i].l1norm;
                m_indexVec.push_back(strIndexNode);
                from += strIndexNode.count; //from advance

                //cache
                strIndexNode_Cache.first = nPid;
                strIndexNode_Cache.addr = -1;
                strIndexNode_Cache.count = strIndexNode.count;
                strIndexNode_Cache.l2norm = strIndexNode.l2norm;
                strIndexNode_Cache.l1norm = strIndexNode.l1norm;
                m_indexCacheVec.push_back(strIndexNode_Cache);

                nPid++; //nPid advance
            }

            if (num < cache_size)
                break;

            memset(tempinfo, 0, (sizeof (_IndexNodeType)) * cache_size); //清零
        }

        m_entryNum = m_indexVec.size();

        //delete [] tempinfo;
        if (fpIndex)
        {
            fclose(fpIndex);
            fpIndex = NULL;
        }
        return true;
    }
    /**
     * 建立索引，并将倒排写入文件
     * 显然用BigVec代码更简洁可以避免循环中的麻烦的缓冲及判断避免基于内存和硬盘写两个函数，但是由于潜在的不稳定因素暂时不改变
     * 问题是默认绑定了l1norm,l2norm 如果应用不需要 可以配置去掉 不计算吗
     */
    bool make_inverted_index()
    {
        LOG_TRACE("Make invert index start from disk");
        FILE *fpCP, *fpInvert;
        if ((fpCP = fopen(m_sortedfileName.c_str(), "rb")) == NULL)
        {
            cerr << "open " << m_sortedfileName << " FATAL!" << endl;
            return false;
        }

        if ((fpInvert = fopen(m_invertfileName.c_str(), "wb")) == NULL)
        {
            cerr << "create " << m_invertfileName << " FATAL!" << endl;
            return false;
        }

        const int cache_size = 4 * 1024; //4k *  cache
        SortNodeType tempinfo[cache_size];
        m_indexVec.reserve(m_entryNum);
        m_indexCacheVec.reserve(m_entryNum);

        IndexNodeType strIndexNode;
        IndexNodeType strIndexNode_Cache;
        vector<InvertNodeType> vecTmpCPList;
        vecTmpCPList.reserve(1024);
        InvertNodeType strInvertNode;

        int nCustID_old = 0;
        L2NormType nTotalWeight = 0;
        L1NormType l1norm = 0;
        int a;
        uint64 from = 0;

        while (!feof(fpCP))
        {
            a = fread(&tempinfo[0], sizeof ( SortNodeType), cache_size, fpCP);

            int i = 0;
            while (i < a)
            {
                if (nCustID_old < tempinfo[i].pid && vecTmpCPList.size() > 0)
                { //added 11.04.20 当恰好你上次i == a break继续读文本而恰好 tempinfo[i+1].pid变大了。。
                    strIndexNode.addr = from * sizeof (InvertNodeType);
                    strIndexNode.count = vecTmpCPList.size();
                    strIndexNode.l2norm = sqrt(nTotalWeight);
                    strIndexNode.l1norm = l1norm;

                    //cache
                    strIndexNode_Cache.first = nCustID_old;
                    strIndexNode_Cache.addr = -1;
                    strIndexNode_Cache.count = strIndexNode.count;
                    strIndexNode_Cache.l2norm = strIndexNode.l2norm;
                    strIndexNode_Cache.l1norm = strIndexNode.l1norm;

                    m_oifVisitor(strIndexNode, strIndexNode_Cache);
                    m_indexVec.push_back(strIndexNode);
                    m_indexCacheVec.push_back(strIndexNode_Cache);

                    //写倒排文件
                    //                    fwrite(&vecTmpCPList[0], sizeof (InvertNodeType), strIndexNode.count, fpInvert);
                    //写倒排文件,因为我们已经知道可以在内存中存储，所以只有需要记录到硬盘我们才写
                    if (m_bPersitant)
                    {
                        fwrite(&vecTmpCPList[0], sizeof (InvertNodeType), strIndexNode.count, fpInvert);
                    }
                    //                else
                    if (m_bNeedCache)
                    { //change 11.05.19
                        //内存中保留 如果没有超过cache
                        if ((vecTmpCPList.size() + m_invertCacheVec.size()) * sizeof (InvertNodeType) <= InvertCacheSize)
                            std::copy(vecTmpCPList.begin(), vecTmpCPList.end(), std::back_inserter(m_invertCacheVec));
                    }
                    vecTmpCPList.clear();
                    nTotalWeight = 0;
                    l1norm = 0;
                    nCustID_old++;
                    from += strIndexNode.count;
                }

                while (nCustID_old < tempinfo[i].pid)
                {
                    //倒排索引
                    strIndexNode.addr = from * sizeof (InvertNodeType);
                    //strIndexNode.count = vecTmpCPList.size();
                    strIndexNode.count = 0;
                    strIndexNode.l2norm = nTotalWeight;
                    strIndexNode.l1norm = l1norm;

                    //cache
                    strIndexNode_Cache.first = nCustID_old;
                    strIndexNode_Cache.addr = -1;
                    strIndexNode_Cache.count = strIndexNode.count;
                    strIndexNode_Cache.l2norm = nTotalWeight;
                    strIndexNode_Cache.l1norm = l1norm;

                    m_oifVisitor(strIndexNode, strIndexNode_Cache);
                    m_indexVec.push_back(strIndexNode);
                    m_indexCacheVec.push_back(strIndexNode_Cache);

                    nCustID_old++;
                }

                //---------------------------------------------nCustID_old == tempinfo[i].pid
                //添加该顾客的购买列表
                while (i < a && nCustID_old == tempinfo[i].pid)
                {
                    inverted::copy(tempinfo[i], strInvertNode);
                    nTotalWeight += tempinfo[i].second * tempinfo[i].second;
                    l1norm += tempinfo[i].second;
                    vecTmpCPList.push_back(strInvertNode);
                    i++;
                }

                if (i == a) //FIXME
                    break;
                if (vecTmpCPList.size() > 0)
                {

                    strIndexNode.addr = from * sizeof (InvertNodeType);
                    strIndexNode.count = vecTmpCPList.size();
                    strIndexNode.l2norm = sqrt(nTotalWeight);
                    strIndexNode.l1norm = l1norm;

                    //cache
                    strIndexNode_Cache.first = nCustID_old;
                    strIndexNode_Cache.addr = -1;
                    strIndexNode_Cache.count = strIndexNode.count;
                    strIndexNode_Cache.l2norm = strIndexNode.l2norm;
                    strIndexNode_Cache.l1norm = strIndexNode.l1norm;

                    m_oifVisitor(strIndexNode, strIndexNode_Cache);
                    m_indexVec.push_back(strIndexNode);
                    m_indexCacheVec.push_back(strIndexNode_Cache);

                    //写倒排文件
                    //                    fwrite(&vecTmpCPList[0], sizeof (InvertNodeType), strIndexNode.count, fpInvert);
                    //写倒排文件,因为我们已经知道可以在内存中存储，所以只有需要记录到硬盘我们才写
                    if (m_bPersitant)
                    {
                        fwrite(&vecTmpCPList[0], sizeof (InvertNodeType), strIndexNode.count, fpInvert);
                    }
                    //                else
                    if (m_bNeedCache)
                    { //change 11.05.19
                        //内存中保留 如果没有超过cache
                        if ((vecTmpCPList.size() + m_invertCacheVec.size()) * sizeof (InvertNodeType) <= InvertCacheSize)
                            std::copy(vecTmpCPList.begin(), vecTmpCPList.end(), std::back_inserter(m_invertCacheVec));
                    }
                    vecTmpCPList.clear();
                    nTotalWeight = 0;
                    l1norm = 0;
                    nCustID_old++;
                    from += strIndexNode.count;
                }

            }

            if (a < cache_size)
                break;
        }

        if (vecTmpCPList.size() > 0)
        {
            strIndexNode.addr = from * sizeof (InvertNodeType);
            strIndexNode.count = vecTmpCPList.size();
            strIndexNode.l2norm = sqrt(nTotalWeight);
            strIndexNode.l1norm = l1norm;

            //cache
            strIndexNode_Cache.first = nCustID_old;
            strIndexNode_Cache.addr = -1;
            strIndexNode_Cache.count = strIndexNode.count;
            strIndexNode_Cache.l2norm = strIndexNode.l2norm;
            strIndexNode_Cache.l1norm = strIndexNode.l1norm;

            m_oifVisitor(strIndexNode, strIndexNode_Cache);
            m_indexVec.push_back(strIndexNode);
            m_indexCacheVec.push_back(strIndexNode_Cache);

            //写倒排文件
            //            fwrite(&vecTmpCPList[0], sizeof (InvertNodeType), strIndexNode.count, fpInvert);
            //写倒排文件,因为我们已经知道可以在内存中存储，所以只有需要记录到硬盘我们才写
            if (m_bPersitant)
            {
                fwrite(&vecTmpCPList[0], sizeof (InvertNodeType), strIndexNode.count, fpInvert);
            }
            //                else
            if (m_bNeedCache)
            { //change 11.05.19
                //内存中保留 如果没有超过cache
                if ((vecTmpCPList.size() + m_invertCacheVec.size()) * sizeof (InvertNodeType) <= InvertCacheSize)
                    std::copy(vecTmpCPList.begin(), vecTmpCPList.end(), std::back_inserter(m_invertCacheVec));
            }
            vecTmpCPList.clear();
            nTotalWeight = 0;
            l1norm = 0;
            nCustID_old++;
            from += strIndexNode.count;
        }

        m_entryNum = m_indexVec.size();

        if (fpCP)
        {
            fclose(fpCP);
            fpCP = NULL;
        }
        if (fpInvert)
        {
            fclose(fpInvert);
            fpInvert = NULL;
        }
        return true;
    }
    /**
     * 建立索引功能同上，但是是从内存中的一个vector中读取数据，而不是从sorted file中读取
     * 注意这个vector要求是按照<index_id, invert_id, weight> 排好序的
     * TODO 和上面的代码重复~
     * 注意只有这种情况并且是!isPersitant我们才不写文件 10/07/06 add 支持直接完全内存不写文件
     */
    bool make_inverted_index(const std::vector<SortNodeType>& tempinfo)
    {
        LOG_TRACE("Make invert index start all in mem");
        FILE *fpInvert = NULL;

        fpInvert = fopen(m_invertfileName.c_str(), "wb");

        if (!fpInvert)
        {
            LOG_WARNING("Open %s failed", m_invertfileName.c_str());
            return false;
        }

        m_indexVec.reserve(m_entryNum);
        m_indexCacheVec.reserve(m_entryNum);

        IndexNodeType strIndexNode;
        IndexNodeType strIndexNode_Cache;
        vector<InvertNodeType> vecTmpCPList;
        vector<InvertNodeType> vecCPList;
        vecTmpCPList.reserve(1024);
        InvertNodeType strInvertNode;

        int nCustID_old = 0;
        L2NormType nTotalWeight = 0;
        L1NormType l1norm = 0;
        uint64 from = 0;

        size_t i = 0;
        size_t size = tempinfo.size();
        while (i < size)
        {
            while (nCustID_old < tempinfo[i].pid)
            {
                //倒排索引
                strIndexNode.addr = from * sizeof (InvertNodeType);
                strIndexNode.count = 0;
                strIndexNode.l2norm = nTotalWeight;
                strIndexNode.l1norm = l1norm;

                //cache
                strIndexNode_Cache.first = nCustID_old;
                strIndexNode_Cache.addr = -1;
                strIndexNode_Cache.count = strIndexNode.count;
                strIndexNode_Cache.l2norm = nTotalWeight;
                strIndexNode_Cache.l1norm = l1norm;

                m_oifVisitor(strIndexNode, strIndexNode_Cache);
                m_indexVec.push_back(strIndexNode);
                m_indexCacheVec.push_back(strIndexNode_Cache);

                nCustID_old++;
            }

            //添加该顾客的购买列表
            while (i < size && nCustID_old == tempinfo[i].pid) //id < size must at first 10.05.19
            {
                inverted::copy(tempinfo[i], strInvertNode);
                nTotalWeight += tempinfo[i].second * tempinfo[i].second;
                l1norm += tempinfo[i].second;
                vecTmpCPList.push_back(strInvertNode);
                i++;
            }
            if (vecTmpCPList.size() > 0)
            {
                strIndexNode.addr = from * sizeof (InvertNodeType);
                strIndexNode.count = vecTmpCPList.size();
                strIndexNode.l2norm = sqrt(nTotalWeight);
                strIndexNode.l1norm = l1norm;
                //cache
                strIndexNode_Cache.first = nCustID_old;
                strIndexNode_Cache.addr = -1;
                strIndexNode_Cache.count = strIndexNode.count;

                strIndexNode_Cache.l2norm = strIndexNode.l2norm;
                strIndexNode_Cache.l1norm = strIndexNode.l1norm;

                m_oifVisitor(strIndexNode, strIndexNode_Cache);
                m_indexVec.push_back(strIndexNode);
                m_indexCacheVec.push_back(strIndexNode_Cache);

                //写倒排文件,因为我们已经知道可以在内存中存储，所以只有需要记录到硬盘我们才写
                if (m_bPersitant)
                {
                    fwrite(&vecTmpCPList[0], sizeof (InvertNodeType), strIndexNode.count, fpInvert);
                }
                //                else
                if (m_bNeedCache)
                { //change 11.05.19
                    //内存中保留 如果没有超过cache 
                    if ((vecTmpCPList.size() + m_invertCacheVec.size()) * sizeof (InvertNodeType) <= InvertCacheSize)
                        std::copy(vecTmpCPList.begin(), vecTmpCPList.end(), std::back_inserter(m_invertCacheVec));
                }
                vecTmpCPList.clear();
                nTotalWeight = 0;
                l1norm = 0;
                nCustID_old++;
                from += strIndexNode.count;
            }
        }
        //TODO remove it! Where creating we must tell how many entries are
        m_entryNum = m_indexVec.size();
        //clear
        if (fpInvert)
        {
            fclose(fpInvert);
            fpInvert = NULL;
        }
        return true;
    }
    /**
     *  目前主要是为了使用BigVec help implement
     *
     * FIXME Using const Vector& tempinfo; Iter iter = tempinfo.begin(); will cause FATAL
     * 1262: FATAL: passing ‘const BigVec<invert::ST_PidKidInfo, invert::CmpSTNodeWeight>’
     * as ‘this’ argument of ‘bigvec_iterator<BigVec<_Node, _Cmp>, _Node> BigVec<_Node, _Cmp>::begin()
     *  [with _Node = invert::ST_PidKidInfo, _Cmp = invert::CmpSTNodeWeight]’ discards qualifiers
     *
     * FIXME temply remove const!!
     * Depreated bigvec may have bug so currently not used!  暂时废弃！！
     */
    template<typename Vector>
    void make_inverted_index_bigvec(Vector & tempinfo)
    {
        FILE *fpInvert = NULL;

        fpInvert = fopen(m_invertfileName.c_str(), "wb");
        if (!fpInvert)
            LOG_WARNING("Open %s failed", m_invertfileName.c_str());

        typedef typename Vector::iterator Iter;

        m_indexVec.reserve(m_entryNum);
        m_indexCacheVec.reserve(m_entryNum);

        IndexNodeType strIndexNode;
        IndexNodeType strIndexNode_Cache;
        vector<InvertNodeType> vecTmpCPList;
        vector<InvertNodeType> vecCPList;
        vecTmpCPList.reserve(1024);
        InvertNodeType strInvertNode;

        int nCustID_old = 0;
        typedef typename InvertNodeType::L2NormType L2NormType;
        L2NormType nTotalWeight = 0;
        L1NormType l1norm = 0;
        uint64 from = 0;

        Iter iter = tempinfo.begin();
        Iter iter_end = tempinfo.end();
        while (iter != iter_end)
        {
            while (nCustID_old < iter->pid)
            {
                //倒排索引
                strIndexNode.addr = from * sizeof (InvertNodeType);
                strIndexNode.count = 0;
                strIndexNode.l2norm = nTotalWeight;
                strIndexNode.l1norm = l1norm;

                //cache
                strIndexNode_Cache.first = nCustID_old;
                strIndexNode_Cache.addr = -1;
                strIndexNode_Cache.count = strIndexNode.count;
                strIndexNode_Cache.l2norm = nTotalWeight;
                strIndexNode_Cache.l1norm = l1norm;

                m_oifVisitor(strIndexNode, strIndexNode_Cache);
                m_indexVec.push_back(strIndexNode);
                m_indexCacheVec.push_back(strIndexNode_Cache);

                nCustID_old++;
            }

            //---------------------------------------------nCustID_old == tempinfo[i].pid
            //添加该顾客的购买列表
            while (iter != iter_end && nCustID_old == iter->pid) //id < size must at first 10.05.19
            {
                inverted::copy(*iter, strInvertNode);
                nTotalWeight += iter->second * iter->second;
                l1norm += iter->second;
                vecTmpCPList.push_back(strInvertNode);
                ++iter;
            }
            if (vecTmpCPList.size() > 0)
            {
                strIndexNode.addr = from * sizeof (InvertNodeType);
                strIndexNode.count = vecTmpCPList.size();
                strIndexNode.l2norm = sqrt(nTotalWeight);
                strIndexNode.l1norm = l1norm;

                //cache
                strIndexNode_Cache.first = nCustID_old;
                strIndexNode_Cache.addr = -1;
                strIndexNode_Cache.count = strIndexNode.count;
                strIndexNode_Cache.l2norm = strIndexNode.l2norm;
                strIndexNode_Cache.l1norm = strIndexNode.l1norm;

                m_oifVisitor(strIndexNode, strIndexNode_Cache);
                m_indexVec.push_back(strIndexNode);
                m_indexCacheVec.push_back(strIndexNode_Cache);

                //写倒排文件,因为我们已经知道可以在内存中存储，所以只有需要记录到硬盘我们才写
                if (m_bPersitant)
                {
                    fwrite(&vecTmpCPList[0], sizeof (InvertNodeType), strIndexNode.count, fpInvert);
                }
                //                else
                if (m_bNeedCache)
                { //change 11.05.19
                    //内存中保留 如果没有超过cache
                    if ((vecTmpCPList.size() + m_invertCacheVec.size()) * sizeof (InvertNodeType) <= InvertCacheSize)
                        std::copy(vecTmpCPList.begin(), vecTmpCPList.end(), std::back_inserter(m_invertCacheVec));
                }
                vecTmpCPList.clear();
                nTotalWeight = 0;
                l1norm = 0;
                nCustID_old++;
                from += strIndexNode.count;
            }
        }
        //TODO remove it! Where creating we must tell how many entries are
        m_entryNum = m_indexVec.size();
        //clear
        if (fpInvert)
        {
            fclose(fpInvert);
            fpInvert = NULL;
        }
    }
    /**
     * 建立内存中的索引和倒排cache
     * 当前采用 simple cache
     * 考虑提供多种cahe 机制 TODO
     *
     */
    bool update_cache()
    {
        IndexType index = m_inMemEndIndex;
        assert(m_indexCacheVec[index - 1].addr != -1 && m_indexCacheVec[index].addr == -1);
        int nFrom = m_indexCacheVec[index - 1].addr + m_indexCacheVec[index - 1].count;
        uint64 nCurInvertCacheSize = 0;
        IndexType i = index;
        for (; i < m_entryNum; i++)
        {
            //判断内存cache有没有剩余空间
            int nCount = m_indexCacheVec[i].count;
            int nLength = nCount * sizeof (InvertNodeType);

            if ((nCurInvertCacheSize + nLength) > InvertCacheSize) //大小超过预定内存限制
            {
                break;
            }
            else
            {
                m_indexCacheVec[i].addr = nFrom;
                nFrom += nCount;
                nCurInvertCacheSize += nLength;
            }
        }
        m_inMemStartIndex = index;
        m_inMemEndIndex = i;
        m_invertCacheVec.resize(nFrom);
        if (fseek(m_fpInvert, m_indexVec[index].addr, 0) == -1)
            return false;
        fread(&m_invertCacheVec[0], sizeof (InvertNodeType), nFrom, m_fpInvert); //第一次读取m_fpInvert
    }
    void make_inverted_cache()
    {
        int64 nCurInvertCacheSize = 0;
        int64 nFrom = 0;
        bool allInMem = true;
        IndexType i = 0;
        for (; i < m_entryNum; i++)
        {
            //判断内存cache有没有剩余空间
            int nCount = m_indexCacheVec[i].count;
            int nLength = nCount * sizeof (InvertNodeType);

            if ((nCurInvertCacheSize + nLength) > InvertCacheSize) //大小超过预定内存限制
            {
                allInMem = false;
                break;
            }
            else
            {
                m_indexCacheVec[i].addr = nFrom;
                nFrom += nCount;
                nCurInvertCacheSize += nLength;
            }
        }
        m_inMemStartIndex = 0;
        m_inMemEndIndex = i;

        //将所有需要CACHE到倒排数据读入CACHE
        //TODO all try c++ style ? copy   TODO 错误处理, 全用异常？
        if (m_invertCacheVec.empty())
        {
            m_invertCacheVec.resize(nFrom);
            fread(&m_invertCacheVec[0], sizeof (InvertNodeType), nFrom, m_fpInvert); //第一次读取m_fpInvert
        }
        else
        {
            //LOG(WARNING) << "Not write the invert to the disk for invert is small and we do not need persit" << endl;
        }

        if (allInMem) //如果全在内存，可以关闭打开的倒排文件
        {
            LOG_INFO("All invert is in mem");
            m_bAllInMem = true;
            if (m_fpInvert)
            {
                fclose(m_fpInvert);
                m_fpInvert = NULL;
            }
        }
        else
        {
            LOG_WARNING("Not all invert is in mem");
        }
    }
    /**从排好序的文本中读取数据，建立倒排索引*/
    bool create_inverted_index()
    {
        //可能需要清空，比如re sort之后再建立倒排
        clear_cache();

        //建立倒排表，倒排post list被写入文件
        make_inverted_index();

        //打开倒排文件
        m_fpInvert = fopen(m_invertfileName.c_str(), "rb");

        if (!m_fpInvert)
        {
            LOG_FATAL("Open %s failed", m_invertfileName.c_str());
            return false;
        }

        //内存中缓存cache
        if (m_bNeedCache)
            make_inverted_cache();

        //索引结构,被写入文件
        if (m_bPersitant)
        {
            if (!write_index())
            {
                LOG_ERROR("write index fail");
                return false;
            }
        }
        return true;
    }
    bool create_inverted_index(std::vector<SortNodeType>& vec)
    {
        //可能需要清空，比如re sort之后再建立倒排
        clear_cache();

        //建立倒排表，倒排post list被写入文件
        make_inverted_index(vec);

        //打开倒排文件
        m_fpInvert = fopen(m_invertfileName.c_str(), "rb");
        if (!m_fpInvert)
        {
            LOG_FATAL("Open %s failed", m_invertfileName.c_str());
            return false;
        }

        //内存中缓存cache
        if (m_bNeedCache)
            make_inverted_cache();

        //索引结构,被写入文件
        if (m_bPersitant)
        {
            if (!write_index())
                return false;
        }
        return true;
    }
    /**
     * FIXME 为什么invert_table_creator 调用的时候,m_invertTable->create(m_tripleVec, m_indexfile.c_str(), m_invertfile.c_str());
     * 编译也会选择走下面的分支而不是选择上面的
     * 暂时废弃
     */
    template<typename Vector>
    void create_inverted_index_bigvec(Vector & vec)
    {
        //可能需要清空，比如re sort之后再建立倒排
        clear_cache();

        //建立倒排表，倒排post list被写入文件
        make_inverted_index_bigVec(vec);

        //打开倒排文件
        m_fpInvert = fopen(m_invertfileName.c_str(), "rb");
        //LOG_IF(FATAL, !m_fpInvert) << "open " << m_invertfileName << "failed" << endl;

        //内存中缓存cache
        make_inverted_cache();

        //索引结构,被写入文件
        if (m_bPersitant)
        {
            if (!write_index())
                return false;
        }
    }

    //--------------------------helper func for 序列化
    bool is_all_in_mem()
    {
        return m_bAllInMem;
    }
    bool open_inverted_file()
    {
        if ((m_fpInvert = fopen(m_invertfileName.c_str(), "rb")) == NULL)
        {
            return false;
        }
    }
    void set_inverted_file(const char* filename)
    {
        m_invertfileName = filename;
    }
    void set_inverted_file(const std::string & filename)
    {
        m_invertfileName = filename;
    }
    static void set_cache_size(int64 sort_size, int64 invert_size)
    {
        SortCacheSize = sort_size;
        InvertCacheSize = invert_size;
    }
    static void set_invert_cache_size(int64 invert_size)
    {
        InvertCacheSize = invert_size;
    }
    static void set_sort_cache_size(int64 sort_size)
    {
        SortCacheSize = sort_size;
    }
    void set_sort_method(SortMethod sort_method)
    {
        m_sortMethod = sort_method;
    }
    SortMethod sort_method()
    {
        return m_sortMethod;
    }
    uint64 invert_size()
    {
        return m_invertSize;
    }
    IndexNodeType & index_node(IndexType index)
    {
        return m_indexVec[index];
    }
    vector<IndexNodeType>& index_vec()
    {
        return m_indexVec;
    }
    IndexType inmem_end_index()
    {
        return m_inMemEndIndex;
    }
    IndexType inmem_start_index()
    {
        return m_inMemStartIndex;
    }
private:
    DISALLOW_COPY_AND_ASSIGN(InvertedIndex);
    std::string m_infileName;
    std::string m_sortedfileName;
    std::string m_indexfileName;
    std::string m_invertfileName;
    std::string m_dir;

    ///内存映射中的倒排索引
    vector<IndexNodeType> m_indexVec;

    ///内存缓冲区
    vector<IndexNodeType> m_indexCacheVec;
    mutable vector< InvertNodeType> m_invertCacheVec;

    ///查找post时候某些接口需要内部利用的空间，注意如果使用则多线程不安全
    vector<InvertNodeType> m_tempVec;
    IndexType m_tempIndex; //标记当前temp存储的是哪个index对应的内容

    IndexType m_inMemStartIndex;
    IndexType m_inMemEndIndex; ///标记当前在外存中的索引最小编号，用于顺序读取大索引时候的更新cache

    IndexType m_entryNum; ///table 的entrie 数目 == clse_vecIndex.size()

    FILE *m_fpInvert; ///倒排文件指针，在建立好倒排索引之后打开

    bool m_bAllInMem; ///标记是否全在cache中，make cache会决定该标记位，如果全在不需要打开倒排文件
    bool m_bPersitant; ///是否需要在硬盘保存索引
    bool m_bNeedCache; ///是否需要内存cache索引，如果不需要就是只为了写invert,index存盘而已

    SortMethod m_sortMethod;

    ValueType m_nullWeight; //无效weight,默认值是0 可设置

    uint64 m_invertSize;

    const _OIFVisitor& m_oifVisitor;

public:
    static int64 SortCacheSize; ///外部归并时的cache大小
    static int64 InvertCacheSize; ///最终生成倒排的时候在内存中的倒排的cache大小
}; //---end of class InvertTable

//FIXME 这里是个GCC BUG？ 为啥我用InvertTable<>显示初始化的数值分别是47M和602M呢
template <class T, template<typename E> class U, template<typename E2, typename F2> class V, class L, class M, class N>
int64 InvertedIndex<T, U, V, L, M, N>::SortCacheSize = 16 * (int64) 1024 * 1024 * 1024; //5G

template <class T, template<typename E> class U, template<typename E2, typename F2> class V, class L, class M, class N>
int64 InvertedIndex<T, U, V, L, M, N>::InvertCacheSize = 16 * (int64) 1024 * 1024 * 1024; //5G

} //-------------end of namespace inverted
#endif  //----end of INVERTED_INDEX_H_
