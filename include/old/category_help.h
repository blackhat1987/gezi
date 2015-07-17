/* 
 * File:   category_help.h
 * Author: chenghuige
 *  当当类别PATH信息的一些处理
 *  当当类别PATH 在category  数据库中表示为  01.00.00.00.00.00的格式
 *  这里在PYTHON数据库读取预处理中去掉了. 即表示为0100000000
 *
 *  6.29 加入了一个专门处理类别信息的类
 * Created on 2010年2月25日, 下午3:23
 */

#ifndef _CATEGORY_HELPE_H
#define	_CATEGORY_HELPE_H
//#include <glog/logging.h>
#include <fstream>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/lexical_cast.hpp>

#include <tr1/unordered_map>
#include "KeywordMapID.h"
#include "debug_help.h"


//FIXME这个对象作为 unorderd_map<string,CategoryInfo>序列化读入会有问题，
//程序退出后出现内存问题,也就是unorderd_map序列化目前似乎只是简单的类型没有问题 TODO

struct CategoryInfo
{
    string path; //00.00.00
    string name; //手机
    int level; //几级类

    CategoryInfo()
    {
    }

    CategoryInfo(const string& _path, const string& _name, int _level)
    : path(_path), name(_name), level(_level)
    {
    }

    ~CategoryInfo()
    {
    }

    void setData(const string& _path, const string& _name, int _level)
    {
        path = _path;
        name = _name;
        level = _level;
    }

    friend class boost::serialization::access; //for 序列化
    //-----------------序列化

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & path;
        ar & name;
        ar & level;
    }
};

///是否是百货类别（当前如果前缀01 07,认为是图书, 03 05 音像制品）

inline bool isHarrodCategory(const string& path)
{
    if ((path[0] == '0' &&
            (path[1] == '1' || path[1] == '3'
            || path[1] == '5' || path[1] == '7' || path[1] == '8'))
            || (path[0] == '1' && path[1] == '0') || (path[0] == '5' && path[1] == '1'))
        return false;
    else
        return true;
}

///通过path 得到它的类别级别

inline int getCategoryLevel(const string& path)
{
    int level = 0;
    for (size_t i = 0; i < path.size(); i += 2)
    {
        if (path[i] != '0' || path[i + 1] != 0)
            level++;
        else
            break;
    }
    return level;
}

///得到父类path,注意不要传0级类

inline string getParentPath(const string& path)
{
    string parent_path;
    parent_path = path;
    for (int i = (int) path.size() - 1; i >= 0; i -= 2)
    {
        if (path[i] != '0' || path[i - 1] != '0')
        {
            parent_path[i] = '0';
            parent_path[i - 1] = '0';
            break;
        }
    }
    return parent_path;
}

//判断path2是否是path1的子path,注意path1 = path2,也视为path2是path1的子path

inline bool isChildPath(const string& path1, const string& path2)
{
    if (path1.empty() || path2.empty())
        return false;
    for (size_t i = 0; i < path1.size(); i += 2)
    {
        if (path1[i] != '0' || path1[i + 1] != '0')
        {
            if (path1[i] != path2[i] || path1[i + 1] != path2[i + 1])
                return false;
        }
        else
            break;
    }
    return true;
}

///内部我把path的.去掉了，这里把.加上转换便于显示

inline string path(const string& ipath)
{
    string path;
    path.push_back(ipath[0]);
    for (size_t i = 1; i < ipath.size(); i++)
    {
        if (i % 2 == 0)
        {
            path.push_back('.');
        }
        path.push_back(ipath[i]);
    }
    return path;
}
//类别id到其它信息的映射
#include <tr1/unordered_map>
typedef std::tr1::unordered_map<int, CategoryInfo> ID2InfoMap;

/**
 * 类别信息帮助类
 */
class CategoryHelper
{
protected:
    //path 到 id 的映射
    typedef std::tr1::unordered_map<string, int> Path2IDMap;
    std::vector<CategoryInfo> m_idInfoMap;
    Path2IDMap m_pathIDMap; //path -> id
    CKeyDictionaryMap<int> m_id2Internal; //  id <-> internal id  // from 0 in sequence
    const static int kPathLength = 12; //6 * 2

public:

    CategoryHelper(const string& cat_file = "static_data/category_sorted.txt")
    {
        load(cat_file.c_str());

        //LOG(INFO) << Pval(getParent(4002084));
    }

