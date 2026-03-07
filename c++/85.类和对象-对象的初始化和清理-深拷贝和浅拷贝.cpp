// 类和对象-对象的初始化和清理-深拷贝和浅拷贝

// 浅拷贝：简单的赋值拷贝操作（默认拷贝构造是浅拷贝）
// 深拷贝：在堆区重新申请空间，进行拷贝操作

#include<iostream>
using namespace std;

class Person
{
public:
    Person()
    {
        cout << "Person的默认构造函数调用" << endl;
    }
    Person(int age, int height)
    {
        m_Age = age;
        m_Height = new int(height);
        cout << "Person的有参构造函数调用" << endl;
    }

    // 当然，我们一般用的编译器比较先进（默认拷贝是值传递，不是地址传递）（不会报错）
    Person(const Person &p)
    {
        cout << "Person 拷贝构造函数的调用（深拷贝）" << endl;
        m_Age = p.m_Age;
        // m_Height = p.m_Height; // （编译器默认代码）此处是浅拷贝（帮助理解二者的区别）
        // 深拷贝操作
        m_Height = new int (*p.m_Height);

    }

    ~ Person()
    {
        // 析构代码，将堆区将堆区开辟的数据做释放操作
        if(m_Height != NULL)
        {
            delete m_Height; // 释放内存
            m_Height = NULL; // 防止释放内存后野指针出现
        }
        cout << "Person的析构函数调用" << endl;
    }

    int m_Age; // 年龄
    int *m_Height; // 身高（开辟到堆区）
};

void test01()
{
    Person p1(18, 150);
    cout << "p1的年龄为：" << p1.m_Age << " 身高为：" << *p1.m_Height << endl;

    Person p2(p1);
    cout << "p2的年龄为：" << p2.m_Age << " 身高为：" << *p2.m_Height << endl;
}

int main()
{
    test01();

    return 0;
}