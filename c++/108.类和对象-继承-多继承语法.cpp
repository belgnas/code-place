// 几田莉拉（YOASOBI的主唱） 入驻b站了，好耶

// 类和对象-继承-多继承语法

// C++允许一个类继承多个类
// 个人语言：一个子类 可以继承 多个父类

// 语法
// class 子类 : 继承方式 父类1, 继承方式 父类2 ...

// 多继承可能会引发父类中的同名函数出现，需要加作用域区分

// ps：C++实际开发中不建议用多继承 !

#include<iostream>
using namespace std;

// 父类1
class Base1
{
public:

    Base1()
    {
        m_A = 100;
    }

    int m_A;
};

// 父类2
class Base2
{
public:

    Base2()
    {
        m_A = 200;
        m_B = 250;
    }

    int m_A;
    int m_B;
};

// 子类  需要同时继承 Base1 和 Base2
// 语法：class 子类 : 继承方式 父类1, 继承方式 父类2 ...
class Son : public Base1, public Base2
{
public:
    Son()
    {
        m_C = 300;
        m_D = 400;
    }

    int m_C;
    int m_D;
};

void test01()
{
    Son s;

    cout << "sizeof Son = " << sizeof(s) << endl;

    cout << "父类Base2 m_B = " << s.m_B << endl;
    // 当父类中出现同名成员时，需要加作用域区分
    cout << "父类Base1 m_A = " << s.Base1::m_A << endl;
    cout << "父类Base2 m_A = " << s.Base2::m_A << endl;
}

int main()
{
    test01();

    return 0;
}

// 总结：多继承如果父类出现了同名情况，子类使用时要加作用域