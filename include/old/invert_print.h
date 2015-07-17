/** 
 *  ==============================================================================
 * 
 *          \file   invert_print.h
 *
 *        \author   chenghuige 
 *          
 *          \date   2010-07-06 09:07:23.189340
 *  
 *  \Description:   打印倒排信息到文件中,包括类别倒排信息
 *  ==============================================================================
 */

#ifndef INVERT_PRINT_H_
#define INVERT_PRINT_H_
#include <string>
#include <fstream>
#include <boost/progress.hpp>
#include <glog/logging.h>
#include "category_help.h"
#include "KeywordMapID.h"
inline void print_invert(const string& dir, const char* outfile)
{
    string indexfile = dir + "/index.idx";
    string invertfile = dir + "/invert.idx";
    string dicfile = dir + "/dict.idx";
    CKeyDictionaryMap<std::string> phr2id;
    LOG(INFO) << "phr2id load begin" << endl;
    phr2id.Load(dicfile.c_str());
    LOG(INFO) << "ph2id load finish" << endl;
    InvertTable<> invert_table;
    invert_table.load(indexfile.c_str(), invertfile.c_str());
    std::ofstream ofs(outfile);
    for (size_t i = 0; i < invert_table.entryNum(); i++)
    {
        ofs << "The initial phrase is " << phr2id.GetKeyFromID(i) << endl;
        std::vector<InvertNode> result_vec;
        invert_table.getPostList(i, result_vec);
        for (size_t j = 0; j < result_vec.size(); j++)
        {
            ofs << phr2id.GetKeyFromID(result_vec[j].m_nID) << " " << result_vec[j].m_nWeight << endl;
        }
    }
    ofs << '\n';
    ofs.close();
}
/**
 *  相关类别显示,
 *  Posting list of 电信3G手机 is 4003355
 */
inline void print_invert_cat(const string& dir, const char* outfile)
{
    string indexfile = dir + "/index.idx";
    string invertfile = dir + "/invert.idx";
    string dicfile = dir + "/dict.idx";

    CategoryHelper cat_helper;

    CKeyDictionaryMap<std::string> phr2id;
    phr2id.Load(dicfile.c_str());
    InvertTable<> invert_table;
    invert_table.load(indexfile.c_str(), invertfile.c_str());
    std::ofstream ofs(outfile);
    LOG(INFO) << Pval(invert_table.entryNum());
    for (size_t i = 0; i < invert_table.entryNum(); i++)
    {
        ofs << "Posting list of " << phr2id.GetKeyFromID(i) << endl;

        std::vector<InvertNode> result_vec;
        invert_table.getPostList(i, result_vec);
        for (size_t j = 0; j < result_vec.size(); j++)
        {
            //            ofs << phr2id.GetKeyFromID(result_vec[j].m_nID) << " " << result_vec[j].m_nWeight << endl;
            int cid;
            try
            {
                cid = boost::lexical_cast<int>(phr2id.GetKeyFromID(result_vec[j].m_nID));
            }
            catch (...)
            {
                continue;
            }
            ofs << phr2id.GetKeyFromID(result_vec[j].m_nID) << " "
                    << cat_helper.getCatName(cid)
                    << " " << cat_helper.getCatPath(cid)
                    << " " << cat_helper.getCatLevel(cid)
                    << " " << result_vec[j].m_nWeight << endl;
        }
    }
    ofs << '\n';
    ofs.close();
}
/*
 * 这个倒排里面直接存储的就是类别真实id
 */
inline void print_invert_cat2(const string& dir, const char* outfile)
{
    string indexfile = dir + "/index.idx";
    string invertfile = dir + "/invert.idx";
    string dicfile = dir + "/dict.idx";

    CategoryHelper cat_helper;

    CKeyDictionaryMap<std::string> phr2id;
    phr2id.Load(dicfile.c_str());
    InvertTable<> invert_table;
    invert_table.load(indexfile.c_str(), invertfile.c_str());
    std::ofstream ofs(outfile);
    LOG(INFO) << Pval(invert_table.entryNum());
    for (size_t i = 0; i < invert_table.entryNum(); i++)
    {
        ofs << "Posting list of " << phr2id.GetKeyFromID(i) << endl;

        std::vector<InvertNode> result_vec;
        invert_table.getPostList(i, result_vec);
        for (size_t j = 0; j < result_vec.size(); j++)
        {
            int cid = result_vec[j].m_nID;
            ofs << cid << " "
                    << cat_helper.getCatName(cid)
                    << " " << cat_helper.getCatPath(cid)
                    << " " << cat_helper.getCatLevel(cid)
                    << " " << result_vec[j].m_nWeight << endl;
        }
    }
    ofs << '\n';
    ofs.close();
}
#endif  //----end of INVERT_PRINT_H_
