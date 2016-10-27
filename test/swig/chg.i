%module libchg
%include "std_string.i"
%include "std_vector.i"

namespace std {
  %template(ivec) vector<int>;
  %template(dvec) vector<double>;
  %template(svec) vector<string>;
};
%{
      /* Includes the header in the wrapper code */
       #include "chg.h"
%}
  
/* Parse the header file to generate wrappers */
%include "chg.h"
%include "def.h"
