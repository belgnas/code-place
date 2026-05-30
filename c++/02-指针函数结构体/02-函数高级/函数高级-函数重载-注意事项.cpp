//函数高级-函数重载-注意事项

// 1.引用作为重载条件
// 2.函数重载碰到函数默认参数

#include<iostream>
using namespace std;

// 函数重载-注意事项
// 1.引用作为重载条件
void test(int &a) //int &a = 10  不合法
{
    cout << "test(int &a) 的调用 1, a = " << a /*这里调用a是为了防止由于未使用a而导致的报错*/<< endl;
}

//加const是防止被修改
void test(const int &a) //const int &a = 10  合法
{
    cout << "test(const int &a) 的调用 2, a = " << a /*调用a的理由同上*/<< endl;
}

// 2.函数重载碰到函数默认参数

void test2(int a, int b = 10)
{
    cout << "test2(int a, int b) 的调用 3, a = " << a /*调用a的理由同上*/<< ", b = " << b /*调用a的理由同上*/<< endl;
}

// void test2()
// {
//     cout << "test2(int a) 的调用 4, a = " << a /*调用a的理由同上*/<< endl;
// }


int main()
{
    int a = 10;
    test(a);// 1
    test(10);// 2

    test2(10, 20);
    test2(10);// 当函数重载碰到默认参数，容易出现问题，可能会引起一些歧义。


    return 0;
}