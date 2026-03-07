// 类和对象-C++运算符重载-递增运算符重载

// 作用：
// 通过重载递增运算符，实现自己的整型数据

// 对于内置的数据类型 编译器会知道怎么实现
// 例如：
// int a = 10;
// cout << ++a << endl; // 输出结果为：11
// cout << a << endl; // 输出结果为：11
// int b = 10;
// cout << b++ << endl; // 输出结果为：10
// cout << b << endl; // 输出结果为：11

// 但是对于自定义的整型变量的数据类型，编译器就不会实现了
// 例如：
// class MyInteger // 这里 MyInteger 的意思是 自己的整型变量
// {
// public:
//     MyInteger()
//     {
//         m_Num = 0;
//     }

// private:
//     int m_Num;
// }

#include<iostream>
using namespace std;

// 自定义整型
class MyInteger // 这里 MyInteger 的意思是 自己的整型变量
{
    friend ostream & operator<<(ostream &cout, const MyInteger &myint);

public:
    MyInteger()
    {
        m_Num = 0;
    }

    // 重载前置++运算符（成员函数）
    // 这里返回引用 是为了一直对一个数据进行递增操作
    MyInteger & operator++()
    {
        // 先 进行++运算
        m_Num++;
        // 再 将自身做返回
        return *this;
    }

    // 重载后置++运算符（成员函数）
    // void operator++(int)   这里的int就是一个占位参数，可以用于区分前置和后置递增
    // 后置递增 相比于 前置递增，只能返回 值，不能返回 引用
    MyInteger operator++(int) // 用 占位参数int 来区分 前置、后置
    {
        // 先 记录自身当时的结果
        MyInteger temp = *this;
        // 再 进行++运算
        m_Num++;
        // 最后 将记录的结果做返回
        return temp;
    }

private:
    int m_Num;
};

// 重载左移 << 运算符
ostream & operator<<(ostream &cout, const MyInteger &myint)
{
    cout << myint.m_Num;
    return cout;
}

void test01()
{
    MyInteger myint1;

    cout << myint1 << endl;
    cout << ++(++myint1) << endl; // 这里会报错没有对应的++运算符
    cout << myint1 << endl;
    // 所以就需要 重载 递增运算符
}

void test02()
{
    MyInteger myint2;

    cout << myint2 << endl;
    cout << myint2++ << endl;
    cout << myint2 << endl;
}

int main()
{
    test01();
    test02();

    return 0;
}



// 写在最后
// 为什么 前置递增返回引用 而 后置递增返回值（副本）？

// 前置递增返回引用
// 语义上：前置递增是先自增对象，再返回自增后的对象本身。返回引用就相当于返回了这个自增后的对象，使得它能像内置类型一样作为左值继续参与运算，符合前置递增的语义。
// 性能上：返回引用避免了创建新对象和复制数据的开销，对于复杂对象或频繁递增操作更高效。

// 后置递增返回值（副本）
// 语义上：后置递增要先返回对象当前值，再自增对象。所以需要创建临时对象保存当前值，自增原对象后返回临时对象，以此符合后置递增先返回原值再自增的语义。
// 不能返回引用的原因：如果返回引用，会返回自增后的对象，不符合后置递增先返回原值的语义。