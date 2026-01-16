//函数高级-默认参数

#include<iostream>
using namespace std;

//函数默认参数

//如果我们自己传入数据，就用自己的数据，如果没有，那么就用默认值
//语法：返回值类型 函数名（形参 = 默认值）
int func(int a,int b = 20,int c = 30)
{
    return a + b + c;
}

//注意事项

// 1.如果某个位置已经有了默认参数，那么从这个位置往后，从左往右都必须要有默认值
/*
int func2(int a,int b = 10,int c)
{
    return a + b + c;
}
*/

// 2.如果函数声明有默认参数，函数实现就不能有默认参数
// 声明和实现只能有一个有默认参数（就是不能重复定义一个位置的默认参数）
int func3(int a, int b = 20);

int func3(int a = 10, int b)//已经有了声明的函数，位置在哪里都可以
{
    return a + b;
}

int main()
{
    cout << func(10, 20) << endl;
    cout << func3() << endl;

    return 0;
}