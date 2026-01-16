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

int pay(int x)
{
    if(x == 0) return 3;
    int money = (fast_pow(3, x + 1, INF) + (x * fast_pow(3, x - 1, INF)));
    // cout << "money = " << money << endl;
    return money;
}

signed main()
{
    IOS;

    // 1个西瓜  3元
    // 3个西瓜  10元
    // 9个西瓜  33元
    // 27个西瓜 108元

    // 1 1
    // 2 2
    // 3 1
    // 4 2
    // 5 3
    // 6 2
    // 7 3
    // 8 4
    // 9 1

    int t;
    cin >> t;
    while(t--)
    {
        int n, k;
        cin >> n >> k;
        // 用不超过k次交易购买n个西瓜，要求花费的钱最少
        
        // 先计算买n个西瓜最多需要多少钱（最少需要多少操作次数）
        // 如果发现 k 小于最少操作次数，说明无法实现，直接返回-1。
        vector<int> arr;
        int n_copy = n;
        while(n_copy != 0)
        {
            int temp = n_copy % 3;
            arr.push_back(temp);
            n_copy /= 3;
        }

        // 找到最多花费金额和最少操作次数
        int money = 0;
        int action = 0;
        for(int i = 0; i < arr.size(); i++)
        {
            money += (arr[i] * pay(i));
            action += arr[i];
        }

        if(action > k)
        {
            cout << "-1" << endl;
            continue;
        }

        // // 然后开始节省金额（浪费次数），每往下添加一个量级，操作次数 -1+3，价格减少 
        // // 直到找到刚好k次操作次数
        // // 当然，如果发现操作次数直接超过了而不是直接等于k，那就返回-1
        // int idx = arr.size() - 1;
        // int memory = money;
        // while(action < k)
        // {
        //     if (idx <= 0) break; // 防止越界（必须保证 idx >= 1 才能调整到上一层）

        //     // 当前操作的层级的操作次数 -1
        //     // 上一层级的操作次数 +3
        //     arr[idx] --;
        //     arr[idx - 1] += 3;

        //     // 总操作次数 +2
        //     // 总花费 减少
        //     action += 2;
        //     memory = money;
        //     money = money - pay(idx) + 3 * pay(idx - 1);

        //     // 如果当前层级无可操作
        //     // 下一次操作的层级 -1
        //     if(arr[idx] == 0)
        //     {
        //         idx--;
        //     }
        // }

        // 然后开始节省金额（浪费次数），每往下添加一个量级，操作次数 -1+3，价格减少 
        // 直到找到刚好k次操作次数
        // 当然，如果发现操作次数直接超过了而不是直接等于k，那就返回-1
        int idx = arr.size() - 1;
        int memory = money;
        while(action < k)
        {
            if (idx <= 0) break; // 防止越界（必须保证 idx >= 1 才能调整到上一层）

            // 判断当前层级需要多少次操作
            int remaining = (k - action) / 2; // 还需要多少次拆分（每次拆分+2次操作）
            int can_split = min(arr[idx], remaining); // 本次最多可拆分的次数（不超过当前层级数量和剩余需求）
            
            if (can_split == 0) {
                idx--;
                continue;
            }

            // 批量处理can_split次拆分
            arr[idx] -= can_split;
            arr[idx - 1] += can_split * 3;
            action += can_split * 2; // 每次拆分增加2次操作
            money = money - can_split * pay(idx) + can_split * 3 * pay(idx - 1);
            memory = money; // 更新记忆值

            // 如果当前层级无可操作
            // 下一次操作的层级 -1
            if(arr[idx] == 0)
            {
                idx--;
            }
        }

        if(action > k)
        {
            cout << memory << endl;
        }
        else
        {
            cout << money << endl;
        }
    }

    return 0;
}
