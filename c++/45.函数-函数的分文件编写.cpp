//函数-函数的分文件编写

//作用：让代码结构更清晰
//个人理解：为实现模块化编程，把不同的函数放在不同的文件中

//函数的文件名编写一般有4个步骤
//1.创建后缀名为.h的文件
//2.创建后缀名为.cpp的文件
//3.在头文件中写函数的声明
//4.在源文件中写函数的定义

#include<iostream>
#include"45.头文件swap.h"
//必须用双引号表示这是自己写的头文件

using namespace std;

//示例：一个交换数字的函数
//函数的声明
void swap(int a,int b);

//函数的定义
/*
void swap(int a,int b)
{
    int temp = a;
    a = b;
    b = temp;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
}
*/

//1.创建后缀名为.h的文件
//2.创建后缀名为.cpp的文件
//3.在头文件中写函数的声明
//4.在源文件中写函数的定义

int main()
{
    int a = 10;
    int b = 20;

    swap(a,b);

    system("pause");

    return 0;
}

