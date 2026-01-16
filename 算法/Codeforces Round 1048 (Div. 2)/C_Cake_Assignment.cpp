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
        int k, x;
        cin >> k >> x;

        int ans = 0;
        int Chocola = x, Vanilla = (1LL << (k + 1)) - x; // 巧克力，香子兰
        // cout << Chocola << " " << Vanilla << endl;
        
        vector<int> action;
        while(Chocola != Vanilla)
        {
            if(Chocola < Vanilla) 
            {
                Vanilla -= Chocola;
                Chocola *= 2;
                ans++;
                action.push_back(1);
                // cout << "Chocola: " << Chocola << endl;
                // cout << "Vanilla: " << Vanilla << endl;
            }
            else
            {
                Chocola -= Vanilla;
                Vanilla *= 2;
                ans++;
                action.push_back(2);
                // cout << "Vanilla: " << Vanilla << endl;
                // cout << "Chocola: " << Chocola << endl;
            }
        }

        cout << ans << endl;
        for(int i = ans - 1; i >= 0; i--)
        {
            cout << action[i] << " ";
        }
        cout << endl;

    }

    return 0;
}
