// 类和对象-继承-菱形继承

// 菱形继承概念：
// 两个派生类继承同一个基类
// 又有某个类同时继承继承者的2个派生类
// 这种继承被称为菱形继承，或者钻石继承


// 图解（典型菱形继承案例）
//     动物
//   ↙   ↘
// 羊       驼
//   ↘   ↙
//     羊驼

// 菱形继承问题：
//  1.羊继承了动物的数据驼一样继承了动物的数据，当羊驼（草泥马）使用数据时，就会产生二义性。
//  2.羊驼（草泥马）继承自动物的数据继承了2份，其实我们应该清楚，这份数据我们只需要一份就可以。

#include<iostream>
using namespace std;

// 动物类
class Animal
{
public:

    int m_Age;
};

//利用虚继承 解决菱形继承的问题
// 在继承之前 加上关键字 virtual 变为虚继承
// 个人理解：可以理解为加了virtual后，让从羊和驼这2个类中传入羊驼的这2个重复的数据，变成一个类似static的一个数据
// Animal类称为 虚基类
// 羊类
class Sheep : virtual public Animal{};

// 驼类
class Tuo : virtual public Animal{};

// 羊驼类
class SheepTuo : public Sheep, public Tuo{};

void test01()
{
    SheepTuo sheeptuo;

    sheeptuo.Sheep::m_Age = 3;
    sheeptuo.Tuo::m_Age = 4;
    // 当菱形继承，两个父类拥有相同数据，需要加以作用域区分
    cout << "sheeptuo.Sheep::m_Age = " << sheeptuo.Sheep::m_Age << endl;
    cout << "sheeptuo.Tuo::m_Age = " << sheeptuo.Tuo::m_Age << endl;
    cout << "sheeptuo.m_Age = " << sheeptuo.m_Age << endl;

    // 这份数据我们知道 只要有一份就可以，菱形继承导致数据有2份，资源浪费
}

int main()
{
    test01();

    return 0;
}
