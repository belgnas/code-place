// 类和对象-继承-继承同名成员处理方式

// 问题：
//  当子类于父类出现同名的成员，如何通过子类对象，访问通过子类对象，访问到子类或父类中的同名的数据呢？

// 回答：
//  1.访问子类同名成员 直接访问即可
//  2.访问父类同名成员 需要加作用域

#include<iostream>
using namespace std;

class Base
{
public:
    Base()
    {
        m_A = 100;
    }

    void func()
    {
        cout << "Base 作用域下的 func() 调用 " << endl;
    }

    void func(int a)
    {
        cout << "Base 作用域下的 func(int a) 调用 " << endl;
    }

    int m_A;
};

class Son : public Base
{
public:
    Son()
    {
        m_A = 200;
    }

    void func()
    {
        cout << "Son 作用域下的 func() 调用 " << endl;
    }

    void func(int a)
    {
        cout << "Son 作用域下的 func(int a) 调用 " << endl;
    }

    int m_A;
};

// 同名成员属性处理
void test01()
{
    Son s1;
    cout << "Son 下 m_A = " << s1.m_A << endl; // 1.访问子类同名成员 直接访问即可
    // 如果通过子类对象 访问到父类中的同名成员，需要加作用域
    cout << "Base 下 m_A = " << s1.Base::m_A << endl; // 2.访问父类同名成员 需要加作用域
}

// 同名成员函数处理
// 如果子类中出现和父类同名的成员函数，子类的同名成员函数会隐藏掉父类中的所有同名成员函数
// 如果想访问到父类中被隐藏的同名成员函数，需要加作用域
void test02()
{
    Son s2;

    s2.func(); // 1.访问子类同名成员 直接访问即可
    // 如果通过子类对象 访问到父类中的同名成员，需要加作用域
    s2.Base::func(10); // 2.访问父类同名成员 需要加作用域

}

int main()
{
    test01();
    test02();

    return 0;
}