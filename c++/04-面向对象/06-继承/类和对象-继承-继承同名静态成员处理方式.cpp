// 类和对象-继承-继承同名静态成员处理方式

// 问题：继承中同名的静态成员变量在子类对象上如何进行访问？

// 静态成员和非静态成员出现同名，处理方式一致

// 访问子类同名成员 直接访问即可
// 访问父类同名成员 需要加作用域

#include<iostream>
using namespace std;

class Base
{
public:

    static int m_A;

    static void func()
    {
        cout << "Base类 static void func()的调用" << endl;
    }
};

int Base::m_A = 100;

class Son : public Base
{
public:

    static int m_A;

    static void func()
    {
        cout << "Son类 static void func()的调用" << endl;
    }
};

int Son::m_A = 200;

// 同名静态成员属性
void test01()
{
    // 1.通过对象访问
    cout << "通过对象访问：" << endl;
    Son s1;
    cout << "子类Son m_A = " << s1.m_A << endl; // 直接调用 子类Son
    cout << "父类Base m_A = " << s1.Base::m_A << endl; // 加了定义域 父类Base

    // 2.通过类名访问
    cout << "通过类名访问：" << endl;
    cout << "子类Son m_A = " << Son::m_A << endl;\
    // 第一个 :: 代表通过类名方式访问
    // 第二个 :: 代表访问父类作用域下
    cout << "父类Base m_A = " << Son::Base::m_A << endl;

}

// 同名静态成员函数
// 如果子类中出现和父类同名的静态成员函数，子类的同名成员函数会隐藏掉父类中的所有同名成员函数
// 如果想访问到父类中被隐藏的同名成员函数，需要加作用域
void test02()
{
    // 1.通过对象访问
    cout << "通过对象访问：" << endl;
    Son s2;
    s2.func();
    s2.Base::func();

    // 2.通过类名访问
    cout << "通过类名访问：" << endl;
    Son::func();
    Son::Base::func();


}

int main()
{
    test01();
    test02();

    return 0;
}