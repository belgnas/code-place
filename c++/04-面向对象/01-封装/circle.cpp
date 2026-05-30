#include "circle.h"


// 设计半径
void Circle::setR(int R)
{
    m_R = R;
}
// 获取半径
int Circle::getR()
{
    return m_R;
}

// 设置圆心
void Circle::setCenter(Point center)
{
    m_Center = center;
}
// 获取圆心
Point Circle::getCenter()
{
    return m_Center;
}