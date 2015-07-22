/** 
 *  ==============================================================================
 * 
 *          \file      inverted_index.h
 *
 *        \author   chenghuige 
 *          
 *          \date     2010-01-31 13:53:58.446039
 *  
 *  \Description: ֧�ּ򵥵ĵ�����������������ӳ��
 *  ������std::pair ���  InvertNode ������ǰ��֤���� first second���־�����
 *
 *  TODO IndexVec IndexCacheVec�����޸� ֻ��һ��bool vec���������Ӧ�ĵ����Ƿ����ڴ��м���,
 *   Ȼ��ֻ����һ��IndexVec
 *
 * ע�ⲻҪ��������������FILE* fpָ����ͬ���ļ�������ɳ������ιرգ�Ҳû�б�Ҫʹ�ÿ�����
 *
 * TODO �������һ���򵥵�inverted_index ������l1norm l2norm ,����ļ̳������򵥵�
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
 * ���ű�
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
        { //ע������п������� ����һ���ر��� ����һ��invertҲ���ǻ᳢�Թر���Ϊ����m_fpInvert������NULL���Ի����
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
        //ɾ������Ҫ���ļ�
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
    /**�趨���ű�����Ҫ���ļ�������������ģ����������ļ����͵����ļ���*/
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

    ///��ȡ�����ļ�
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
     * ��������ļ���Ϊ���룬�������ű�Node��ʾ�ļ�����Ԫ��������
     *<phrase,ad> ����<phrase, phrase , weight>
     *����GETPID������WinnerTree_Linux.h�е�Ҫ����Ҫ�ṩ������Cmp��Node��δ�ṩ
     * ͬʱ�ṩindexfile,invertfile,sorted_file������
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
     * @param dir    ����������·�������ִ���Ĭ������ļ�������
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
    ///���溯����Ĭ�����򷽷�
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

    ///���Ѿ��ź�����ļ��н�����������
    void create(const char * sortedfile_name, const char *indexfile_name, const char* invertfile_name)
    {
        clear();
        m_indexfileName = indexfile_name;
        m_invertfileName = invertfile_name;
        m_sortedfileName = sortedfile_name;

        //do real work here
        create_inverted_index();
    }
    ///������Ϊ�˱��� void create(const char *dir, int nFreeMemSize = SortCacheSize) �ظ�
    void create2(const char* dir)
    {
        clear();
        m_dir = dir;
        m_indexfileName = m_dir + "/index.idx";
        m_invertfileName = m_dir + "/invert.idx";
        m_sortedfileName = m_dir + "/sorted.idx";

        create_inverted_index();
    }

    ///�����ڴ�ĵ�����������
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
     * ������Žṹ�Ѿ������ô洢���ļ������ȡ�����͵����ļ�
     * �������ű�
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

        //�򿪵����ļ�
        if ((m_fpInvert = fopen(m_invertfileName.c_str(), "rb")) == NULL)
        {
            LOG_ERROR("Fail to open invert file %s", m_invertfileName.c_str());
            return false;
        }

        load_inverted_index<_IndexNodeType > ();

        //�ڴ��л���cache
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

        //�򿪵����ļ�
        if ((m_fpInvert = fopen(m_invertfileName.c_str(), "rb")) == NULL)
        {
            LOG_WARNING("Open %s failed", m_invertfileName.c_str());
            return false;
        }

        load_inverted_index_nosequence<_IndexNodeType > ();

        //�ڴ��л���cache
        make_inverted_cache();
        return true;
    }


    ///�������ṹд���ļ�
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

    ///���������ٽ�������,��ʵ���ʱ�������������ǲ�����ģ���Ϊ��ʵ�Ѿ�����id������,��������ڴ�治�µ������ʱֻ�������ȽϺ���
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
     * ���趼���ڴ�Ļ� ����Ӧ�ñȽϿ�
     * ��ʱ�����Ļ� ��ô����������� ��ôֻ��temp����仯�ˣ�û��д�������ļ���TODO
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

    ///���ű�(���ú�)�ж��ٸ���ڣ������ٸ�post list
    IndexType entry_num() const
    {
        return m_entryNum;
    }
    ///��õ���size
    IndexType size() const
    {
        return m_entryNum;
    }
    /**
     * ��ȡĳ��������Ӧ�ĵ��ŵ�begin()
     * ע��Ĭ�����е���������int��ŵģ�ͨ��ӳ��,��0��elem_num -1)
     * �ⲿ��Ҫ�ṩһ����vector,��Ϊ�п��ܵ���list�����ڴ�cache�У���ʱ����Ҫ�������vector��
     * �����ⲿ��Ҫ��ʼ������ʼλ�ú�Ҫ���ĵ���listԪ����Ŀ,�������cache ��start == &(vec[0])
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
     * -1 ��ʾ����ʧ��
     * ���� >= 0 ���ز鵽����Ŀ
     */
    int get_post(IndexType index, std::vector<InvertNodeType>& temp_vec, InvertNodeType*& post_start) const
    {
        //��������������Ч��
        if (index < 0 || index >= m_entryNum)
        {
            post_start = NULL;
            return -1;
        }

        uint64 nAddr;
        bool bRt;
        int post_num = 0;
        //���һ������Ƿ���
        if (m_indexCacheVec[index].addr != -1)
        {
            //cout << "reading from cache" << endl;
            //������Ϣ
            post_num = m_indexCacheVec[index].count;
            nAddr = m_indexCacheVec[index].addr;
            post_start = &(m_invertCacheVec[nAddr]);
        }
        else//�Ӵ����ж�ȡ
        {
            //            LOG_WARNING("read post from file");
            temp_vec.clear();
            //            cout << "reading from file" << endl;
            //������Ϣ
            post_num = m_indexVec[index].count;

            //file read
            bRt = read_invert(m_fpInvert, m_indexVec[index], temp_vec, post_num);
            if (!bRt) return -1;

            post_start = &(temp_vec[0]);
        }
        return post_num;
    }
    /**
     * ��ʹ������Ϣ���ڴ���Ҳ���Ƶ�result vec
     * return false ��ʾ����ʧ��
     * �ⲿȷ��result_vecΪ��
     */
    bool get_post(IndexType index, std::vector<InvertNodeType>& result_vec) const
    {
        //��������������Ч
        if (index < 0 || index >= m_entryNum)
            return false;

        int post_num;
        uint64 nAddr;
        bool bRt;
        //���һ������Ƿ���
        if (m_indexCacheVec[index].addr != -1)
        {
            //cout << "reading from cache" << endl;
            //������Ϣ
            post_num = m_indexCacheVec[index].count;
            nAddr = m_indexCacheVec[index].addr;

            for (int i = nAddr; i < nAddr + post_num; i++)
            {
                result_vec.push_back(m_invertCacheVec[i]);
            }
        }
        else//�Ӵ����ж�ȡ
        {
            //            LOG_WARNING("read post from file");
            //������Ϣ
            post_num = m_indexVec[index].count;
            //file read
            bRt = read_invert(m_fpInvert, m_indexVec[index], result_vec, post_num);
            if (!bRt) return false;
        }
        return true;
    }
    bool get_post(IndexType index, std::vector<InvertNodeType>& result_vec, int max_len) const
    {
        //��������������Ч
        if (index < 0 || index >= m_entryNum)
            return false;

        int post_num;
        uint64 nAddr;
        bool bRt;
        //���һ������Ƿ���
        if (m_indexCacheVec[index].addr != -1)
        {
            //cout << "reading from cache" << endl;
            //������Ϣ
            post_num = m_indexCacheVec[index].count;
            post_num = std::min(post_num, max_len);
            nAddr = m_indexCacheVec[index].addr;
            for (int i = nAddr; i < nAddr + post_num; i++)
            {
                result_vec.push_back(m_invertCacheVec[i]);
            }
        }
        else//�Ӵ����ж�ȡ
        {
            //            LOG_WARNING("read post from file");
            //������Ϣ
            post_num = m_indexVec[index].count;
            post_num = std::min(post_num, max_len);
            //file read
            bRt = read_invert(m_fpInvert, m_indexVec[index], result_vec, post_num);
            if (!bRt) return false;
        }
        return true;
    }
    /**
     *  ����ĳ�������ڵ�ĵ��ţ��÷�,ע����̲߳���ȫ
     *  Range range = invert.post(i);
     * for (InvertNodeType* cur = range.first; cur != range.second; ++cur)
     * {
     *      cur->first
     *      cur->second
     * }
     */
    Range posting(IndexType index)
    {
        //��������������Ч��
        if (index < 0 || index >= m_entryNum)
        {
            return Range(NULL, NULL);
        }
        InvertNodeType* post_start = NULL;
        InvertNodeType* post_end = NULL;
        uint64 nAddr;
        bool bRt;
        int post_num = 0;
        //���һ������Ƿ���
        if (m_indexCacheVec[index].addr != -1)
        {
            //������Ϣ
            post_num = m_indexCacheVec[index].count;
            nAddr = m_indexCacheVec[index].addr;
            post_start = &(m_invertCacheVec[nAddr]);
        }
        else//�Ӵ����ж�ȡ
        {
            if (m_tempIndex == index)
            {
                post_start = &(m_tempVec[0]);
                return Range(post_start, post_start + m_tempVec.size());
            }
            m_tempVec.clear();
            //������Ϣ
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
        //��������������Ч��
        if (index < 0 || index >= m_entryNum)
        {
            return Range(NULL, NULL);
        }
        InvertNodeType* post_start = NULL;
        InvertNodeType* post_end = NULL;
        uint64 nAddr;
        bool bRt = false;
        int post_num = 0;
        //���һ������Ƿ���
        if (m_indexCacheVec[index].addr != -1)
        {
            //������Ϣ
            post_num = m_indexCacheVec[index].count;
            nAddr = m_indexCacheVec[index].addr;
            post_start = &(m_invertCacheVec[nAddr]);
        }
        else//�Ӵ����ж�ȡ
        {
            if (m_tempIndex == index)
            {
                post_start = &(m_tempVec[0]);
                return Range(post_start, post_start + m_tempVec.size());
            }
            m_tempVec.clear();
            //������Ϣ
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
     * ͬ�ϣ������±���
     */
    Range operator[](IndexType index)
    {
        InvertNodeType* post_start = NULL;
        InvertNodeType* post_end = NULL;
        uint64 nAddr;
        bool bRt;
        int post_num = 0;
        //���һ������Ƿ���
        if (m_indexCacheVec[index].addr != -1)
        {
            //������Ϣ
            post_num = m_indexCacheVec[index].count;
            nAddr = m_indexCacheVec[index].addr;
            post_start = &(m_invertCacheVec[nAddr]);
        }
        else//�Ӵ����ж�ȡ
        {
            if (m_tempIndex == index)
            {
                post_start = &(m_tempVec[0]);
                return Range(post_start, post_start + m_tempVec.size());
            }
            m_tempVec.clear();
            //������Ϣ
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
     * ͬ�ϣ��ⲿ�ṩ���ܵı��ÿռ䣬���̰߳�ȫ
     */
    Range posting(IndexType index, std::vector<InvertNodeType>& temp_vec) const
    {
        //��������������Ч��
        if (index < 0 || index >= m_entryNum)
        {
            return Range(NULL, NULL);
        }
        InvertNodeType* post_start = NULL;
        InvertNodeType* post_end = NULL;
        uint64 nAddr;
        bool bRt;
        int post_num = 0;
        //���һ������Ƿ���
        if (m_indexCacheVec[index].addr != -1)
        {
            //������Ϣ
            post_num = m_indexCacheVec[index].count;
            nAddr = m_indexCacheVec[index].addr;
            post_start = &(m_invertCacheVec[nAddr]);
        }
        else//�Ӵ����ж�ȡ
        {
            temp_vec.clear();
            //������Ϣ
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
        //��������������Ч��
        if (index < 0 || index >= m_entryNum)
        {
            return Range(NULL, NULL);
        }
        InvertNodeType* post_start = NULL;
        InvertNodeType* post_end = NULL;
        uint64 nAddr;
        bool bRt;
        int post_num = 0;
        //���һ������Ƿ���
        if (m_indexCacheVec[index].addr != -1)
        {
            //������Ϣ
            post_num = m_indexCacheVec[index].count;
            nAddr = m_indexCacheVec[index].addr;
            post_start = &(m_invertCacheVec[nAddr]);
        }
        else//�Ӵ����ж�ȡ
        {
            temp_vec.clear();
            //������Ϣ
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
     * ��ѯid1������id2��Ӧ��weight,����Ҳ������ؿ�
     * �������˳�����,���������ʹ�������M(i, j)
     */
    optional<ValueType> get_val(IndexType id1, KeyType id2) const
    {
        std::vector<InvertNodeType> temp_vec;
        InvertNodeType* post_start = NULL;
        int num = get_post(id1, temp_vec, post_start);
        if (num <= 0)
            return optional<ValueType > ();
        if (m_sortMethod != BY_ID || num < 5)
        {//˳�����
            for (int i = 0; i < num; i++, post_start++)
            {
                if (id2 == post_start->first)
                    return optional<ValueType > (post_start->second);
            }
        }
        else
        {//���ֲ���
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
     * ����ϡ������ʽ�����ڲ��� M(i,j),���Ӧ�þ���Ĭ�ϰ���id
     * ������ˣ����ֲ���
     * Ϊ���ٶ����ţ�Ĭ����null weight
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
        //��������������Ч��
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
     * ���Ӧ�����ڲ����õ�,ֻ�ṩ������sim_calc.h�ã���Ҫ�����������
     * �����¸�add_index ��Ҫ�����д�뵹���ļ���ַ��add_index ���漰����make cache.
     *
     * ������ sim_calc.h�У��������ƴʵ�����������������ĵ�ÿ���ʵ����ƴʴ���һ�������е�
     *  invert.set_dir("my_index");
     *  
     * 1. invert.set_file(indexfile, invertfile)   //ȷ�����������͵����ļ�������
     * 2. File* fp_invert = fopen(invert.get_invert_filename(), "wb"))
     *     from = 0;
     * 3  foreach phrase_id
     *           get similar phrase to post_vec
     *           from = invert.add_posting(post_vec, phrase_id, from, fp_invert, max_num)  //from�����λ�ã������ļ��е�
     *     fclose(fp_invert)
     * 4. invert.write_index()  //д�����ļ��������ļ��Ѿ���add_index������д����
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
        {//����־û�����д����
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
     * ע���ⲿ��������Ҫ��֤˳��д������ index 0,1, 2....
     */
    template<typename _Iter>
    void add_posting(IndexType index, _Iter biter, _Iter eiter)
    {
        static uint64 from = 0;
        static IndexType now_pos = 0; //���ڱ�Ӧ�ô����index �±�
        IndexNodeType strIndexNode; //�ڴ��е�MapID�����ڵ�
        IndexNodeType strIndexNode_Cache; //���������ڵ�
        InvertNodeType strInvertNode; //�����¼�ڵ�
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
        strIndexNode.count = post_size; //�������Ʒ����
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

        //д�����ļ�
        if (m_bPersitant)
        {
            fwrite(&(*biter), sizeof (InvertNodeType), strIndexNode.count, m_fpInvert);
        }
        if (m_bNeedCache) //һ���� need cache and persistant �����ܲ���persitant����д�ļ���ͬʱ��д�ڴ�������Ҳ����
        {//�������Ϊ�˴浽Ӳ�� ����Ҫ�ڴ�cache,����Ϊ���߼��򵥣�Ĭ�϶����ڴ滺�棬�ɿ��Ƶ����Ƿ�дӲ������ TODO!�Ƿ��ڴ滺��ӿ��� FIXME
            //ע��������趨�˲�д�����ļ�����ô��Ҫ�Լ���֤�ڴ�����ȫ��װ�£����趨��invert���õ��ڴ����ƴ�С�Ͳ�������������
            //�ڴ��б��� ���û�г���cache
            if ((m_invertCacheVec.size() + strIndexNode.count) * sizeof (InvertNodeType) <= InvertCacheSize)
            {
                m_indexCacheVec[m_indexCacheVec.size() - 1].addr = m_invertCacheVec.size(); //֧��ʵʱ�ڴ�����,ע��ͺ����make_inverted_cache�ظ���TODO
                std::copy(biter, eiter, std::back_inserter(m_invertCacheVec));
            }
        }

        from += strIndexNode.count;
        now_pos++; //advace you pos ,do not forget
    }
    /**
     * ����������
     */
    uint64 add_posting(const std::vector<InvertNodeType>& post_vec, IndexType index, uint64 from, FILE* fp_invert,
            size_t max_num = std::numeric_limits<size_t>::max())
    {
        IndexNodeType strIndexNode; //�ڴ��е�MapID�����ڵ�
        IndexNodeType strIndexNode_Cache; //���������ڵ�
        InvertNodeType strInvertNode; //�����¼�ڵ�

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
        strIndexNode.count = post_size; //�������Ʒ����
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

        //д�����ļ�
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
    ///��������,gcc4.1.4����֧��Ĭ�Ϻ���ģ����������֧��template <typename IndexType = IndexNodeType>)
    ///����ģ��Ϊ����Ӧ��ĳ���д�õ��������ܲ���˳����߸�����ͬ
    ///���Ƕ���id��count
    ///load֮ǰ��ȷ�������ṹ�����ڻ��߱����
    template <typename _IndexNodeType>
    bool load_inverted_index()
    {
        m_indexVec.reserve(m_entryNum); //ΪC2P���������ڴ�
        m_indexCacheVec.reserve(m_entryNum);
        vector<_IndexNodeType> tempinfo;
        //index����ȫ�������ڴ�
        if (!read_vec(m_indexfileName, tempinfo))
        {
            LOG_ERROR("Can not open index file %s", m_indexfileName.c_str());
            return false;
        }
        //cout << "new mem using " << timer.elapsed() << " " << cache_size << endl;
        //ʵ����40M����ֱ�Ӷ�ջ����ˣ�ֻ�ܶ�̬���٣�һ�δ��ļ�����������������ı��������
        //vector��ܶ�
        //_IndexNodeType tempinfo[cache_size];  //notice for speed may be wrong for big! FIXME
        //std::vector<_IndexNodeType> tempinfo;
        //tempinfo.resize(cache_size);
        IndexNodeType strIndexNode; //�ڴ��е�MapID�����ڵ�
        IndexNodeType strIndexNode_Cache; //���������ڵ�

        int num = (int) tempinfo.size();
        uint64 from = 0;
        int nPid = 0;

        for (int i = 0; i < num; i++)
        {
            //������,���Ϊ��
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
    ///��Ҫ�����index��0��ʼ˳����
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

        m_indexVec.reserve(m_entryNum); //ΪC2P���������ڴ�
        m_indexCacheVec.reserve(m_entryNum);

        const int cache_size = 4 * 1024;
        _IndexNodeType tempinfo[cache_size];
        // _IndexNodeType *tempinfo = new _IndexNodeType[cache_size];
        IndexNodeType strIndexNode; //�ڴ��е�MapID�����ڵ�
        IndexNodeType strIndexNode_Cache; //���������ڵ�

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

            memset(tempinfo, 0, (sizeof (_IndexNodeType)) * cache_size); //����
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
     * ������������������д���ļ�
     * ��Ȼ��BigVec����������Ա���ѭ���е��鷳�Ļ��弰�жϱ�������ڴ��Ӳ��д������������������Ǳ�ڵĲ��ȶ�������ʱ���ı�
     * ������Ĭ�ϰ���l1norm,l2norm ���Ӧ�ò���Ҫ ��������ȥ�� ��������
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
                { //added 11.04.20 ��ǡ�����ϴ�i == a break�������ı���ǡ�� tempinfo[i+1].pid����ˡ���
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

                    //д�����ļ�
                    //                    fwrite(&vecTmpCPList[0], sizeof (InvertNodeType), strIndexNode.count, fpInvert);
                    //д�����ļ�,��Ϊ�����Ѿ�֪���������ڴ��д洢������ֻ����Ҫ��¼��Ӳ�����ǲ�д
                    if (m_bPersitant)
                    {
                        fwrite(&vecTmpCPList[0], sizeof (InvertNodeType), strIndexNode.count, fpInvert);
                    }
                    //                else
                    if (m_bNeedCache)
                    { //change 11.05.19
                        //�ڴ��б��� ���û�г���cache
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
                    //��������
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
                //��Ӹù˿͵Ĺ����б�
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

                    //д�����ļ�
                    //                    fwrite(&vecTmpCPList[0], sizeof (InvertNodeType), strIndexNode.count, fpInvert);
                    //д�����ļ�,��Ϊ�����Ѿ�֪���������ڴ��д洢������ֻ����Ҫ��¼��Ӳ�����ǲ�д
                    if (m_bPersitant)
                    {
                        fwrite(&vecTmpCPList[0], sizeof (InvertNodeType), strIndexNode.count, fpInvert);
                    }
                    //                else
                    if (m_bNeedCache)
                    { //change 11.05.19
                        //�ڴ��б��� ���û�г���cache
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

            //д�����ļ�
            //            fwrite(&vecTmpCPList[0], sizeof (InvertNodeType), strIndexNode.count, fpInvert);
            //д�����ļ�,��Ϊ�����Ѿ�֪���������ڴ��д洢������ֻ����Ҫ��¼��Ӳ�����ǲ�д
            if (m_bPersitant)
            {
                fwrite(&vecTmpCPList[0], sizeof (InvertNodeType), strIndexNode.count, fpInvert);
            }
            //                else
            if (m_bNeedCache)
            { //change 11.05.19
                //�ڴ��б��� ���û�г���cache
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
     * ������������ͬ�ϣ������Ǵ��ڴ��е�һ��vector�ж�ȡ���ݣ������Ǵ�sorted file�ж�ȡ
     * ע�����vectorҪ���ǰ���<index_id, invert_id, weight> �ź����
     * TODO ������Ĵ����ظ�~
     * ע��ֻ���������������!isPersitant���ǲŲ�д�ļ� 10/07/06 add ֧��ֱ����ȫ�ڴ治д�ļ�
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
                //��������
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

            //��Ӹù˿͵Ĺ����б�
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

                //д�����ļ�,��Ϊ�����Ѿ�֪���������ڴ��д洢������ֻ����Ҫ��¼��Ӳ�����ǲ�д
                if (m_bPersitant)
                {
                    fwrite(&vecTmpCPList[0], sizeof (InvertNodeType), strIndexNode.count, fpInvert);
                }
                //                else
                if (m_bNeedCache)
                { //change 11.05.19
                    //�ڴ��б��� ���û�г���cache 
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
     *  Ŀǰ��Ҫ��Ϊ��ʹ��BigVec help implement
     *
     * FIXME Using const Vector& tempinfo; Iter iter = tempinfo.begin(); will cause FATAL
     * 1262: FATAL: passing ��const BigVec<invert::ST_PidKidInfo, invert::CmpSTNodeWeight>��
     * as ��this�� argument of ��bigvec_iterator<BigVec<_Node, _Cmp>, _Node> BigVec<_Node, _Cmp>::begin()
     *  [with _Node = invert::ST_PidKidInfo, _Cmp = invert::CmpSTNodeWeight]�� discards qualifiers
     *
     * FIXME temply remove const!!
     * Depreated bigvec may have bug so currently not used!  ��ʱ��������
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
                //��������
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
            //��Ӹù˿͵Ĺ����б�
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

                //д�����ļ�,��Ϊ�����Ѿ�֪���������ڴ��д洢������ֻ����Ҫ��¼��Ӳ�����ǲ�д
                if (m_bPersitant)
                {
                    fwrite(&vecTmpCPList[0], sizeof (InvertNodeType), strIndexNode.count, fpInvert);
                }
                //                else
                if (m_bNeedCache)
                { //change 11.05.19
                    //�ڴ��б��� ���û�г���cache
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
     * �����ڴ��е������͵���cache
     * ��ǰ���� simple cache
     * �����ṩ����cahe ���� TODO
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
            //�ж��ڴ�cache��û��ʣ��ռ�
            int nCount = m_indexCacheVec[i].count;
            int nLength = nCount * sizeof (InvertNodeType);

            if ((nCurInvertCacheSize + nLength) > InvertCacheSize) //��С����Ԥ���ڴ�����
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
        fread(&m_invertCacheVec[0], sizeof (InvertNodeType), nFrom, m_fpInvert); //��һ�ζ�ȡm_fpInvert
    }
    void make_inverted_cache()
    {
        int64 nCurInvertCacheSize = 0;
        int64 nFrom = 0;
        bool allInMem = true;
        IndexType i = 0;
        for (; i < m_entryNum; i++)
        {
            //�ж��ڴ�cache��û��ʣ��ռ�
            int nCount = m_indexCacheVec[i].count;
            int nLength = nCount * sizeof (InvertNodeType);

            if ((nCurInvertCacheSize + nLength) > InvertCacheSize) //��С����Ԥ���ڴ�����
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

        //��������ҪCACHE���������ݶ���CACHE
        //TODO all try c++ style ? copy   TODO ������, ȫ���쳣��
        if (m_invertCacheVec.empty())
        {
            m_invertCacheVec.resize(nFrom);
            fread(&m_invertCacheVec[0], sizeof (InvertNodeType), nFrom, m_fpInvert); //��һ�ζ�ȡm_fpInvert
        }
        else
        {
            //LOG(WARNING) << "Not write the invert to the disk for invert is small and we do not need persit" << endl;
        }

        if (allInMem) //���ȫ���ڴ棬���Թرմ򿪵ĵ����ļ�
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
    /**���ź�����ı��ж�ȡ���ݣ�������������*/
    bool create_inverted_index()
    {
        //������Ҫ��գ�����re sort֮���ٽ�������
        clear_cache();

        //�������ű�����post list��д���ļ�
        make_inverted_index();

        //�򿪵����ļ�
        m_fpInvert = fopen(m_invertfileName.c_str(), "rb");

        if (!m_fpInvert)
        {
            LOG_FATAL("Open %s failed", m_invertfileName.c_str());
            return false;
        }

        //�ڴ��л���cache
        if (m_bNeedCache)
            make_inverted_cache();

        //�����ṹ,��д���ļ�
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
        //������Ҫ��գ�����re sort֮���ٽ�������
        clear_cache();

        //�������ű�����post list��д���ļ�
        make_inverted_index(vec);

        //�򿪵����ļ�
        m_fpInvert = fopen(m_invertfileName.c_str(), "rb");
        if (!m_fpInvert)
        {
            LOG_FATAL("Open %s failed", m_invertfileName.c_str());
            return false;
        }

        //�ڴ��л���cache
        if (m_bNeedCache)
            make_inverted_cache();

        //�����ṹ,��д���ļ�
        if (m_bPersitant)
        {
            if (!write_index())
                return false;
        }
        return true;
    }
    /**
     * FIXME Ϊʲôinvert_table_creator ���õ�ʱ��,m_invertTable->create(m_tripleVec, m_indexfile.c_str(), m_invertfile.c_str());
     * ����Ҳ��ѡ��������ķ�֧������ѡ�������
     * ��ʱ����
     */
    template<typename Vector>
    void create_inverted_index_bigvec(Vector & vec)
    {
        //������Ҫ��գ�����re sort֮���ٽ�������
        clear_cache();

        //�������ű�����post list��д���ļ�
        make_inverted_index_bigVec(vec);

        //�򿪵����ļ�
        m_fpInvert = fopen(m_invertfileName.c_str(), "rb");
        //LOG_IF(FATAL, !m_fpInvert) << "open " << m_invertfileName << "failed" << endl;

        //�ڴ��л���cache
        make_inverted_cache();

        //�����ṹ,��д���ļ�
        if (m_bPersitant)
        {
            if (!write_index())
                return false;
        }
    }

    //--------------------------helper func for ���л�
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

    ///�ڴ�ӳ���еĵ�������
    vector<IndexNodeType> m_indexVec;

    ///�ڴ滺����
    vector<IndexNodeType> m_indexCacheVec;
    mutable vector< InvertNodeType> m_invertCacheVec;

    ///����postʱ��ĳЩ�ӿ���Ҫ�ڲ����õĿռ䣬ע�����ʹ������̲߳���ȫ
    vector<InvertNodeType> m_tempVec;
    IndexType m_tempIndex; //��ǵ�ǰtemp�洢�����ĸ�index��Ӧ������

    IndexType m_inMemStartIndex;
    IndexType m_inMemEndIndex; ///��ǵ�ǰ������е�������С��ţ�����˳���ȡ������ʱ��ĸ���cache

    IndexType m_entryNum; ///table ��entrie ��Ŀ == clse_vecIndex.size()

    FILE *m_fpInvert; ///�����ļ�ָ�룬�ڽ����õ�������֮���

    bool m_bAllInMem; ///����Ƿ�ȫ��cache�У�make cache������ñ��λ�����ȫ�ڲ���Ҫ�򿪵����ļ�
    bool m_bPersitant; ///�Ƿ���Ҫ��Ӳ�̱�������
    bool m_bNeedCache; ///�Ƿ���Ҫ�ڴ�cache�������������Ҫ����ֻΪ��дinvert,index���̶���

    SortMethod m_sortMethod;

    ValueType m_nullWeight; //��Чweight,Ĭ��ֵ��0 ������

    uint64 m_invertSize;

    const _OIFVisitor& m_oifVisitor;

public:
    static int64 SortCacheSize; ///�ⲿ�鲢ʱ��cache��С
    static int64 InvertCacheSize; ///�������ɵ��ŵ�ʱ�����ڴ��еĵ��ŵ�cache��С
}; //---end of class InvertTable

//FIXME �����Ǹ�GCC BUG�� Ϊɶ����InvertTable<>��ʾ��ʼ������ֵ�ֱ���47M��602M��
template <class T, template<typename E> class U, template<typename E2, typename F2> class V, class L, class M, class N>
int64 InvertedIndex<T, U, V, L, M, N>::SortCacheSize = 16 * (int64) 1024 * 1024 * 1024; //5G

template <class T, template<typename E> class U, template<typename E2, typename F2> class V, class L, class M, class N>
int64 InvertedIndex<T, U, V, L, M, N>::InvertCacheSize = 16 * (int64) 1024 * 1024 * 1024; //5G

} //-------------end of namespace inverted
#endif  //----end of INVERTED_INDEX_H_
