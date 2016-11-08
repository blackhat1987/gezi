/***************************************************************************
 * 
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/



/**
 * @file ./src/u_wordrank.cpp
 * @author chenzulong01(com@baidu.com)
 * @date 2013/09/06 11:49:37
 * @brief 
 *  
 **/
#include "u_wordrank.h"

Sdict_build* WordRank::test_load_word_tag_dict(const char *conf_path, const char *filename)
{
    if(!conf_path || !filename)
    {
        printf("%s:Wrong Parameter", __func__);
        return NULL;
    }

    char line_buf[512], term[256];
    int ntag = 0, nval = 0;
    Sdict_snode snode;
    char full_file_name[512];
    Sdict_build * word_tag_dict = NULL;
    snprintf (full_file_name, sizeof (full_file_name), "%s/%s", conf_path, filename);
    FILE * pofile = fopen (full_file_name, "r");
    if(NULL == pofile)
    {
        printf("File [%s] cannot be opened for reading", full_file_name);
        return NULL;
    }

    word_tag_dict = db_creat (4096, 0);
    if(NULL == word_tag_dict)
    {
        fclose(pofile);
        pofile = NULL;
        printf("db_creat (4096, 0) for word_tag_dict fail");
        return NULL;
    }

    int line_num = 0;
    while(fgets (line_buf, sizeof (line_buf), pofile))
    {
        int nscanf_num = sscanf (line_buf, "%s\t%d\t%d", term, &ntag, &nval);
        if(3 != nscanf_num)
        {
            printf("sscanf error, nscanf_num=%d", nscanf_num);
            continue;
        }
        char term_sign[256];
        snprintf(term_sign, sizeof(term_sign), "%d_%s", ntag, term);
        creat_sign_f64 (term_sign, strlen (term_sign), &snode.sign1, &snode.sign2);
        snode.other = ntag;
        snode.code = nval;
        if(db_op1 (word_tag_dict, &snode, ADD) > 0)
        {
        }
        else
        {
        }
        ++line_num;
    }

    fclose(pofile);

    return word_tag_dict;
}

int WordRank::wimp_get_train_tokens( scw_out_t* p_scwout,tag_t tags[], int tagcnt,token_t tokens[], int max_count)
{
    token_t phtokens[MAX_TERM_COUNT];
    int phtcnt;
    phtcnt = scw_get_token_1( p_scwout, SCW_OUT_WPCOMP|SCW_OUT_PROP, phtokens, MAX_TERM_COUNT );
    char buff[TERM_MAX_LEN];
    int tcnt = 0;
    int toffcnt = 0;

    for (int i = 0; i< tagcnt; ++i)
    {
        if((int)tags[i].offset > toffcnt)
        {
            for(int k = toffcnt; k < tags[i].offset; k++)
            {
                tokens[tcnt].prop.m_lprop = phtokens[toffcnt].prop.m_lprop;
                tokens[tcnt].prop.m_hprop = phtokens[toffcnt].prop.m_hprop;
                tokens[tcnt].length       = phtokens[toffcnt].length;
                tokens[tcnt].offset       = phtokens[toffcnt].offset;
                strncpy(tokens[tcnt].buffer,phtokens[toffcnt].buffer,TERM_MAX_LEN);
                tcnt++;
                toffcnt++;
            }
        }
        ut_join_tokens( phtokens, phtcnt, tags[i].offset, tags[i].length, buff, TERM_MAX_LEN, NULL );
        if ( 1 == tags[i].length )
        {
            tokens[tcnt].prop.m_lprop = phtokens[toffcnt].prop.m_lprop;
            tokens[tcnt].prop.m_hprop = phtokens[toffcnt].prop.m_hprop;
        }
        else
        {
            SET_PHRASE(tokens[tcnt].prop);
        }

        tokens[tcnt].length = strlen(buff);
        tokens[tcnt].offset = phtokens[toffcnt].offset;
        strncpy(tokens[tcnt].buffer,buff,TERM_MAX_LEN);
        tcnt++;
        toffcnt = tags[i].offset + tags[i].length;
    }

    if(toffcnt<phtcnt)
    {
        for(int k = toffcnt; k < phtcnt; k++)
        {
            tokens[tcnt].prop.m_lprop = phtokens[toffcnt].prop.m_lprop;
            tokens[tcnt].prop.m_hprop = phtokens[toffcnt].prop.m_hprop;
            tokens[tcnt].length       = phtokens[toffcnt].length;
            tokens[tcnt].offset       = phtokens[toffcnt].offset;
            strncpy(tokens[tcnt].buffer,phtokens[toffcnt].buffer,TERM_MAX_LEN);
            tcnt++;
            toffcnt++;
        }
    }

    if((tcnt >= tagcnt) && (tcnt <= phtcnt))
    {
        return tcnt;
    }
    else
    {
        return -1;
    }    
}

