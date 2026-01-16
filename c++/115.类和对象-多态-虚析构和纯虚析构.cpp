// 类和对象-多态-虚析构和纯虚析构

// 多态使用时，如果子类中有属性开辟到堆区，那么父类指针在释放时无法调用到子类的虚构代码

// 解决方法：将父类中的析构函数改为 虚析构 或 纯虚析构

// 虚析构和纯虚析构的共性：
//  1.可以解决父类指针释放子类对象；
//  2.都需要有具体的函数实现

// 虚析构和纯虚析构的区别：
//  如果是纯虚析构，该类属于抽象类，无法实例化对象

// 虚析构语法：
//      virtual ~类名(){}

// 纯虚析构语法：
//      virtual ~类名() = 0;
//      类名::类名(){}


#include<iostream>
#include<string>
using namespace std;

class Animal
{
public:

    Animal()
    {
        cout << "Animal构造函数调用" << endl;
    } 

    // 纯虚函数
    virtual void speak() = 0;

    // 虚析构
    // 利用虚析构可以解决 父类指针释放子类对象是不干净的问题
    // virtual ~ Animal()
    // {
    //     cout << "Animal虚析构函数调用" << endl;
    // } 

    // 纯虚析构
    // 有了纯虚析构 之后，这个类也属于抽象类，无法实例化对象
    // 纯虚析构 需要声明也需要实现
    // 纯虚析构 声明
    virtual ~ Animal() = 0;

};
// 纯虚析构实现
Animal::~ Animal()
{
    cout << "Animal纯虚析构函数调用" << endl;
}

class Cat : public Animal
{
public:

    Cat(string name)
    {
        cout << "Cat的构造函数调用" << endl;
        m_Name = new string(name);
    }

    virtual void speak()
    {
        cout << *m_Name << "小猫在说话" << endl;
    }

    ~Cat()
    {
        if(m_Name != NULL)
        {
            cout << "Cat的析构函数调用" << endl;
            delete m_Name;
            m_Name = NULL;
        }
    }

    //开始添加一点内容
    // 比如说加上小猫的名字

    string *m_Name;
};

void test01()
{
    Animal * animal = new Cat("猫又");
    animal->speak();
    // 父类的指针在析构的时候不会调用子类中的析构函数，导致子类如果有堆区属性，会出现内存泄露
    delete animal;
}

int main()
{
    test01();

    return 0;
}

// 总结：
//  1.虚析构或纯虚析构就是用来解决通过父类指针释放子类对象
//  2.如果子类中，没有堆区数据，可以不写为虚析构或纯虚析构
//  3.拥有纯虚析构函数的类，也属于抽象类