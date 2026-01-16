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

//  静态成员函数
//      1.所有对象共享同一个函数
//      2.静态成员函数只能访问静态成员函数
class Person
{
public:

    static void func()
    {
        m_A = 100;
        cout << m_A << endl;

        // m_B = 200; // 静态成员函数 不可以访问 非静态成员变量
        // （个人理解）原因：m_Bb 不唯一，静态成员函数不知道应该调用的哪个 m_B；
        
        cout << "static void func的调用" << endl;
    }
    
    static int m_A; // 静态成员变量
    int m_B; // 非静态成员变量（静态成员函数无法访问）

private:
    // 静态成员函数也是有访问权限的
    // 类外访问不到私有静态成员函数
    static void func2()
    {
        cout << "私有静态成员函数static void func2的调用" << endl;
    }
};

int Person::m_A = 1;

// 有2种访问方式
void test01()
{
    // 1. 通过对象进行访问
    Person p;
    p.func();

    // 2. 通过类名进行访问
    Person::func();

    // Person::func2(); // 类外访问不到私有静态成员函数
}

int main()
{
    test01();

    return 0;
}