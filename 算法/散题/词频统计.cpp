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
#include <queue> // 队列
#include <deque> // 双端队列

using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define endl '\n'
typedef pair<int, int> PII;

const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
// &: 只有当两个相应的位都为 1 时,结果位才为 1,否则为 0
// |: 只要两个相应的位中有一个为 1,结果位就为 1,否则为 0
// ^: 如果两个相应的位不同(一个为 1，另一个为 0),则结果位为 1,如果相同则结果位为 0

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

const int N = 110;
int cnt1[N], cnt2[N];
bool st[N];
int n, m;

signed main()
{
    IOS;

    cin >> n >> m;
    while (n--)
    {
        int len;
        cin >> len;
        memset(st, 0, sizeof st);
        while (len--)
        {
            int x;
            cin >> x;
            cnt2[x]++;
            st[x] = 1;
        }
        for (int i = 1; i <= m; i++)
        {
            if (st[i])
                cnt1[i]++;
        }
    }
    for (int i = 1; i <= m; i++)
        cout << cnt1[i] << " " << cnt2[i] << endl;

    return 0;
}