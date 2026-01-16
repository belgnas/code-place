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
#include <climits>  // INT_MAX, LLONG_MAX - 整数最大最小值
#include <stack>    // 引入栈

using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define endl '\n'
typedef pair<int, int> PII;

const int INF = INT_MAX;;
const long long LLNF = LLONG_MAX;
const int MOD = 1e9 + 7;
const int MAXN = 300005; // 根据题目 N <= 3e5
const int LOGN = 20;     // 2^19 > 3e5

// 全局变量定义，防止栈溢出
int a[MAXN];
int st[MAXN][LOGN]; // ST表用于区间最大值查询
int lg[MAXN];       // 预处理 log 值
int pre[MAXN];      // 前缀和
int L[MAXN], R[MAXN]; // 左右边界

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

// 手动实现 lcm
int lcm(int a, int b)
{
    if (a == 0 || b == 0)
        return 0;             // 避免除以零
    return a / gcd(a, b) * b; // 先除后乘防止溢出
}

// 预处理 log 函数
void init_log() {
    lg[1] = 0;
    for (int i = 2; i < MAXN; i++) lg[i] = lg[i / 2] + 1;
}

// 构建 ST 表 (Range Maximum Query)
void build_st(int n) {
    for (int i = 1; i <= n; i++) st[i][0] = a[i];
    for (int j = 1; j < LOGN; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }
}

// 查询区间最大值 O(1)
int query_max(int l, int r) {
    int k = lg[r - l + 1];
    return max(st[l][k], st[r - (1 << k) + 1][k]);
}

signed main()
{
    IOS;
    init_log(); // 程序开始前只初始化一次 log 数组

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        
        // 读入数据并计算前缀和
        pre[0] = 0;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            pre[i] = pre[i - 1] + a[i];
        }

        // 1. 构建 ST 表
        build_st(n);

        // 2. 单调栈求左右边界
        // L[i]: i 左边第一个小于 a[i] 的位置
        // R[i]: i 右边第一个小于 a[i] 的位置
        stack<int> s;
        
        // 求左边界
        for (int i = 1; i <= n; i++) {
            while (!s.empty() && a[s.top()] >= a[i]) {
                s.pop();
            }
            L[i] = s.empty() ? 0 : s.top();
            s.push(i);
        }

        while (!s.empty()) s.pop(); // 清空栈

        // 求右边界
        for (int i = n; i >= 1; i--) {
            while (!s.empty() && a[s.top()] >= a[i]) {
                s.pop();
            }
            R[i] = s.empty() ? n + 1 : s.top();
            s.push(i);
        }

        // 3. 计算最小代价
        // 初始代价为不进行任何操作的情况
        int ans = pre[n];

        for (int i = 1; i <= n; i++) {
            // 有效操作区间是 (L[i], R[i])，即闭区间 [L[i] + 1, R[i] - 1]
            int l = L[i] + 1;
            int r = R[i] - 1;

            if (l > r) continue;

            // 原始总和 - 该区间原始和 + 该区间变小后的和 + 操作花费(区间最大值)
            int range_sum = pre[r] - pre[l - 1];
            int range_max = query_max(l, r);
            int new_range_sum = a[i] * (r - l + 1);
            
            int current_cost = (pre[n] - range_sum) + new_range_sum + range_max;
            
            if (current_cost < ans) {
                ans = current_cost;
            }
        }

        cout << ans << endl;
    }

    return 0;
}