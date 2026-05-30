//常量

//两种定义方式：

//1.#define宏常量：#define 常量名 常量值（ps：注意这里有空格）
//通常在文件上方定义，表示一个常量，不可修改

//2.const修饰的变量：const 数据类型 常量名=常量值（ps：注意空格）
//通常在变量定义前面加关键字const，修饰变量为常量，不可修改。

#define day 7//这里是第一种方法

#include<iostream>
using namespace std;

int main()
{
    cout<<"一个周有"<<day<<"天"<<"\n";//接上面第一种方法

    const int hour=24;//这里是第二种方法
    cout<<"一天有"<<hour<<"小时"<<"\n";

    system("pause");
    
    return 0;
}