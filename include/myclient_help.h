/** 
 *  ==============================================================================
 * 
 *          \file   myclient_help.h
 *
 *        \author   gezi  
 *          
 *          \date   2010-10-25 09:04:28.111630
 *  
 *  \Description:   对于myclient的包装，配置文件采用百度格式:分隔，用comconfig读取。
 *                  目的是通过配置文件和本来完全隔离数据库操作，对外提供一个可访问的
 *                  MyclientRes res;
 *
 *  ==============================================================================
 */
#ifndef  MYCLIENT_HELP_H_
#define  MYCLIENT_HELP_H_
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <string.h>
#include "myclient_include.h"
#include "config_help.h"
#include "common_help.h"
#include "debug_help.h"
#include "ul_log_help.h"
/**
 * 这个是只针对mysql的
 */
class DBStream;

/**
 * 推荐只配置sql,不使用Selct From Where
 */
class DBHelper
{
protected:
  MyclientServerConf* _client_conf;
  MyclientPool* _pool;
  MysqlConnection* _p_conn;
  std::string _sql; ///可以者解配置sql语句，忽略 Select Whre From
  int _db_num; ///分成几个分库
  int _dbsource_num; ///几个数据源，比如两个IP 相同的库，确保安全

public:

  DBHelper()
  : _p_conn(NULL), _db_num(1), _client_conf(NULL), _pool(NULL)
  {
  }

  virtual ~DBHelper()
  {
    log_off(); //关闭数据库连接
    if (_client_conf)
    {
      delete [] _client_conf;
      _client_conf = NULL;
    }
    //it seems myclientpool use resouce pool? So can not delete and can not used on stack!
    //Must new and not delete!
    //        if (_pool)  //FIXME myclient bug 不能关闭 否则可能core,另外init db偶尔会失败可以循环尝试连接
    //        {
    //            delete _pool;
    //            _pool = NULL;
    //        }
  }

  void log_off()
  {
    if (_p_conn)
    {
      _pool->putBackConnection(_p_conn);
      _p_conn = NULL;
    }
  }

  bool init(const std::string& path, const std::string& config_file, const std::string& section = "", int dbsource_num = 1)
  {
    if (!read_config(path, config_file, section, dbsource_num))
    {
      LOG_ERROR("Open config file %s/%s fail", path.c_str(), config_file.c_str());
      return false;
    }
    if (!init_db())
    {
      LOG_ERROR("Init db false");
      return false;
    }
    return true;
  }

  bool init(int dbnum, const std::string& path, const std::string& config_file, const std::string& section = "", int dbsource_num = 1)
  {
    _db_num = dbnum;
    if (!read_config(path, config_file, section, dbsource_num))
    {
      LOG_ERROR("Open config file %s/%s fail", path.c_str(), config_file.c_str());
      return false;
    }
    if (!init_db())
    {
      LOG_ERROR("Init db false");
      return false;
    }
    return true;
  }

  /**重新配置文件执行其它sql操作,也可以直接再执行set_sql操作等等*/
  bool reset(const std::string& path, const std::string& config_file, const std::string& section = "")
  {
    if (!read_config(path, config_file, section))
    {
      LOG_ERROR("Open config file %s/%s fail", path.c_str(), config_file.c_str());
      return false;
    }
    return true;
  }

  std::string sql() const
  {
    return _sql;
  }

  int db_num() const
  {
    return _db_num;
  }

  int execute(MyclientRes& res, bool is_need_reconnect = false)
  {
    if (_p_conn)
    {
      _pool->putBackConnection(_p_conn, is_need_reconnect);
      _p_conn = NULL;
    }
    int err = 0;
    _p_conn = _pool->fetchConnection(MYCLIENT_AVERAGE_HOST_TYPE, &err, 0);
    if (_p_conn == NULL)
    {
      LOG_WARNING("fetch fail");
      cout << "fetch fail" << endl;
      return -1;
    }
    res.free();
    return _p_conn->query(_sql.c_str(), &res, true);
  }

  int execute(const std::string& _sql, MyclientRes& res, bool is_need_reconnect = false)
  {
    if (_p_conn)
    {
      _pool->putBackConnection(_p_conn, is_need_reconnect);
      _p_conn = NULL;
    }
    int err = 0;
    _p_conn = _pool->fetchConnection(MYCLIENT_AVERAGE_HOST_TYPE, &err, 0);
    if (_p_conn == NULL)
    {
      LOG_WARNING("fetch fail");
      cout << "fetch fail" << endl;
      return -1;
    }
    res.free();
    return _p_conn->query(_sql.c_str(), &res, true);
  }

  void perror()
  {
    unsigned int err = _p_conn->getLastMysqlErrorno();
    LOG_WARNING("getMysqlError ok!,err:%u", err);
    LOG_WARNING("%s", _p_conn->getError(err));
  }

