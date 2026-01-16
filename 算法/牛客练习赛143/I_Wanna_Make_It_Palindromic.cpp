// #include <bits/stdc++.h>
#include <iostream> // cin, cout, cerr - 标准输入输出流
#include <cmath>    // sqrt, pow, sin, cos - 数学函数
#include <algorithm>// sort, min, max, reverse - 常用算法
#include <iomanip>  // setprecision, setw, fixed - 输入输出格式化
#include <string>   // string, getline - 字符串类
#include <vector>   // vector - 动态数组（向量）
#include <cstring>  // strcpy, strcmp, strlen - C风格字符串函数
#include <set>      // set, multiset - 集合
#include <tuple>    // tuple, make_tuple - 元组
#include <bitset>   // bitset - 位集
#include <utility>  // pair, make_pair - 对（序偶）
#include <queue>    // queue, priority_queue - 队列和优先队列
#include <deque>    // deque - 双端队列
#include <numeric>  // gcd, lcm, accumulate - 数值算法

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
    while(t--)
    {
        int n;
        cin >> n;
        vector<int> arr(n, 0);
        for(int i = 0; i < n; i++)
        {
            cin >> arr[i];
        }

        // ---------------------- 新增核心逻辑开始 ----------------------
        vector<pair<int, int>> bad_pairs; // 存储不相等的对称对（坏对）
        int m = 0; // 坏对的总数量
        // 遍历所有对称对（i < j，跳过中间元素）
        for(int i = 0, j = n - 1; i < j; i++, j--)
        {
            if(arr[i] != arr[j])
            {
                bad_pairs.emplace_back(arr[i], arr[j]);
                m++;
            }
        }
        // 若没有坏对，直接输出0（已为回文）
        if(m == 0)
        {
            cout << 0 << endl;
            continue;
        }

        // 1. 统计每个值在坏对中出现的次数（cnt[v]：包含v的坏对数量）
        vector<int> cnt(401, 0); // 取值范围-200~200，偏移200后为0~400
        for(auto &[x, y] : bad_pairs)
        {
            cnt[x + 200]++; // 偏移量200，将负数转为非负索引
            cnt[y + 200]++;
        }

        // 2. 统计每个（x<=y）的坏对出现频率（避免重复计算）
        vector<vector<int>> freq(401, vector<int>(401, 0));
        for(auto &[x, y] : bad_pairs)
        {
            if(x > y) swap(x, y); // 统一存储为x<=y，确保一对只算一次
            int idx1 = x + 200;
            int idx2 = y + 200;
            freq[idx1][idx2]++;
        }

        // 3. 枚举所有可能的p1和p2，找最大覆盖的坏对数量S_max
        int S_max = 0;
        for(int v1 = -200; v1 <= 200; v1++) // p1的所有可能值
        {
            int idx1 = v1 + 200;
            for(int v2 = -200; v2 <= 200; v2++) // p2的所有可能值
            {
                int idx2 = v2 + 200;
                int current_S;

                if(v1 == v2)
                {
                    // 若p1=p2，覆盖的坏对数量就是包含v1的坏对数量
                    current_S = cnt[idx1];
                }
                else
                {
                    // 容斥原理：覆盖数 = 含v1的数量 + 含v2的数量 - 同时含v1和v2的数量
                    int x = min(v1, v2);
                    int y = max(v1, v2);
                    int x_idx = x + 200;
                    int y_idx = y + 200;
                    int common = freq[x_idx][y_idx]; // 同时含v1和v2的坏对数量
                    current_S = cnt[idx1] + cnt[idx2] - common;
                }

                S_max = max(S_max, current_S); // 更新最大覆盖数
            }
        }

        // 4. 最小金币数 = 2*m - S_max（推导见思路）
        int min_cost = 2 * m - S_max;
        cout << min_cost << endl;
        // ---------------------- 新增核心逻辑结束 ----------------------
    }

    return 0;
}