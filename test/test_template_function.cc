/** 
 *  ==============================================================================
 * 
 *          \file   test_template_function.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-11-19 07:53:31.623973
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#include <cassert>

template <class T>
void foo()
{
}

/** Determine whether the 'foo' attribute of an object is negative. */
template <class T>
bool foo_negative(T& v)
{
    return (v.foo) < 0;
}

struct X
{
    int foo;
};

int main()
{
    X x;
    x.foo = 5;
    assert(!foo_negative(x));
    return 0;
}
