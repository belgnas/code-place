// 类和对象-继承-继承方式

// 继承的语法：class 子类 : 继承方式 父类

// 继承方式一共有三种（也就是3种权限）
//  1.公共继承
//  2.保护继承
//  3.私有继承

// // 父类
// class A
// {
// public:
//     int a;
// protected:
//     int b;
// private: // 隐私度最高（无论什么继承都无法访问）
//     int c;
// };

// // 1.公有继承
// class B : public A // 父类是什么，公有继承就是什么（直接复制下来）
// {
// public: 
//     int a;
// protected:
//     int b;
// // 不可访问:// 父类中private隐私度最高（无论什么继承都无法访问）
//     int c;
// };

// // 2.公有继承
// class B : protected A // 父类的public变成保护继承子类的protected
// {
// protected:
//     int a;
//     int b;
// // 不可访问:// 父类中private隐私度最高（无论什么继承都无法访问）
//     int c;
// };

// // 3.私有继承
// class B : private A // 父类的public和private变成私有继承子类的private
// {
// private:
//     int a;
//     int b;
// // 不可访问:// 父类中private隐私度最高（无论什么继承都无法访问）
//     int c;
// };

#include<iostream>
using namespace std;

// 父类1
class Base_1
{
public:
    int m_A;
protected:
    int m_B;
private: // 隐私度最高（无论什么继承都无法访问）
    int m_C;
};

// 1.公有继承
class Son_1 : public Base_1 // 父类是什么，公有继承就是什么（直接复制下来）
{
public: 
    
    void func() 
    {
        m_A = 10; // 父类中的公共权限成员 到子类中依旧是公共权限
        m_B = 10; // 父类中的保护权限成员 到子类中依旧是保护权限
        // m_C = 10; // 父类中的私有权限成员 到子类中无法访问
    }
};

void test01()
{
    Son_1 s1;
    s1.m_A = 100;
    // s1.m_B = 100; // 到了Son_1 中，m_B仍然是保护权限，类外访问不到
    // s1.m_C = 100; // 父类私有权限 无法访问
}

// 父类2
class Base_2
{
public:
    int m_A;
protected:
    int m_B;
private: // 隐私度最高（无论什么继承都无法访问）
    int m_C;
};

// 2.保护继承
class Son_2 : protected Base_2 // 父类的public变成保护继承子类的protected
{
protected:

    void func()
    {
        m_A = 100; // 父类中的公共权限成员 到子类中变成保护权限
        m_B = 100; // 父类中的保护权限成员 到子类中依旧是保护权限
        // m_C = 100; // 父类中的私有权限成员 到子类中无法访问
    }
// 不可访问:// 父类中private隐私度最高（无论什么继承都无法访问）
};

void test02()
{
    Son_2 s2;
    // s2.m_A = 1000; // 到了Son_2 中，m_A变成保护权限，类外访问不到
    // s2.m_B = 1000; // 到了Son_2 中，m_B仍然是保护权限，类外访问不到
    // s2.m_C = 1000; // 父类私有权限 无法访问
}

// 父类3
class Base_3
{
public:
    int m_A;
protected:
    int m_B;
private: // 隐私度最高（无论什么继承都无法访问）
    int m_C;
};

// 3.私有继承
class Son_3 : private Base_3 // 父类的public和private变成私有继承子类的private
{
public:

    void func()
    {
        // m_A = 100; // 父类中的公共权限成员 到子类中变成私有权限
        // m_B = 100; // 父类中的保护权限成员 到子类中变成私有权限
        // m_C = 100; // 父类中的私有权限成员 到子类中仍然无法访问
    }
};
class GrandSon_3 : public Son_3
{
public:

    void func()
    {
        // m_A = 1000; // 父类中的私有权限成员 到子类中仍然无法访问
        // m_B = 1000; // 父类中的私有权限成员 到子类中仍然无法访问
        // m_C = 1000; // 父类中的私有权限成员 到子类中仍然无法访问
    }
}

void test03()
{
    Son_3 s3;
    // s3.m_A = 1000; // 到了Son_3 中，m_A变成私有权限，类外访问不到
    // s3.m_B = 1000; // 到了Son_3 中，m_B变成私有权限，类外访问不到
    // s3.m_C = 1000; // 父类私有权限 无法访问
}

int main()
{
    test01();
    test02();
    test03();

    return 0;
}