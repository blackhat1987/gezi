/** 
 *  ==============================================================================
 * 
 *          \file   ul_dict_help.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-04-01 18:44:34.718989
 *  
 *  \Description:
 *  ==============================================================================
 */

#ifndef UL_DICT_HELP_H_
#define UL_DICT_HELP_H_

#include "ul_dict.h"
#include "ul_sign.h"
class UlDict
{
public:
    const static int kMaxLine = 1024;
    Sdict_build* wordDict;
    UlDict()
    : wordDict(NULL)
    {

    }
    ~UlDict()
    {
        db_del(wordDict);
        wordDict = NULL;
    }
    inline int init_dict(char* file, int dictSize = 1024)
    {
        char buffer[kMaxLine];
        unsigned sign1, sign2;
        char* pbuff = NULL;
        int lineCount = 0;
        FILE* fp = NULL;
        int ret = 0;

        fp = fopen(file, "r");
        if (fp == NULL)
        {
            fprintf(stderr, "can't open word file [%s] to read reason:[%m]\n", file);
            ret = -1;
            goto out;
        }

        wordDict = db_creat(dictSize, 0);
        if (NULL == wordDict)
        {
            fprintf(stderr, "creat word dict size[%d] failed. reason:[%m]\n", dictSize);
            ret = -1;
            goto out;
        }

        while (fgets(buffer, kMaxLine, fp) != NULL)
        {
            lineCount++;
            if (strlen(buffer) == 1)
            {
                fprintf(stderr, "get invalid line at line[%d] in file[%s]\n", lineCount, file);
                continue;
            }

            pbuff = buffer + strlen(buffer) - 1;

            while (pbuff > buffer && (*pbuff == '\n' || *pbuff == '\r'))
            {
                *pbuff = 0;
                pbuff--;
            }

//            printf("add word %s to word dict.\n", buffer);
            //对字符串进行签名, ul_dict使用签名作为key
            creat_sign_f64(buffer, strlen(buffer), &sign1, &sign2);
            Sdict_snode snode;
            snode.sign1 = sign1;
            snode.sign2 = sign2;

            snode.code = -1;
            snode.other = 0;
            //放入hash字典中
            if (db_op1(wordDict, &snode, ADD) == -1)
            {
                fprintf(stderr, "add snode to ul_dict error");
            }
            //放入后other有时会被改变,不希望他们改变用db_op1(dict,&snode,MOD),强制改变一次
        }
//        printf("create nomeandict finish!\n\n");

out:
        if (fp)
        {
            fclose(fp);
            fp = NULL;
        }
        return ret;
    }

    void save(char* path, char* filename)
    {
        db_save(wordDict, path, filename);
    }
    /**
     * @brief 判断某个词是否在字典中，是返回true，否则返回false
     *
     * @param [in] word: char*
     * @return  bool
     * @author jipch
     * @date 2008/03/01 21:36:02
     **/
    inline bool query_dict(char* word)
    {
        unsigned sign1, sign2;
        Sdict_snode snode;

        creat_sign_f64(word, strlen(word), &sign1, &sign2);
        snode.sign1 = sign1;
        snode.sign2 = sign2;
        snode.code = -1;
        db_op1(wordDict, &snode, SEEK);
        //东西不存在snode.code会被置-1, 函数返回值也会被置为0
        if (snode.code != -1)
        {
            return true;
        }
        return false;
    }
};



#endif  //----end of UL_DICT_HELP_H_
