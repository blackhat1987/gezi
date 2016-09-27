/** 
 *  ==============================================================================
 * 
 *          \file   otl_db_reader.h
 *
 *        \author   gezi  
 *          
 *          \date   2010-10-25 09:04:28.111630
 *  
 *  \Description:   希望提供一个方便的读数据，写<a,b,c..> 这样格式的文本
 *                  可以支持不同长度，间隔莫认是 '\t' 可配置, 最后多余一个 '\t'即 '\t\n'
 *
 *                  要读的数据库设置和要写的文件都由配置文件read_db.ini配置
 *
 *                  read_db.cc 对应默认使用程序
 *
 *                  同时提供一个接口，由外部给出仿函数使用otl_stream数据
 *  ==============================================================================
 */

#ifndef OTL_DB_READER_H_
#define OTL_DB_READER_H_

#define OTL_ODBC
#define OTL_STL
#define OTL_ODBC_SELECT_STM_EXECUTE_BEFORE_DESCRIBE
#define OTL_ODBC_MYSQL
#define OTL_ODBC_UNIX
#include <string>
#include <vector>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include "otlv4.h" //in lib/include/otlv4.h
#include "types.h"
#include "config_help.h"
#include "debug_help.h"
using std::string;
using std::vector;
using boost::format;
using boost::property_tree::ptree;

/**
 * 这个是针对mysql的DBReader,其实SqlServer的更简单，但是这个先写的就作为base了
 * DBReader 也支持写数据库等操作
 */
class DBReader
{
private:
    string DBType; //是mysql 还是 sqlserver 
    string Driver, Option, Font;
    string IP, Port, DB, User, Pwd; ///for read db
    string From; ///需要读取的表名
    string Out; ///要写的文件名称
    string Select, Where, DataType, DataTypes; ///查询表的语句部分
    string Sql; ///可以者解配置sql语句，忽略 Select Whre From

    otl_connect conn; ///otl连接
    ptree pt; ///for read config file
    __int64 readNum; ///how many lines is read
    const static int kBuffSize = 1024;

    enum SqlDataType
    {
        IntType, StringType
    };
public:

    DBReader()
    {
    }

    DBReader(const string& config_file, const string& section_ = "")
    {
        init(config_file, section_);
    }

    ~DBReader()
    {
        logOff(); //关闭数据库连接
    }

    void logOff()
    {
        LOG(INFO) << "Log off the database" << "\n";
        conn.logoff();
    }

    void init(const string& config_file, const string& section_ = "")
    {
        readConfig(config_file, section_);
        initDB();
        initSql();
    }

    /**重新配置文件执行其它sql操作,也可以直接再执行setSql操作等等*/
    void reset(const string& config_file, const string& section_ = "")
    {
        readConfig(config_file, section_);
        initSql();
    }

    void process()
    {
        LOG(INFO) << Pval(Sql) << "\n";
        if (DataTypes.empty())
        {
            if (DataType.find("int,int,str") != string::npos)
            {
                LOG(INFO) << "int begin and the last is str type" << "\n";
                processWrite_int_int_str();
            }
            else if (DataType.find("int,str") != string::npos)
            {
                LOG(INFO) << "int than str type" << "\n";
                processWrite_int_str();
            }
            else if (DataType == "int")
            {
                LOG(INFO) << "int only type" << "\n";
                processWrite<int>();
                LOG(INFO) << "wrint int finish" << "\n";
            }
            else if (DataType.find("str") != string::npos)
            {
                LOG(INFO) << "string only type" << "\n";
                processWrite<string > ();
            }
            else
            {
                LOG(FATAL) << "Your data type " << DataType << " in Sql is not support " << "\n";
            }
        }
        else
        {
            LOG(INFO) << "int string mix type" << "\n";
            processWrite_mix();
        }
    }

    /**TODO 如何能方便处理两种需求呢，类似sort能接受临时的functor可其它的时候可能希望能传递引用*/

    /*似乎没有好办法要么你写一个Func& 写一个const Func& 要么你干脆只写一个const Func& 但是这样会有warning 说你把const去掉了 呵呵
     */
    template<typename Func>
    void process(const Func& func)
    {
        //        process(func);
        LOG(INFO) << Pval(Sql) << "\n";
        try
        {
            otl_stream os(kBuffSize, Sql.c_str(), conn); //连接好数据库，并读出数据
            func(os);
            os.flush();
        }
        catch (otl_exception& p)
        { // intercept OTL exceptions
            cerr << p.msg << endl; // print out error message
            cerr << p.stm_text << endl; // print out SQL that caused the error
            cerr << p.sqlstate << endl; // print out SQLSTATE message
            cerr << p.var_info << endl; // print out the variable that caused the error
        }
    }

