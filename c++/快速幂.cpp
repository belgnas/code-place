// 快速幂
// // AcWing - 89. a^b

// 题目描述：
// 求 a 的 b 次方对 p 取模的值。

// 输入格式
// 三个整数 a,b,p,在同一行用空格隔开。

// 输出格式
// 输出一个整数，表示a^b mod p的值。

// 数据范围
// 0 ≤ a,b ≤ 10^9
// 1 ≤ p ≤ 10^9

// 输入样例：
// 3 2 7
// 输出样例：
// 2

#include<iostream>

using namespace std;

int fast_pow(int a, int b, int mod)
{
    int res = 1 % mod;
    while(b)
    {
        if(b & 1)
        {
            res = res * 1ll * a % mod;
        }
        a = a * 1ll * 2 % mod;
        b >>= 1;
    }
    return res;
}

int main()
{
    int a, b, p;
    cin >> a >> b >> p;
    int ans = fast_pow(a, b, p);
    cout << ans << endl;
    
    
    return 0;
}