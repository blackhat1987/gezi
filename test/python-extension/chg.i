%module chg
%{
      /* Includes the header in the wrapper code */
       #include "chg.h"
%}
  
/* Parse the header file to generate wrappers */
%include "chg.h"
