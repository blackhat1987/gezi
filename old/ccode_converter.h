/** 
 *  ==============================================================================
 * 
 *          \file   ccode_converter.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-06-11 13:57:44.024376
 *  
 *  \Description:
 *  ==============================================================================
 */

#ifndef CCODE_CONVERTER_H_
#define CCODE_CONVERTER_H_
#include "ul_ccode.h"
#include "ul_log_help.h"
class CCodeConverter
{
public:
    CCodeConverter()
    {
    }
    ~CCodeConverter()
    {
        ul_ccode_del();
    }
    bool load(const string& dir)
    {
        if (ul_ccode_load((char *) dir.c_str()) < 0)
        {
            LOG_ERROR("Ccode loading error");
            return false;
        }
        return true;
    }
    bool normalize(const char* src, char* dest, bool to_lower = true, bool to_simp = true, bool to_half = true)
    {
        if (to_simp)
        {
            if (ul_trans2gb((char *) src, dest, CODETYPE_GB) < 0)
                return false;
        }
        else
        {
            strcpy(dest, src);
        }
        if (to_half)
        {
            ul_trans2bj(dest, dest);
            ul_trans2bj_ext(dest, dest);
        }
        if (to_lower)
            ul_trans2lower(dest, dest);
        return true;
    }
    std::string normalize(const std::string& src, bool to_lower = true, bool to_simp = true, bool to_half = true)
    {
        char* dest = new char[src.size() + 1];
        dest[0] = '\0';
        if (to_simp)
        {
            if (ul_trans2gb((char *) src.c_str(), dest, CODETYPE_GB) < 0)
                return false;
        }
        else
        {
            strcpy(dest, src.c_str());
        }
        if (to_half)
            ul_trans2bj_ext(dest, dest);
        if (to_lower)
            ul_trans2lower(dest, dest);
        std::string result = dest;
        if (dest)
        {
            delete [] dest;
        }
        return result;
    }
};

class CCodeConverterThread
{
public:
    CCodeConverterThread()
    {
        ul_ccode_conv_open();
    }
    ~CCodeConverterThread()
    {
        ul_ccode_conv_close();
    }
};

#endif  //----end of CCODE_CONVERTER_H_