int WordRank::init_wordrank(int argc,char* argv[])
{

    if ( argc < 9){
        ul_writelog(UL_LOG_WARNING,"the argc is error,usage: %s segDictPath rankDictPath tagDictPath trkDictPath splitDictPath word_tag_path nerDictPath langid\n", argv[0]);
        return 1;
    }

    if((pgconf = scw_load_conf(argv[0]/*"./data/worddict/scw.conf"*/)) == NULL)
    {
        ul_writelog(UL_LOG_WARNING,"DICT[%s],FILE:[%s],FUNCTION:[%s],LINE:[%d]*****load worddict scw.conf error****",argv[0],__FILE__,__FUNCTION__,__LINE__);
        return 1;
    }

    p_worddict = scw_load_worddict( argv[1] );
    if ( !p_worddict )
    {
        ul_writelog(UL_LOG_WARNING,"DICT[%s],FILE:[%s],FUNCTION:[%s],LINE:[%d]*****can not load the segment dict****",argv[1],__FILE__,__FUNCTION__,__LINE__);
        return 1;
    }



    if ( NULL == (p_nerdict = ner_dict_load(argv[7])) ){
        ul_writelog(UL_LOG_WARNING,"FILE:[%s],FUNCTION:[%s],LINE:[%d]*****can not load the ner dict****",__FILE__,__FUNCTION__,__LINE__);
        return 1;
    }



    p_rankdict = wdr_create(argv[2]);
    if ( !p_rankdict )
    {
        ul_writelog(UL_LOG_WARNING,"FILE:[%s],FUNCTION:[%s],LINE:[%d]*****can not load the word rank dict****",__FILE__,__FUNCTION__,__LINE__);
        return 1;
    }

    p_tagdict = tag_create(argv[3]);
    if ( !p_tagdict )
    {
        ul_writelog(UL_LOG_WARNING,"FILE:[%s],FUNCTION:[%s],LINE:[%d]*****can not load the pos tagging dict****",__FILE__,__FUNCTION__,__LINE__);
        exit(-1);
    }
    
    p_trkdict = trk_create(argv[4]);
    if ( !p_trkdict )
    {
        ul_writelog(UL_LOG_WARNING,"FILE:[%s],FUNCTION:[%s],LINE:[%d]*****can not load the trunk parsing dict****",__FILE__,__FUNCTION__,__LINE__);
        return 1;
    }
    p_splitphrasedict = ds_load(argv[5], SPLIT_DICT_NAME);
    if ( !p_splitphrasedict )
    {
        ul_writelog(UL_LOG_WARNING,"FILE:[%s],FUNCTION:[%s],LINE:[%d]****can not load the p_splitphrase dict****",__FILE__,__FUNCTION__,__LINE__);
        return 1;
    }

    char word_tag_path[256];
    snprintf(word_tag_path, sizeof(word_tag_path), "%s", argv[6]);
    p_wordtagdict = test_load_word_tag_dict(word_tag_path, "word_tag.txt");
    if ( !p_wordtagdict )
    {
        ul_writelog(UL_LOG_WARNING,"FILE:[%s],FUNCTION:[%s],LINE:[%d]****can not load word tag dict****",__FILE__,__FUNCTION__,__LINE__);
        return 1;
    }

    langid = atoi(argv[8]);
    return 0;
}

bool WordRank::isValidate(int i)
{
    switch(i)
    {
        case 3:
        case 5:
        case 8:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 34:
        case 35:
        case 36:
            return true;
            break;
        default :
            return false;
            break;
    }
}


