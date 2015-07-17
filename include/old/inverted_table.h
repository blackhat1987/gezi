/**
 *  ==============================================================================
 * 
 *          \file   inverted_table.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-05-15 22:30:19.106618
 *  
 *  \Description:   ������ȫ����InvertedIndex�ṩ��ͬ�ӿ�
 *                  ���ǲ������ڴ治�ܷ�������ģ�����Ϊ�ڴ���������㹻��
 *                  ��������ģ��ϡ�����Ҳ
 *                  ���ö�ά����ʵ��vector<vector> 
 * //valarry��ɶ�ô�û��
 *                  �ṩload,save
 *                  ��ֵ��������ϵ����ִ洢ûɶ�ô���
 *
 *                  Eigen��sparse matrix����ôʵ�ֵģ�Ч�����
 *
 *  TODO �ռ����� ������ʡ��capacity ��ӵ�ʱ���ֶ�reserve,sharank mem show mem
 *
 *  InvertedTable<float>
 *  InvertedTable<int>   InvertedTable<int, TableInvertNode2>
 *
 *  Ҫ������� Ϊ�˸��õķ���  <key, value> std::pair first second
 *
 *  �ṩrow��ҪΪ�˼���InvertedIndex ��Ϊ�Ǹ��õ�1ά���� ����begin(), end()
 *  ==============================================================================
 */

#ifndef INVERTED_TABLE_H_
#define INVERTED_TABLE_H_
#include "inverted_table_node_types.h"
#include "inverted_default_value.h"
#include "common_help.h"
#include "ul_log_help.h"
namespace inverted {
template <typename _ValueType = float,
        template <typename _T1, typename _T2> class _InvertNode = std::pair,
        typename _KeyType = int, typename _IndexType = int>
        class Table
{
public:
    typedef _InvertNode<_KeyType, _ValueType> Pair;
    typedef Pair Node;
    typedef Pair InvertNode;
    typedef Pair InvertNodeType;
    typedef _IndexType IndexType;
    typedef _KeyType KeyType;
    typedef _ValueType ValueType;
    typedef vector<Pair> Row;
    typedef typename Row::iterator iterator;
    typedef typename std::pair<iterator, iterator> Range;
    typedef vector<Row> Mat;
public:
    Table()
    : _sort_method(UNKNOWN_ORDER)
    {
        init_default_null_value(_null_value);
    }
    Table(const Mat& mat)
    {
        _mat.swap(mat);
    }
    Table(KeyType size)
    : _sort_method(UNKNOWN_ORDER)
    {
        init_default_null_value(_null_value);
        _mat.resize(size);
    }
    static void set_cache_size(int64 sort_size, int64 invert_size)
    {
    }
    static void set_invert_cache_size(int64 invert_size)
    {
    }
    static void set_sort_cache_size(int64 sort_size)
    {
    }
    //-----------------helper
    /**
     * ռ���ڴ��С��ͳ��tableռ���ڴ棬����������
     * ���ص�λ��M
     */
    float mem_size()
    {
        int64 mem_size = 0;
        IndexType m_nLevel = (IndexType) _mat.size();
        for (IndexType i = 0; i < m_nLevel; i++)
        {
            mem_size += _mat[i].capacity() * sizeof (Node);
        }
        return mem_size / (1024 * 1024.0);
    }
    void shrank_mem()
    {
        IndexType m_nLevel = (IndexType) _mat.size();
        for (IndexType i = 0; i < m_nLevel; i++)
        {
            _mat[i].swap(Row(_mat[i].begin(), _mat[i].end()));
        }
    }
    //-----------------for create
    void clear()
    {
        _mat.clear();
    }
    void resize(IndexType size)
    {
        _mat.resize(size);
    }
    /**
     * �ⲿ��֤���ظ�add �޸�ʹ��modify ��Ϊtalbe(i,j)���ܲ�����ֵ���Բ��ṩ�޸�
     * add(index, key, value)
     * ��ʵ��Ӧ����IndexType, KeyType ValueType����,����һ��IndexType==KeyType�㹻��
     */
    void add(IndexType index, KeyType key, ValueType value)
    {
        while (index >= _mat.size())
        {
            _mat.push_back(Row());
        }
        _mat[index].push_back(Pair(key, value));
    }
    /**
     * ����У������漰�޸�ԭ�з���
     */
    void add_row(IndexType index, vector<Pair> & vec)
    {
        while (index >= _mat.size())
        {
            _mat.push_back(Row());
        }
        _mat[index].swap(vec);
    }
    void copy_row(IndexType index, const vector<Pair> & vec)
    {
        while (index >= _mat.size())
        {
            _mat.push_back(Row());
        }
        _mat[index] = vec;
    }
    void add_posting(IndexType index, vector<Pair> & vec)
    {
        while (index >= _mat.size())
        {
            _mat.push_back(Row());
        }
        _mat[index].swap(vec);
    }
    void copy_posting(IndexType index, const vector<Pair> & vec)
    {
        while (index >= _mat.size())
        {
            _mat.push_back(Row());
        }
        _mat[index] = vec;
    }

