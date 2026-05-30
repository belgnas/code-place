#pragma once
#include<iostream>
using namespace std;

// 点类
class Point
{
public:
    // 设置x
    void setX(int X);
    // 获取X
    int getX();

    // 设置Y
    void setY(int Y);
    // 获取Y
    int getY();

private:
    int m_X; // x坐标
    int m_Y; // y坐标

};