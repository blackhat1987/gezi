/***************************************************************************
 * 
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/



/**
 * @file ./include/u_wordrank.h
 * @author chenzulong01(com@baidu.com)
 * @date 2013/09/06 11:41:49
 * @brief 
 *  
 **/




#ifndef  ____INCLUDE_U_WORDRANK_H_
#define  ____INCLUDE_U_WORDRANK_H_

#define SPLIT_DICT_NAME "splitphrasedict"
#define MAX_TEXT_LENGTH 4096
#define MAX_TERM_COUNT 256
#define DEFAULT_NER_OUT_FLAG 0x1F

#include "ul_dict.h"
#include "ul_sign.h"
#include "iwordrank.h"
#include "isegment.h"
#include "scwdef.h"
#include "itrunk.h"
#include "iwordner.h"
#include "ipostag.h"
#include "ul_log.h"

#include <map>

extern int ut_chomp_line(char *str);
extern const char *get_pos_str( unsigned int nPOS ); 
extern int scw_get_token_1( scw_out_t* pout, int type, token_t result[], unsigned max );
extern int ut_join_tokens( token_t tokens[], int tcnt, int begin, int count,char *buff, int max_bufflen, char* joiner);

class WordRank
{
    public :
        //初始化wordrank
        int init_wordrank(int argc,char* argv[]);

        //wordrank 内部处理函数
        int wimp_get_train_tokens( scw_out_t* p_scwout,tag_t tags[], int tagcnt,token_t tokens[], int max_count );
        Sdict_build* test_load_word_tag_dict(const char *conf_path, const char *filename);

        /**
         * param 一个待处理的字符串
         * return 返回字符串中每一个切割后的带权map
         */
        typedef int rank;
        typedef float weight;
        std::map<std::string,std::pair<rank,weight> > get_rank(std::string& strline);

        //析构词典
        ~WordRank();
    private :
        scw_worddict_t *p_worddict ;

        ner_dict_t *p_nerdict ;

        rank_dict_t *p_rankdict;
        tag_dict_t *p_tagdict ;
        trunk_dict_t *p_trkdict ;
        Sdict_search *p_splitphrasedict;
        Sdict_build *p_wordtagdict ;


        
        int langid;
    private :
        /**
         * param 判断一个词的词性是不是需要的
         * return 如果是，返回true,
         */
        bool isValidate(int i);
};

#endif  //___/INCLUDE/U_WORDRANK_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
