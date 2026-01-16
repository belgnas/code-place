// 类和对象-多态-案例1-计算器类

// 案例描述：分别用普通写法和多态技术，实现两个操作数进行运算的计算器类

// 多态的优点
//  1.代码组织清晰
//  2.可读性强
//  3.利于前期和后期的扩展和维护

// 强调：C++开发提倡使用多态设计程序架构，因为多态的优点很多

#include<iostream>
#include<string>
using namespace std;

// 利用 普通写法 实现计算器

class Calculator
{
public:

    int getResult(string oper)
    {
        if(oper == "+")
        {
            return m_Num1 + m_Num2;
        }
        else if(oper == "-")
        {
            return m_Num1 - m_Num2;
        }
        else if(oper == "*")
        {
            return m_Num1 * m_Num2;
        }
        // 如果想扩展新的功能，需要修改源码（这不是我们想要的）
        // 在真实的开发中，提倡 开闭原则
        // 开闭原则：对扩展进行开发，对修改进行关闭
    }

    int m_Num1; // 操作数1
    int m_Num2; // 操作数2
};

void test01()
{
    // 创建计算机对象
    Calculator c;
    c.m_Num1 = 10;
    c.m_Num2 = 10;
    cout << c.m_Num1 << " + " << c.m_Num2 << " = " << c.getResult("+") << endl;
    cout << c.m_Num1 << " - " << c.m_Num2 << " = " << c.getResult("-") << endl;
    cout << c.m_Num1 << " * " << c.m_Num2 << " = " << c.getResult("*") << endl;
}

// 利用 多态技术 实现计算器
// 好处：
//  1.组织结构清晰（模块化）
//  2.可读性强
//  3.对于前期和后期的可维护性强（开闭原则）

// 实现计算器抽象类
class AbstractCaculator
{
public:
    virtual int getResult()
    {
        return 0;
    }

    int m_Num1;
    int m_Num2;
};

// 加法计算器类
class AddCalculator : public AbstractCaculator
{
public:
    virtual int getResult()
    {
        return m_Num1 + m_Num2;
    }
};

// 减法计算器类
class SubCalculator : public AbstractCaculator
{
public:
    virtual int getResult()
    {
        return m_Num1 - m_Num2;
    }
};

// 乘法计算器类
class MulCalculator : public AbstractCaculator
{
public:
    virtual int getResult()
    {
        return m_Num1 * m_Num2;
    }
};

void test02()
{
    // 多态使用条件
    // 父类的指针或引用 指向子类对象

    // 加法运算
    AbstractCaculator * abc = new AddCalculator;
    abc->m_Num1 = 10;
    abc->m_Num2 = 10;

    cout << abc->m_Num1 << " + " << abc->m_Num2 << " = " << abc->getResult() << endl;

    // 用完后记得销毁
    delete abc;


    // 减法运算
    abc = new SubCalculator; // 前面销毁abc只是销毁了abc在堆区的数据，没有改变 abc 的类型，即是父类的指针
    abc->m_Num1 = 10;
    abc->m_Num2 = 10;

    cout << abc->m_Num1 << " - " << abc->m_Num2 << " = " << abc->getResult() << endl;

    // 用完后记得销毁
    delete abc;


    // 乘法运算
    abc = new MulCalculator; // 前面销毁abc只是销毁了abc在堆区的数据，没有改变 abc 的类型，即是父类的指针
    abc->m_Num1 = 10;
    abc->m_Num2 = 10;

    cout << abc->m_Num1 << " * " << abc->m_Num2 << " = " << abc->getResult() << endl;

    // 用完后记得销毁
    delete abc;
}

int main()
{
    // 普通写法
    test01();

    // 多态技术
    test02();

    return 0;
}