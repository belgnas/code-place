// 类和对象-继承-继承中的构造和析构顺序

// 子类继承父类后，当创建子类对象，也会调用父类的构造函数

// 问题：父类和子类的构造和析构顺序是谁先谁后？

// 回答：
// 父类构造 -> 子类构造 -> 子类析构 -> 父类析构
// （记忆技巧：先有父亲再有儿子，但是白发人送黑发人）


#include<iostream>
using namespace std;

class Base
{
public:
    Base()
    {
        cout << "Base构造函数调用！" << endl;
    }
    ~Base()
    {
        cout << "Base析构函数调用！" << endl;
    }
};

class Son : public Base
{
public:
    Son()
    {
        cout << "Son构造函数调用！" << endl;
    }
    ~ Son()
    {
        cout << "Son析构函数调用！" << endl;
    }
};

void test01()
{
    Son son; // 父类构造 -> 子类构造 -> 子类析构 -> 父类析构
}

int main()
{
    test01();

    return 0;
}