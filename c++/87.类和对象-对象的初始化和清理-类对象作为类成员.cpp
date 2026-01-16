// 类和对象-对象的初始化和清理-类对象作为类成员

// C++类中的成员可以是另一个类的对象，我们称为该成员为 对象成员
//  个人理解：类的嵌套

//  当其他类对象作为本类成员，构造函数时先构造类对象，再构造自身
//  析构的顺序与构造相反 -> 当其他类对象作为本类成员，构造函数时先析构自身，再析构类对象

// 例子：
//      class A {};
//      class B
//      {
//          A a;
//      };

#include<iostream>
#include<string>
using namespace std;

class Phone
{
public:

    Phone(string p_name)
    {
        m_P_Name = p_name;
        cout << "Phone构造函数调用" << endl;
    }

    ~ Phone()
    {
        cout << "Phone析构函数调用" << endl;
    }

    // 手机品牌名称
    string m_P_Name;

};

class Person
{
public:

    Person(string name, string p_name): m_Name(name), m_Phone(p_name) // 这里m_Phone(p_name) 相当于 Phone m_Phone = p_name;
    {
        cout << "Person构造函数调用" << endl;
    }
    ~ Person()
    {
        cout << "Person析构函数调用" << endl;
    }

    // 姓名
    string m_Name;
    // 手机
    Phone m_Phone;
};

void test01()
{
    Person p("张三", "苹果Pro");
    cout << "这个人的名字：" << p.m_Name << " 他的手机品牌名称：" << p.m_Phone.m_P_Name << endl;
}

int main()
{
    test01();

    return 0;
}