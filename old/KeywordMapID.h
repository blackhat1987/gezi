/**
 *  ==============================================================================
 *
 *          \file   KeywordMapID.h
 *
 *                    10.03.04�����������л�дvector���ļ��������л����룬��ͨ��vector��ʼhash
 *                    �ٶȺ�Load��࣬���ļ��Կ�
 *  ==============================================================================
 */

#ifndef KEYWORD_MAP_ID_H
#define KEYWORD_MAP_ID_H

#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#if __GNUC__ > 3
#include<tr1/unordered_map>  //chg modified using unordered map
#else 
#include <boost/unordered_map.hpp>
#endif
#include <fstream>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
using namespace std;

template<typename T>
class CKeyDictionaryMap {
public:

    CKeyDictionaryMap()
    {
    }

    ~CKeyDictionaryMap()
    {
    }

public:

    typedef T item_type;
    typedef size_t id_type;

    static const size_t null_id;
    typedef typename std::vector<T>::iterator iterator;
    typedef typename std::vector<T>::const_iterator const_iterator;

    iterator begin()
    {
        return m_index.begin();
    }

    iterator end()
    {
        return m_index.end();
    }

    const_iterator begin()const
    {
        return m_index.begin();
    }

    const_iterator end()const
    {
        return m_index.end();
    }

    size_t size()const
    {
        return m_index.size();
    }

    bool empty()const
    {
        return m_index.empty();
    }

private:
#if __GNUC__ > 3
    typedef std::tr1::unordered_map<T, id_type> hash_map_type;
#else
    typedef boost::unordered_map<T, id_type> hash_map_type;
#endif
    //mutable hash_map_type m_hashdict;
    hash_map_type m_hashdict;
    std::vector<T> m_index; //kid->key
public:

    ///����boost ���л���û�ж�unorderd_map��֧��:(��
    ///�������л�����m_index����Ҫ�ֶ���ʼ���鰸
    ///�ҳ�������unorderd_map_serilize.h�ɹ��Ľ�hash���л����ɶ�д������
    ///�����൫�ǲ�����ʾ���ж�����ٶȲ���Load :(
    ///Ҫ��m_index�Ѿ��������

    void regainHash()
    {
        for (size_t i = 0; i < m_index.size(); i++) {
            m_hashdict[m_index[i]] = i;
        }
    }

    //clear dic

    void ClearDic()
    {
        hash_map_type().swap(m_hashdict);
        vector<T > ().swap(m_index);
    }

    // get a item's key from id

    inline const T& GetKeyFromID(id_type nID)
    {
        return m_index.at(nID);
    }

    // add a item into dict return new item's id

    inline id_type AddKeyID(const T& f)
    {
        typename hash_map_type::const_iterator it = m_hashdict.find(f);
        if (it != m_hashdict.end())
            return it->second;

        id_type id = m_index.size();
        m_hashdict[f] = id;
        m_index.push_back(f);
        return id;
    }

    //get a item's id (index in dict),if the item does not exist return null_id

    inline id_type GetIDFromKey(const T& f) const
    {
        typename hash_map_type::const_iterator it = m_hashdict.find(f);
        if (it == m_hashdict.end())
            return null_id;
        return it->second;
    }

    //is or not is key item in dict),

    inline bool HasKeyItem(const T& f) const
    {
        return m_hashdict.find(f) != m_hashdict.end();
    }

    bool Load(const string& file)
    {
        return Load(file.c_str());
    }

    template<typename T_>
    void read(T_& tWord, int& nIndex, char chBuffer[], int len, FILE* pFile)
    {
        while (fgets(chBuffer, len, pFile) != NULL) {
            sscanf(chBuffer, "%d %u", &tWord, &nIndex);
            m_hashdict[tWord] = nIndex;
        }
    }

    void read(string& tWord, int& nIndex, char chBuffer[], int len, FILE* pFile)
    {//TODO д��ʱ������"\t"��������ȡ��ʱ���㣬����Ŀǰ����ܶ���ֵ䶼�Ѿ������ʽ����ʱ����
        boost::char_separator<char> sep(" ");
        typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
        while (fgets(chBuffer, 1024, pFile) != NULL) {
            chBuffer[strlen(chBuffer) - 1] = '\0'; //��ifs.getline��ͬfgets��س�Ҫȥ��
            tWord = chBuffer;
            vector<string> vec;
            tokenizer tokens(tWord, sep);
            std::copy(tokens.begin(), tokens.end(), std::back_inserter(vec));
            nIndex = boost::lexical_cast<int>(vec[vec.size() - 1]);
            tWord = "";
            for (size_t k = 0; k < vec.size() - 2; k++)
                tWord += (vec[k] + " ");
            tWord += vec[vec.size() - 2];
            m_hashdict[tWord] = nIndex;
            memset(chBuffer, '\0', 1024);
        }
    }

