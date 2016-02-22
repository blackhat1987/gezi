/**
 *  ==============================================================================
 *
 *          \file   chg.h
 *
 *        \author   chenghuige
 *
 *          \date   2016-02-15 11:11:07.219857
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef chg_
#define chg_
#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Chg
{
  public:
    Chg():
      m_age(28){ m_friend.push_back("mm");}
    int getAge()
    {
      return m_age;
    }
    int friendSize()
    {
      return m_friend.size();
    }

    static int x()
    {
      static thread_local int _x = 3;
      vector<int> u;
      //auto v = move(u); //not support now..
      return _x;
    }

    int m_age;
    vector<string> m_friend;
    vector<int> m_nums;
};

void haha();

#endif