std::map<std::string,std::pair<int,float> > WordRank::get_rank(std::string& strline)
{
    token_t splitokens[MAX_TERM_COUNT];
    //token_t tokens[MAX_TERM_COUNT];
    //token_t newtokens[MAX_TERM_COUNT];
    //trunk_t trunks[MAX_TERM_COUNT];
    //trunk_t newtrunks[MAX_TERM_COUNT];

    char line[201];

    memset(line,0,sizeof(line));
    snprintf(line,sizeof(line)-1,"%s",strline.c_str());

    std::map<std::string,std::pair<rank,weight> > rank_weight;

    int splitokens_len = 0;
    //int tokens_len = 0;
    //int newtokens_len = 0;

    //clock_t start = clock();
    int len, ret;

    len = ut_chomp_line(line);
    if( 0 == len ){
        return rank_weight;
    }

    ul_trans2bj(line, line);
    ul_trans2bj_ext(line, line);
    ul_trans2lower(line, line);

    scw_out_t* p_scwout = scw_create_out( MAX_TERM_COUNT, SCW_OUT_ALL | SCW_OUT_PROP );
    if ( !p_scwout )
    {
        return rank_weight;
    }

    /*
    ner_out_t *p_nerout ;
    if ( NULL == (p_nerout = ner_out_create(p_nerdict, MAX_TERM_COUNT)) ){
        return rank_weight;
    }
    */

    memset( splitokens, 0, MAX_TERM_COUNT * sizeof( token_t ) );
    //memset( tokens, 0, MAX_TERM_COUNT * sizeof( token_t ) );
    //memset( newtokens, 0, MAX_TERM_COUNT * sizeof( token_t ) );
    scw_segment_words( p_worddict, p_scwout, line, strlen(line), langid );

    splitokens_len = seg_split(p_splitphrasedict, p_scwout, splitokens, MAX_TERM_COUNT);
    ret = tag_postag(p_tagdict, splitokens, splitokens_len);
    if ( !ret ){
        return rank_weight;
    }

    /*
    tokens_len = scw_get_token_1( p_scwout, SCW_OUT_WPCOMP|SCW_OUT_PROP, tokens, MAX_TERM_COUNT );
    int tagcnt = ner_tag(p_nerdict, tokens, tokens_len, p_nerout, langid);
    if ( tagcnt < 0 ){
        return rank_weight;
    }
    newtokens_len = wimp_get_train_tokens( p_scwout , p_nerout->sub_tags , p_nerout->sub_tag_num , newtokens, MAX_TERM_COUNT );
    if ( newtokens_len < 0 ){
        return rank_weight;
    }
    ret = tag_postag(p_tagdict, newtokens, newtokens_len);
    if( !ret ){
        return rank_weight;
    }

    memset( trunks, 0, sizeof(trunks) );
    memset( newtrunks, 0, sizeof(newtrunks) );
    ret = trk_parse_add_svm(p_trkdict, p_rankdict, NULL, p_wordtagdict, splitokens, splitokens_len, trunks, splitokens_len, newtokens, newtokens_len, newtrunks, newtokens_len, p_nerout->sub_tags, p_nerout->sub_tag_num, langid);

    for(int i=0;i<ret;i++)
    {
        if(isValidate(splitokens[i].type))
        {
            rank_weight[splitokens[i].buffer].second = trunks[i].weight;
            rank_weight[splitokens[i].buffer].first = trunks[i].rank;
        }
    }

    if ( p_nerout ){
        ner_out_destroy( p_nerout );
        p_nerout = NULL;
    }*/

    const char* terms[201];
    float term_value[201];

    for(int i =0;i<splitokens_len;i++)
    {
        terms[i] = splitokens[i].buffer;
    }

    ret = wdr_evaluate(p_rankdict,terms,splitokens_len,term_value);

    if(ret != splitokens_len)
    {
        return rank_weight;
    }

    for(int i =0;i<splitokens_len;i++)
    {
        if(isValidate(splitokens[i].type))
        {
            rank_weight[splitokens[i].buffer].second = term_value[i];
            rank_weight[splitokens[i].buffer].first = 0;
        }
    }

    if(p_scwout)
    {
        scw_destroy_out( p_scwout );
        p_scwout = NULL;
    } 

    return rank_weight;
}

WordRank::~WordRank()
{

   if(p_worddict)
   {
        scw_destroy_worddict( p_worddict );
        p_worddict = NULL;
   }

   if ( p_nerdict ){
        ner_dict_destroy( p_nerdict );
        p_nerdict = NULL;
    }

    if ( p_rankdict ){
        wdr_destroy(p_rankdict);
        p_rankdict = NULL;
    }
    if ( p_tagdict ){
        tag_destroy(p_tagdict);
        p_tagdict = NULL;
    }
    if ( p_trkdict ){
        trk_destroy(p_trkdict);
        p_trkdict = NULL;
    }
    if ( p_splitphrasedict ){
        ds_del(p_splitphrasedict);
        p_splitphrasedict = NULL;
    }
    if ( p_wordtagdict ){
        db_del(p_wordtagdict);
        p_wordtagdict = NULL;
    }
 
}
/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
