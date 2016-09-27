/** 
 *  ==============================================================================
 * 
 *          \file   myclient_stream.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-05-14 09:13:01.061460
 *  
 *  \Description:  ��myclient��MyclientRes��ʵ�����Ƕ�MYSQL_RES��>>����װ
 *                 ���Լ�read_db.cc
 *  ==============================================================================
 */

#ifndef MYCLIENT_STREAM_H_
#define MYCLIENT_STREAM_H_
#include <string>
#include <boost/lexical_cast.hpp>
#include "myclient_help.h"
/**
 * ��ǰ�������ӵļ�飬ת���쳣���ⲿ��׽
 * ����е�field���ܴ���null����char*���� ���ⲿ�ж��Ƿ�null ��null���Լ�ת������ TO_INT...
 * ������Ǵ��ڻ��ߴ󲿷ִ��ڿɿ��ǲ���DBStreamֱ��ʹ��MyclientRes������ ����ҲҪע��bool���͵���y..ʹ��to_boo_sql��Ҫ��TO_BOOL
 * ע���ʼ��֮���ⲿ��MyclientRes��Ҫ�ڵ���[][]���ʱ����±�仯��Ϊmysql_data_seek(_p_res, 0)ֻ�ǳ�ʼ��ִ��һ��
 */
class DBStream
{
private:
    int _col_index;
    int _nrows;
    int _ncols;
    MYSQL_RES* _p_res;
    MYSQL_ROW _p_row; //��ǰ�У�nullͬʱ��ʾ�˽���eof
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
        _p_row = NULL; //֧��re open
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
     * ע���÷�ֻ���������Ƶ�ʹ�ã��������eof��>> �δ����ⲿȷ�����!!!������Ϊ���ٶȲ����
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
        {//��Ҫ����
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