    template<typename Func>
    void process_(const Func& func)
    {
        //        process(func);
        LOG(INFO) << Pval(Sql) << "\n";
        try
        {
            otl_stream os(1, Sql.c_str(), conn); //连接好数据库，写数据
            func(os);
            os.flush();
        }
        catch (otl_exception& p)
        { // intercept OTL exceptions
            cerr << p.msg << endl; // print out error message
            cerr << p.stm_text << endl; // print out SQL that caused the error
            cerr << p.sqlstate << endl; // print out SQLSTATE message
            cerr << p.var_info << endl; // print out the variable that caused the error
        }
    }

    template<typename Func>
    void process_write(const Func& func)
    {
        //        process(func);
        LOG(INFO) << Pval(Sql) << "\n";
        try
        {
            otl_stream os(1, Sql.c_str(), conn); //连接好数据库，写数据
            func(os);
            os.flush();
        }
        catch (otl_exception& p)
        { // intercept OTL exceptions
            cerr << p.msg << endl; // print out error message
            cerr << p.stm_text << endl; // print out SQL that caused the error
            cerr << p.sqlstate << endl; // print out SQLSTATE message
            cerr << p.var_info << endl; // print out the variable that caused the error
        }
    }

    string getOutFileName()
    {
        return Out;
    }

    string getFrom()
    {
        return From;
    }

    string getTable()
    {
        return From;
    }

    string getWhere()
    {
        return Where;
    }

    string getSql()
    {
        return Sql;
    }
private:

    /**读取所有配置信息*/
    void readConfig(const string& config_file, const string& section_)
    {
        if (config_file.empty())
            LOG(FATAL) << "You need to specify which config to use" << "\n";
        LOG(INFO) << Pval(config_file) << "\n";
        LOG(INFO) << Pval(section_) << "\n";
        read_ini(config_file, pt); //初始化propetry tree 用于读取配置文件
        //先设置成默认配置
        ValGet(DBType, "mysql"); //默认是mysql数据库
        ValGet(Driver, "MySQL ODBC 3.51 Driver"); //这些sqlserver不需要不过没关系。。。
        ValGet(Option, "1048576");
        ValGet(Font, "gbk");
        ValGet(IP, "");
        ValGet(Port, "");
        ValGet(DB, "");
        ValGet(User, "");
        ValGet(Pwd, "");
        ValGet(Out, "");
        ValGet(Sql, ""); //如果Sql取出不为空，则忽略Selct From Where
        ValGet(Select, "");
        ValGet(From, "");
        ValGet(Where, "");
        ValGet(DataType, "int");
        ValGet(DataTypes, "");

        //获取具体section对应的配置，如果没有配置用上面的默认配置
        if (section_.empty())
        {
            LOG(WARNING) << "Do not use any section" << "\n";
            return;
        }

        PropGet(DBType, section_, DBType);
        PropGet(IP, section_, IP);
        PropGet(Port, section_, Port);
        PropGet(DB, section_, DB);
        PropGet(User, section_, User);
        PropGet(Pwd, section_, Pwd);
        PropGet(From, section_, From);
        PropGet(Out, section_, Out);
        PropGet(Sql, section_, Sql);
        PropGet(Select, section_, Select);
        PropGet(Where, section_, Where);
        PropGet(DataType, section_, DataType);
        PropGet(DataTypes, section_, DataTypes);
    }

    string getDBFile_mysql()
    {
        LOG(INFO) << "get db in base" << "\n";
        string db_file =
                (format("Driver = %1%; Database = %2%; UID = %3%; PWD = %4%; Server = %5%; port = %6%; stmt=set names %7%;Option = %8%")
                % Driver % DB % User % Pwd % IP % Port % Font % Option).str();
        return db_file;
    }

    string getDBFile_sqlserver()
    {
        LOG(INFO) << "getDBFile in sqlserver" << "\n";
        string db_file =
                (format("%1%/%2%@%3%")
                % User % Pwd % DB).str();
        return db_file;
    }

    string getDBFile()
    {
        if (DBType == "sqlserver")
        {
            return getDBFile_sqlserver();
        }
        else if (DBType == "mysql")
        {
            return getDBFile_mysql();
        }
        else
        {
            LOG(WARNING) << "Unsurported DB Type " << DBType << " assume it as sqlserver" << "\n";
            return getDBFile_sqlserver();
        }
    }

    void initDB()
    {
        ///初始化otl连接
        string db_file = getDBFile();

        LOG(INFO) << Pval(db_file) << "\n";
        try
        {
            conn.rlogon(db_file.c_str());
        }
        catch (otl_exception& p)
        {
            cerr << "failed: " << "\n"
                    << "\t" << p.msg << "\n"
                    << "\t" << p.stm_text << "\n"
                    << "\t" << p.sqlstate << "\n"
                    << "\t" << p.var_info << "\n"
                    << endl;
            exit(1);
        }

        LOG(INFO) << "Sucessfully logged the db file" << "\n";
    }

