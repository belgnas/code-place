//函数-函数的声明

//个人理解：简单来说，就是提前告诉编译器代码中有其他函数的存在，以免因为函数的顺序问题而报错

//作用：告诉编译器函数名称及如何调用函数。函数的实际主体可以单独定义。

//ps：函数的声明可以多次，但是函数的定义只能有一次

#include<iostream>
using namespace std;


//可以提前告诉编译器函数存在，可以利用函数的声明
//这对于先写主函数再写副函数至关重要
int max(int a,int b);
//ps：函数的声明可以多次，但是函数的定义只能有一次
int max(int a,int b);
int max(int a,int b);

int main()
{
    int a = 200;
    int b = 300;
    cout << max(a,b) << endl;
    
    system("pause");

    return 0;   
}

//定义一个比较函数
int max(int a,int b)
{
    return a > b ? a : b;//三目运算符
    //注意这里的return，非常容易搞忘
}