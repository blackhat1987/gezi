/**
 *  ==============================================================================
 *
 *          \file   DataBase.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-01-23 15:14:46.316474
 *
 *  \Description:  封装myclient读取数据库，在db/otl 里面的内容是通过otl来读取数据库 那样需要odbc的安装
 *  ==============================================================================
 */

#ifndef DATABASE_H_
#define DATABASE_H_
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <string.h>
#include "myclient_include.h"
#include "common_util.h"

namespace gezi
{

class DBStream;

/**
 * 这个是只针对mysql的
 */
class DataBase
{
protected:
  MyclientServerConf* _client_conf;
  MyclientPool* _pool;
  std::string _sql;
  int _db_num; ///分成几个分库
  int _dbsource_num; ///几个数据源，比如两个IP 相同的库，确保安全

public:

  DataBase()
  :_db_num(1), _client_conf(NULL), _pool(NULL)
  {
  }

  virtual ~DataBase()
  {
    logOff(); //关闭数据库连接
    if (_client_conf)
    {
      delete [] _client_conf;
      _client_conf = NULL;
    }
  }

  void logOff()
  {
	if (_pool)
	{
	  _pool->destroy();
	  delete _pool;
	}
  }

  void init(const std::string& config_file, const std::string& section = "",
          const std::string& path = "./conf", int dbsource_num = 1)
  {
    readConfig(path, config_file, section, dbsource_num);
    initDB();
  }

  void init(int dbnum, const std::string& config_file, const std::string& section = "",
          const std::string& path = "./conf", int dbsource_num = 1)
  {
    _db_num = dbnum;
    readConfig(path, config_file, section, dbsource_num);
    initDB();
  }

  /**重新配置文件执行其它sql操作,也可以直接再执行set_sql操作等等*/
  void reset(const std::string& config_file, const std::string& section = "", const std::string& path = "./conf")
  {
    readConfig(path, config_file, section);
  }

  std::string sql() const
  {
    return _sql;
  }

  int db_num() const
  {
    return _db_num;
  }

  //所有execute 返回<0表示失败 >=0表示成功并且返回row count, 如果是非读操作res = NULL, store = false
  inline int execute(MyclientRes& res, bool store = true)
  {
	return execute(_sql, &res, store);
  }

  inline int execute(MyclientRes* res, bool store = true)
  {
	return execute(_sql, res, store);
  }
    
  int execute(const std::string& sql, MyclientRes& res, bool store = true)
  {
	return execute(sql, &res, store);
  }
  
  int execute(const std::string& sql, MyclientRes* res, bool store = true)
  {
	int err = 0;
    MysqlConnection* p_conn = _pool->fetchConnection(MYCLIENT_AVERAGE_HOST_TYPE, &err, 0);
    while (p_conn == NULL)
    {
      LOG(WARNING) << "fetch fail: " << _pool->getError(err);
      p_conn = _pool->fetchConnection(MYCLIENT_AVERAGE_HOST_TYPE, &err, 0);
    }
    res->free();
    int ret = p_conn->query(sql.c_str(), res, store);
	if (ret < 0 && p_conn->getMysqlErrno() != ER_NO_SUCH_TABLE)
	{
		_pool->putBackConnection(p_conn, true); //需要重连
		p_conn = _pool->fetchConnection(MYCLIENT_AVERAGE_HOST_TYPE, &err, 0);
		ret = p_conn->query(sql.c_str(), res, store);
		if (ret < 0)
		{
		  perror(p_conn);
		} 
	}
	_pool->putBackConnection(p_conn);
	return ret;
  }
  
  void perror(MysqlConnection* p_conn)
  {
    unsigned int err = p_conn->getLastMysqlErrorno();
    LOG(WARNING) << "getMysqlError ok!,err:" << err;
    LOG(WARNING) << p_conn->getError(err);
  }

