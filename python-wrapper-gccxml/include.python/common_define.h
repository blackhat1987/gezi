#ifndef GEZI_COMMON_DEFINE_H_
#define GEZI_COMMON_DEFINE_H_
#ifndef IS_HIGH_COMPILER
#define IS_HIGH_COMPILER  !defined(GCCXML) && (__GNUC__ > 3 || defined(WIN32))
#endif
#endif
