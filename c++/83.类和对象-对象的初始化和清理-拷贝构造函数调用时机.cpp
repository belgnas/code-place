// 类和对象-对象的初始化和清理-拷贝构造函数调用时机

// C++中拷贝构造函数调用时机通常有三种情况
//      1. 使用一个已经创建完毕的对象来初始化一个新对象
//      2. 值传递的方式给函数参数传值
//      3. 以值方式返回局部对象

#include<iostream>
using namespace std;

class Person
{
public:
    Person()
    {
        cout << "Person默认构造函数调用" << endl;
    }
    Person(int age)
    {
        m_Age = age;
        cout << "Person有参构造函数调用" << endl;
    }
    Person(const Person &p)
    {
        m_Age = p.m_Age;
        cout << "Person拷贝构造函数调用" << endl;
    }

    ~ Person()
    {
        cout << "Person析构函数调用" << endl;
    }

    int m_Age;

};

// 1. 使用一个已经创建完毕的对象来初始化一个新对象
void test01()
{
    Person p1(20);
    Person p2(p1);
}

// 2. 值传递的方式给函数参数传值
void doWork(Person copy_p) // 传入的是 p 的副本（形参），也就是 copy_p , copy_ 的改变不会影响到原来的 p
{
    // 理解逻辑，此处内容为空（不需要内容）
}
void test02()
{
    Person p;
    doWork(p); // 此处为值传递：即将 p 拷贝了一份副本在函数 doWork 中使用
}

// 3. 以值方式返回局部对象
Person doWork_2()
{
    Person p3;
    return p3;// 同理 值传递：此处是值返回，返回的是拷贝后的副本
    // 由于新编译器有优化，所以这里不会用到拷贝构造函数；
}
void test03()
{
    Person p = doWork_2();
}

int main()
{
    // test01(); // 1
    // test02(); // 2
    test03(); // 3

    return 0;
}