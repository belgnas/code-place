// 类和对象-C++运算符重载-加号运算符重载

// 运算符重载 
// 概念：对已有的运算符重新进行定义，赋予其另一种功能，以适应不同的数据类型


// 重要！！
// 总结1：对于内置的数据类型的表达式的运算是不可以发生改变的
// 总结2：不要滥用运算符重载（会变得非常晦涩难懂）




// 加号运算符重载：
// 作用：实现2个自定义数据类型相加的运算


// 对于内置的数据类型，编译器知道如何进行计算
// 例如：
//  int a = 1;
//  int b = 2;
//  int c = a + b;

// 但是对于自定义的数据类型，编译器就不会运算了
// 例如：
//  class Person
//  {
//  public:
//  
//      int m_age;
//      int m_phone_numble;
//  }
//  
//  Person p1;
//  p1.m_age = 18;
//  p1.m_phone_numble = 12345;
//  
//  Person p2;
//  p2.m_age = 28;
//  p2.m_phone_numble = 11111;
//  
//  Person p3 = p1 + p2; // 这里我想要让数据类型为 Person 的2个对象加起来（按照m_age为两者之和，m_phone_numble保留前者，的规律进行运算）

// 解决方法一
// 通过自己写成员函数（在p1里写），实现2个对象相加属性后返回新的对象
//  Person Person_Add_Person(Person &p)
//  {
//      Perosn temp;
//      temp.m_age = this->m_age + p.m_age;
//      temp.m_phone_numble = this->m_phone_numble;
//      return temp;
//  }
// 如何调用：Person p3 = p1.Person_Add_Person(p2);

// 解决方法二
// 函数重载（使用编译器起的通用的名称：“operator+”） 
// 
// ①通过成员函数重载 + 号
//  Person operator+(Person &p)
//  {
//      Perosn temp;
//      temp.m_age = this->m_age + p.m_age;
//      temp.m_phone_numble = this->m_phone_numble;
//      return temp;
//  }
// 如何调用：
//  Person p3 = p1.operator+(p2); // 本质调用
//      或 简化成
//  Person p3 = p1 + p2;

// ②通过全局函数重载 + 号
//  Person operator+(Person &p1, Person &p2)
//  {
//      Person temp;
//      temp.m_age = p1.m_age + p2.m_age;
//      temp.m_phone_numble = p1.m_phone_numble;
//      return temp;
//  }
// 如何调用：
// Person p3 = operator+(p1, p2); // 本质调用
//      或 简化成
// Person p3 = p1 + p2;


#include<iostream>
using namespace std;

// 加号运算符重载
class Person
{
public:

    // 方法一：
    // 成员函数重载+号
    // Person operator+(Person &p)
    // {
    //     Person temp;
    //     temp.m_age = this->m_age + p.m_age;
    //     temp.m_phone_numble = this->m_phone_numble;
    //     return temp;
    // }
 
    int m_age;
    int m_phone_numble;
};

// 方法二：
// 全局函数重载+号
Person operator+(Person &p1, Person &p2)
{
    Person temp;
    temp.m_age = p1.m_age + p2.m_age;
    temp.m_phone_numble = p1.m_phone_numble;
    return temp;
}

// ps：运算符重载也可以发生函数重载
//  例子：
Person operator+(Person &p1, int numble) // 按照m_age为两者之和，m_phone_numble为前者，的规律进行运算
{
    Person temp;
    temp.m_age = p1.m_age + numble;
    temp.m_phone_numble = p1.m_phone_numble;
    return temp;
}

void test01()
{
    Person p1;
    p1.m_age = 18;
    p1.m_phone_numble = 12345;

    Person p2;
    p2.m_age = 28;
    p2.m_phone_numble = 11111;

    Person p3 = p1 + p2; // 这里我想要让数据类型为 Person 的2个对象加起来（按照m_age为两者之和，m_phone_numble保留前者，的规律进行运算）

    cout << "p3.m_age = " << p3.m_age << endl;
    cout << "p3.m_phone_numble = " << p3.m_phone_numble << endl;

    Person p4 = p1 + 100; // Person数据类型 + int数据类型

    cout << "p4.m_age = " << p4.m_age << endl;
    cout << "p4.m_phone_numble = " << p4.m_phone_numble << endl;

}


int main()
{
    test01();

    return 0;
}