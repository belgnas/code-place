// 类和对象-封装-设计案例2-点和圆的关系

// 设计一个圆形类，和一个点类，计算点和圆的位置关系

#include<iostream>
using namespace std;

// 点类
class Point
{
public:
    // 设置x
    void setX(int X)
    {
        m_X = X;
    }
    // 获取X
    int getX()
    {
        return m_X;
    }

    // 设置Y
    void setY(int Y)
    {
        m_Y = Y;
    }
    // 获取Y
    int getY()
    {
        return m_Y;
    }

private:
    int m_X; // x坐标
    int m_Y; // y坐标

};

class Circle
{
public:
    // 设计半径
    void setR(int R)
    {
        m_R = R;
    }
    // 获取半径
    int getR()
    {
        return m_R;
    }

    // 设置圆心
    void setCenter(Point center)
    {
        m_Center = center;
    }
    // 获取圆心
    Point getCenter()
    {
        return m_Center;
    }


private:
    int m_R; // 半径
    // 在类中可以让另一个类 作为本类中的成员
    Point m_Center; // 圆心（前面自定义圆心类）
};

// 判断点和圆的关系
void isInCireter(Circle &c, Point &p)
{
    // 计算两点之间距离 平方
    int distance = 
        (c.getCenter().getX() - p.getX()) * (c.getCenter().getX() - p.getX()) + 
        (c.getCenter().getY() - p.getY()) * (c.getCenter().getY() - p.getY());

    // 计算半径的平方
    int rDistance = c.getR() * c.getR();

    // 判断关系
    if(distance == rDistance)
    {
        cout << "点在圆上"  << endl;
    }
    else if(distance > rDistance)
    {
        cout << "点在圆外" << endl;
    }
    else
    {
        cout << "点在圆内" << endl;
    }
}

int main()
{
    // 创建圆
    Circle c;
    c.setR(10);
    Point center;
    center.setX (0);
    center.setY(0);
    c.setCenter(center);

    // 创建点()
    Point p; //（输入）
    int x, y;
    cin >> x;
    cin >> y;
    p.setX(x);
    p.setY(y);

    // 判断关系
    isInCireter(c, p);
    
    return 0;
}