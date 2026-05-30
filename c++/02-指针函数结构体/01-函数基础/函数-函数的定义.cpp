//函数-函数的定义

// 一般有5个步骤：
// 1.返回值类型--------一个函数可以返回一个值，在函数的定义中
// 2.函数名------------给函数起个名字
// 3.参数列表----------使用该函数时，传入的数据
// 4.函数体语句--------花括号内的代码，函数内需要执行的语句
// 5.return表达式------和返回值类型相挂钩，函数执行完后，返回相应的数据

// 语法：
//
//    返回值类型 函数名 (参数列表)
//    {
//        函数体语句
   
//        return表达式
//    }



// 实例：实现一个加法函数
// 功能是：传入2个整型数据，计算数据相加的结果，并且返回
// 5个步骤：
// 1.返回值类型      int
// 2.函数名          add
// 3.参数列表        (int num1,int num2)
// 4.函数体语句      int sum = num1 + num2;
// 5.return表达式    return sum;

//    int add(int num1, int num2)
//    {
//        int sum = num1 + num2;
//    
//        return sum;
//    }

#include<iostream>
using namespace std;

int add(int num1,int num2)
{
    int sum = num1 + num2;

    return sum;
}

int main()
{
    

    system("pause");

    return 0;
}