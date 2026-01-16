// 快速乘
// AcWing - 90. 64位整数乘法

// 题目描述
// 求 a 乘 b 对 p 取模的值。

// 输入格式
// 第一行输入整数a，第二行输入整数b，第三行输入整数p。

// 输出格式
// 输出一个整数，表示 a*b%p 的值。

// 数据范围
// 1 ≤ a, b, p ≤ 10^18

// 输入样例：
// 3
// 4
// 5

// 输出样例：
// 2

#include<iostream>
using namespace std;

long long fast_mul(long long a, long long b, long long mod)
{
    long long res = 0;
    while(b)
    {
        if(b & 1) res = (res + a) % mod;
        a = a * 2 % mod;
        b >>= 1;
    }
    return res;
}

int main()
{
    long long a, b, p;
    cin >> a >> b >> p;
    long long ans = fast_mul(a, b, p);
    cout << ans << endl;
    
    
    return 0;
}