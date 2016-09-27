/* 
 * File:   json_help.h
 * Author: root
 *
 * Created on 2010年6月27日, 下午6:27
 */

#ifndef JSON_HELP_H
#define	JSON_HELP_H

#define PropGets(s)\
s = pt.get<std::string>(#s);

#define PropGeti(s)\
s = pt.get<int>(#s);

#define PropGetf(s)\
s = pt.get<float>(#s);

#define PropGetd(s)\
s = pt.get<double>(#s);

#define PropGetb(s)\
s = pt.get<bool>(#s);

#define PropGet(s,type)\
s = pt.get<type>(#s)

/**从s组中查找u,s.u*/
#define PropGet2(s, u, type)\
string a = #s; \
a += ".";\
a += #u;\
s = pt.get<type>(a)

#define PropGet2s(s, u)\
string a = #s; \
a += ".";\
a += #u;\
s = pt.get<string>(a)

#define PropGet2i(s, u)\
string a = #s; \
a += ".";\
a += #u;\
s = pt.get<int>(a)

#define PropGet2f(s, u, type)\
string a = #s; \
a += ".";\
a += #u;\
s = pt.get<float>(a)

#define PropGet2d(s, u, type)\
string a = #s; \
a += ".";\
a += #u;\
s = pt.get<double>(a)

#endif	/* JSON_HELP_H */