  /**读取所有配置信息 TODO有冗余*/
  bool read_config(const std::string& path, const std::string& config_file, const std::string & my_section, int dbsource_num = 1)
  {
    comcfg::Configure conf;
    if (conf.load(path.c_str(), config_file.c_str()) != 0)
      return false;

    _dbsource_num = dbsource_num;

    string section = my_section;

    if (section.empty())
    {
      VAL_GET(section, "");
    }

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
      VAL_GET2(_client_conf[i], port, 3306);
      VAL_GET2(_client_conf[i], read_timeout, 2000);
      VAL_GET2(_client_conf[i], write_timeout, 2000);
      VAL_GET2(_client_conf[i], connect_timeout, 2000);
      VAL_GET2(_client_conf[i], min_connection, 3);
      VAL_GET2(_client_conf[i], max_connection, 5);
      VAL_STRCPY(_client_conf[i].ip, ip, "");
      VAL_STRCPY(_client_conf[i].username, username, "");
      VAL_STRCPY(_client_conf[i].password, password, "");
      VAL_STRCPY(_client_conf[i].charset, charset, "gbk");
    }
    _sql = get_val(conf, "sql", "");
    VAL_GET(dbname, "");
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

        PROP_GET2(_client_conf[i], port, section_, (int) _client_conf[i].port);
        PROP_GET2(_client_conf[i], read_timeout, section_, _client_conf[i].read_timeout);
        PROP_GET2(_client_conf[i], write_timeout, section_, _client_conf[i].write_timeout);
        PROP_GET2(_client_conf[i], connect_timeout, section_, _client_conf[i].connect_timeout);
        PROP_GET2(_client_conf[i], min_connection, section_, _client_conf[i].min_connection);
        PROP_GET2(_client_conf[i], max_connection, section_, _client_conf[i].max_connection);
        PROP_STRCPY(_client_conf[i].ip, ip, section_, _client_conf[i].ip);
        PROP_STRCPY(_client_conf[i].username, username, section_, _client_conf[i].username);
        PROP_STRCPY(_client_conf[i].password, password, section_, _client_conf[i].password);
        PROP_STRCPY(_client_conf[i].charset, charset, section_, _client_conf[i].charset);
        PROP_GET(dbname, section, dbname);
        strncpy(_client_conf[i].dbname, dbname.c_str(), dbname.size());
        _client_conf[i].dbname[dbname.size()] = '\0';
      }
      PROP_GET(_sql, section, _sql);
      _sql = get_val(conf, section, "sql", _sql);
    }
    for (int i = 0; i < _dbsource_num; i++)
    {
      strncpy(_client_conf[i].tag, MYCLIENT_AVERAGE_HOST_TYPE, strlen(MYCLIENT_AVERAGE_HOST_TYPE));
      _client_conf[i].tag[strlen(MYCLIENT_AVERAGE_HOST_TYPE)] = '\0';
    }

    /*	 Pval(_dbsource_num);
        for (int i = 0; i < _dbsource_num; i++)
        {
          Pval(_client_conf[i].ip);
          Pval(_client_conf[i].port);
          Pval(_client_conf[i].username);
          Pval(_client_conf[i].password);
          Pval(_client_conf[i].dbname);

          Pval(_sql);
        }*/

    return true;
  }

  bool init_db()
  {
    _pool = new MyclientPool();
    if (!_pool)
    {
      LOG_ERROR("New pool fail!");
      return false;
    }
    int ret = 0;
    ret = _pool->init();
    ret = _pool->addServer(_client_conf, _dbsource_num);
    if (ret != 0)
    { //偶尔会fail但是其实不检测继续执行也没事。。。 myclient bug
      LOG_ERROR("error in add server:%d, connect db fail!", ret);
      return false;
    }
    int err = 0;
    _p_conn = _pool->fetchConnection(MYCLIENT_AVERAGE_HOST_TYPE, &err, 0);
    if (_p_conn == NULL)
    {
      LOG_ERROR("error in fetch:%d", errno);
      return false;
    }
    //        test_connection->setFailHandler(fail_handler); //TODO FIXME
    //        LOG_INFO("get connection ok!!!");

    return true;
  }
};

class DBOper : public DBHelper
{
private:
  MyclientRes _res; //注意这个要重复使用要自己调用free的
public:

  ~DBOper()
  {
    _res.free();
  }

  MyclientRes& res()
  {
    return _res;
  }

  int execute(bool is_need_reconnect = false)
  {
    if (_p_conn)
    {
      _pool->putBackConnection(_p_conn, is_need_reconnect);
      _p_conn = NULL;
    }
    int err = 0;
    _p_conn = _pool->fetchConnection(MYCLIENT_AVERAGE_HOST_TYPE, &err, 0);
    if (_p_conn == NULL)
    {
      LOG_WARNING("fetch fail");
      return -1;
    }
    _res.free();
    return _p_conn->query(_sql.c_str(), &_res, true);
  }

  /**
   * 执行和配置文件原始读入的sql不同的命令
   * TODO FIXME 都putBackConnection
   */
  int execute(const std::string & _sql, bool is_need_reconnect = false)
  {//理论上不需要每次putBack,但是为了安全。。。 因为网络可能存在不稳定，瞬间断，如果执行失败可以尝试再次execute(sql, true)
    if (_p_conn)
    {
      _pool->putBackConnection(_p_conn, is_need_reconnect);
      _p_conn = NULL;
    }
    int err = 0;
    _p_conn = _pool->fetchConnection(MYCLIENT_AVERAGE_HOST_TYPE, &err, 0);
    if (_p_conn == NULL)
    {
      LOG_WARNING("fetch fail");
      return -1;
    }
    _res.free();
    return _p_conn->query(_sql.c_str(), &_res, true);
  }

  template<typename _Func>
  void process_rows(_Func func)
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

#endif  //----end of OTL_DB_READER_H_
