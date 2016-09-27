/** 
 *  ==============================================================================
 * 
 *          \file   gbk_datrie.h
 *
 *        \author   gezi  
 *          
 *          \date   2010-10-18 10:54:34.886276
 *  
 *  \Description:
 *  ==============================================================================
 */

#ifndef GBK_DATRIE_H_
#define GBK_DATRIE_H_

#include "datrie.h"
#include "gbk_encoder.h"
#include "seg_type.h"
namespace segment
{

class GBK_DATrie
{
private:
    DATrie m_datrie; //datrie using short as key elem
    Encoder m_encoder; //gbk encoder
public:

    GBK_DATrie()
    {
    }

    GBK_DATrie(const string& datrie_file, const string& map_file)
    : m_datrie(datrie_file), m_encoder(map_file)
    {
    }

    void load(const string& datrie_file, const string& map_file)
    {
        m_datrie.load(datrie_file);
        m_encoder.load(map_file);
    }

    /**查询一个gbk格式的string是否datrie字典中*/
    bool search(const string& key)
    {
        u16_string code;
        m_encoder.getKeyCode(key, code);
        return m_datrie.search(code);
    }

    /**如果没有*/
    bool search(const string& key, int& val)
    {
        u16_string code;
        m_encoder.getKeyCode(key, code);
        return m_datrie.search(code, val);
    }

    void getKeyCode(const string& key, u16_string& code)
    {
        m_encoder.getKeyCode(key, code);
    }

    u16_string getKeyCode(const string& key)
    {
        u16_string code;
        m_encoder.getKeyCode(key, code);
        return code;
    }
    //    uint getVal(const string& key) const
    //    {
    //        u16_string code;
    //        m_encoder.getKeyCode(key, code);
    //        uint val;
    //        if (m_datrie.search(code, val))
    //        {
    //            return val;
    //        }
    //        else
    //        {
    //            return 0;
    //        }
    //    }
};

class GBK_DATrie_
{
private:
    const DATrie& m_datrie; //datrie using short as key elem
    const Encoder& m_encoder; //gbk encoder
public:

    GBK_DATrie_(const DATrie& datrie, const Encoder& encoder)
    : m_datrie(datrie), m_encoder(encoder)
    {
    }

    /**查询一个gbk格式的string是否datrie字典中*/
    bool search(const string& key) const
    {
        u16_string code;
        m_encoder.getKeyCode(key, code);
        return m_datrie.search(code);
    }

    /**如果没有*/
    bool search(const string& key, int& val) const
    {
        u16_string code;
        m_encoder.getKeyCode(key, code);
        return m_datrie.search(code, val);
    }

    void getKeyCode(const string& key, u16_string& code) const
    {
        m_encoder.getKeyCode(key, code);
    }

    u16_string getKeyCode(const string& key) const
    {
        u16_string code;
        m_encoder.getKeyCode(key, code);
        return code;
    }
    //    uint getVal(const string& key) const
    //    {
    //        u16_string code;
    //        m_encoder.getKeyCode(key, code);
    //        uint val;
    //        if (m_datrie.search(code, val))
    //        {
    //            return val;
    //        }
    //        else
    //        {
    //            return 0;
    //        }
    //    }
};
}//end of namespace segment

#endif  //----end of GBK_DATRIE_H_
