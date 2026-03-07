// 类和对象-对象的初始化和清理-构造函数的分类及调用

// 2种分类方式：
//      按参数分为：有参构造、无参构造（无参又称为默认构造函数）
//      按类型分为：普通构造、拷贝构造

// 3种分类方式：
//      ① 括号法
//      ② 显示法
//      ③ 隐式转换法

#include<iostream>
using namespace std;


class Person
{
public:
    // 构造函数
    Person()
    {
        cout << "Person 无参 构造函数的调用" << endl;
    }
    Person(int a)
    {
        age = a;
        cout << "Person 有参 构造函数的调用" << endl;
    }
    // 拷贝构造函数
    Person(const Person &p)
    {
        // 将传入的人的身上的所有属性，拷贝到我身上
        age = p.age;
        cout << "Person 拷贝构造函数的调用" << endl;
    }

    ~Person()
    {
        cout << "Person 析构函数的调用" << endl;
    }



    int age; // 测试变量（age年龄）

};

// 调用
void test01()
{
    // 1.括号法
    Person p1; // 无参函数调用 (ps:调用无参函数的时候不要加小括号“()”,"Person p1()"会被当成函数的声明)
    Person p2(10); // 有参函数构造
    Person p3(p2); // 拷贝函数构造

    cout << "p2的年龄为：" << p2.age << endl;
    cout << "p3的年龄为：" << p3.age << endl;
    
    // 2.显示法

    Person p4; // 无参函数调用 
    Person p5 = Person(10); // 有参函数构造
    Person p6 = Person(p5); // 拷贝函数构造
    
    Person(10); // 匿名对象 特点：当前行执行结束后，系统会立即回收掉匿名对象(而不是等函数test01全部执行完后再回收)
    cout << "匿名对象已回收" << endl;

    // 不要利用拷贝构造函数来初始化一个匿名对象
    //Person(p6); // 因为编译器会认为 Person (p6) == Person p6;（对象的声明）

    // 3.隐式转换法
    Person p7 = 10; // 相当于写了 Person p7 = Person(10);  有参构造
    Person p8 = p7; // 拷贝构造
}

int main()
{
    test01();

    system("pause");

    return 0;
}