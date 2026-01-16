// 类和对象-友元-类做友元

// 在程序中，有些私有属性，如果也想让类外的特殊的一些函数或者类进行访问，就需要用到 友元 的技术
// 友元的目的：让一个函数或一个类，访问另一个类中的私有成员
// 友元の关键词： friend

// 友元の3种实现
//      1. 全局变量做友元
//      2. 类做友元
//      3. 成员函数做友元

#include <iostream>
using namespace std;

class Building; // 对后来会写的 Building类 进行声明，防止写的时候报错

class good_Friend
{
public: 

    good_Friend();

    void visit(); // 参观函数，访问 Building 中的属性 

    Building * building;

};

class Building
{
    // 本课の核心
    friend class good_Friend; // 意思是：good_Friend 是本类（Building类）的好朋友，可以访问本类中的私有成员

public:
    Building();// 类外写成员函数 在类内写函数声明

public:

    string m_SittingRoom; // 客厅

private:

    string m_Bedroom; // 卧室

};

// 类外写成员函数
Building::Building() // “Building::” 是告诉编译器这是 Building类 下的函数
{
    m_SittingRoom = "客厅";
    m_Bedroom = "卧室";

}

good_Friend::good_Friend()
{
    // 创建一个建筑物对象
    building = new Building; // 在堆区创建了一个对象，并且让Building这个指针指向了这个对象

}

void good_Friend::visit() // “good_Friend::” 是告诉编译器这是 good_Friend类 下的函数
{
    cout << "visit函数 可以访问 good_Friend类里的 visit：" << building->m_SittingRoom << endl;

    cout << "visit函数 可以访问 good_Friend类里的 visit：" << building->m_Bedroom << endl;
}

void test01()
{
    good_Friend gf1;
    gf1.visit();
}

int main()
{
    test01();

    return 0;
}
