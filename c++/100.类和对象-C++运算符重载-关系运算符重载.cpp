// 类和对象-C++运算符重载-关系运算符重载

// 作用：
// 重载关系运算符，可以让2个自定义类型对象进行对比操作

// 对于内置的数据类型 编译器会知道怎么对比
// 例如：
// int a = 17;
// int b = 17;
// if(a == b)
// {
//     cout << " a 和 b 相等" << endl;
// }

// 但是对于自定义的整型变量的数据类型，编译器就不会对比了
// 例如：
// Person p1;
// Person p2;
// if(p1 == p2)
// {
//     cout << " p1 和 p2 相等" << endl;
// }
// if(p1 ！= p2)
// {
//     cout << " p1 和 p2 不相等" << endl;
// }

#include<iostream>
#include<string>
using namespace std;

class Person
{
public:
    Person(string name, int age)
    {
        m_Name = name;
        m_Age = age;
    }

    // 重载 == 号
    bool operator==(Person &p)
    {
        if(this->m_Name == p.m_Name && this->m_Age == p.m_Age)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    // 重载 != 号 
    bool operator!=(Person &p)
    {
        if(this->m_Name == p.m_Name && this->m_Age == p.m_Age)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    string m_Name; // 名字
    int m_Age; // 年龄
};

void test01()
{
    Person p1("Belgnas", 18);

    Person p2("Belgnas", 18);

    Person p3("奇奇莫拉", 16);

    if(p1 == p2) // 对于自定义的数据类型，编译器会报错，这时就需要重载 ==运算符
    {
        cout << "p1 和 p2 相等" << endl;
    }
    else
    {
        cout << "p1 和 p2 不相等" << endl;
    }
    if(p1 == p3) // 对于自定义的数据类型，编译器会报错，这时就需要重载 ==运算符
    {
        cout << "p1 和 p3 相等" << endl;
    }
    else
    {
        cout << "p1 和 p3 不相等" << endl;
    }

    if(p1 != p3) // 对于自定义的数据类型，编译器会报错，这时就需要重载 ==运算符
    {
        cout << "p1 和 p3 不相等" << endl;
    }
    else
    {
        cout << "p1 和 p3 相等" << endl;
    }
}

int main()
{
    test01();

    return 0;
}