    //---------------------get
    IndexType size() const
    {
        return _mat.size();
    }
    /**
     * �������������ע���� Ҫ��first second.. ���� ����InvertNode������������Node{first, second} :)
     * �鷳һ��������Ը�hash map �� allocator?
     * ע��operator[]����Row, row()����Row
     */
    Range row(IndexType index) const
    {
        return Range(_mat[index].begin(), _mat[index].end());
    }
    Range range(IndexType index) const
    {
        return Range(_mat[index].begin(), _mat[index].end());
    }
    Range posting(IndexType index) const
    {
        return Range(_mat[index].begin(), _mat[index].end());
    }
    Range posting(IndexType index, std::vector<Node>& vec) const
    {
        return Range(_mat[index].begin(), _mat[index].end());
    }
    /**ע���InvertedIndex���涨��Ĳ�һ��,������InvertedIndexʹ��[]*/
    Row & operator[] (IndexType index)
    {
        return _mat[index];
    }
    Mat& mat()
    {
        return _mat;
    }
    /**
     *
     * @param id1  index
     * @param id2  key
     * @return
     */
    optional<ValueType> get_val(IndexType id1, KeyType id2) const
    {
        const Row& vec = _mat[id1];
        int num = vec.size();
        if (num == 0)
            return optional<ValueType > ();
        if (_sort_method != BY_ID || num < 5)
        {//˳�����
            for (int i = 0; i < num; i++)
            {
                if (id2 == vec[i].first)
                    return optional<ValueType > (vec[i].second);
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
                id = vec[middle].first;
                if (id2 == id)
                {
                    return optional<ValueType > (vec[middle].second);
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
    ValueType operator()(IndexType id1, KeyType id2) const
    {
        const Row& vec = _mat[id1];
        int num = vec.size();
        if (num == 0)
            return _null_value;
        if (_sort_method != BY_ID || num < 5)
        {//˳�����
            for (int i = 0; i < num; i++)
            {
                if (id2 == vec[i].first)
                    return vec[i].second;
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
                id = vec[middle].first;
                if (id2 == id)
                {
                    return vec[middle].second;
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
        return _null_value;
    }
    /**
     * ע�ⲻ���߽�
     * �ṩ���޸ģ���ǰ���ṩɾ�� ���û���ҵ������κδ�����Ӱ��
     */
    void modify(IndexType id1, KeyType id2, ValueType value)
    {
        const Row& vec = _mat[id1];
        int num = vec.size();
        if (num == 0)
            return;
        if (_sort_method != BY_ID || num < 5)
        {//˳�����
            for (int i = 0; i < num; i++)
            {
                if (id2 == vec[i].first)
                    vec[i].second = value;
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
                id = vec[middle].first;
                if (id2 == id)
                {
                    vec[middle].second = value;
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
    //����Խ����
    int get_posting_len(IndexType index) const
    {
        return _mat[index].size();
    }
    int get_row_len(IndexType index) const
    {
        return _mat[index].size();
    }

    //--------------------- set
    void set_null_value(ValueType null_value)
    {
        _null_value = null_value;
    }

    //----------sort
    void sort(SortMethod sort_method = BY_ID)
    {
        _sort_method = sort_method;
        if (sort_method == BY_ID)
        {
            int len = (int) _mat.size();
            for (int i = 0; i < len; i++)
                std::sort(_mat[i].begin(), _mat[i].end(), CmpNodeByID());
        }
        else if (sort_method == BY_VALUE)
        {
            int len = (int) _mat.size();
            for (int i = 0; i < len; i++)
                std::sort(_mat[i].begin(), _mat[i].end(), CmpNodeByValue());
        }
    }
    void set_sort_method(SortMethod sort_method)
    {
        _sort_method = sort_method;
    }
    void save(const std::string& dir)
    {
        LOG_INFO("Table saving %s", dir.c_str());
        if (!bf::exists(dir))
        {
            LOG_WARNING("%s not exist, will create first", dir.c_str());
            bf::create_directories(dir);
        }
        std::string file = dir + "/invert.idx";
        write_vec2d(_mat, file);
    }
    bool load(const std::string& dir)
    {
        LOG_INFO("Table loading %s", dir.c_str());
        std::string file = dir + "/invert.idx";
        return read_vec2d(file, _mat);
    }

protected:
    mutable Mat _mat;
    ValueType _null_value;
    SortMethod _sort_method;
};

/**
 * ע��Ĭ��Ϊfloat
 */
template <typename _ValueType = float,
        template <typename ELEM> class _TableIndexNode = TableIndexNode,
        template <typename _T1, typename _T2> class _InvertNode = std::pair,
        typename _KeyType = int, typename _IndexType = int>
        class InvertedTable : public Table<_ValueType, _InvertNode, _KeyType, _IndexType>
{
public:
    typedef Table<_ValueType, _InvertNode, _KeyType, _IndexType> Base;
    using Base::_mat;
    using Base::_null_value;
    using Base::_sort_method;
    typedef _InvertNode<_KeyType, _ValueType> Pair;
    typedef Pair Node;
    typedef Pair InvertNode;
    typedef Pair InvertNodeType;
    typedef _IndexType IndexType;
    typedef _KeyType KeyType;
    typedef _ValueType ValueType;
    typedef vector<Pair> Row;
    typedef typename Row::iterator iterator;
    typedef typename std::pair<iterator, iterator> Range;
    typedef vector<Row> Mat;
    //----new
    typedef _TableIndexNode<ValueType> IndexNodeType;
    typedef typename IndexNodeType::L1Norm L1Norm;
    typedef typename IndexNodeType::L2Norm L2Norm;
    typedef typename NormTypeTraits<ValueType>::L1NormType L1NormType;
    typedef typename NormTypeTraits<ValueType>::L2NormType L2NormType;
public:
    InvertedTable()
    {
    }
    InvertedTable(IndexType size)
    : Base(size)
    {
        _index_vec.resize(size);
    }
    //---------------------for create
    void resize(IndexType size)
    {
        _mat.resize(size);
        _index_vec.resize(size);
    }
    void add(IndexType index, KeyType key, ValueType value)
    {
        while (index >= _mat.size())
        {
            _mat.push_back(Row());
            _index_vec.push_back(IndexNodeType());
        }
        _mat[index].push_back(Pair(key, value));
    }
    /**
     * ����У������漰�޸�ԭ�з���
     */
    void add_row(IndexType index, vector<Pair> & vec)
    {
        while (index >= _mat.size())
        {
            _mat.push_back(Row());
            _index_vec.push_back(IndexNodeType());
        }
        _mat[index].swap(vec);
    }
    template<typename Func>
    void add_row(IndexType index, vector<Pair> & vec, Func func)
    {
        while (index >= _mat.size())
        {
            _mat.push_back(Row());
            _index_vec.push_back(IndexNodeType());
        }
        _mat[index].swap(vec);
        func(*this, index);
    }
    void copy_row(IndexType index, const vector<Pair> & vec)
    {
        while (index >= _mat.size())
        {
            _mat.push_back(Row());
            _index_vec.push_back(IndexNodeType());
        }
        _mat[index] = vec;
    }
    void add_posting(IndexType index, vector<Pair> & vec)
    {
        while (index >= _mat.size())
        {
            _mat.push_back(Row());
            _index_vec.push_back(IndexNodeType());
        }
        _mat[index].swap(vec);
    }
    void copy_posting(IndexType index, const vector<Pair> & vec)
    {
        while (index >= _mat.size())
        {
            _mat.push_back(Row());
            _index_vec.push_back(IndexNodeType());
        }
        _mat[index] = vec;
    }
    void clear()
    {
        _mat.clear();
        _index_vec.clear();
    }
    //----------------------for norm
    void calc_l1norm()
    {
        int len = (int) _index_vec.size();
        for (int i = 0; i < len; i++)
        {
            _index_vec[i].l1norm = 0;
            for (iterator iter = _mat[i].begin(); iter != _mat[i].end(); ++iter)
            {
                _index_vec[i].l1norm += iter->second;
            }
        }
    }
    void calc_l2norm()
    {
        int len = (int) _index_vec.size();
        for (int i = 0; i < len; i++)
        {
            L2NormType sum = 0;
            for (iterator iter = _mat[i].begin(); iter != _mat[i].end(); ++iter)
            {
                sum += (iter->second * iter->second);
            }
            _index_vec[i].l2norm = sqrt(sum);
        }
    }
    void calc_l1norm(IndexType i)
    {
        _index_vec[i].l1norm = 0;
        for (iterator iter = _mat[i].begin(); iter != _mat[i].end(); ++iter)
        {
            _index_vec[i].l1norm += iter->second;
        }
    }
    void calc_l2norm(IndexType i)
    {
        L2NormType sum = 0;
        for (iterator iter = _mat[i].begin(); iter != _mat[i].end(); ++iter)
        {
            sum += (iter->second * iter->second);
        }
        _index_vec[i].l2norm = sqrt(sum);
    }
    void build(SortMethod sort_methord = BY_ID, bool calc_l1 = true, bool calc_l2 = true)
    {
        this->sort(sort_methord);
        if (calc_l1)
            calc_l1norm();
        if (calc_l2)
            calc_l2norm();
    }
    L2Norm l2norm(IndexType index) const
    {
        return _index_vec[index].l2norm;
    }
    L1Norm l1norm(IndexType index) const
    {
        return _index_vec[index].l1norm;
    }
    IndexNodeType& index_node(int index)
    {
        return _index_vec[index];
    }
    vector<IndexNodeType>& index_vec()
    {
        return _index_vec;
    }
    void save(const std::string& dir)
    {
        LOG_INFO("InvertedTable saving %s", dir.c_str());
        Base::save(dir);
        std::string file = dir + "/index.idx";
        write_vec(_index_vec, file);
    }
    bool load(const std::string& dir)
    {
        LOG_INFO("InvertedTable loading %s", dir.c_str());
        if (!Base::load(dir))
            return false;
        std::string file = dir + "/index.idx";
        return read_vec(file, _index_vec);
    }
private:
    vector<IndexNodeType> _index_vec;
};

} //----end of namespace inverted

#endif  //----end of INVERTED_TABLE_H_
