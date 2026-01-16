// #include <bits/stdc++.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <string>
#include <vector>
#include <cstring>
#include <set>
#include <tuple>
#include <bitset>
#include <utility>
#include <queue>   // 队列
#include <deque>   // 双端队列
#include <numeric> // 用于 gcd 函数

using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define endl '\n'
typedef pair<int, int> PII;

const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
// &（按位与）: 只有当两个相应的位都为 1 时,结果位才为 1,否则为 0
// |（按位或）: 只要两个相应的位中有一个为 1,结果位就为 1,否则为 0
// ^（按位异或）: 如果两个相应的位不同(一个为 1，另一个为 0),则结果位为 1,如果相同则结果位为 0

// 快速幂
int fast_pow(int a, int b, int mod) // a ^ b % mod
{
    int res = 1 % mod;
    while (b)
    {
        if (b & 1)
        {
            res = res * 1ll * a % mod;
        }
        a = a * 1ll * a % mod;
        b >>= 1;
    }
    return res;
}

// 手动实现 gcd
int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 手动实现 lcm
int lcm(int a, int b)
{
    if (a == 0 || b == 0)
        return 0;             // 避免除以零
    return a / gcd(a, b) * b; // 先除后乘防止溢出
}

// pref 前缀（prefix）
// suff 后缀（suffix）

signed main()
{
    IOS;

    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> pref(n, 0);
        vector<int> suff(n, 0);
        for (int i = 0; i < n; i++)
            cin >> pref[i];
        for (int i = 0; i < n; i++)
            cin >> suff[i];

        bool valid = true;

        // 检查 1：pref 非递增，suff 非递减
        for (int i = 0; i < n - 1; i++)
        {
            if (pref[i] < pref[i + 1] || suff[i] > suff[i + 1])
            {
                valid = false;
                break;
            }
        }
        if (!valid)
        {
            cout << "NO" << endl;
            continue;
        }

        // 检查 2：首尾元素兼容性
        // ans[0] = pref[0] 必须是 suff[0] 的倍数，且满足与 suff[1] 的 GCD 约束（若 n>1）
        if (pref[0] % suff[0] != 0)
            valid = false;
        if (n > 1 && gcd(suff[1], pref[0]) != suff[0])
            valid = false;

        // ans[n-1] = suff[n-1] 必须是 pref[n-1] 的倍数，且满足与 pref[n-2] 的 GCD 约束（若 n>1）
        if (suff.back() % pref.back() != 0)
            valid = false;
        if (n > 1 && gcd(pref[n - 2], suff.back()) != pref[n - 1])
            valid = false;

        // 检查 3：中间元素的前缀和后缀递推约束
        for (int i = 1; i < n - 1; i++)
        {
            // pref[i] 必须是 pref[i-1] 的约数
            if (pref[i - 1] % pref[i] != 0)
            {
                valid = false;
                break;
            }
            // suff[i] 必须是 suff[i+1] 的约数
            if (suff[i + 1] % suff[i] != 0)
            {
                valid = false;
                break;
            }
            // ans[i] 取 LCM(pref[i], suff[i])，检查是否满足前后 GCD 约束
            int lcm_ij = lcm(pref[i], suff[i]);
            if (gcd(pref[i - 1], lcm_ij) != pref[i])
            {
                valid = false;
                break;
            }
            if (gcd(suff[i + 1], lcm_ij) != suff[i])
            {
                valid = false;
                break;
            }
        }

        cout << (valid ? "YES" : "NO") << endl;
    }

    return 0;
}