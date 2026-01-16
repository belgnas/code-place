//数据类型：字符串

#include<iostream>
using namespace std;
#include<string>//方法2的头文件

int main()

{
    //1.C风格的字符串：char 变量名[]="字符串值"
    //ps：char 字符串名 []
    //等号后面要用双引号包含起字符串
    char str1[]="hello world";
    cout<<str1<<"\n";

    //2.C++风格的字符串
    //包含一个头文件    #include<string>
    string str2="hello world";
    cout<<str2<<"\n";

    system("pause");

    return 0;
}