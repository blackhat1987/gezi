/** 
 *  ==============================================================================
 * 
 *          \file   myclient_stream.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-05-14 09:13:01.061460
 *  
 *  \Description:  对myclient的MyclientRes其实本质是对MYSQL_RES的>>流包装
 *                 测试见read_db.cc
 *  ==============================================================================
 */

#ifndef MYCLIENT_STREAM_H_
#define MYCLIENT_STREAM_H_
#include <string>
#include <boost/lexical_cast.hpp>
#include "myclient_help.h"
/**
 * 当前不做复杂的检查，转换异常请外部捕捉
 * 如果有的field可能存在null请用char*类型 并外部判断是否null 非null再自己转换比如 TO_INT...
 * 如果都是存在或者大部分存在可考虑不用DBStream直接使用MyclientRes更方便 但是也要注意bool类型的是y..使用to_boo_sql不要用TO_BOOL
 * 注意初始化之后外部的MyclientRes不要在单独[][]访问避免下标变化因为mysql_data_seek(_p_res, 0)只是初始化执行一次
 */
class DBStream
{
private:
    int _col_index;
    int _nrows;
    int _ncols;
    MYSQL_RES* _p_res;
    MYSQL_ROW _p_row; //当前行，null同时标示了结束eof
public:
    DBStream()
    : _col_index(0), _p_res(NULL),
    _nrows(0), _ncols(0), _p_row(NULL)
    {

    }
    DBStream(MyclientRes& res)
    : _col_index(0), _p_res(res.getRawObj()),
    _nrows(res.getRowsCount()), _ncols(res.getFieldsCount()),
    _p_row(NULL)
    {
        if (_nrows)
            seek(0);
    }
    DBStream(DBOper& oper)
    : _col_index(0), _p_res(oper.res().getRawObj()),
    _nrows(oper.res().getRowsCount()), _ncols(oper.res().getFieldsCount()),
    _p_row(NULL)
    {
        if (_nrows)
            seek(0);
        Pval(_nrows);
        Pval((_p_row == NULL));
    }
    void open(MyclientRes& res)
    {
        _p_res = NULL;
        _p_row = NULL; //支持re open
        _p_res = res.getRawObj();
        _nrows = res.getRowsCount();
        _ncols = res.getFieldsCount();
        if (_nrows)
            seek(0);
    }
    void open(DBOper& oper)
    {
        open(oper.res());
    }
    bool is_open()
    {
        return _p_row;
    }
    void seek(size_t pos)
    {
        mysql_data_seek(_p_res, pos);
        _p_row = mysql_fetch_row(_p_res);
        _col_index = 0;
    }
    bool eof()
    {
        return !_p_row;
    }
    /**
     * 注意用法只能是流类似的使用，如果到了eof还>> 段错误，外部确保检查!!!，这里为了速度不检测
     * while(!ifs.eof())
     * {
     * }
     */
    template<typename T>
    DBStream & operator >>(T& val)
    {
        val = boost::lexical_cast<T > (_p_row[_col_index]);
        advance();
        return *this;
    }
    DBStream & operator >>(bool& val)
    {
        val = to_bool_sql(_p_row[_col_index]);
        advance();
        return *this;
    }
    DBStream & operator >>(char*& val)
    {
        val = _p_row[_col_index];
        advance();
        return *this;
    }
    DBStream & operator >>(void*& val)
    {//FIXME why void* and call char * will use >>(T&)???
        val = _p_row[_col_index];
        advance();
        return *this;
    }
    DBStream & operator >>(std::string& val)
    {
        val = _p_row[_col_index];
        advance();
        return *this;
    }
private:
    void advance()
    {
        if (_col_index + 1 == _ncols)
        {//需要换行
            _p_row = mysql_fetch_row(_p_res);
            _col_index = 0;
        }
        else
        {
            _col_index++;
        }
    }
};
typedef DBStream MyClientStream;
#endif  //----end of MYCLIENT_STREAM_H_
