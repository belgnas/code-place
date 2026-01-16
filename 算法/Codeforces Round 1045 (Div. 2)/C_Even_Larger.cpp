// #include <bits/stdc++.h>
#include <iostream>  // cin, cout, cerr - 标准输入输出流
#include <cmath>     // sqrt, pow, sin, cos - 数学函数
#include <algorithm> // sort, min, max, reverse - 常用算法
#include <iomanip>   // setprecision, setw, fixed - 输入输出格式化
#include <string>    // string, getline - 字符串类
#include <vector>    // vector - 动态数组（向量）
#include <cstring>   // strcpy, strcmp, strlen - C风格字符串函数
#include <set>       // set, multiset - 集合
#include <tuple>     // tuple, make_tuple - 元组
#include <bitset>    // bitset - 位集
#include <utility>   // pair, make_pair - 对（序偶）
#include <queue>     // queue, priority_queue - 队列和优先队列
#include <deque>     // deque - 双端队列
#include <numeric>   // gcd, lcm, accumulate - 数值算法

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

// stoi/stoll: string数字 -> int/long long整数
// to_string: int/long long/float/double -> string字符串

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
// 迭代（循环）实现
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

// // 手动实现 gcd
// // 递归实现
// int gcd(int a, int b)
// {
//     if (b == 0) return a;
//     return gcd(b, a % b);
// }

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
        vector<int> arr(n, 0);
        for (int i = 0; i < n; i++)
            cin >> arr[i];

        int cost = 0;
        int correction = 0;

        // P 存储原始前缀和, M 存储修正后的前缀和的历史最大值
        vector<int> P(n + 1, 0);
        vector<int> M(n + 1, 0);

        // P[0] 和 M[0] 默认为 0

        for (int i = 1; i <= n; ++i)
        {
            int d_i;
            // 注意题目是1-based索引, 而我们的arr是0-based
            if (i % 2 == 1)
            { // 原始索引为奇数
                d_i = -arr[i - 1];
            }
            else
            { // 原始索引为偶数
                d_i = arr[i - 1];
            }

            P[i] = P[i - 1] + d_i;

            int corrected_P_i = P[i] + correction;

            // 条件 P'[i] >= max(P'[0], ..., P'[i-2])
            if (i >= 2)
            {
                int required_min = M[i - 2];
                if (corrected_P_i < required_min)
                {
                    int delta = required_min - corrected_P_i;
                    cost += delta;
                    correction += delta;
                    corrected_P_i = required_min;
                }
            }

            // 更新修正后的前缀和最大值
            M[i] = max(M[i - 1], corrected_P_i);
        }

        cout << cost << endl;
    }

    return 0;
}
