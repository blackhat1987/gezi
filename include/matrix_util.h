/** 
 *  ==============================================================================
 * 
 *          \file   matrix_util.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-02-26 18:54:55.190241
 *  
 *  \Description: 
 *  ==============================================================================
 */

#ifndef MATRIX_UTIL_H_
#define MATRIX_UTIL_H_

#include "Matrix.h"
#include "Dense"

using namespace Eigen;

namespace gezi {

typedef Matrix< double, Dynamic, Dynamic > Mat;
typedef Matrix< double, Dynamic, Dynamic > Dmat;
typedef Matrix< float, Dynamic, Dynamic > Fmat;
typedef Matrix< int, Dynamic, Dynamic > Imat;

typedef Matrix< double, Dynamic, 1 > Vec;
typedef Matrix< float, Dynamic, 1 > Fvec;
typedef Matrix< int, Dynamic, 1 > Ivec;

typedef Matrix< double, 1, Dynamic> Rvec;
typedef Matrix< float, 1, Dynamic> Frvec;
typedef Matrix< int, 1, Dynamic> Irvec;

typedef Matrix< double, 2, 2 > Mat2;
typedef Matrix< double, 3, 3 > Mat3;
typedef Matrix< double, 4, 4 > Mat4;

typedef Matrix< float, 2, 2 > Fmat2;
typedef Matrix< float, 3, 3 > Fmat3;
typedef Matrix< float, 4, 4 > Fmat4;

typedef Matrix< int, 2, 2 > Imat2;
typedef Matrix< int, 3, 3 > Imat3;
typedef Matrix< int, 4, 4 > Imat4;

typedef Matrix< double, 2, 1 > Vec2;
typedef Matrix< double, 3, 1 > Vec3;
typedef Matrix< double, 4, 1 > Vec4;

typedef Matrix< float, 2, 1 > Fvec2;
typedef Matrix< float, 3, 1 > Fvec3;
typedef Matrix< float, 4, 1 > Fvec4;

typedef Matrix< int, 2, 1 > Ivec2;
typedef Matrix< int, 3, 1 > Ivec3;
typedef Matrix< int, 4, 1 > Ivec4;

} // end of namespace gezi
#endif
