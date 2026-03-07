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

    // 输入三个参数：数组长度n，模数m，子数组长度l
    int n, m, l;
    cin >> n >> m >> l;

    // 存储原始数组A
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    // 初始化DP数组：dp[j]表示当前状态下，（增量）模m余数为j时的最小操作次数
    // 初始时设为极大值INF，仅dp[0] = 0（初始状态）
    vector<int> dp(m, INF);
    dp[0] = 0; // 初始状态：没有任何操作时，余数状态为0的成本是0

    // 按"分层"处理数组（层号i对应间隔l的元素：i, i+l, i+2l...）
    for (int i = 0; i < l; i++)
    {
        // next数组存储处理当前层后的新状态
        vector<int> next(m, INF);

        // 枚举当前层所有可能的"目标调整值"j（j的含义：该层元素调整后对模m的贡献）
        for (int j = 0; j < m; j++)
        {
            // 计算将当前层所有元素调整到满足"j"所需的操作成本
            int cost = 0;
            // 遍历当前层的所有元素（位置k = i, i+l, i+2l...）
            for (int k = i; k < n; k += l)
            {
                if (a[k] <= j)
                {
                    // 直接增加到j，成本是j - a[k]
                    cost += j - a[k];
                }
                else
                {
                    // 需要绕一圈（模m特性），等价于增加到j + m，成本是(j + m) - a[k]
                    cost += j - a[k] + m;
                }
            }

            // 状态转移：结合之前的状态dp[k]，更新新状态next[new_mod]
            for (int k = 0; k < m; k++)
            {
                // 新的余数状态 = (原状态k + 当前层贡献j) 模m
                int new_mod = (k + j) % m;
                // 取"之前状态成本 + 当前层成本"的最小值
                next[new_mod] = min(next[new_mod], dp[k] + cost);
            }
        }

        // 更新dp为当前层处理后的状态，进入下一层处理
        dp = next;
    }

    // 最终要求余数状态回到0（所有子数组和模m为0），输出最小操作次数
    cout << dp[0] << "\n";

    return 0;
}