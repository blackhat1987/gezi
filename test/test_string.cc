#include <iostream> 
#include <string> 
#include <vector> 
#include <map> 
using namespace std; 

//结论 基本可以用 string 而不需要 const string&  内部估计采用了引用计数
void test1(string c)  //并没有进行值拷贝 内部copy实现是类似传引用
{ 
    printf("c[%u]\n",c.c_str()); 
    c = "def"; 
    printf("c2[%u]\n",c.c_str());  
} 
void test2(const string& d) 
{ 
    printf("d[%u]\n",d.c_str()); 
} 
void test3(const string e) 
{ 
    printf("e[%u]\n",e.c_str()); 
} 

void test4(string f = "ufo") 
{
	printf("f[%u]\n",f.c_str()); 
}
int main(int argc, const char *argv[]) 
{ 
    string a = "one"; 
    string b = a; 
    printf("a[%u]b[%u]\n",a.c_str(),b.c_str()); 
    test1(a); 
    printf("a[%u]b[%u]\n",a.c_str(),b.c_str()); 
    b += "3";  //当进行写操作 才进行copy 注意这个和c#就不一样 c#会修改a了 因为c#全是引用
    printf("a[%u]b[%u]\n",a.c_str(),b.c_str()); 
    test2(a); 
    test3(a); 
    a="s"; 
    printf("a[%u]b[%u]\n",a.c_str(),b.c_str()); 
    test4(); 
    test4(a);
    return 0; 
}