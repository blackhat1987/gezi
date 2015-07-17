/* 
 * File:   category_help.h
 * Author: chenghuige
 *  �������PATH��Ϣ��һЩ����
 *  �������PATH ��category  ���ݿ��б�ʾΪ  01.00.00.00.00.00�ĸ�ʽ
 *  ������PYTHON���ݿ��ȡԤ������ȥ����. ����ʾΪ0100000000
 *  ./read -table category
 *
 *  6.29 ������һ��ר�Ŵ��������Ϣ����
 * Created on 2010��2��25��, ����3:23
 */

#ifndef _CATEGORY_HELPE_H
#define	_CATEGORY_HELPE_H
#include <fstream>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/lexical_cast.hpp>
#include <glog/logging.h>
#include <tr1/unordered_map>
#include "KeywordMapID.h"
#include "debug_help.h"


//FIXME���������Ϊ unorderd_map<string,CategoryInfo>���л�����������⣬
//�����˳�������ڴ�����,Ҳ����unorderd_map���л�Ŀǰ�ƺ�ֻ�Ǽ򵥵�����û������ TODO
struct CategoryInfo
{
    string path; //00.00.00
    string name; //�ֻ�
    int level; //������
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

    friend class boost::serialization::access; //for ���л�
    //-----------------���л�
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & path;
        ar & name;
        ar & level;
    }
};

///�Ƿ��ǰٻ���𣨵�ǰ���ǰ׺01 07,��Ϊ��ͼ��, 03 05 ������Ʒ��
inline bool isHarrodCategory(const string& path)
{
    if (path[0] == '0' && (path[1] == '1' || path[1] == '3' || path[1] == '5' || path[1] == '7'))
        return false;
    else
        return true;
}

///ͨ��path �õ�������𼶱�
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

///�õ�����path,ע�ⲻҪ��0����
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

//�ж�path2�Ƿ���path1����path,ע��path1 = path2,Ҳ��Ϊpath2��path1����path
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

///�ڲ��Ұ�path��.ȥ���ˣ������.����ת��������ʾ
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
//���id��������Ϣ��ӳ��
#include <tr1/unordered_map>
typedef std::tr1::unordered_map<int, CategoryInfo> ID2InfoMap;
/**
 * �����Ϣ������
 */
class CategoryHelper
{
private:
    //path �� id ��ӳ��
    typedef std::tr1::unordered_map<string, int> Path2IDMap;
    std::vector<CategoryInfo> m_idInfoMap;
    Path2IDMap m_pathIDMap; //path -> id
    CKeyDictionaryMap<int> m_id2Internal; //  id <-> internal id  // from 0 in sequence
public:
    CategoryHelper(const char* cat_file = "temp_data/category_sorted.txt")
    {
        load(cat_file);

        LOG(INFO) << Pval(getParent(4002084));
    }
    void load(const char* file)
    {
        LOG(INFO) << "Load category info" << endl;
        FILE *pSrcFile = fopen(file, "rb");

        if (!pSrcFile)
            LOG(ERROR) << "failed to open " << file << "\n";

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
            sscanf(chBuffer, "%d %s %s %d", &cid, path, name, &level);

            path_str = path;
            name_str = name;

            id = m_id2Internal.AddKeyID(cid);

            m_idInfoMap.push_back(CategoryInfo(path_str, name_str, level));

            if (m_pathIDMap.find(path_str) == m_pathIDMap.end()) //path -> id path ���ڲ�id
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
    int getCatLevel(int cid)
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
    {
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

    ///�ж�cid2�Ƿ���cid1�����࣬��������ͬ���
    bool isChildCat(int cid1, int cid2)
    {
        string path1 = getCatPath(cid1);
        string path2 = getCatPath(cid2);
        return isChildPath(path1, path2);
    }
    int getIDFromPath(const string& path)
    {
        if (m_pathIDMap.find(path) == m_pathIDMap.end())
            return -1;
        return m_id2Internal.GetKeyFromID(m_pathIDMap[path]);
    }

    ///������ϵ�ĳ��level���������id
    //���cid��levle 3, Ҫ���level 4���򷵻�-1,��ʾ������,���Ҫ���level 3���򷵻�cid ����
    //����ͨ��path��Ϊ��ת ��������Ϣ����Ϊ�ٶ�Ҫ����̫�߻�ok,�������Ԥ�Ƚ�����ص�����
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

        return getIDFromPath(cur_path);
    }
    int getParent(int cid)
    {
        int cur_level = getCatLevel(cid);
        if (cur_level <= 0)
            return -1;

        string cur_path = getCatPath(cid);
        cur_path = getParentPath(cur_path);
        return getIDFromPath(cur_path);
    }
    bool isHarrodCat(int cid)
    {
        return isHarrodCategory(getCatPath(cid));
    }
    /**
     *  ��������Ĺ��̴洢
     */
    void getFullPath(int cid, vector<string>& vec)
    {
        vec.clear();
        vec.push_back(boost::lexical_cast<string > (cid));
        int level = getCatLevel(cid);

        while (level > 2)
        {
            cid = getParent(cid);
            if (cid != -1)
                vec.push_back(boost::lexical_cast<string > (cid));
            else
                break;
            level--;
        }
    }
};

inline void addAllCatName(CKeyDictionaryMap<string>& dict)
{
    CategoryHelper cat_helper; //�����Ϊ��ͳһm_phr2id�ֵ��������
    int cat_num;
    cat_num = cat_helper.getCatNum();
    for (int i = 0; i < cat_num; i++)
    {
        dict.AddKeyID(boost::lexical_cast<string > (cat_helper.getCatIDFromID(i)));
    }
}
#endif	/* _CATEGORY_HELPE_H */