    void initSql()
    {
        cout << "initSql" << endl;
        if (!Sql.empty()) //如果已经读取到配置好的sql语句
            return;

        if (Select.empty()) //如果没有初始化的时候设置select语句表示外部运行时设置，setSql,可以多次设置，多次process,但是conn的连接是不变的
            return;

        if (Where.empty())
        {
            Sql = (format("SELECT %1% FROM %2%") % Select % From).str(); //select pid from talbe
        }
        else if (Where.find("%1%") == string::npos)
        {//如果有%1% 意味着程序需要自己再设置Where setWhere(boost::format(getWhere()%a%b).str())
            Sql = (format("SELECT %1% FROM %2% WHERE %3%") % Select % From % Where).str(); //select pid from talbe where date > 1982
        }

        Pval(Sql);
    }

    void initSql2()
    {

        if (Select.empty()) //如果没有初始化的时候设置select语句表示外部运行时设置，setSql,可以多次设置，多次process,但是conn的连接是不变的
            return;

        if (Where.empty())
        {
            Sql = (format("SELECT %1% FROM %2%") % Select % From).str(); //select pid from talbe
        }
        else if (Where.find("%1%") == string::npos)
        {//如果有%1% 意味着程序需要自己再设置Where setWhere(boost::format(getWhere()%a%b).str())
            Sql = (format("SELECT %1% FROM %2% WHERE %3%") % Select % From % Where).str(); //select pid from talbe where date > 1982
        }
    }

    void setSql(const string& sql)
    {
        Sql = sql;
    }

    void setSelect(const string& select)
    {
        Select = select;
        initSql2();
    }

    void setFrom(const string& from)
    {
        From = from;
        initSql2();
    }

    void setTable(const string& from)
    {
        From = from;
        initSql2();
    }

    void setWhere(const string& where)
    {
        Where = where;
        initSql2();
    }

    /**
     * 读取数据库表中的每一行，按照要求输出到文件或者屏幕, 但是这样要求数据类型全是一种类型
     * <pid, cust_id, count> int 还比较常见
     * <title, title_syn, title_pri> string 一般常见
     */
    template<typename T>
    void processWrite()
    {
        LOG(INFO) << Pval(Out) << "\n";
        vector<string> vec;
        boost::algorithm::split(vec, Select, boost::is_any_of(","));
        if (vec.empty())
            return;
        T data;

        try
        {
            otl_stream os(kBuffSize, Sql.c_str(), conn); //连接好数据库，并读出数据
            if (Out.empty())
                readWrite(os, vec.size(), data, std::cout);
            else
            {
                std::ofstream ofs(Out.c_str());
                readWrite(os, vec.size(), data, ofs);
            }

            os.flush();
            LOG(INFO) << "Finish reading and writting file" << "\n";
        }
        catch (otl_exception& p)
        { // intercept OTL exceptions
            cerr << p.msg << endl; // print out error message
            cerr << p.stm_text << endl; // print out SQL that caused the error
            cerr << p.sqlstate << endl; // print out SQLSTATE message
            cerr << p.var_info << endl; // print out the variable that caused the error
        }
        LOG(INFO) << "At the end of process write" << "\n";
    }

    /**第一个是int类型 后面是string*/
    void processWrite_int_str()
    {
        LOG(INFO) << Pval(Out) << "\n";
        vector<string> vec;
        boost::algorithm::split(vec, Select, boost::is_any_of(","));
        if (vec.size() < 2)
            return;

        try
        {
            otl_stream os(kBuffSize, Sql.c_str(), conn); //连接好数据库，并读出数据
            if (Out.empty())
                readWrite_int_str(os, vec.size(), std::cout);
            else
            {
                std::ofstream ofs(Out.c_str());
                readWrite_int_str(os, vec.size(), ofs);
            }
            os.flush();
        }
        catch (otl_exception& p)
        { // intercept OTL exceptions
            cerr << p.msg << endl; // print out error message
            cerr << p.stm_text << endl; // print out SQL that caused the error
            cerr << p.sqlstate << endl; // print out SQLSTATE message
            cerr << p.var_info << endl; // print out the variable that caused the error
        }
    }

    void processWrite_int_int_str()
    {
        LOG(INFO) << Pval(Out) << "\n";
        vector<string> vec;
        boost::algorithm::split(vec, Select, boost::is_any_of(","));
        if (vec.size() < 2)
            return;

        try
        {
            otl_stream os(kBuffSize, Sql.c_str(), conn); //连接好数据库，并读出数据
            if (Out.empty())
                readWrite_int_int_str(os, vec.size(), std::cout);
            else
            {
                std::ofstream ofs(Out.c_str());
                readWrite_int_int_str(os, vec.size(), ofs);
            }
            os.flush();
        }
        catch (otl_exception& p)
        { // intercept OTL exceptions
            cerr << p.msg << endl; // print out error message
            cerr << p.stm_text << endl; // print out SQL that caused the error
            cerr << p.sqlstate << endl; // print out SQLSTATE message
            cerr << p.var_info << endl; // print out the variable that caused the error
        }
    }

