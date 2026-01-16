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

using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define endl '\n'
typedef pair<int, int> PII;

const int INF = INT_MAX;;
const long long LLNF = LLONG_MAX;
const int MOD = 1e9 + 7;

// 增加一个辅助函数：计算在 h * w 的子网格中，步长为1的象能走多少格
int calc(int h, int w) {
    if (h == 0 || w == 0) return 0;
    // 如果只有1行或1列，象无法进行对角线移动（因为需要行+1且列+1），只能呆在原地
    if (h == 1 || w == 1) return 1;
    // 否则，象可以在同色格子上任意移动，占总格子数的一半（向上取整）
    return (h * w + 1) / 2;
}

signed main()
{
    IOS;

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        // 1. 统计奇数/偶数 行和列的数量
        // 1, 3, 5...
        int odd_r = (n + 1) / 2; 
        int odd_c = (m + 1) / 2;
        // 2, 4, 6...
        int even_r = n / 2;
        int even_c = m / 2;

        // 2. 计算四种起点的最大可达数量
        // 情况1: 起点在 (奇数行, 奇数列)
        int ans1 = calc(odd_r, odd_c);
        // 情况2: 起点在 (奇数行, 偶数列)
        int ans2 = calc(odd_r, even_c);
        // 情况3: 起点在 (偶数行, 奇数列)
        int ans3 = calc(even_r, odd_c);
        // 情况4: 起点在 (偶数行, 偶数列)
        int ans4 = calc(even_r, even_c);

        // 3. 输出最大值
        cout << max({ans1, ans2, ans3, ans4}) << endl;
    }

    return 0;
}