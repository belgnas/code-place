// 类和对象-C++对象模型和this指针-空指针访问成员函数

// C++中空指针也是可以调用成员函数的，但是也要注意有没有用到空指针

// 如果用到this指针，需要加以判断保证代码的健壮性

#include<iostream>
using namespace std;

class Person
{
public:

    void showClassName()
    {
        cout << "this is Person class." << endl;

    }

    void showPersonAge()
    {
        // 这里打印不出来 m_Age 是因为传入的this指针是一个空指针(NULL)（个人理解：其实可以理解成你连女朋友都没有，怎么会有女朋友的年龄）

        // 怎么解决？如何避免这种情况？
        if (this == NULL) // 这行代码可以防止自己往函数里乱传一些空指针(可以提升代码的健壮性)
        {
            return;
        }

        {
            /* code */
        }
        

        cout << "m_Age = " << m_Age << endl;
    }

    int m_Age = 10;

};

void test01()
{
    Person *p = NULL;

    p->showClassName();
    p->showPersonAge();
}

int main()
{
    test01();

    return 0;
}