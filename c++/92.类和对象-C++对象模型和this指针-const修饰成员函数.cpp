// 类和对象-C++对象模型和this指针-const修饰成员函数

// 常函数：
//      1.成员函数后加个 const 后，我们称这个函数为常函数
//      2.常函数内不可以修改成员属性
//      3.成员属性声明是加关键字 mutable 后，在常函数中依然可以修改

// 常对象：
//      1.声明对象前加 const ，称该对象为常对象
//      2.常对象只能调用常函数

#include<iostream>
using namespace std;

// 常函数
class Person
{
public:
    // this指针的本质 是指针常量 这种指针的指向是不可以修改的,但是其指向的值是可以修改的
    // 这里的this指针相当于被这样定义了： Person * const this

    // 但是，如果不想让函数能修改类内的值，就像这样加个 const（值和指向都不可以修改）
    // 这个函数后面的 const 修饰的是 this 指针指向的值，让 this 指针指向的值也不可以修改
    // 这里的this指针相当于被这样定义了：const Person * const this
    void showPerson() const 
    {
        //加了const后的错误示范
        // m_A = 100;// 或 this->m_A = 100; // 这2种的方法任选一种使用
        // 比如 this->m_A = NULL; // 指针指向的值不可以修改了

        this->m_B = 200; // 加了 mutable 后，在常函数中也可以修改了
    }

    void func()
    {

    }

    int m_A;
    mutable int m_B; // 加了关键字 mutable 就变成了特殊变量，即使是在常函数中，也可以修改这个值
};

void test01()
{
    Person p;
    p.showPerson();
}

// 常对象
void test02()
{
    const Person p2 = Person(); // 在对象前面加 const，变成常对象(ps，需要进行初始化操作)
    // p2.m_A = 100; // 常对象的值是不可以修改的
    p2.m_B = 100;
    cout << "p2.m_B: " << p2.m_B << endl;

    p2.showPerson(); // 常对象只能调用常函数
    cout << "调用常函数后p2.m_B: " << p2.m_B << endl;

    // p2.func(); // 常对象不能调用其他函数

}

int main()
{
    test01();
    test02();

    return 0;
}
