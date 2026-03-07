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

signed main()
{
    IOS;

    int n, k;
    cin >> n >> k;
    string s1, s2;
    cin >> s1 >> s2;
    s1 = " " + s1;
    s2 = " " + s2;
    vector<int> prep(n + 1, 0);
    for(int i = 1; i <= k; i++)
    {
        int l, r;
        cin >> l >> r;
        prep[l]++;
        prep[r + 1]--;
    }

// 测试
    // for(auto x : prep)
    // {
    //     cout << x << " ";
    // }
    // cout << endl;

    int num;
    num = 0;
    for(int i = 1; i <= n; i++)
    {
        num += prep[i];
        if(num % 2 == 0)
        {
            cout << s1[i];
        }
        else
        {
            cout << s2[i];
        }
    }
    cout << endl;

// 这一题只需要输出第一个字符串就可以了，无需输出第二个字符串
    // num = 0;
    // for(int i = 1; i <= n; i++)
    // {
    //     num += prep[i];
    //     if(num % 2 == 1)
    //     {
    //         cout << s1[i];
    //     }
    //     else
    //     {
    //         cout << s2[i];
    //     }
    // }
    // cout << endl;

    return 0;
}