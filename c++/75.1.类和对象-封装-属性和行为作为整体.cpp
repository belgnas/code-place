//类和对象-封装-属性和行为作为整体

#include<iostream>
using namespace std;
//圆周率
const double PI = 3.14;

//设计一个圆，求圆的周长
//圆求周长公式：2 * PI * 半径

//class 代表设计一个类，类后面紧跟着的是类名称
class Circle
{
    //访问权限
    //公共权限
public:

    //属性
    //半径
    int m_r;

    //行为
    //获取圆的周长
    double calculate_zhouchang()
    {
        return 2 * PI * m_r;
    }

};

int main()
{
    //通过圆类 创建具体的圆（对象）
    Circle cl;
    //给圆对象 的属性进行赋值
    cl.m_r = 10;

    cout << "圆的周长为：" << cl.calculate_zhouchang() << endl;

    return 0;
}