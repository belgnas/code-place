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

// 判断是否是回文数
bool huiwen(int num)
{
    string str_num = to_string(num);
    
    bool flat = true;
    int l = 0, r = str_num.size() - 1;
    while(l <= r)
    {
        if(str_num[l] != str_num[r])
        {
            flat = false;
            break;
        }
        l++, r--;
    }
    return flat;
}

int fanzhuan(int num)
{
    string str_num = to_string(num);

    int l = 0, r = str_num.size() - 1;
    while(l <= r)
    {
        swap(str_num[l], str_num[r]);
        l++, r--;
    }

    return stoll(str_num);
}

signed main()
{
    IOS;

    int t;
    cin >> t;
    while(t--)
    {
        int n, k;
        cin >> n >> k;
        // 判断是不是回文数，是的话直接返回该数字和0
        if(huiwen(n))
        {
            cout << n << " " << "0" << endl;
            continue;
        }

        bool possible = false;
        int act = 1;
        for(act = 1; act <= k; act++)
        {
            // 回文操作
            int n2 = n;
            // while(n2 % 10 == 0)
            // {
            //     n2 /= 10;
            // }
            n2 = fanzhuan(n2);

            n += n2;

            if(huiwen(n))
            {
                possible = true;
                break;
            }
        }

        if(possible)
        {
            cout << n << " " << act << endl;
        }
        else
        {
            cout << n << " " << "-1" << endl;
        }
    }

    return 0;
}