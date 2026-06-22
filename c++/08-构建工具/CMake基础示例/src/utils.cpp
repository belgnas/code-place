// utils.cpp — CMake 多文件示例的实现文件
#include"utils.h"
#include<iostream>

std::string greet(const std::string& name)
{
    return "Hello, " + name + "! (from utils.cpp)";
}

int add(int a, int b)
{
    return a + b;
}
