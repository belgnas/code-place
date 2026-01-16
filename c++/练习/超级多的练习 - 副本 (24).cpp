#include <iostream>
using namespace std;

typedef unsigned long long ull;

// 龟速乘：计算 (a * b) % mod，避免乘法溢出
ull slow_mul(ull a, ull b, ull mod)
{
    ull res = 0;
    a %= mod;
    while (b > 0)
    {
        if (b & 1)
            res = (res + a) % mod; // 当前位为1时累加
        a = (a * 2) % mod;         // a翻倍并取模
        b >>= 1;                   // 右移一位
    }
    return res;
}

// 快速幂：使用龟速乘替代普通乘法
ull fast_pow(ull a, ull b, ull mod)
{
    ull res = 1;
    a %= mod;
    while (b > 0)
    {
        if (b & 1)
            res = slow_mul(res, a, mod); // 使用龟速乘
        a = slow_mul(a, a, mod);         // 使用龟速乘
        b >>= 1;
    }
    return res;
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        ull a, b, mod;
        cin >> a >> b >> mod;
        cout << fast_pow(a, b, mod) << endl;
    }
    return 0;
}