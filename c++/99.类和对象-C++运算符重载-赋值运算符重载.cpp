// 请你知道，键盘之上，我的主场+


// 类和对象-C++运算符重载-赋值运算符重载

// C++编译器至少给一个类添加4个函数
//      1.默认构造函数(无参，函数体为空)
//      2.默认析构函数(无参，函数体为空)
//      3.默认拷贝构造函数，对属性进行值拷贝
//      4.赋值运算符 operator= ，对属性进行值拷贝 (本节探究的问题)

// 如果类中有属性指向堆区，做赋值操作时也会出现深拷贝问题


#include<iostream>
using namespace std;

class Person
{
public:

    Person(int age)
    {
        m_Age = new int(age);
    }

    ~Person()
    {
        if(m_Age != NULL)
        {
            delete m_Age; 
            m_Age = NULL; 
            // 有的编译器这里会报错（崩溃）
            // 是因为出现了深拷贝问题（重复释放内存）
            // 当然，这里好像因为vscode的编译器比较先进，所以没有报错呐
        }
    }

    // 如果报错的话，那么
    // 重载 赋值运算符
    Person & operator=(Person &p)
    {
        // 编译器提供的是浅拷贝（如下一行）
        // m_Age = p.m_Age;

        // 应该先判断是否有属性在堆区，如果有就先释放干净，然后再深拷贝
        if(m_Age != NULL)
        {
            delete m_Age;
            m_Age = NULL;
        }

        // 深拷贝操作：
        // 让自身这个指针去指向这个新的内存空间
        m_Age =  new int(*p.m_Age);

        return *this;

    }

    int *m_Age;
};

void test01()
{
    Person p1(16);

    Person p2(17);

    Person p3(18);

    cout << "p1的年龄为：" << *p1.m_Age << endl;
    cout << "p2的年龄为：" << *p2.m_Age << endl;

    p2 = p1; // 赋值操作

    cout << "p1的年龄为：" << *p1.m_Age << endl;
    cout << "p2的年龄为：" << *p2.m_Age << endl;

    p3 = p2 = p1; // 链式编程思想

    cout << "p1的年龄为：" << *p1.m_Age << endl;
    cout << "p2的年龄为：" << *p2.m_Age << endl;
    cout << "p3的年龄为：" << *p3.m_Age << endl;

}

int main()
{
    test01();

    return 0;
}
