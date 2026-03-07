// 类和对象-C++对象模型和this指针-成员变量和成员函数分开存储

// C++种成员变量和成员函数分开存储
// 只有非静态成员变量才属于类的对象上

#include<iostream>
using namespace std;

class Person_1
{

};

class Person_2
{
    int m_A; // 非静态成员变量 // 属于类对象上
};

class Person_3
{
    static int m_B;// 静态成员变量和静态成员函数 // 不属于类对象上
    static void func1()
    {

    }

    void func2() // 非静态成员函数 // 同样不属于类对象上
    {

    }
};
int Person_3::m_B = 0;

void test01()
{
    Person_1 p1;
    // 空对象占用的内存空间为：1个字节 ！
    // 原因：C++编译器会给每个空对象也分配一个字节空间，是为了区分空对象占内存的位置
    // ps：每个空对象也应该有一个独一无二的内存地址
    cout << "size of p1 = " << sizeof(p1) << endl;
}

void test02()
{
    Person_2 p2;
    cout << "size of p2 = " << sizeof(p2) << endl;
}

void test03()
{
    Person_3 p3;
    cout << "size of p3 = " << sizeof(p3) << endl;
}

int main()
{
    test01();
    test02();
    test03();

    return 0;
}