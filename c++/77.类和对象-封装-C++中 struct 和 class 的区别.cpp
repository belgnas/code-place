// 类和对象-封装-C++中 struct 和 class 的 区别

//在C++中struct和class唯一的区别就在于 默认的访问权限不同

// 区别：
// struct 默认权限为公共
// class 默认权限为私有

#include<iostream>
#include<cstring>
using namespace std;

class C1
{
    int m_A; //默认权限是 私有 

};

struct C2
{
    int m_A; //默认权限是 公共 
};

int main()
{

    C1 c1;
    // c1.m_A = 100; // class 默认权限为 私有

    C2 c2;
    c2.m_A = 100; // struct 默认权限是 公共



    return 0;
}