    void processWrite_mix()
    {
        LOG(INFO) << Pval(Out) << "\n";
        int data_num;
        vector<string> vec;
        boost::algorithm::split(vec, Select, boost::is_any_of(","));
        if (vec.empty())
            return;
        data_num = vec.size();
        vec.clear();
        boost::algorithm::split(vec, DataTypes, boost::is_any_of(","));
        LOG_IF(FATAL, vec.size() != data_num) << "You specifiy wrong number of data types" << std::endl;
        vector<int> types(data_num);
        for (int i = 0; i < data_num; i++)
        {
            try
            {
                types[i] = boost::lexical_cast<int>(vec[i]);
            }
            catch (...)
            {
                LOG(INFO) << "You spcify wrong data type" << "\n";
            }
        }

        try
        {
            otl_stream os(kBuffSize, Sql.c_str(), conn); //连接好数据库，并读出数据
            if (Out.empty())
                readWrite_mix(os, types, std::cout);
            else
            {
                std::ofstream ofs(Out.c_str());
                readWrite_mix(os, types, ofs);
            }
            os.flush();
        }
        catch (otl_exception& p)
        { // intercept OTL exceptions
            cerr << p.msg << endl; // print out error message
            cerr << p.stm_text << endl; // print out SQL that caused the error
            cerr << p.sqlstate << endl; // print out SQLSTATE message
            cerr << p.var_info << endl; // print out the variable that caused the error
        }
    }

    template<typename OutStream, typename T>
    void readWrite(otl_stream& os, int len, T& data, OutStream& out)
    {
        const string kspace = "\t";
        while (!os.eof())
        {
            size_t i;
            for (i = 0; i < len - 1; i++)
            {
                os >> data;
                out << data << kspace;
            }
            os >> data;
            out << data << "\n";
        }
    }

    template<typename OutStream>
    void readWrite_int_str(otl_stream& os, int len, OutStream& out)
    {
        const string kspace = "\t";
        int data_int;
        string data_str;
        while (!os.eof())
        {
            os >> data_int;
            out << data_int << kspace;
            size_t i;
            for (i = 0; i < len - 2; i++)
            {
                os >> data_str;
                out << data_str << kspace;
            }
            os >> data_str;
            out << data_str << "\n";
        }
    }

    template<typename OutStream>
    void readWrite_int_int_str(otl_stream& os, int len, OutStream& out)
    {
        const string kspace = "\t";
        int data_int;
        string data_str;
        while (!os.eof())
        {
            size_t i;
            for (i = 0; i < len - 1; i++)
            {
                os >> data_int;
                out << data_int << kspace;
            }
            os >> data_str;
            out << data_str << "\n";
        }
    }

    /**type 存储 Sql 语句中所有变量的类型 当前只支持int,string int<=>0 string<=>1*/
    template<typename OutStream>
    void readWrite_mix(otl_stream& os, vector<int>& type, OutStream& out)
    {
        string kspace = "\t";
        int num = type.size();
        string data_str;
        int data_int;
        while (!os.eof())
        {
            size_t i;
            for (i = 0; i < num; i++)
            {
                if (i == num - 1)
                    kspace = "\n";
                if (type[i] == StringType) //string 1
                {
                    os >> data_str;
                    out << data_str << kspace;
                }
                else //int 0
                {
                    os >> data_int;
                    out << data_int << kspace;
                }
            }
        }
    }

    bool execute()
    {
        LOG(INFO) << "excute sql: " << Sql << endl;
        try
        {
            otl_stream o(kBuffSize, Sql.c_str(), conn);
            conn.commit();
        }
        catch (otl_exception& p)
        {
            cerr << "OTL_DB_READER execute failed: " << "\n"
                    << "\tsql: " << Sql << "\n"
                    << "\t" << p.msg << "\n"
                    << "\t" << p.stm_text << "\n"
                    << "\t" << p.sqlstate << "\n"
                    << "\t" << p.var_info << "\n"
                    << endl;
            return false;
        }
        return true;
    }

    bool drop(const string& table)
    {
        Sql = "drop table " + table;
        return execute();
    }

    bool create(const string& table)
    {
        Sql = ("create table " + table + " ") + Sql;
        return execute();
    }

    bool insert(const string& table)
    {
        Sql = ("insert into " + table + " ") + Sql;
    }
};


#endif  //----end of OTL_DB_READER_H_
