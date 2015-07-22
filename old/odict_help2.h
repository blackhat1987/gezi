/** 
 *  ==============================================================================
 * 
 *          \file   odict_help2.h
 *
 *        \author   chenghuige  
 *          \date   2011-05-10 19:46:40.980996
 *  
 *  \Description:  ODICT的C++简单封装  只针对支持string类型
 *                 TODO gsparse hash map  或者 dense hashmap tr1::unordered map如果用这个签名效果如何
 *                 不过key是两个u_int 64bit签名 相当 TODO考虑研究下各种签名函数
 *  ==============================================================================
 */

#ifndef ODICT_HELP2_H_
#define ODICT_HELP2_H_
#include "ul_sign.h"
#include "odict.h"
#include <limits>
#include <string>
#include <boost/filesystem.hpp>
#include "ul_log_help.h"

const char* odict_file_name = "odict";
class ODictBuilder
{
public:
    ODictBuilder(int hash_num = -1)
    {
        sdb = odb_creat(hash_num);
    }
    ~ODictBuilder()
    {
        if (sdb)
            odb_destroy(sdb);
    }
    void clear()
    {
        odb_destroy(sdb);
        sdb = NULL;
    }
    inline bool has(const std::string& phrase) const
    {
        sodict_snode_t snode;
        u_int sign1, sign2;
        //        creat_sign_fs64((char *) phrase.c_str(), phrase.size(), &sign1, &sign2);
        creat_sign_fs64((char *) phrase.c_str(), phrase.size(), &sign1, &sign2);
        snode.sign1 = sign1;
        snode.sign2 = sign2;

        return ODB_SEEK_OK == odb_seek(sdb, &snode);
    }
    inline bool get(const std::string& phrase, unsigned int & value) const
    {
        sodict_snode_t snode;
        u_int sign1, sign2;
        //        creat_sign_fs64((char *) phrase.c_str(), phrase.size(), &sign1, &sign2);
        creat_sign_fs64((char *) phrase.c_str(), phrase.size(), &sign1, &sign2);
        snode.sign1 = sign1;
        snode.sign2 = sign2;

        if (ODB_SEEK_OK == odb_seek(sdb, &snode))
        {
            value = snode.cuint1;
            return true;
        }
        else
        {
            return false;
        }
    }
    inline int id(const std::string& phrase) const
    {
        sodict_snode_t snode;
        u_int sign1, sign2;
        //        creat_sign_fs64((char *) phrase.c_str(), phrase.size(), &sign1, &sign2);
        creat_sign_fs64((char *) phrase.c_str(), phrase.size(), &sign1, &sign2);
        snode.sign1 = sign1;
        snode.sign2 = sign2;

        if (ODB_SEEK_OK == odb_seek(sdb, &snode))
        {
            return (int) snode.cuint1;
        }
        else
        {
            return null_id;
        }
    }
    inline int id(const std::string& phrase, sodict_snode_t& snode) const
    {
        u_int sign1, sign2;
        //        creat_sign_fs64((char *) phrase.c_str(), phrase.size(), &sign1, &sign2);
        creat_sign_fs64((char *) phrase.c_str(), phrase.size(), &sign1, &sign2);
        snode.sign1 = sign1;
        snode.sign2 = sign2;

        if (ODB_SEEK_OK == odb_seek(sdb, &snode))
        {
            return (int) snode.cuint1;
        }
        else
        {
            return null_id;
        }
    }
    inline bool add(sodict_snode_t& snode, unsigned int value = std::numeric_limits<unsigned int>::max())
    {
        snode.cuint1 = value;
        return ODB_ADD_OK == odb_add(sdb, &snode, 1);
    }
    inline bool add(const std::string& phrase, unsigned int value = std::numeric_limits<unsigned int>::max())
    {
        sodict_snode_t snode;
        u_int sign1, sign2;
        //        creat_sign_fs64((char *) phrase.c_str(), phrase.size(), &sign1, &sign2);
        creat_sign_fs64((char *) phrase.c_str(), phrase.size(), &sign1, &sign2);
        snode.sign1 = sign1;
        snode.sign2 = sign2;
        snode.cuint1 = value;
        return ODB_ADD_OK == odb_add(sdb, &snode, 1);
    }
    inline bool modify(const std::string& phrase, unsigned int value = std::numeric_limits<unsigned int>::max())
    {
        sodict_snode_t snode;
        u_int sign1, sign2;
        //        creat_sign_fs64((char *) phrase.c_str(), phrase.size(), &sign1, &sign2);
        creat_sign_fs64((char *) phrase.c_str(), phrase.size(), &sign1, &sign2);
        snode.sign1 = sign1;
        snode.sign2 = sign2;
        snode.cuint1 = value;
        return ODB_ADD_OK == odb_add(sdb, &snode, 1);
    }
    bool save(const std::string& dir, const std::string& file = odict_file_name)
    {
        namespace bf = boost::filesystem;
        bf::path path(dir); //如果索引输出路径文件夹未被建立则首先建立，比如update_data/abc,需要首先建立abc文件夹
        if (!bf::exists(path))
        {
            LOG_WARNING("%s not exist, will create first", dir.c_str());
            bf::create_directories(path);
        }
        return ODB_SAVE_OK == odb_save(sdb, (char *) dir.c_str(), (char *) file.c_str());
    }
    /**
     * 明文文件读入数据
     */
    bool load(const string& file)
    {
        std::ifstream ifs(file.c_str());
        if (!ifs.is_open())
        {
            LOG_ERROR("Open %s failed\n", file.c_str());
            return false;
        }

        std::string line, key;
        int id = 0;
        while (std::getline(ifs, line))
        {
            int pos = line.find("\t");
            if (pos == std::string::npos)
            {
                key = line;
            }
            else
            {
                key = line.substr(0, pos);
            }
            add(key, id++);
        }

        return true;
    }
    bool create(const string& file)
    {
        return load(file);
    }
    int size() const
    {
        return odb_get_nodenum(sdb);
    }

private:
    static const int null_id = -1;
    sodict_build_t *sdb; //for build only
};
class ODict
{
public:
    ODict()
    : ssdb(NULL)
    {

    }
    ~ODict()
    {
        if (ssdb)
            odb_destroy_search(ssdb);
    }
    inline bool has(const std::string& phrase) const
    {
        sodict_snode_t snode;
        u_int sign1, sign2;
        //        creat_sign_fs64((char *) phrase.c_str(), phrase.size(), &sign1, &sign2);
        creat_sign_fs64((char *) phrase.c_str(), phrase.size(), &sign1, &sign2);
        snode.sign1 = sign1;
        snode.sign2 = sign2;
        return ODB_SEEK_OK == odb_seek_search(ssdb, &snode);
    }
    void clear()
    {
        odb_destroy_search(ssdb);
        ssdb = NULL;
    }
    int size() const
    {
        return odb_search_get_nodenum(ssdb);
    }
    bool load(const std::string& path, const std::string& file = odict_file_name)
    {
        ssdb = odb_load_search((char *) path.c_str(), (char *) file.c_str());
        return ssdb != NULL;
    }
    inline bool get(const std::string& phrase, unsigned int & value) const
    {
        sodict_snode_t snode;
        u_int sign1, sign2;
        //        creat_sign_fs64((char *) phrase.c_str(), phrase.size(), &sign1, &sign2);
        creat_sign_fs64((char *) phrase.c_str(), phrase.size(), &sign1, &sign2);
        snode.sign1 = sign1;
        snode.sign2 = sign2;

        if (ODB_SEEK_OK == odb_seek_search(ssdb, &snode))
        {
            value = snode.cuint1;
            return true;
        }
        else
        {
            return false;
        }
    }
    inline int id(const std::string& phrase) const
    {
        sodict_snode_t snode;
        u_int sign1, sign2;
        //        creat_sign_fs64((char *) phrase.c_str(), phrase.size(), &sign1, &sign2);
        creat_sign_fs64((char *) phrase.c_str(), phrase.size(), &sign1, &sign2);
        snode.sign1 = sign1;
        snode.sign2 = sign2;

        if (ODB_SEEK_OK == odb_seek_search(ssdb, &snode))
        {
            return (int) snode.cuint1;
        }
        else
        {
            return null_id;
        }
    }
    //    void report_node(sodict_snode_t *node, int *stop_now)
    //    {
    //        fprintf(stderr, "sign1: %u\n", node->sign1);
    //        fprintf(stderr, "sign2: %u\n", node->sign2);
    //        fprintf(stderr, "custom data1: %u\n", node->cuint1);
    //        fprintf(stderr, "custom data2: %u\n", node->cuint2);
    //
    //        // if (....) {
    //        //   *stop_now设置为1, 可以终止遍历
    //        //   *stop_now = 1;
    //        //}
    //    }
    //    void search_report(sodict_search_t *sdb)
    //    {
    //        odb_traverse_search(sdb, report_node);
    //    }
private:
    static const int null_id = -1;
    sodict_search_t *ssdb; //for search only
};
#endif  //----end of ODICT_HELP_H_
