// 类和对象-对象的初始化和清理-初始化列表

// 作用： C++提供了初始化列表语法，用来初始化属性

// 语法：
//      构造函数():属性1(值1), 属性2(值2), ...{}

#include<iostream>
using namespace std;

class Person
{
public:

    // // 传统初始化操作
    // Person(int a, int b, int c)
    // {
    //     m_A = a;
    //     m_B = b;
    //     m_C = c;
    // }

    // 使用初始化列表初始化属性

    // Person():m_A(10), m_B(20), m_C(30)
    // {
    //      // 使用这种的话只能用 Person p 调用（初始值已被固定）
    // }

    Person(int a, int b, int c):m_A(a), m_B(b), m_C(c)
    {

    }

    int m_A;
    int m_B;
    int m_C;
};

void test01()
{
    Person p(10, 20, 30); // 如果要使用上面第一种初始值固定的 “Person():m_A(10), m_B(20), m_C(30)”， 需要把这里的 “(10, 20, 30)” 删掉
    cout << "m_A = " << p.m_A << endl;
    cout << "m_B = " << p.m_B << endl;
    cout << "m_C = " << p.m_C << endl;
}

int main()
{
    test01();

    return 0;
}