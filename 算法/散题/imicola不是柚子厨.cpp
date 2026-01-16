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
const int MOD = 1e18 + 7;
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

// void solve()
// {

// }

signed main()
{
    IOS;

    // 概括一下这段代码
    // 1. 先预处理出10到10^18的所有数的位数
    // 2. 对于每个查询k，从低到高枚举位数j
    // 3. 计算当前位数j的范围[min_temp, max_temp]
    // 4. 检查k是否在当前位数j的范围内
    // 5. 如果在范围内，计算第k个数字在当前位数j中的具体位置
    //      5.1 计算第k个数字在当前位数j中的具体位置的第t个“j位数”）
    //      5.2 计算第k个数字在当前位数j中的具体位置的第pos位
    // 6. 如果不在范围内，继续枚举下一个位数j
    // 7. 输出第k个数字

    int n, q;
    cin >> n >> q;

    // 预生成10到10^18
    vector<int> p(19, 1);
    for (int i = 1; i <= 18; i++)
    {
        p[i] = p[i - 1] * 10;
    }

    while (q--)
    {
        int k;
        cin >> k; // 求第k个数字

        int sum = 0;

        for (int j = 1; j <= 18; j++)
        {
            // 范围
            int min_temp = p[j - 1];          // 位数最小值
            int max_temp = p[j] - 1;          // 位数最大值
            int l = (min_temp + (n - 1)) / n; // 左i
            int r = max_temp / n;             // 右i

            // cout << "min_temp: " << min_temp << endl;
            // cout << "max_temp: " << max_temp << endl;
            // cout << "l: " << l << endl; // 这里的l是第i位的最小值
            // cout << "r: " << r << endl; // 这里的r是第i位的最大值

            if (r < l)
                continue;

            int cnt = r - l + 1; // 当前这个j的数量
            int len = cnt * j;   // 当前这个j的。总位数

            // k有没有在当前位数j的范围内
            if (sum + len >= k)
            {
                int pianyi = k - sum - 1; // 偏移量 = 要求的第k个数字 - 之前所有位数的总位数 - 1
                int t = pianyi / j;       // 第t个“j位数” = 偏移量 / 当前位数j
                int pos = pianyi % j;     // 第pos位 = 偏移量 % 当前位数j
                int num = n * (l + t);    // 第t个“j位数”的第pos位 = 第t个“j位数” * n + 在第t个“j位数”中的位置

//                 cout << "第" << k << "个数字在第" << j << "位的第" << t << "个数的第" << pos << "位"<< endl;
//                 cout << "所在的“j位数”num为：" << num << endl;

                int ans = (num / fast_pow(10, j - pos - 1, MOD)) % 10; // 第t个“j位数”的第pos位 = 第t个“j位数” * n + 在第t个“j位数”中的位置
                cout << ans << endl;
                // 我想找到这个数字：也就是找到所处的num这个数中的所处的数位的数
                // 整除移位：用 num 除以一个 “10 的幂次”，把目标位移动到个位（高位的数字会被整除掉）；
                // 取余 10：对移位后的结果取余 10，只保留个位数字（即目标位）。

                break;
            }

            sum += len;
        }
    }

    return 0;
}