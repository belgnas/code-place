// 类和对象-友元-全局函数做友元

// 在程序中，有些私有属性，如果也想让类外的特殊的一些函数或者类进行访问，就需要用到 友元 的技术
// 友元的目的：让一个函数或一个类，访问另一个类中的私有成员
// 友元の关键词： friend

// 友元の3种实现
//      1. 全局变量做友元
//      2. 类做友元
//      3. 成员函数做友元

#include <iostream>
#include <string>
using namespace std;

// 建筑物类
class Building
{
    // good_Friend全局函数 是 Building类 的好朋友，可以访问 Building类 中的私有成员
    friend void good_Friend(Building &building);

public:
    Building()
    {
        m_SittingRoom = "客厅";
        m_BedRoom = "卧室";
    }

public:
    string m_SittingRoom; // 客厅

private:
    string m_BedRoom; // 卧室

};

// 全局函数
void good_Friend(Building &building) //想要让全局函数可以访问类中的私有成员，只需将 全局函数的声明前面加个friend关键词 写进类中就可以了；
{
    cout << "good_Friend全局函数 可以访问 Building类 中的：" << building.m_SittingRoom << endl;

    cout << "good_Friend全局函数 可以访问 Building类 中的：" << building.m_BedRoom << endl;
}

void test01()
{
    Building building;
    good_Friend(building);
}

int main()
{
    test01();

    return 0;
}