/** 
 *  ==============================================================================
 * 
 *          \file   otl_db_reader.h
 *
 *        \author   gezi  
 *          
 *          \date   2010-10-25 09:04:28.111630
 *  
 *  \Description:   ϣ���ṩһ������Ķ����ݣ�д<a,b,c..> ������ʽ���ı�
 *                  ����֧�ֲ�ͬ���ȣ����Ī���� '\t' ������, ������һ�� '\t'�� '\t\n'
 *
 *                  Ҫ�������ݿ����ú�Ҫд���ļ����������ļ�read_db.ini����
 *
 *                  read_db.cc ��ӦĬ��ʹ�ó���
 *
 *                  ͬʱ�ṩһ���ӿڣ����ⲿ�����º���ʹ��otl_stream����
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
 * ��������mysql��DBReader,��ʵSqlServer�ĸ��򵥣����������д�ľ���Ϊbase��
 * DBReader Ҳ֧��д���ݿ�Ȳ���
 */
class DBReader
{
private:
    string DBType; //��mysql ���� sqlserver 
    string Driver, Option, Font;
    string IP, Port, DB, User, Pwd; ///for read db
    string From; ///��Ҫ��ȡ�ı���
    string Out; ///Ҫд���ļ�����
    string Select, Where, DataType, DataTypes; ///��ѯ�����䲿��
    string Sql; ///�����߽�����sql��䣬���� Select Whre From

    otl_connect conn; ///otl����
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
        logOff(); //�ر����ݿ�����
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

    /**���������ļ�ִ������sql����,Ҳ����ֱ����ִ��setSql�����ȵ�*/
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

    /**TODO ����ܷ��㴦�����������أ�����sort�ܽ�����ʱ��functor��������ʱ�����ϣ���ܴ�������*/

    /*�ƺ�û�кð취Ҫô��дһ��Func& дһ��const Func& Ҫô��ɴ�ֻдһ��const Func& ������������warning ˵���constȥ���� �Ǻ�
     */
    template<typename Func>
    void process(const Func& func)
    {
        //        process(func);
        LOG(INFO) << Pval(Sql) << "\n";
        try
        {
            otl_stream os(kBuffSize, Sql.c_str(), conn); //���Ӻ����ݿ⣬����������
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
            otl_stream os(1, Sql.c_str(), conn); //���Ӻ����ݿ⣬д����
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
            otl_stream os(1, Sql.c_str(), conn); //���Ӻ����ݿ⣬д����
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

    /**��ȡ����������Ϣ*/
    void readConfig(const string& config_file, const string& section_)
    {
        if (config_file.empty())
            LOG(FATAL) << "You need to specify which config to use" << "\n";
        LOG(INFO) << Pval(config_file) << "\n";
        LOG(INFO) << Pval(section_) << "\n";
        read_ini(config_file, pt); //��ʼ��propetry tree ���ڶ�ȡ�����ļ�
        //�����ó�Ĭ������
        ValGet(DBType, "mysql"); //Ĭ����mysql���ݿ�
        ValGet(Driver, "MySQL ODBC 3.51 Driver"); //��Щsqlserver����Ҫ����û��ϵ������
        ValGet(Option, "1048576");
        ValGet(Font, "gbk");
        ValGet(IP, "");
        ValGet(Port, "");
        ValGet(DB, "");
        ValGet(User, "");
        ValGet(Pwd, "");
        ValGet(Out, "");
        ValGet(Sql, ""); //���Sqlȡ����Ϊ�գ������Selct From Where
        ValGet(Select, "");
        ValGet(From, "");
        ValGet(Where, "");
        ValGet(DataType, "int");
        ValGet(DataTypes, "");

        //��ȡ����section��Ӧ�����ã����û�������������Ĭ������
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
        ///��ʼ��otl����
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
        if (!Sql.empty()) //����Ѿ���ȡ�����úõ�sql���
            return;

        if (Select.empty()) //���û�г�ʼ����ʱ������select����ʾ�ⲿ����ʱ���ã�setSql,���Զ�����ã����process,����conn�������ǲ����
            return;

        if (Where.empty())
        {
            Sql = (format("SELECT %1% FROM %2%") % Select % From).str(); //select pid from talbe
        }
        else if (Where.find("%1%") == string::npos)
        {//�����%1% ��ζ�ų�����Ҫ�Լ�������Where setWhere(boost::format(getWhere()%a%b).str())
            Sql = (format("SELECT %1% FROM %2% WHERE %3%") % Select % From % Where).str(); //select pid from talbe where date > 1982
        }

        Pval(Sql);
    }

    void initSql2()
    {

        if (Select.empty()) //���û�г�ʼ����ʱ������select����ʾ�ⲿ����ʱ���ã�setSql,���Զ�����ã����process,����conn�������ǲ����
            return;

        if (Where.empty())
        {
            Sql = (format("SELECT %1% FROM %2%") % Select % From).str(); //select pid from talbe
        }
        else if (Where.find("%1%") == string::npos)
        {//�����%1% ��ζ�ų�����Ҫ�Լ�������Where setWhere(boost::format(getWhere()%a%b).str())
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
     * ��ȡ���ݿ���е�ÿһ�У�����Ҫ��������ļ�������Ļ, ��������Ҫ����������ȫ��һ������
     * <pid, cust_id, count> int ���Ƚϳ���
     * <title, title_syn, title_pri> string һ�㳣��
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
            otl_stream os(kBuffSize, Sql.c_str(), conn); //���Ӻ����ݿ⣬����������
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

    /**��һ����int���� ������string*/
    void processWrite_int_str()
    {
        LOG(INFO) << Pval(Out) << "\n";
        vector<string> vec;
        boost::algorithm::split(vec, Select, boost::is_any_of(","));
        if (vec.size() < 2)
            return;

        try
        {
            otl_stream os(kBuffSize, Sql.c_str(), conn); //���Ӻ����ݿ⣬����������
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
            otl_stream os(kBuffSize, Sql.c_str(), conn); //���Ӻ����ݿ⣬����������
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
            otl_stream os(kBuffSize, Sql.c_str(), conn); //���Ӻ����ݿ⣬����������
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

    /**type �洢 Sql ��������б��������� ��ǰֻ֧��int,string int<=>0 string<=>1*/
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
