#include <iostream> 
#include <string> 
#include <vector> 
#include <map> 
using namespace std; 

//���� ���������� string ������Ҫ const string&  �ڲ����Ʋ��������ü���
void test1(string c)  //��û�н���ֵ���� �ڲ�copyʵ�������ƴ�����
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
    b += "3";  //������д���� �Ž���copy ע�������c#�Ͳ�һ�� c#���޸�a�� ��Ϊc#ȫ������
    printf("a[%u]b[%u]\n",a.c_str(),b.c_str()); 
    test2(a); 
    test3(a); 
    a="s"; 
    printf("a[%u]b[%u]\n",a.c_str(),b.c_str()); 
    test4(); 
    test4(a);
    return 0; 
}