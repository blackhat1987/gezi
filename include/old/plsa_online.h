/** 
 *  ==============================================================================
 * 
 *          \file   plsa_online.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-07-18 10:50:21.037960
 *  
 *  \Description:   plsa ��������ģ��
 *                  ��ʱֻ����Ч��
 *  ==============================================================================
 */

#ifndef PLSA_ONLINE_H_
#define PLSA_ONLINE_H_

#include "inverted_index.h"
#include <vector>
#include <stdlib.h>
#include "matrix_help.h"
#include "common_help.h"
#include "debug_help.h"
#include "vec_calc.h"
namespace plsa {
namespace online {
using namespace inverted;
template<typename _Table = InvertedIndex<float> >
        class TModel
{
public:
    /**
     * ������p(z|w)����
     */
    TModel(_Table& invert, const std::vector<float>& back_ground, float beta = 0.95)
    : _znum(invert.size()), _pzw(invert), _back_ground(back_ground), _beta(beta)
    {
        Pval(_znum);
    }
    void set_znum(int znum)
    {
        _znum = znum;
    }
    void inference(const std::vector<std::pair<int, int> >& content_vec, std::vector<float>& pdz, int round = 20)
    {
        //--------------------------init
        pdz.clear();
        pdz.resize(_znum + 1, 0);

        int len = content_vec.size();
        float nword = 0;
        for (int i = 0; i < len; i++)
        {
            nword += content_vec[i].second;
        }

        //        Pval(_pwz(689563, 133));
        //        Pval(_pwz(689563, 350));
        //�򵥵Ļ���ƺ�Ч�����ã���Ϊ��дword����ĳ��topic����̫�ߣ��ǹ��������Ĵ�
        //        for (int i = 0; i < _znum; i++)
        //        {
        //            double temp = 0;
        //            for (int j = 0; j < len; j++)
        //            {
        //                int wid = content_vec[j].first;
        //                int n = content_vec[j].second;
        //                temp += n * _pwz(wid, i);
        //            }
        //            pdz[i] = temp / sum;
        //        }

        //--------------------------init
        double sum = 0;
        for (size_t i = 0; i <= _znum; i++)
        {
            pdz[i] = drand48() * drand48();
            sum += pdz[i];
        }
        for (size_t i = 0; i <= _znum; i++)
        {
            pdz[i] /= sum;
        }
        Fmat pwz = Fmat::Zero(len, _znum + 1);
        //--------------------------infer
        for (int i = 0; i < round; i++)
        {
            //-----e-step calc pwz// p(z|w,d)
            for (int j = 0; j < len; j++) //word
            {
                int wid = content_vec[j].first;
                //p(w,d)
                float pw_d = 0;
                for (int zid = 0; zid < _znum; zid++)
                {
                    pw_d += pdz[zid] * _pzw(zid, wid);
                }
                for (int zid = 0; zid < _znum; zid++) //z topic
                {
                    if (pw_d) // /0Σ�ա�����
                        pwz(j, zid) = (pdz[zid] * _pzw(zid, wid)) / pw_d;
                }
                float up = _beta * _back_ground[wid];
                float down = (up + (1 - _beta) * pw_d);
                if (down)
                    pwz(j, _znum) = up / down;
            }

            //-----m-step calc p(z|d)
            for (int zid = 0; zid < _znum; zid++) //topic
            {
                float up = 0;
                for (int j = 0; j < len; j++) //word
                {
                    int wid = content_vec[j].first;
                    float weight = content_vec[j].second;
                    up += weight * pwz(j, zid) * (1 - pwz(j, _znum));
                }
                pdz[zid] = up / nword;
            }
        }

        vector<std::pair<int, float> > vec;
        for (int i = 0; i < _znum; i++)
        {
            vec.push_back(std::make_pair(i, pdz[i]));
        }
        std::sort(vec.begin(), vec.end(), std2::CmpNodeByValue());
        Prange2(vec.begin(), vec.begin() + 20);

        //---------չʾһ�� p(z|d) * p(w|z) = p(w|d) ��Ч�� �ܷ�ﵽ��ȡ���Ĵʵ�����
        //---������back ground�����ĸ���
        {
            vector<std::pair<int, float> > vec;
            for (int i = 0; i < len; i++)
            {
                //                float score = dot2(pwz(i), pzd + z_num, pwz, pwz + z_num, float(0.0));
                float score = 0;
                for (int j = 0; j < _znum; j++)
                {
                    score += pdz[j] * pwz(i, j);
                }
                vec.push_back(std::make_pair(content_vec[i].first, score));
            }
            std::sort(vec.begin(), vec.end(), std2::CmpNodeByValue());
            //            Prange2(vec.begin(), vec.begin() + 20);
            KeyIDMap<string> keyid_map;
            keyid_map.load("keyid_map.idx");
            InvertedIndexPrinter printer(keyid_map);
            printer.print_post(vec.begin(), vec.begin() + 100);
        }
    }
private:
    int _znum;
    _Table& _pzw;

    float _beta;
    const std::vector<float>& _back_ground;
};
typedef TModel<> Model;
}
} //----end of namespace plsa

#endif  //----end of PLSA_ONLINE_H_
