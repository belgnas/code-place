// main.cpp — CMake 多文件项目示例
#include<iostream>
#include"utils.h"
using namespace std;

int main()
{
    cout << "========================================" << endl;
    cout << "|     CMake 多文件项目示例            |" << endl;
    cout << "========================================" << endl;

    cout << greet("CMake User") << endl;
    cout << "3 + 5 = " << add(3, 5) << endl;

    cout << "\n构建命令 (在此目录下执行):" << endl;
    cout << "  mkdir build && cd build" << endl;
    cout << "  cmake .." << endl;
    cout << "  cmake --build ." << endl;
    cout << "  .\\Debug\\cmake_demo.exe  (Windows/MSVC)" << endl;
    cout << "  ./cmake_demo             (Linux/GCC)" << endl;

    system("pause");
    return 0;
}
