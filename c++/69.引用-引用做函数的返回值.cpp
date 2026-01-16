//引用-引用做函数的返回值

//作用：引用是可以作为函数的返回值存在的

//注意：不要返回局部变量引用

//用法：函数调用作为左值

#include<iostream>
using namespace std;

//引用做函数的返回值


// 1.不要返回局部变量引用
// 错误的
/*
int& test02()
{
    int a = 20; //局部变量存放在内存四区中的 栈区 
    return a;
}
*/

// 2.函数的调用可以作为左值
int& test01()
{
    static int a = 10;// 静态变量，存放在全局区，全局区上的数据在程序结束后系统释放
    return a;
}

int main()
{
    int &ref1 = test01();

    cout << "ref1 = " << ref1 << endl;//正确示范
    cout << "ref1 = " << ref1 << endl;//正确示范
    
    test01() = 1000;
    cout << "ref1 = " << ref1 << endl;//正确示范
    cout << "ref1 = " << ref1 << endl;//正确示范

    /*
    int &ref2 = test02();

    cout << "ref2 = " << ref2 << endl;//错误的
    */

    return 0;
}