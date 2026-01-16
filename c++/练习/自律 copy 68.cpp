#include <iostream>
#include <string>
using namespace std;

const long long MOD = 1e9 + 7;

// 快速幂函数，计算 (base^exponent) % MOD
long long quick_pow(long long base, long long exponent)
{
    long long result = 1;
    while (exponent > 0)
    {
        if (exponent & 1)
        {
            result = (result * base) % MOD;
        }
        base = (base * base) % MOD;
        exponent >>= 1;
    }
    return result;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--)
    {
        long long n;
        string s;
        cin >> n >> s;

        long long m = n * s.length();
        // 计算 (2^m - 1) % MOD
        long long ans = (quick_pow(2, m) - 1 + MOD) % MOD;
        cout << ans << endl;
    }

    return 0;
}