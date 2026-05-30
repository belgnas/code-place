//函数-函数的分文件编写

//4个步骤
//1.创建后缀名为.h的文件
//2.创建后缀名为.cpp的文件
//3.在头文件中写函数的声明
//4.在源文件中写函数的定义


//这2行一定不要忘了
#include<iostream>
using namespace std;

//一个交换数字的函数
//函数的定义
void swap(int a,int b)
{
    int temp = a;
    a = b;
    b = temp;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
}