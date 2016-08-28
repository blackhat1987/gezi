/** 
 *  ==============================================================================
 * 
 *          \file   test_double_equal.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2016-06-19 14:32:17.106932
 *  
 *  \Description: http://stackoverflow.com/questions/18971533/c-comparison-of-two-double-values-not-working-properly
 *
 *  ==============================================================================
 */


#include <cmath>
#include <iostream>
using namespace std;
class Sphere
{
    double r;
public:
    double V() const { return (4/3) * 3.14 * pow(r,3); }
    bool equal(const Sphere& s) const
    {
        cout  << V() << " == " << s.V() << " : " << ( V() == s.V() ) << endl;
        return ( V() == s.V() );

    }

    explicit Sphere(double rr = 1): r(rr){}

};
main()
{
    Sphere s(3);
    s.equal(s);
}
