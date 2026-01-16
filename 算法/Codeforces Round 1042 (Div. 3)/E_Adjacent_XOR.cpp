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

signed main()
{
    IOS;
    
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> arr(n), brr(n);
        for (int i = 0; i < n; i++)
            cin >> arr[i];
        for (int i = 0; i < n; i++)
            cin >> brr[i];

        // 首先判断最后一位是否相等，不相等直接不可能
        if (arr.back() != brr.back())
        {
            cout << "NO" << endl;
            continue;
        }

        bool possible = true;
        // 从后往前遍历（除了最后一位，因为最后一位已经判断过）
        for (int i = n - 2; i >= 0; i--)
        {
            if (arr[i] == brr[i])
                continue;
            // 判断是否能通过操作让 arr[i] 变成 brr[i]
            // 操作只能是 arr[i] = arr[i] ^ arr[i+1]，同时要考虑 arr[i+1] 最终要等于 brr[i+1]
            bool op1 = (arr[i] ^ arr[i + 1]) == brr[i];
            bool op2 = (arr[i] ^ brr[i + 1]) == brr[i];
            if (!op1 && !op2)
            {
                possible = false;
                break;
            }
            // 这里不需要实际修改 arr[i]，因为我们是在判断是否“可能”，而不是真的去修改数组
            // 只要存在一种可能的操作能让 arr[i] 最终等于 brr[i] 即可
        }

        cout << (possible ? "YES" : "NO") << endl;
    }
    return 0;
}