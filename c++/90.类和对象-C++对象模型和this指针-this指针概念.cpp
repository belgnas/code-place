// 类和对象-C++对象模型和this指针-this指针概念

// 通过第89小节我们知道C++中成员变量和成员函数是分开存储的
// 每一个非静态成员函数只会诞生一份函数实例，也就是说多个同类型的对象会共用同一块代码
// 那么问题是：这一块代码是如何区分哪个对象调用自己的呢？

// C++通过提供特殊的对象指针，this指针，解决上述问题。

//    *** this指针指向被调用的成员函数所属的对象 ***
// (个人理解：谁调用this指针，this指针就指向)

// this指针是隐含每一个非静态成员函数内的一种指针
// this指针不需要定义，直接使用即可

// this指针的用途：
//      1. 当形参和成员变量同名时，可以用this指针来区分
//      2. 在类的非静态成员函数中返回对象本身，可使用 return *this

#include<iostream>
using namespace std;

class Person
{
public:
    Person(int age)
    {
        this->age = age; 
        // 用this指向Person类内的age，可以防止名称冲突

        // 当然，一般我们会选择使用 m_age 来表示类内的 age
    }


    // 个人理解：
    //   强调：这里是 "Person &"， 不是 "Person" ；
    // Person & PersonAddAge(Person &p) 是 按引用返回  
    //      当函数PersonAddAge按引用返回时，返回的是*this本身，
    //      也就是调用函数的对象本身的引用，而不是一个新的副本。
    // Person PersonAddAge(Person &p) 则是 按值返回
    //      当函数PersonAddAge按值返回时，会创建一个新的Person对象，
    //      这个新对象是通过复制*this对象得到的。
    //      也就是说，返回的是调用函数的对象（*this）的一个副本。
    Person & PersonAddAge(Person &p)
    {
        this->age += p.age;

        // this 指向p2的指针，而 *this 指向的就是p2这个对象本体
        return *this;
    }

    int age;
};

// 1. 解决名称冲突
void test01()
{
    Person p(18);
    cout << "p的年龄为：" << p.age << endl;
}

void test02()
{
    Person p1(10);
    Person p2(10);
    
    // 链式编程思想
    p2.PersonAddAge(p1).PersonAddAge(p1).PersonAddAge(p1); // 这里的逻辑是:把“p2.PersonAddAge(p1)” 当成一个新的p2 来代进去后面的 ~.PersonAddAge(p1).PersonAddAge(p1)
    cout << "p2的年龄为：" << p2.age << endl;
}

// 2. 返回对象本身用 *

int main()
{
    test01();
    test02();

    return 0;
}