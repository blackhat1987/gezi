/** 
 *  ==============================================================================
 * 
 *          \file   inverted_map_table.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-05-16 15:10:23.931693
 *  
 *  \Description:   ע������ģ������Ĳ�ͬ���ܷ�������map ��  unordered_map
 *                  ֻ��Container������Ҳ�����ˡ���
 *                  ģ��ϡ�����һ��ֻ���ڿ��ٲ�ѯ,��ȫ�ڴ�
 *
 *  TDO �����Ƿ� {id, value}���� ��Ϊ first second
 * Ҫ������� Ϊ�˸��õķ���  <key, value> std::pair first second
 *  key Ҳ���Ա�� ����һ���int�� ��Ϊ�����ڴ��Ӧ��   >2G�� row_num ����Ū��
 *  IndexNodeType���������� ���� ��Ĭ�ϵ�  InvertNodeType ����std::pair�����ˡ�����Ĭ�� һ��ֻ��Ҫ����value
 *  ֧�ָ��ӵ�value
 *
 *  //ע�������_Map::value_type ��const key! void add(KeyType index_id, const vector<Pair> & vec) ����ʹ�� push_back �漰=
 *  _Map::value_type �� std::pair
 *
 *  �����������cos֮�����map��Ȼ���� ��Ҫ�ⲿ��vector ��һ�°���id/first��������
 *  ����ʹ��row Ϊ�˼��ݸ����������ݽṹ
 *  ==============================================================================
 */

#ifndef INVERTED_MAP_TABLE_H_
#define INVERTED_MAP_TABLE_H_
#include "inverted_table_node_types.h"
#include "inverted_default_value.h"
namespace inverted {
/**
 * ����Ҫ����������ֻ��Ҫ����
 */
template<typename _Map, typename _IndexType = int>
        class MapTable
{
public:
    typedef _IndexType IndexType;
    typedef typename _Map::key_type KeyType;
    typedef typename _Map::value_type::second_type ValueType;
    typedef typename std::pair<KeyType, ValueType> Pair;
    typedef Pair Node;
    typedef Pair InvertNode;
    typedef typename _Map::iterator iterator;
    typedef typename std::pair<iterator, iterator> Range;
    typedef _Map Row;
    typedef vector<Row> Mat;
public:
    MapTable()
    {
        //֮��������Ϊ�˼���value�Ǹ������͵����
        init_default_null_value(_null_value);
    }
    MapTable(IndexType size)
    {
        init_default_null_value(_null_value);
        _mat.resize(size);
    }
    //--------------------load and save

    //-----------------for create
    void resize(IndexType size)
    {
        _mat.resize(size);
    }
    /**
     * �ⲿ��֤���ظ�add �޸�ʹ��modify ��Ϊtalbe(i,j)���ܲ�����ֵ���Բ��ṩ�޸�
     * add(index, key, value)
     */
    void add(IndexType index, KeyType key, ValueType value)
    {
        while (index >= _mat.size())
        {
            _mat.push_back(Row());
        }
        _mat[index].insert(Pair(key, value));
    }
    /**
     * add_row  ��������ݱ����swap
     * ����У������漰�޸�ԭ�з���
     *
     */

    void add_row(IndexType index, _Map& map_)
    {
        while (index >= _mat.size())
        {
            _mat.push_back(Row());
        }
        _mat[index].swap(map_);
    }
    /**
     * copy ������ swap �������ݲ����
     */
    void copy_row(IndexType index, const vector<Pair> & vec)
    {
        while (index >= _mat.size())
        {
            _mat.push_back(Row());
        }
        _mat[index].clear();
        std::copy(vec.begin(), vec.end(), std::inserter(_mat[index], _mat[index].begin()));
    }
    void copy_row(IndexType index, const _Map& map_)
    {
        while (index >= _mat.size())
        {
            _mat.push_back(Row());
        }
        _mat[index] = map_;
    }
    void add_posting(IndexType index, _Map& map_)
    {
        while (index >= _mat.size())
        {
            _mat.push_back(Row());
        }
        _mat[index].swap(map_);
    }
    void add_posting(IndexType index, const vector<Pair> & vec)
    {
        while (index >= _mat.size())
        {
            _mat.push_back(Row());
        }
        _mat[index].clear();
        std::copy(vec.begin(), vec.end(), std::inserter(_mat[index], _mat[index].begin()));
    }
    /**
     * copy ������ swap �������ݲ����
     */
    void copy_posting(IndexType index, const vector<Pair> & vec)
    {
        while (index >= _mat.size())
        {
            _mat.push_back(Row());
        }
        _mat[index].clear();
        std::copy(vec.begin(), vec.end(), std::inserter(_mat[index], _mat[index].begin()));
    }
    void copy_posting(IndexType index, const _Map& map_)
    {
        while (index >= _mat.size())
        {
            _mat.push_back(Row());
        }
        _mat[index] = map_;
    }