    void load(const char* file)
    {
        //LOG(INFO) << "Load category info" << endl;
        FILE *pSrcFile = fopen(file, "rb");

        //LOG_IF(FATAL, !pSrcFile) << "failed to open " << file << "\n";

        char chBuffer[102400];

        int cid, level;
        char path[1024];
        char name[1024];
        int id = 0;
        string path_str;
        string name_str;
        while (fgets(chBuffer, 102400, pSrcFile) != NULL)
        {
            memset(path, '\0', 1024);
            memset(name, '\0', 1024);
            sscanf(chBuffer, "%d %s %s %d", &cid, path, name, &level); //or use stringstream

            path_str = path;
            name_str = name;

            id = m_id2Internal.AddKeyID(cid);

            m_idInfoMap.push_back(CategoryInfo(path_str, name_str, level));

            if (m_pathIDMap.find(path_str) == m_pathIDMap.end()) //path -> id path 到内部id
            {
                m_pathIDMap[path_str] = id;
            }

        }

        fclose(pSrcFile);
    }

    bool isCatID(int cid)
    {
        return m_id2Internal.HasKeyItem(cid);
    }

    int getCatNum()
    {
        return m_idInfoMap.size();
    }

    int getID(int cid)
    {
        return m_id2Internal.GetIDFromKey(cid);
    }

    int getCatIDFromID(int id)
    {
        return m_id2Internal.GetKeyFromID(id);
    }

    string getCatNameFromID(int id)
    {
        return m_idInfoMap[id].name;
    }

    int getCatLevelFromID(int id)
    {
        return m_idInfoMap[id].level;
    }

    string getCatPathFromID(int id)
    {
        return m_idInfoMap[id].path;
    }

    int getCatLevel(int cid) const
    {
        if (!m_id2Internal.HasKeyItem(cid)) //do not has this cat id
            return -1;

        int id = m_id2Internal.GetIDFromKey(cid);

        return m_idInfoMap[id].level;
    }

    string getCatPath(int cid)
    {
        if (!m_id2Internal.HasKeyItem(cid)) //do not has this cat id
            return "";

        int id = m_id2Internal.GetIDFromKey(cid);

        return m_idInfoMap[id].path;
    }

    string getCatName(int cid)
    {//TODO 其它 是否 特殊处理下？
        if (!m_id2Internal.HasKeyItem(cid)) //do not has this cat id
            return "";

        int id = m_id2Internal.GetIDFromKey(cid);

        return m_idInfoMap[id].name;
    }

    CategoryInfo getCatInfo(int cid)
    {
        if (!m_id2Internal.HasKeyItem(cid)) //do not has this cat id
            return CategoryInfo("", "", -1);

        int id = m_id2Internal.GetIDFromKey(cid);

        return m_idInfoMap[id];
    }

    ///判断cid2是否是cid1的子类，或者是相同类别

    bool isChildCat(int cid1, int cid2)
    {
        string path1 = getCatPath(cid1);
        string path2 = getCatPath(cid2);
        return isChildPath(path1, path2);
    }

    string getInterPath(const string& ipath)
    {//10.34.25.00 ->103425000000
        string path;
        size_t i = 0;
        for (i = 0; i < ipath.size(); i++)
        {
            if ((i + 1) % 3 == 0)
            {
                continue;
            }
            path.push_back(ipath[i]);
        }
        i = path.size();
        for (; i < kPathLength; i++)
        {
            path.push_back('0');
        }
        return path;
    }

    int getCatIDFromPath(const string& path)
    {
        string ipath = getInterPath(path);
        return getCatIDFromInterPath(ipath);
    }

    int getCatIDFromInterPath(const string& ipath)
    {
        if (m_pathIDMap.find(ipath) == m_pathIDMap.end())
            return -1;
        return m_id2Internal.GetKeyFromID(m_pathIDMap[ipath]);
    }

    int getIDFromPath(const string& path)
    {
        string ipath = getInterPath(path);
        return getIDFromInterPath(ipath);
    }

    int getIDFromInterPath(const string& ipath)
    {
        if (m_pathIDMap.find(ipath) == m_pathIDMap.end())
            return -1;
        return m_pathIDMap[ipath];
    }

    bool isAdultCat(int cid, int adult_cat_id = 4001661)
    { //因为成人用品顶级类别一般不会改变id 所以默认这里写死即可 如果以后改动 注意这里手动改动 毕竟更新频率很低 应有程序可能考虑成人用品id透明
        return isChildPath(getCatPath(adult_cat_id), getCatPath(cid));
    }

