/** 
 *  ==============================================================================
 * 
 *          \file   collocation_measure.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-04-07 17:23:01.006853
 *  
 *  \Description:  ��������������ʽ��������������
 *                               w1 = term1     w1!= term1
 *              w2 = term2        a00             a01
 *              w2 != term2       a10             a11
 *              N = a00 + a01 + a10 + a11
 *              a00 = P(term1,term2)
 *              a10 = P(term1) - a00
 *              a01 = P(term2) - a00
 *  ==============================================================================
 */

#ifndef COLLOCATION_MEASURE_H_
#define COLLOCATION_MEASURE_H_

#include <math.h>
//#include "statistic_help.h"
namespace semantic {

typedef double DP;
enum CoMeasureType
{
    FREQ,
    CHI,
    T_TEST,
    MI, //mutual info
    EMI, //expected mutual info
    LIR, //likely hood ratio
};
struct ChiSquareFunc
{
    /**
     *
     * @param a00  coccur num of (term1,ter2)
     * @param nl   occur num of term1
     * @param nr   occur num of occur term2
     * @param n    total words
     * @return     messure
     *
     *  x^2 = N(a00a11 - a01a10)^2/(a00 + a01)(a00 + a10)(a01 + a11)(a10 + a11)
     *  Ϊ�˷�ֹ���ӹ��������˳��� ��Ϊ��ʱ
     */
    //    DP operator()(int a00, int nterm1, int nterm2, unsigned long long n)
    //    {
    //        if (!a00)
    //            return 0;
    //        int a10 = nterm1 - a00;
    //        int a01 = nterm2 - a00;
    //        long long a11 = n - a00 - a10 - a01;
    //        DP t = DP(a00 * a11 - a01 * a10);
    //        return ( t / (a00 + a10)) * (t / (a01 + a11))
    //                * (n / DP(a10 + a11)) / (a00 + a01);
    //    }
    DP operator()(int a00, int nterm1, int nterm2, unsigned long long n)
    {
        if (!a00)
            return 0;
        int a10 = nterm1 - a00;
        int a01 = nterm2 - a00;
        long long a11 = n - a00 - a10 - a01;
        DP t = DP(a00 * a11 - a01 * a10);
        return ( t / (a00 + a10)) / 100000.0 * (t / (a01 + a11))
                * (n / DP(a10 + a11)) / (a00 + a01);
    }
};
struct EchoFunc
{
    DP operator()(int a00, int nterm1, int nterm2, unsigned long long n)
    {
        return a00;
    }
};
struct MutualInfoFunc
{
    /**
     *  �㻥��Ϣ
     *  log ( P(AB) / P(A)P(B) ) <=> log(O11/ E11)
     *     (AB / N) / (A / N) (B / N) = (AB * N) / (A * B )
     * 
     */
    DP operator()(int a00, int nterm1, int nterm2, unsigned long long n)
    {
        if (!a00)
            return std::numeric_limits<int>::min();
        return log(DP(n / nterm1) * (DP(a00) / nterm2)) / log(2);
    }
};
struct MutualInfoFunc2
{
    /**
     *  �㻥��Ϣ
     *  log ( P(AB) / P(A)P(B) ) <=> log(O11/ E11)
     *     (AB / N) / (A / N) (B / N) = (AB * N) / (A * B )
     *
     */
    DP operator()(int a00, int nterm1, int nterm2, unsigned long long n)
    {
        if (!a00)
            return std::numeric_limits<int>::min();
        Pval(log(DP(n / nterm1) * (DP(a00) / nterm2)) / log(2));
        Pval((DP(a00) / n));
        Pval((DP(a00) / n) * log(DP(n / nterm1) * (DP(a00) / nterm2)) / log(2));
        Pval((DP(nterm1 - a00) / n) * log(DP(n / nterm1) * (DP(nterm1 - a00) / (n - nterm2))) / log(2));
        Pval((DP(nterm2 - a00) / n) * log(DP(n / nterm2) * (DP(nterm2 - a00) / (n - nterm1))) / log(2));
        Pval(DP(n - (nterm1 + nterm2 - a00) / n) *
                log(DP(n / (n - nterm1)) * (DP(n - (nterm1 + nterm2 - a00)) / (n - nterm2))) / log(2));
        Pval((DP(n) / nterm1) * (DP(a00) / nterm2));
        Pval( (DP(n) / nterm1) * (DP(nterm1 - a00) / (n - nterm2)) );
        Pval( (nterm1 - a00) );
        Pval( (n - nterm2) );
        return (DP(a00) / n) * log((DP(n) / nterm1) * (DP(a00) / nterm2)) / log(2) +
                (DP(nterm1 - a00) / n) * log((DP(n) / nterm1) * (DP(nterm1 - a00) / (n - nterm2))) / log(2) +
                (DP(nterm2 - a00) / n) * log((DP(n) / nterm2) * (DP(nterm2 - a00) / (n - nterm1))) / log(2) +
                (DP(n - (nterm1 + nterm2 - a00)) / n) *
                log((DP(n) / (n - nterm1)) * (DP(n - (nterm1 + nterm2 - a00)) / (n - nterm2))) / log(2);
    }
};
inline DP mutual_info(int a00, int nterm1, int nterm2, unsigned long long n)
{
    if (!a00)
        return std::numeric_limits<int>::min();
    return log(DP(n / nterm1) * (DP(a00) / nterm2)) / log(2);
}
struct DiscountedMutualInfoFunc
{
    /**
     *  �㻥��Ϣ
     *  log ( P(AB) / P(A)P(B) ) <=> log(O11/ E11)
     *     (AB / N) / (A / N) (B / N) = (AB * N) / (A * B )
     *
     */
    DP operator()(int a00, int nterm1, int nterm2, unsigned long long n)
    {
        if (!a00)
            return 0;
        int m = std::min(nterm1, nterm2);
        return ( (a00 / DP(a00 + 1)) * (m / DP(m + 1)))
                * log(DP(n / nterm1) * (DP(a00) / nterm2)) / log(2);
    }
};
struct EMutualInfoFunc
{
    /**
     * ����Ϣ������ֵ
     * E(plog ( P(AB) / P(A)P(B) )
     * ����Ϣ�Ļ����� * ʵ�ʶ�Ԫ���ָ��ʣ���������Ϣ���ڵ�Ƶ�ʵ�ƫ��
     */
    DP operator()(int a00, int nterm1, int nterm2, unsigned long long n)
    {
        if (!a00)
            return 0;
        return (DP(a00) / n) * (log(DP(n / nterm1) * (DP(a00) / nterm2)) / log(2));
    }

};
struct TTestFunc
{
    /**
     * t_test
     *  ( mean(actual) - mean(bad suppose) ) / (sd(actual) )
     *  ��ֵԽ�����bad suppose����ؼٶ�Խ�����գ�Ҳ���Ǵ���̶�Խ��
     *  FIXME ������nan
     */
    DP operator()(int a00, int nterm1, int nterm2, unsigned long long n)
    {
        if (!a00)
            return 0;
        //        return DP( a00  - nterm1 * nterm2 / n) / sqrt(a00 * n);
        return DP(a00 - (nterm1 * nterm2) / n) / sqrt(a00) * sqrt(n);
    }
};
struct EChiSquareFunc
{
    /**
     *
     * @param a00  coccur num of (term1,ter2)
     * @param nl   occur num of term1
     * @param nr   occur num of occur term2
     * @param n    total words
     * @return     messure
     *
     *  x^2 = N(a00a11 - a01a10)^2/(a00 + a01)(a00 + a10)(a01 + a11)(a10 + a11)
     *  Ϊ�˷�ֹ���ӹ��������˳��� ��Ϊ��ʱ
     */
    DP operator()(int a00, int nterm1, int nterm2, unsigned long long n)
    {
        if (!a00)
            return 0;
        int a10 = nterm1 - a00;
        int a01 = nterm2 - a00;
        long long a11 = n - a00 - a10 - a01;
        DP t = DP(a00 * a11 - a01 * a10);
        return DP(a00) * (t / (a00 + a10)) * (t / (a01 + a11))
                * (n / DP(a10 + a11)) / (a00 + a01);
    }
};
struct LogEChiSquareFunc
{
    /**
     *
     * @param a00  coccur num of (term1,ter2)
     * @param nl   occur num of term1
     * @param nr   occur num of occur term2
     * @param n    total words
     * @return     messure
     *
     *  x^2 = N(a00a11 - a01a10)^2/(a00 + a01)(a00 + a10)(a01 + a11)(a10 + a11)
     *  Ϊ�˷�ֹ���ӹ��������˳��� ��Ϊ��ʱ
     *  ע��ȷ��a00 > 0
     */
    DP operator()(int a00, int nterm1, int nterm2, unsigned long long n)
    {
        if (!a00)
            return 0;
        int a10 = nterm1 - a00;
        int a01 = nterm2 - a00;
        long long a11 = n - a00 - a10 - a01;
        DP t = DP(a00 * a11 - a01 * a10);
        return log(a00) * DP(t / (a00 + a10)) * (t / (a01 + a11))
                * (n / DP(a10 + a11)) / (a00 + a01);
    }
};

} //----end of namespace semantic

#endif  //----end of COLLOCATION_MEASURE_H_
