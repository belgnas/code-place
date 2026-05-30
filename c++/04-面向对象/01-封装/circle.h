#pragma once
#include<iostream>
using namespace std;

#include "point.h"

class Circle
{
public:
    // 设计半径
    void setR(int R);
    // 获取半径
    int getR();

    // 设置圆心
    void setCenter(Point center);
    // 获取圆心
    Point getCenter();


private:
    int m_R; // 半径
    // 在类中可以让另一个类 作为本类中的成员
    Point m_Center; // 圆心（前面自定义圆心类）
};