    bool isAdultCatID(int id, int adult_cat_id = 4001661)
    {
        return isAdultCat(getCatIDFromID(id), adult_cat_id);
    }
    ///获得向上的某个level的祖先类别id
    //如果cid是levle 3, 要获得level 4的则返回-1,表示不可能,如果要获得level 3的则返回cid 本身
    //都是通过path作为中转 获得相关信息，因为速度要求不是太高还ok,否则可以预先建立相关的索引

    int getParent(int cid, int level)
    {
        if (level < 0)
            return -1;

        int cur_level = getCatLevel(cid);
        if (cur_level < level)
            return -1;

        if (cur_level == level)
            return cid;

        string cur_path = getCatPath(cid);
        int times = cur_level - level;
        for (int i = 0; i < times; i++)
        {
            cur_path = getParentPath(cur_path);
        }

        return getCatIDFromInterPath(cur_path);
    }

    int getParent(int cid)
    {
        int cur_level = getCatLevel(cid);
        if (cur_level <= 0)
            return -1;

        string cur_path = getCatPath(cid);
        cur_path = getParentPath(cur_path);
        return getCatIDFromInterPath(cur_path);
    }

    int getParentID(int id, int level)
    {
        if (level < 0)
            return -1;

        int cur_level = getCatLevelFromID(id);
        if (cur_level < level)
            return -1;

        if (cur_level == level)
            return id;

        string cur_path = getCatPathFromID(id);
        int times = cur_level - level;
        for (int i = 0; i < times; i++)
        {
            cur_path = getParentPath(cur_path);
        }

        return getIDFromInterPath(cur_path);
    }

    int getParentID(int id)
    {
        int cur_level = getCatLevelFromID(id);
        if (cur_level <= 0)
            return -1;

        string cur_path = getCatPathFromID(id);
        cur_path = getParentPath(cur_path);
        return getIDFromInterPath(cur_path);
    }

    /**
     * 不再通过path判断是否是百货类别，直接通过是否400开头判断
     */
    bool isHarrodCat(int cid)
    {
        string cid_str = boost::lexical_cast<string > (cid);
        string kB2CCatIDStart = "400";
        if (cid_str.substr(0, kB2CCatIDStart.size()) == kB2CCatIDStart)
            return true;
        return false;
        //        if (!m_id2Internal.HasKeyItem(cid)) //do not has this cat id
        //            return false;
        //        return isHarrodCategory(getCatPath(cid));
    }

    bool isHarrodID(int id)
    {
        return isHarrodCat(getCatIDFromID(id));
    }

    /**
     *  到二级类的过程存储
     */
    void getFullPath(int cid, vector<string>& vec, int top_level = 2)
    {
        vec.clear();
        vec.push_back(boost::lexical_cast<string > (cid));
        int level = getCatLevel(cid);

        while (level > top_level)
        {
            cid = getParent(cid);
            if (cid != -1)
                vec.push_back(boost::lexical_cast<string > (cid));
            else
                break;
            level--;
        }
    }

    void getFullPath(int cid, vector<string>& vec, vector<string>& vec2, int top_level = 2)
    {
        vec.clear();
        vec2.clear();
        vec.push_back(boost::lexical_cast<string > (cid));
        vec2.push_back(getCatName(cid));
        int level = getCatLevel(cid);

        while (level > top_level)
        {
            cid = getParent(cid);
            if (cid != -1)
            {
                vec.push_back(boost::lexical_cast<string > (cid));
                vec2.push_back(getCatName(cid));
            }
            else
                break;
            level--;
        }
    }
};

inline void addAllCatName(CKeyDictionaryMap<string>& dict)
{
    CategoryHelper cat_helper; //这个是为了统一m_phr2id字典所必须的
    int cat_num;
    cat_num = cat_helper.getCatNum();
    for (int i = 0; i < cat_num; i++)
    {
        dict.AddKeyID(boost::lexical_cast<string > (cat_helper.getCatIDFromID(i)));
    }
}

/*
 * for adindex.load
 * 按照类别level从大到小排序
 */
struct CatCmpStr
{
public:
    const CategoryHelper m_catHelper;

    CatCmpStr(const CategoryHelper & cat_helper)
    : m_catHelper(cat_helper)
    {
    }

    bool operator () (const string& cat1, const string & cat2) const
    {
        return m_catHelper.getCatLevel(boost::lexical_cast<int>(cat1)) >
                m_catHelper.getCatLevel(boost::lexical_cast<int>(cat2));
    }
};


#endif	/* _CATEGORY_HELPE_H */

