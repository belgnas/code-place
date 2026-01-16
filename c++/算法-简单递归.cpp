#include<iostream>
using namespace std;

// 递归函数 digui，接受一个整数参数 a，用于计算特定的数值序列
int digui(int a)
{
    int numble = 0;  // 定义一个整数变量 numble，并初始化为 0
    if (a == 1)      // 如果输入的参数 a 等于 1
    {
        numble = 1;  // 将 numble 赋值为 1
    }
    else
    {
        numble = digui(a - 1) + 3;  // 否则，递归调用 digui 函数，参数为 a - 1，并将结果加上 3 赋值给 numble
    }
    return numble;  // 返回 numble 的值
}

int main()
{
    int a;          // 定义一个整数变量 a
    cin >> a;       // 从标准输入读取一个整数赋值给 a
    cout << digui(a) << endl;  // 调用 digui 函数，传入参数 a，计算结果并输出
    system("pause");  // 在某些操作系统上暂停程序执行，以便查看输出结果（依赖特定操作系统，不是可移植的方法）
    return 0;
}