  /**读取所有配置信息 TODO有冗余*/
  void readConfig(const std::string& path, const std::string& config_file,
          const std::string & section, int dbsource_num = 1)
  {
    PVAL(path);
    PVAL(config_file);
    comcfg::Configure conf;
    CHECK_EQ(conf.load(path.c_str(), config_file.c_str()), 0) << "Load db config fail " << path << " " << config_file;

    _dbsource_num = dbsource_num;

    if (_db_num == 1)
    {
      int dbnum = get_val(conf, "dbnum", 1);
      if (!section.empty())
        dbnum = get_val(conf, section, "dbnum", dbnum);
      _db_num = dbnum;
    }

    if (_dbsource_num == 1)
    {
      int dnum = get_val(conf, "dbsource_num", 1);
      if (!section.empty())
        dnum = get_val(conf, section, "dbsource_num", dnum);
      _dbsource_num = dnum;
    }


    _client_conf = new MyclientServerConf[_dbsource_num];
    string dbname;
    //先设置成默认配置
    for (int i = 0; i < _dbsource_num; i++)
    {      
      CONF2_CLASS(_client_conf[i], port, 3306);
      CONF2_CLASS(_client_conf[i], read_timeout, 2000);
      CONF2_CLASS(_client_conf[i], write_timeout, 2000);
      CONF2_CLASS(_client_conf[i], connect_timeout, 2000);
      CONF2_CLASS(_client_conf[i], min_connection, 3);
      CONF2_CLASS(_client_conf[i], max_connection, 1024);
      CONF_STRCPY_VAL(_client_conf[i].ip, ip, "");
      CONF_STRCPY_VAL(_client_conf[i].username, username, "");
      CONF_STRCPY_VAL(_client_conf[i].password, password, "");
      CONF_STRCPY_VAL(_client_conf[i].charset, charset, "gbk");
    }
    _sql = get_val(conf, "sql", "");
    CONF(dbname);
    strncpy(_client_conf[0].dbname, dbname.c_str(), dbname.size());
    _client_conf[0].dbname[dbname.size()] = '\0';

    //        //获取具体section对应的配置，如果没有配置用上面的默认配置,如果是多个source 需要section必须不为空
    if (!section.empty())
    {
      for (int i = 0; i < _dbsource_num; i++)
      {
        string section_ = section;
        if (i > 0)
        {
          section_ += TO_STRING(i);
        }

        PCONF2_CLASS(_client_conf[i], port, section_, (int) _client_conf[i].port);
        PCONF2_CLASS(_client_conf[i], read_timeout, section_, _client_conf[i].read_timeout);
        PCONF2_CLASS(_client_conf[i], write_timeout, section_, _client_conf[i].write_timeout);
        PCONF2_CLASS(_client_conf[i], connect_timeout, section_, _client_conf[i].connect_timeout);
        PCONF2_CLASS(_client_conf[i], min_connection, section_, _client_conf[i].min_connection);
        PCONF2_CLASS(_client_conf[i], max_connection, section_, _client_conf[i].max_connection);
        CONF_STRCPY_PROP(_client_conf[i].ip, ip, section_, _client_conf[i].ip);
        CONF_STRCPY_PROP(_client_conf[i].username, username, section_, _client_conf[i].username);
        CONF_STRCPY_PROP(_client_conf[i].password, password, section_, _client_conf[i].password);
        CONF_STRCPY_PROP(_client_conf[i].charset, charset, section_, _client_conf[i].charset);
        PCONF2(dbname, section, dbname);
        strncpy(_client_conf[i].dbname, dbname.c_str(), dbname.size());
        _client_conf[i].dbname[dbname.size()] = '\0';
      }
      PCONF2(_sql, section, _sql);
      _sql = get_val(conf, section, "sql", _sql);
    }
    for (int i = 0; i < _dbsource_num; i++)
    {
      strncpy(_client_conf[i].tag, MYCLIENT_AVERAGE_HOST_TYPE, strlen(MYCLIENT_AVERAGE_HOST_TYPE));
      _client_conf[i].tag[strlen(MYCLIENT_AVERAGE_HOST_TYPE)] = '\0';
    }
    PVAL(_client_conf[0].max_connection);
  }

  void initDB()
  {
	MyclientPoolConf conn_pool_conf;
    conn_pool_conf.monitor_reconnection_time = 5;   //后台线程每隔5秒去检测连接的连通性
    conn_pool_conf.sqlBufSize= 1024;                
    conn_pool_conf.failHandler= NULL;       //do nothing
        
    _pool = new MyclientPool(&conn_pool_conf);
    CHECK_NOTNULL(_pool);
    int ret = 0;
    ret = _pool->init();
    ret = _pool->addServer(_client_conf, _dbsource_num);
    if (ret != 0)
    { //偶尔会fail但是其实不检测继续执行也没事。。。 myclient bug
      LOG(WARNING) << format("error in add server:%d, connect db fail!") % ret;
    }
  }
};

//线程内使用 自己拥有资源  适用于单线程环境 或者多线程 但是不介意每个线程独立的数据库连接资源

class DBHelper : public DataBase
{
private:
  MyclientRes _res; //注意这个要重复使用要自己调用free的
public:

  ~DBHelper()
  {
    _res.free();
  }

  MyclientRes& res()
  {
    return _res;
  }

  //所有execute 返回<0表示失败 >=0表示成功并且返回row count

  inline int execute()
  {
	return DataBase::execute(_res);
  }

  /**
   * 执行和配置文件原始读入的sql不同的命令
   */
  inline int execute(const std::string & sql)
  {//理论上不需要每次putBack,但是为了安全。。。 因为网络可能存在不稳定，瞬间断，如果执行失败可以尝试再次execute(sql, true)
	return DataBase::execute(sql, _res);
  }

  template<typename _Func>
  void processRows(_Func func)
  {
    _res.free();
    size_t nrows = _res.getRowsCount();
    for (size_t i = 0; i < nrows; i++)
    {
      func(_res[i]);
    }
  }

  template<typename _Func>
  void process(_Func func)
  {
    _res.free();
    func(DBStream(_res));
  }

};

class SharedDataBase
{
public:

  static DataBase* instance()
  {
    static DataBase db;
    return &db;
  }

  //can only use instance or dataBase, can not use both

  static DataBase& dataBase()
  {
    static DataBase db;
    return db;
  }
};

inline size_t get_nrows(const MyclientRes& res)
{
  return res.getRowsCount();
}

inline bool to_bool_sql(const char* input)
{
  if (strcmp(input, "y") == 0)
    return true;
  else
    return false;
}

inline int get_ncols(const std::string& sql)
{
  int num = 0;
  int pos = sql.find("from");
  string temp = sql.substr(0, pos);
  for (size_t i = 0; i < temp.size(); i++)
  {
    if (sql[i] == ',')
      num++;
  }
  return num + 1;
}

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

  DBStream(DBHelper& oper)
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

  void open(DBHelper& oper)
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


} //----end of namespace gezi

#endif  //----end of DATABASE_H_
