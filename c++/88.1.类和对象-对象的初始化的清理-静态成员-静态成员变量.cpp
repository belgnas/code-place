// 类和对象-对象的初始化的清理-静态成员

// 静态成员就是在成员变量和成员函数前面加上关键字 static ，称为静态成员

// 静态成员分成：
//      1.静态成员变量
//          ① 所有对象共享同一份数据 (好像可以理解成类里的全局变量)
//          ② 在编译阶段分享内存
//          ③ 类内声明，内外初始化
//      2.静态成员函数
//          ① 所有对象共享同一个函数
//          ② 静态成员函数只能访问静态成员函数

#include<iostream>
using namespace std;

class Person
{
public:

    // 1. 所有对象都共享同一份数据
    // 2. 编译阶段就分配了内存
    // 3. 类内声明，类外初始操作
    static int m_A;

    // 静态成员变量也是有访问权限的
private:
    static int m_B; // 类外访问不到私有的静态成员变量

};

int Person::m_A = 100;
// int Person::m_B = 200; // 类外访问不到私有的静态成员变量

void test01()
{
    Person p1;
    cout << p1.m_A << endl;

    Person p2;
    p2.m_A = 200;

    cout << p1.m_A << endl; // p1.m_A的值被 “p2.m_A = 200;” 修改成了200，体现了静态成员变量共享同一份数据的特点
}

void test02()
{
    // 静态成员变量，不属于某个对象上，所有的对象都共享同一份数据
    // 因此静态成员变量有2种访问方式

    // 1. 通过对象进行访问
    Person p;
    cout << p.m_A << endl;

    // 2. 通过类名进行访问
    cout << Person::m_A << endl;

    // cout << Person::m_B << endl; // 类外访问不到私有的静态成员变量

}

int main()
{
    test01();
    test02();

    return 0;
}