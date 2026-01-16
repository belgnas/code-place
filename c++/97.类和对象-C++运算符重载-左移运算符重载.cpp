// 类和对象-C++运算符重载-左移运算符重载

// C++左移运算符 “ << ” 重载
// 作用：
// 可以输出自定义数据类型

// 对于内置的数据类型，编译器知道如何进行输出
// 例如：
// int a = 10;
// cout << a << endl;

// 但是对于自定义的数据类型，编译器就不会输出了
// 例如：
// class Person
// {
// public:

//     int m_A;
//     int m_B;
// }

// Person p;
// p.m_A = 10;
// p.m_B = 20;
// 
// cout << p << endl; // 这里我想要输出数据类型为Person的p（按照将p里面的成员依次输出的规律进行输出）

// 
#include<iostream>
using namespace std;

class Person
{
    friend ostream & operator<<(ostream &cout, Person &p);

public:

    Person(int a, int b)
    {
        m_A = a;
        m_B = b;
    }

private:

// 方法一代码：利用成员函数重载 左移运算符
    // ostream& operator<<(ostream& cout) const
    // {
    //     out << "m_A = " << m_A << " " << "m_B = " << m_B;
    //     return cout;
    // }
//但是这样子实现出来的代码的调用最终是 p << cout << endl;（是反过来的）
// 所以我们一般不会用成员函数重载 左移运算符 “<<” 

    int m_A;
    int m_B;
};

// 方法二代码：利用全局函数重载 左移运算符
// ostream 标准输出流对象
ostream & operator<<(ostream &cout, Person &p) // 本质是 operator<<(cout, p) 可简化为 cout << p;
{
    cout << "m_A = " << p.m_A << " " << "m_B = " << p.m_B;
    return cout;
}

void test01()
{
    Person p(10, 20);

    // 常规方法：
    // cout << p.m_A << endl;
    // cout << p.m_B << endl;

    // 但是这里我想使用
    cout << p << endl; // 这个时候就需要重载运算符了

    // 方法一：利用成员函数重载 左移运算符(一般不会使用)、

    // 方法二：利用全局函数重载 左移运算符 ！！！
    
}




int main()
{
    test01();

    return 0;
}