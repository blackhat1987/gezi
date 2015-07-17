/* 
 * File:   normalize.h
 * Author: chenghuige
 *
 * Created on 2010年2月25日, 下午3:14
 *
 *  TODO normalize 效率提高， normalize的效果如何
 */

#ifndef _NORMALIZE_H
#define	_NORMALIZE_H

#include <vector>
#include <limits>
/** normalize all the value in vec to 0.001-0.9995*/
inline void normalize(std::vector<int>& vec, float base = 1000.0, float base2 = 1000.0)
{
    double dMaxValue = -1.0;
    //double dMinValue = 2.0;
    double dMinValue = std::numeric_limits<int>::max();
    int len = vec.size();
    std::vector<double> P;
    P.resize(len);
    for (int i = 0; i < len; i++)
    {
        P[i] = vec[i] / base;
    }
    for (int i = 0; i < len; i++)
    {
        if (P[i] < dMinValue)
            dMinValue = P[i];
        if (P[i] > dMaxValue)
            dMaxValue = P[i];
    }
    if (dMaxValue - dMinValue < 0.0000001)
        return;
    for (int i = 0; i < len; i++)
    {
        if (P[i] <= (dMinValue * 1.005)) //do not use boundary value
            P[i] = dMinValue * 1.005;
        if (P[i] >= (dMaxValue * 0.995))
            P[i] = dMaxValue * 0.995;
        P[i] = (P[i] - dMinValue) / (dMaxValue - dMinValue);
        //P[i] = ((0.5 - 0.001) / 0.5) * P[i] + 0.001;
        P[i] = ((0.5 - 0.1) / 0.5) * P[i] + 0.1;
    }

    for (int i = 0; i < len; i++)
        vec[i] = (int) (P[i] * base2);
}
/** normalize all the value in vec to 0.001-0.0.9995*/
template<typename T>
void normalize(std::vector<T>& vec, float base = 1000.0, float base2 = 1000.0)
{
    std::vector<int> temp_vec;
    temp_vec.resize(vec.size());

    for (size_t i = 0; i < vec.size(); i++)
        temp_vec[i] = vec[i].m_nWeight;

    normalize(temp_vec, base, base2);

    for (size_t i = 0; i < vec.size(); i++)
        vec[i].m_nWeight = temp_vec[i];
}
/**
 * normalize all the value in vec to 0.001-0.9995
 * start from  from
 */
inline void normalize2(std::vector<int>& vec, int from, float base = 1000.0, float base2 = 1000.0)
{
    double dMaxValue = -1.0;
    //double dMinValue = 2.0;
    double dMinValue = std::numeric_limits<int>::max();
    int len = vec.size();
    std::vector<double> P;
    P.resize(len);
    for (int i = from; i < len; i++)
    {
        P[i] = vec[i] / base;
    }
    for (int i = from; i < len; i++)
    {
        if (P[i] < dMinValue)
            dMinValue = P[i];
        if (P[i] > dMaxValue)
            dMaxValue = P[i];
    }
    if (dMaxValue - dMinValue < 0.0000001)
        return;
    for (int i = from; i < len; i++)
    {
        if (P[i] <= (dMinValue * 1.005)) //do not use boundary value
            P[i] = dMinValue * 1.005;
        if (P[i] >= (dMaxValue * 0.995))
            P[i] = dMaxValue * 0.995;
        P[i] = (P[i] - dMinValue) / (dMaxValue - dMinValue);
        //P[i] = ((0.5 - 0.001) / 0.5) * P[i] + 0.001;
        P[i] = ((0.5 - 0.1) / 0.5) * P[i] + 0.1;
    }

    for (int i = from; i < len; i++)
        vec[i] = (int) (P[i] * base2);
}
/** normalize all the value in vec to 0.001-0.0.9995*/
template<typename T>
void normalize2(std::vector<T>& vec, int from, float base = 1000.0, float base2 = 1000.0)
{
    std::vector<int> temp_vec;
    temp_vec.resize(vec.size());

    for (size_t i = from; i < vec.size(); i++)
        temp_vec[i] = vec[i].m_nWeight;

    normalize2(temp_vec, from, base, base2);

    for (size_t i = from; i < vec.size(); i++)
        vec[i].m_nWeight = temp_vec[i];
}

#endif	/* _NORMALIZE_H */