    //---------------------get
    IndexType size() const
    {
        return _mat.size();
    }
    void clear()
    {
        _mat.clear();
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
    Range posting(IndexType index)
    {
        return Range(_mat[index].begin(), _mat[index].end());
    }
    /**ע���InvertedIndex���涨��Ĳ�һ��,������InvertedIndexʹ��[]*/
    Row & operator[] (KeyType index)
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
    optional<ValueType> at(IndexType id1, KeyType id2) const
    {
        iterator iter = _mat[id1].find(id2);
        if (iter == _mat[id1].end())
            return optional<ValueType > ();
        else
            return optional<ValueType > (iter->second);
    }
    ValueType operator()(IndexType id1, KeyType id2) const
    {
        iterator iter = _mat[id1].find(id2);
        if (iter == _mat[id1].end())
            return _null_value;
        else
            return iter->second;
    }
    /**
     * ע�ⲻ���߽�
     * �ṩ���޸ģ���ǰ���ṩɾ��
     */
    void modify(IndexType id1, KeyType id2, ValueType value)
    {
        iterator iter = _mat[id1].find(id2);
        iter->second = value;
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

protected:
    mutable Mat _mat;
    ValueType _null_value;
};
/**
 * ʹ������
 * typedef std::tr1::unordered_map<int, float> Map; // int id���Ͳ��ñ䣬 float value���Ϳ�����
 * InvertedMapTable<Map> map_table;
 *
 * ���ʹ�ø������͵�value��ô������Ҫ�Լ���NormTraits<YourComplexType> �ػ����� Ĭ�Ͼ��� long double, double
 * �����ͨ������Լ���IndexNode�̳������Լ���Ҫ�����ݣ�Ҳ�����Լ���ƴӶ����� l1norm,l2norm�򣬵���������Ҫȡ����calc_l1norm
 * ��֮����Ҫ��дһ�������̳��ˡ���������Ҳ����hackһ�� ���ⲿ����
 * �������������������洢������������id�±������Ϳ�����
 */
template <typename _Map, template <typename ELEM> class _TableIndexNode = TableIndexNode, typename _IndexType = int>
class InvertedMapTable : public MapTable<_Map, _IndexType>
{
public:
    typedef MapTable<_Map, _IndexType> Base;
    using Base::_mat;
    using Base::_null_value;

    typedef _IndexType IndexType;
    typedef typename _Map::key_type KeyType;
    typedef typename _Map::value_type::second_type ValueType;
    typedef typename std::pair<KeyType, ValueType> Pair;
    typedef Pair Node;
    typedef Pair InvertNode;
    typedef typename _Map::iterator iterator;
    typedef typename std::pair<iterator, iterator> Range;
    typedef _Map Row;
    typedef vector<Row> Mat;
    //----new
    typedef _TableIndexNode<ValueType> IndexNodeType;
    typedef typename IndexNodeType::L1Norm L1Norm;
    typedef typename IndexNodeType::L2Norm L2Norm;
    typedef typename NormTypeTraits<ValueType>::L1NormType L1NormType;
    typedef typename NormTypeTraits<ValueType>::L2NormType L2NormType;
public:
    InvertedMapTable()
    {
    }
    InvertedMapTable(IndexType size)
    : MapTable<_Map>(size)
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
        _mat[index].insert(Pair(key, value));
    }
    /**
     * add_row�������漰�����еĸ��£�ԭ�з���
     */
    void add_row(IndexType index, const vector<Pair > &vec)
    {
        while (index >= _mat.size())
        {
            _mat.push_back(Row());
            _index_vec.push_back(IndexNodeType());
        }
        _mat[index].clear();
        std::copy(vec.begin(), vec.end(), std::inserter(_mat[index], _mat[index].begin()));
    }
    /**
     * ע�ⲻ������һ���ǲ���Ҫ������ �����Ҫ���ı�ԭ���Ļ� copy_row
     */
    void add_row(IndexType index, _Map& map_)
    {
        while (index >= _mat.size())
        {
            _mat.push_back(Row());
            _index_vec.push_back(IndexNodeType());
        }
        _mat[index].swap(map_);
    }
    void copy_row(IndexType index, const _Map& map_)
    {
        while (index >= _mat.size())
        {
            _mat.push_back(Row());
            _index_vec.push_back(IndexNodeType());
        }
        _mat[index] = map_;
    }
    void add_posting(IndexType index, const vector<Pair > &vec)
    {
        while (index >= _mat.size())
        {
            _mat.push_back(Row());
            _index_vec.push_back(IndexNodeType());
        }
        _mat[index].clear();
        std::copy(vec.begin(), vec.end(), std::inserter(_mat[index], _mat[index].begin()));
    }
    /**
     * ע�ⲻ������һ���ǲ���Ҫ������ �����Ҫ���ı�ԭ���Ļ� copy_row
     */
    void add_posting(IndexType index, _Map& map_)
    {
        while (index >= _mat.size())
        {
            _mat.push_back(Row());
            _index_vec.push_back(IndexNodeType());
        }
        _mat[index].swap(map_);
    }
    void copy_posting(IndexType index, const _Map& map_)
    {
        while (index >= _mat.size())
        {
            _mat.push_back(Row());
            _index_vec.push_back(IndexNodeType());
        }
        _mat[index] = map_;
    }
    void clear()
    {
        _mat.clear();
        _index_vec.clear();
    }
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
    void build(bool calc_l1 = true, bool calc_l2 = true)
    {
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
    IndexNodeType& index_node(IndexType index)
    {
        return _index_vec[index];
    }
    vector<IndexNodeType>& index_vec()
    {
        return _index_vec;
    }
private:
    vector<IndexNodeType> _index_vec;
};

} //----end of namespace inverted

#endif  //----end of INVERTED_MAP_TABLE_H_
