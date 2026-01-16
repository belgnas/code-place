// 类和对象-C++运算符重载-关系运算符重载

// 函数调用运算符 () 也可以重载
// 由于重载后使用的方式非常像函数的调用，因此被称为仿函数
// 仿函数没有固定写法，非常灵活

// 在后续的 STL 学习中 会大量地使用 仿函数

#include<iostream>
#include<string>
using namespace std;

// 函数调用运算符重载

// 打印输出类
class MyPrint
{
public:

    // 重载函数调用运算符
    void operator()(string test)
    {
        cout << test << endl;
    }



};

// 正常的函数
void MyPrint02(string test)
{
    cout << test << endl;
}

void test01()
{
    MyPrint myPrint;

    myPrint("hello world!"); // 由于使用起来非常类似于函数调用，因此被称为 仿函数

    MyPrint02("hello world.");

}

// 仿函数非常的灵活，没有固定的写法

// 加法类
class MyAdd
{
public:
    
    int operator()(int num1, int num2)
    {
        return num1 + num2;
    }
};

void test02()
{
    MyAdd myadd;
    int ret = myadd(17, 17);
    cout << "ret = " << ret << endl;
}

void test03()
{
    // 匿名函数对象
    cout << MyAdd()(18, 18) << endl;
}

int main()
{
    test01();
    test02();
    test03();

    return 0;
}