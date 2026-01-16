//数据类型：字符型变量（1个字节）

//作用：字符型变量用于显示单个字符
//语法：char ch='a'
//ps：用单引号，不是双引号；单引号内只能有一个字符，不能是字符串

#include<iostream>
using namespace std;

int main()
{
    char ch='a';
    cout<<ch<<"\n";

    //字符型变量所占的内存大小
    cout<<"char字符型变量所占的内存"<<sizeof(char)<<endl;

    //字符型变量对应的ASCII编码
    //ps：程序不储存字符，而是储存对应的编码。
    //常见的字符所对应的编码需要记下来
    //如：a?97，A?65，b、c、d依次往后数就可以了
    cout<<(int)ch<<"\n";

    system("pause");
    return 0;
}