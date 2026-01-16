// 类和对象-对象的初始化和清理-构造函数调用规则

// 默认情况下，C++编译器至少给一个类添加3个函数
//      1. 默认构造函数（无参，函数体为空）（空实现）
//      2. 默认析构函数（无参，函数体为空）（空实现）
//      3. 默认拷贝构造函数，对属性进行值拷贝（值拷贝）

// 构造函数调用规则如下：
//      1. 如果用户定义有参构造函数，C++不会提供默认无参构造，但是会提供默认拷贝构造
//      2. 如果用户定义拷贝构造函数，C++不会再提供其他构造函数

#include<iostream>
using namespace std;

class Person
{
public:
    Person()
    {
        cout << "Person的默认构造函数调用" << endl;
    }
    Person(int age)
    {
        cout << "Person的有参构造函数调用" << endl;
        m_Age = age;
    }
    // Person(const Person &p)
    // {
    //     cout << "Person的拷贝构造函数调用" << endl;
    //     m_Age = p.m_Age;
    // }

    ~ Person()
    {
        cout << "Person的析构默认构造函数调用" << endl;
    }

    int m_Age;
};

void test01()
{
    Person p;
    p.m_Age = 17;

    Person p2(p); // 我们把自己写的拷贝构造函数注释掉了，就相当于我们没有写拷贝构造函数的情况，此时C++编译器会提供默认拷贝构造函数
    cout << "p2的age为：" << p2.m_Age << endl;
}

void test02()
{
    Person p3;
    Person p4(18);
    Person p5(p4);
    // ps:（否则会报错）
    //    1. 如果用户定义有参构造函数，C++不会提供默认无参构造，但是会提供默认拷贝构造
    //    2. 如果用户定义拷贝构造函数，C++不会再提供其他构造函数
}

int main()
{
    test01();
    test02();

    return 0;
}