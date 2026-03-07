// 类和对象-友元-成员函数做友元

// 在程序中，有些私有属性，如果也想让类外的特殊的一些函数或者类进行访问，就需要用到 友元 的技术
// 友元的目的：让一个函数或一个类，访问另一个类中的私有成员
// 友元の关键词： friend

// 友元の3种实现
//      1. 全局变量做友元
//      2. 类做友元
//      3. 成员函数做友元

#include<iostream>
#include<string>
using namespace std;

class Building;

class good_Friend
{
public:

    good_Friend();

    void visit1(); // 让 vivit1函数  可以访问  Building类 中的私有成员
    void visit2(); // 让 vivit2函数 不可以访问 Building类 中的私有成员

    Building * building;
};

class Building
{
    friend void good_Friend::visit1(); // visit1函数 是 Building类 的友元

public:
    Building();

public:

    string m_SittingRoom; // 客厅

private:

    string m_BedRoom; // 卧室

};

// 类外实现成员函数
Building::Building()
{
    m_SittingRoom = "客厅";
    m_BedRoom = "卧室";
}

good_Friend::good_Friend()
{
    building = new Building;

}

void good_Friend::visit1()
{
    cout << "vivit1函数 正在访问：" << building->m_SittingRoom << endl;

    cout << "vivit1函数 正在访问：" << building->m_BedRoom << endl;
}
void good_Friend::visit2()
{
    cout << "vivit2函数 正在访问：" << building->m_SittingRoom << endl;

    // cout << "vivit1函数 正在访问：" << building->m_BedRoom << endl;
}

void test01()
{
    good_Friend gf1;
    gf1.visit1();
    gf1.visit2();
}

int main()
{
    test01();

    return 0;
}