    bool Load(const char *fileFullName)
    {
        if (fileFullName == NULL) {
            return false;
        }
        FILE *pFile = fopen(fileFullName, "rb");
        if (pFile == NULL) {
            return false;
        }
        char chBuffer[1024];
        memset(chBuffer, '\0', 1024);
        char word[100];
        int nIndex;
        T tWord;
        size_t nNum;

        read(tWord, nIndex, chBuffer, 1024, pFile);

        int nMaxKeyId = 0;
        typename hash_map_type::const_iterator it = m_hashdict.begin();
        for (; it != m_hashdict.end(); ++it) {
            if (it->second > nMaxKeyId) {
                nMaxKeyId = it->second;
            }
        }

        m_index.resize(nMaxKeyId + 1, "");

        typename hash_map_type::const_iterator iter = m_hashdict.begin();
        for (; iter != m_hashdict.end(); ++iter) {
            m_index[iter->second] = iter->first;
        }

        fclose(pFile);
        pFile = NULL;
        return true;
    }

    void Save(const string& file)
    {
        Save(file.c_str());
    }

    template<typename T_>
    void save_(T_ key, int value, char lineInfo[])
    {
        sprintf(lineInfo, "%d %u\n", key, value);
    }

    void save_(string& key, int value, char lineInfo[])
    {
        sprintf(lineInfo, "%s %u\n", key.c_str(), value);
    }

    void Save(const char *fileFullName)
    {
        //        LOG_IF(ERROR, !fileFullName) << "input file name null" << endl;
        FILE *fp = fopen(fileFullName, "wb");
        //        LOG_IF(ERROR, !fp) << "open " << fileFullName << " failed" << endl;

        typename hash_map_type::const_iterator it;
        int keyID = -1;
        char lineInfo[1024];
        for (it = m_hashdict.begin(); it != m_hashdict.end(); it++) {
            keyID = (*it).second;
            //            LOG_IF(WARNING, (*it).first.length() > 1000) << (*it).first.length() << " keyword too long" << endl;

            //            save_((*it).first, keyID, lineInfo);

            sprintf(lineInfo, "%s %u\n", (*it).first.c_str(), keyID);

            fputs(lineInfo, fp);
        }
        fflush(fp);
        fclose(fp);
        fp = NULL;
    }

    //FIXME use one Save for int also using traits

    void SaveInt(const char *fileFullName)
    {//for ���ݾɴ���
        Save(fileFullName);
    }


    ///ֻдm_index �������load���

    void save(const char *fileFullName)
    {
        std::ofstream ofs(fileFullName, std::ios::binary);
        //std::ofstream ofs(fileFullName);
        std::copy(m_index.begin(), m_index.end(), std::ostream_iterator<T > (ofs, "\n"));
        ofs.close();
    }
    ///����m_index vec
    ///���Ϊʲôload��Load��Ҫ��һ����

    void load(const char *fileFullName)
    {
        //        //��൫�ǱȽ���
        ////        std::ifstream ifs(fileFullName, std::ios::binary);  //open with binay will not work for this case TODO
        //        std::ifstream ifs(fileFullName, std::ios::binary);
        //        istream_iterator<T> data_begin(ifs);
        //        istream_iterator<T> data_end;
        //        //or can use std::vector<T> vec(data_begin, data_end);  m_index.swap(vec);
        //        std::copy(data_begin, data_end, std::back_inserter(m_index));
        //        ifs.close();
        FILE *pFile = fopen(fileFullName, "rb");

        char chBuffer[1024];
        char word[100];
        size_t nNum;
        T tWord;
        int nIndex = 0;
        while (fgets(chBuffer, 1024, pFile) != NULL) {
            sscanf(chBuffer, "%s", word);

            if (typeid (T) == typeid (string)) {
                tWord = (T) word;
            } else if (typeid (T) == typeid (int)) {
                nNum = atoi(word);
                tWord = *(T*)&(nNum);
            }
            m_hashdict[tWord] = nIndex++;
            m_index.push_back(tWord);
        }
        fclose(pFile);
    }

};

//template <typename T, typename HashFunc, typename EqualKey >
//const size_t CKeyDictionaryMap<T, HashFunc, EqualKey>::null_id =~(typename CKeyDictionaryMap<T, HashFunc, EqualKey>::id_type)(0); // -1 is null_id
//chg modified
template <typename T>
        const size_t CKeyDictionaryMap<T>::null_id = ~(typename CKeyDictionaryMap<T>::id_type)(0); // -1 is null_id

#endif  //end of define KEYWORD_MAP_ID_H
