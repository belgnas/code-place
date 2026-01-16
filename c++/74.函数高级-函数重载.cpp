//函数高级-函数重载（基本语法）

//作用：函数名可以相同，提高复用性

//函数重载满足条件：
// 1.同一个作用域下
// 2.函数名称相同
// 3.函数参数 类型不同 或 个数不同 或 顺序不同

//注意：函数返回值不可以作为函数重载的条件

#include<iostream>
using namespace std;

// 函数高级-函数重载
// 作用：函数名可以相同，提高复用性

// 条件：
// 1.同一个作用域下
// 2.函数名称相同
// 3.函数参数 类型不同 或 个数不同 或 顺序不同

void test()
{
    cout << "test的调用 1" << endl;
}

void test(int a)//个数不同
{
    cout << "test(int a) 的调用 2" << endl;
}

void test(double a)//类型不同
{
    cout << "test(double a) 的调用 3" << endl;
}

void test(int a, double b)//顺序不同
{
    cout << "test(int a, double b) 的调用 4" << endl;
}

void test(double a, int b)//顺序不同
{
    cout << "test(double a, int b) 的调用 5" << endl;
}

//注意：函数返回值不可以作为函数重载的条件
// 个人理解：就是说仅根据函数的返回值无法确定应该调用哪个具体的函数版本。
// 例子：如果下边的代码取消注释，编译器无法判断应该调用 函数 5 还是 函数 6 
/*int test(double a, int b)//顺序不同
{
    cout << "test(double a, int b) 的调用 6" << endl;
}*/

int main()
{
    test();
    test(10);
    test(1.12);
    test(10, 1.12);
    test(1.12, 10);

    return 0;
}