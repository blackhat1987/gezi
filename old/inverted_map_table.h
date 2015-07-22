/** 
 *  ==============================================================================
 * 
 *          \file   inverted_map_table.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-05-16 15:10:23.931693
 *  
 *  \Description:   注意由于模板参数的不同不能范型容器map 和  unordered_map
 *                  只能Container级别范型也可以了。。
 *                  模拟稀疏矩阵，一般只用于快速查询,完全内存
 *
 *  TDO 考虑是否 {id, value}命名 改为 first second
 * 要重新设计 为了更好的范型  <key, value> std::pair first second
 *  key 也可以变吧 不过一般就int吧 因为对于内存的应用   >2G的 row_num 不好弄了
 *  IndexNodeType可任意配置 不过 有默认的  InvertNodeType 就用std::pair就行了。。。默认 一般只需要配置value
 *  支持复杂的value
 *
 *  //注意如果是_Map::value_type 是const key! void add(KeyType index_id, const vector<Pair> & vec) 则不能使用 push_back 涉及=
 *  _Map::value_type 是 std::pair
 *
 *  如果做向量求交cos之类的用map不然无序 需要外部用vector 接一下按照id/first排序再做
 *  建议使用row 为了兼容各种其它数据结构
 *  ==============================================================================
 */

#ifndef INVERTED_MAP_TABLE_H_
#define INVERTED_MAP_TABLE_H_
#include "inverted_table_node_types.h"
#include "inverted_default_value.h"
namespace inverted {
/**
 * 不需要索引的数据只需要倒排
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
        //之所以这样为了兼容value是复杂类型的情况
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
     * 外部保证不重复add 修改使用modify 因为talbe(i,j)可能不存在值所以不提供修改
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
     * add_row  输入的内容被清空swap
     * 添加行，可能涉及修改原行废弃
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
     * copy 而不是 swap 输入内容不清空
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
     * copy 而不是 swap 输入内容不清空
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
     * 但是这个用起来注意了 要用first second.. 所以 当初InvertNode命名还不如用Node{first, second} :)
     * 麻烦一点这里可以该hash map 的 allocator?
     * 注意operator[]返回Row, row()返回Row
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
    /**注意和InvertedIndex里面定义的不一样,不建议InvertedIndex使用[]*/
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
     * 注意不检测边界
     * 提供了修改，当前不提供删除
     */
    void modify(IndexType id1, KeyType id2, ValueType value)
    {
        iterator iter = _mat[id1].find(id2);
        iter->second = value;
    }
    //不做越界检测
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
 * 使用例如
 * typedef std::tr1::unordered_map<int, float> Map; // int id类型不用变， float value类型可配置
 * InvertedMapTable<Map> map_table;
 *
 * 如果使用复杂类型的value那么可能需要自己对NormTraits<YourComplexType> 特化处理 默认就是 long double, double
 * 你可以通过设计自己的IndexNode继承增加自己需要的内容，也可以自己设计从而不用 l1norm,l2norm域，但是那样不要取调用calc_l1norm
 * 总之你需要再写一个类来继承了。。。或者也可以hack一下 类外部操作
 * 或者你外面再添加数组存储其它东西，按id下标索引就可以了
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
     * add_row都可能涉及到整行的更新，原行废弃
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
     * 注意不拷贝，一般是不需要拷贝的 如果需要不改变原来的话 copy_row
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
     * 注意不拷贝，一般是不需要拷贝的 如果需要不改变原来的话 copy_row
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
