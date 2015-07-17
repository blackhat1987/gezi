/** 
 *  ==============================================================================
 * 
 *          \file   inverted_common.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-05-15 23:28:16.042966
 *  
 *  \Description:
 *  ==============================================================================
 */

#ifndef INVERTED_COMMON_H_
#define INVERTED_COMMON_H_
#include <stdio.h>
#include <iostream>
#include <vector>
#include <set>
#include <functional>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <functional>
#include <numeric>
#include <boost/filesystem.hpp>
#include <boost/optional.hpp>
//#include <boost/tr1/functional.hpp>
#include <boost/lambda/lambda.hpp>
#include "common_traits.h"
#include "common_cmper.h"
namespace inverted {
using std::cout;
using std::endl;
using std::vector;
using boost::optional;
using namespace std2;
namespace bf = boost::filesystem;
//using std::tr1::placeholders::_1;
//using std::tr1::bind;
//using boost::lambda::_1;
//using namespace boost::lambda;

typedef double DP;
typedef unsigned long long uint64;
typedef long long int64;
enum SortMethod
{
    BY_ID, ///post list ���� id/first ����
    BY_VALUE, ///post list ���� value/second ����
    BY_VALUE_REVERSE, //���մ�С�������� ע���stlĬ�ϵĴ�С�����������෴
    NO_ORDER, ///post list �������
    UNKNOWN_ORDER ///��֪���Ƿ�������ɶ˳��
};

//-----------cmper
struct CmpSTNodeID
{
    template<typename _STNode>
            bool operator() (const _STNode& i, const _STNode & j)
    {
        return ((i.pid < j.pid)
                || ((i.pid == j.pid) && (i.kid < j.kid)));
    }
};
///weight �Ӵ�С
struct CmpSTNodeWeight
{
    template<typename _STNode>
            bool operator() (const _STNode& i, const _STNode & j)
    {
        return ((i.pid < j.pid)
                || ((i.pid == j.pid) && (i.second > j.second))
                || ((i.pid == j.pid) && (i.second == j.second) && (i.kid < j.kid)));
    }
};
struct CmpSTNodeWeight_Reverse
{
    template<typename _STNode>
            bool operator() (const _STNode& i, const _STNode & j)
    {
        return ((i.pid < j.pid)
                || ((i.pid == j.pid) && (i.second < j.second))
                || ((i.pid == j.pid) && (i.second == j.second) && (i.kid < j.kid)));
    }
};
struct CmpSTNodeNoOrder
{
    template<typename _STNode>
            bool operator() (const _STNode& i, const _STNode & j)
    {
        return (i.pid < j.pid);
    }
};
} //----end of namespace inverted

#endif  //----end of INVERTED_COMMON_H_
