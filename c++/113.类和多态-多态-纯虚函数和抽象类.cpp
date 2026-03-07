// 类和多态-多态-纯虚函数和抽象类

// 在多态中，通常父类中虚函数是没有意义的，主要都是调用子类重写的内容

// 因此可以将虚函数改成纯虚函数

// 纯虚函数语法
//  virtual 返回值类型 函数名 (参数列表) = 0;

// 当类中有了纯虚函数，这个类被称为 抽象类

// 抽象类特点：
//  1.无法实例化对象
//  2.子类必须重写抽象类中的纯虚函数，否则也属于抽象类

#include<iostream>
using namespace std;

// 纯虚函数和抽象类
class Base
{
public:
    // 纯虚函数
    // 这个类只要有一个纯虚函数，这个类被称为抽象类
    // 抽象类特点：
    // 1.无法实例化对象
    // 2.抽象类的子类 必须 要重写父类中的纯虚函数，否则也属于抽象类
    
    // 纯虚函数示例
    virtual void func() = 0;

};

class Son : public Base
{
public:
    virtual void func()
    {
        cout << "func函数调用" << endl;
    }


};

void test01()
{
    // Base b; // 抽象类是无法实例化对象的
    // new Base; // 抽象类是无法实例化对象的

    // Son s; // 子类必须要重写父类中的纯虚函数,否则无法实例化对象

    Base * base = new Son;
    base->func();
}

int main()
{
    test01();

    return 0;
}