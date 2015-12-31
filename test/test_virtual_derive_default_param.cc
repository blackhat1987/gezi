/** 
 *  ==============================================================================
 * 
 *          \file   test_virtual_derive_default_param.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2015-12-31 16:54:35.070568
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#include <iostream>
using namespace std;
class A
{
public:
    virtual void out(int i = 1)
    {
        cout << "class A  " << i <<endl;
    }
};
class B : public A
{
public:
    virtual void out(int i)
    {
        cout  <<"class B " <<i <<endl;
    }
    
};
int main()
{
    A a;
    B b;
    A * p = &a;
    
    p->out();
    p->out(3);
    p = &b;
    p->out();
    p->out(4);
    
    return 0;
}
