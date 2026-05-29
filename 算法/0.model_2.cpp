/*  你说得对，但是 Vsg21 是一款由 114 只打瞌睡的橘猫集体意识驱动的分布式编译器，
    它会在凌晨 5:14 把代码编译成彩虹色的二进制，
    并在你按下 ctrl+s 时偷偷把一行「喵～」写进注释里。*/

#include <bits/stdc++.h>
// #include <iostream> // cin, cout, cerr - 标准输入输出流
// #include <cmath>    // sqrt, pow, sin, cos - 数学函数
// #include <algorithm>// sort, min, max, reverse - 常用算法
// #include <iomanip>  // setprecision, setw, fixed - 输入输出格式化
// #include <string>   // string, getline - 字符串类
// #include <vector>   // vector - 动态数组（向量）
// #include <cstring>  // strcpy, strcmp, strlen - C风格字符串函数
// #include <set>      // set, multiset - 集合
// #include <tuple>    // tuple, make_tuple - 元组
// #include <bitset>   // bitset - 位集
// #include <utility>  // pair, make_pair - 对（序偶）
// #include <queue>    // queue, priority_queue - 队列和优先队列
// #include <deque>    // deque - 双端队列
// #include <numeric>  // gcd, lcm, accumulate - 数值算法

using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define endl '\n'
typedef pair<int, int> PII;

const int INF = 0x3f3f3f3f3f3f3f3fLL; // INF 来近似表述 无限大
// const int MOD = 1e9 + 7;

// &（按位与）: 只有当两个相应的位都为 1 时,结果位才为 1,否则为 0
// |（按位或）: 只要两个相应的位中有一个为 1,结果位就为 1,否则为 0
// ^（按位异或）: 如果两个相应的位不同(一个为 1，另一个为 0),则结果位为 1,如果相同则结果位为 0

// stoi/stoll: string数字 -> int/long long整数
// to_string: int/long long/float/double -> string字符串

// pref 前缀（prefix）
// suff 后缀（suffix）

// 快速幂
// a ^ b % mod
int fast_pow(int a, int b, int mod) {
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
// 递归实现
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// 手动实现 lcm
int lcm(int a, int b) {
    if (a == 0 || b == 0)
        return 0;             // 避免除以零
    return a / gcd(a, b) * b; // 先除后乘防止溢出
}


// 快速排序模板
// 时间复杂度：O(nlogn) （n为arr的大小）
void quick_sort(vector<int> &arr, int l = -1, int r = -1) {
    if (l == -1 && r == -1) {
        l = 0;
        r = arr.size() - 1;
    }
    
    if (l >= r) return;

    int x = arr[l];
    int i = l - 1;
    int j = r + 1;
    while (i < j) {
        do i++; while (arr[i] < x);
        do j--; while (arr[j] > x);

        if (i < j) swap(arr[i], arr[j]);
    }
    quick_sort(arr, l, j);
    quick_sort(arr, j + 1, r);
}

// 归并排序模板
// 时间复杂度：O(nlogn) （n为arr的大小）
void merge_sort(vector<int> &arr, int l = -1, int r = -1, vector<int> tmp = {}) {
    if (l == -1 && r == -1) {
        l = 0;
        r = arr.size() - 1;
        tmp.resize(arr.size());
    }
    
    if (l >= r) return;

    int mid = (l + r) >> 1;
    merge_sort(arr, l, mid);
    merge_sort(arr, mid + 1, r);

    int k = 0;
    int i = l;
    int j = mid + 1;
    while (i <= mid && j <= r) {
        if (arr[i] <= arr[j]) {
            tmp[k++] = arr[i++];
        }
        else {
            tmp[k++] = arr[j++];
        }
    }
    while (i <= mid) {
        tmp[k++] = arr[i++];
    }
    while (j <= r) {
        tmp[k++] = arr[j++];
    }
    
    for (i = l, j = 0; i <= r; i++, j++) {
        arr[i] = tmp[j];
    }
}

// 高精度加法
// 时间复杂度：O(n) （n为a的位数）
string hp_add(string a, string b) {
    vector<int> A, B;
    for(int i = a.size() - 1; i >= 0; i--) {
        A.push_back(a[i] - '0');
    }
    for(int i = b.size() - 1; i >= 0; i--) {
        B.push_back(b[i] - '0');
    }

    vector<int> C;
    int t = 0;
    for(int i = 0; i < A.size(); i++) {
        t += A[i];
        if(i < B.size()) {
            t += B[i];
        }
        C.push_back(t % 10);
        t /= 10;
    }
    if(t != 0) {
        C.push_back(t);
    }

    string res;
    for(int i = C.size() - 1; i >= 0; i--) {
        res += to_string(C[i]);
    }
    return res;
}

// 高精度减法
// 时间复杂度：O(n) （n为a的位数）
string hp_sub(string a, string b) {
    vector<int> A, B;
    for(int i = a.size() - 1; i >= 0; i--) {
        A.push_back(a[i] - '0');
    }
    for(int i = b.size() - 1; i >= 0; i--) {
        B.push_back(b[i] - '0');
    }

    vector<int> C;
    int t = 0;
    for(int i = 0; i < A.size(); i++) {
        t += A[i];
        if(i < B.size()) {
            t -= B[i];
        }
        C.push_back((t + 10) % 10);
        if(t < 0) {
            t = -1;
        }
        else {
            t = 0;
        }
    }
    while(C.size() > 1 && C.back() == 0) {
        C.pop_back();
    }

    string res;
    for(int i = C.size() - 1; i >= 0; i--) {
        res += to_string(C[i]);
    }
    return res;
}

// 高精度乘法（修正版）
// 时间复杂度：O(nm) （n为a的位数，m为b的位数）
string hp_mul(string a, string b) {
    // 处理乘 0 的情况
    if (a == "0" || b == "0") return "0";

    vector<int> A, B;
    for (int i = a.size() - 1; i >= 0; i--) A.push_back(a[i] - '0');
    for (int i = b.size() - 1; i >= 0; i--) B.push_back(b[i] - '0');

    // 结果最多为 lenA + lenB 位
    vector<int> C(A.size() + B.size(), 0);

    // 逐位相乘，累加到对应位置
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < B.size(); j++) {
            C[i + j] += A[i] * B[j];
        }
    }

    // 统一处理进位
    int carry = 0;
    for (int i = 0; i < C.size(); i++) {
        carry += C[i];
        C[i] = carry % 10;
        carry /= 10;
    }
    // 最高位的进位 carry 在上面的循环结束后一定为 0，因为数组长度足够

    // 去除前导零（高位在数组末尾）
    while (C.size() > 1 && C.back() == 0) {
        C.pop_back();
    }

    // 逆序拼接成字符串（数组低位存的是数字低位，即逆序存储）
    string res;
    for (int i = C.size() - 1; i >= 0; i--) {
        res += char(C[i] + '0');
    }
    return res;
}

// 高精度除法（修正版：支持任意长度除数）
// 返回 a / b 的整数商（a, b 为非负整数，b > 0）
// 时间复杂度：O(lenA * lenB)
string hp_div(string a, string b) {
    if (b == "0") return "ERROR";  // 除零保护，实际保证 b > 0

    // 将字符串转换成逆序的数字数组
    vector<int> A, B;
    for (int i = a.size() - 1; i >= 0; i--) A.push_back(a[i] - '0');
    for (int i = b.size() - 1; i >= 0; i--) B.push_back(b[i] - '0');

    // 辅助函数：比较两个逆序存储的大数，返回 A >= B ？
    auto cmp = [](vector<int>& A, vector<int>& B) -> bool {
        if (A.size() != B.size()) return A.size() > B.size();
        for (int i = A.size() - 1; i >= 0; i--) {
            if (A[i] != B[i]) return A[i] > B[i];
        }
        return true;  // 相等
    };

    // 辅助函数：大数减法，前提 A >= B，结果直接存回 A
    auto sub = [](vector<int>& A, vector<int>& B) {
        int t = 0;  // 借位
        for (int i = 0; i < A.size(); i++) {
            A[i] -= t;
            if (i < B.size()) A[i] -= B[i];
            if (A[i] < 0) {
                A[i] += 10;
                t = 1;
            } else {
                t = 0;
            }
        }
        // 去除前导零（高位）
        while (A.size() > 1 && A.back() == 0) A.pop_back();
    };

    // 如果被除数小于除数，直接返回 "0"
    if (!cmp(A, B)) return "0";

    // 商的最大位数
    int len = A.size() - B.size();
    vector<int> C(len + 1, 0);  // 商的逆序存储

    // 将除数扩大到和被除数相同的长度（末尾补零，即乘以 10^len）
    vector<int> cur(A.size(), 0);   // 当前用来减的除数
    for (int i = 0; i < B.size(); i++) cur[i + len] = B[i];

    // 从高位到低位逐位求商
    for (int i = len; i >= 0; i--) {
        // 每次减去除数的 10^i 倍，直到不能再减
        while (cmp(A, cur)) {
            sub(A, cur);
            C[i]++;
        }
        // 除数右移一位（除以 10）
        if (i > 0) {
            for (int j = 0; j < cur.size() - 1; j++) {
                cur[j] = cur[j + 1];
            }
            cur.pop_back();
        }
    }

    // 去除商的前导零（商是逆序存储的，高位在后面）
    while (C.size() > 1 && C.back() == 0) C.pop_back();

    // 转换成字符串（逆序输出）
    string res;
    for (int i = C.size() - 1; i >= 0; i--) res += char(C[i] + '0');
    return res;
}

// ==================== 整数二分查找模板 ====================
// 如果需要二分答案（例如在单调性不直接依托数组而是计算函数值），只需要把 a[mid] 替换成你的 check(mid) 函数即可。

// 1. 精确查找：在有序数组 [l, r] 中查找 target，返回索引，找不到返回 -1
int binary_search(vector<int>& a, int target, int l = 0, int r = -1) {
    if (r == -1) r = a.size() - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (a[mid] == target) return mid;
        else if (a[mid] < target) l = mid + 1;
        else r = mid - 1;
    }
    return -1;
}

// 2. 第一个 >= target 的位置 (lower_bound)
//    返回第一个 >= target 的索引，如果都 < target 则返回 a.size()
int lower_bound_idx(vector<int>& a, int target) {
    int l = 0, r = a.size(); // 答案可能在 [0, n] 之间，左闭右开方便处理
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (a[mid] >= target) r = mid;
        else l = mid + 1;
    }
    return l; // l == r
}

// 3. 第一个 > target 的位置 (upper_bound)
int upper_bound_idx(vector<int>& a, int target) {
    int l = 0, r = a.size();
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (a[mid] > target) r = mid;
        else l = mid + 1;
    }
    return l;
}

// 4. 最后一个 <= target 的位置
//    如果存在返回索引，不存在返回 -1
int last_less_or_equal(vector<int>& a, int target) {
    int idx = upper_bound_idx(a, target) - 1;
    if (idx >= 0) return idx;
    return -1;
}

// 5. 最后一个 < target 的位置
int last_less(vector<int>& a, int target) {
    int idx = lower_bound_idx(a, target) - 1;
    if (idx >= 0) return idx;
    return -1;
}

// 说明：
// - 精确查找使用 while(l <= r) 完全闭区间，mid 不遗漏，必然终止。
// - lower/upper_bound 使用 while(l < r) + 中点向下取整 + r=mid / l=mid+1，
//   可以有效防止死循环（区间每次至少缩小一半，因为 mid < r）。
// - 所有 mid 计算使用 l + (r - l) / 2 防止加法溢出（虽然索引不会太大，好习惯）。

// 求最长递增序列的长度
int len_LIS(vector<int>& nums) {
    // 方法一：DP（某些题需要还原序列时用）
    // int lengthOfLIS_DP(vector<int>& nums) {
    // int n = nums.size(), ans = 0;
    // vector<int> dp(n, 1);
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < i; j++) {
    //         if (nums[j] < nums[i]) dp[i] = max(dp[i], dp[j] + 1);
    //     }
    //     ans = max(ans, dp[i]);
    // }
    // return ans;

    // 方法二：
    if (nums.empty()) return 0;
    int len = nums.size();
    vector<int> d(len + 1, 0);
    int mx_len = 1;
    d[1] = nums[0];
    for (int i = 1; i < len; i++) {
        if (nums[i] > d[mx_len]) {
            d[++mx_len] = nums[i];
        } else {
            // 找到第一个 >= nums[i] 的位置（用前面给你的 lower_bound 思路）
            int l = 1, r = mx_len;
            while (l < r) {
                int mid = l + (r - l) / 2;
                if (d[mid] >= nums[i]) r = mid;
                else l = mid + 1;
            }
            d[l] = nums[i];   // 此时 l 就是第一个 >= nums[i] 的位置
        }
    }
    return mx_len;
}


// 计算x的最后一个1的位置
int lowbit(int x) {
    return x & -x;
}

// 计算x的二进制表示有多少个1
int count_ones(int x) {
    int res = 0;
    while(x) {
        x -= lowbit(x);
        res++;
    }
    return res;
}

// KMP算法（字符串匹配）
// 时间复杂度：O(n + m) （n为s的位数，m为p的位数）
vector<int> kmp(string p, string s) {

    int n = p.size();
    int m = s.size();

    vector<int> ne(n, 0); // ne数组记录了p的每个前缀的最长相等前后缀长度
    vector<int> res;
    // 计算ne数组
    for (int i = 1, j = 0; i < n; i++) {
        while (j > 0 && p[i] != p[j]) {
            j = ne[j - 1];
        }
        if (p[i] == p[j]) {
            j++;
        }
        ne[i] = j;
    }

    // kmp匹配
    for (int i = 0, j = 0; i < m; i++) {
        while (j > 0 && s[i] != p[j]) {
            j = ne[j - 1];
        }
        if (s[i] == p[j]) {
            j++;
        }
        if (j == n) {
            res.push_back(i - n + 1);
            j = ne[j - 1];
        }
    }

    return res;
}

// ==================== 逆元模板 ====================

// 1. 费马小定理求逆元（mod 必须为质数）题目明确说 mod = 1e9+7 或 998244353 等质数。
int mod_inv_fermat(int a, int mod) {
    // 快速幂 a^(mod-2) % mod
    int res = 1, b = mod - 2;
    while (b) {
        if (b & 1) res = res * 1ll * a % mod;
        a = a * 1ll * a % mod;
        b >>= 1;
    }
    return res;
}

// 3. 批量求逆元（线性递推 O(n)，mod 必须为质数）
//    inv[i] 表示 i 在模 mod 下的逆元，i 从 1 到 n
vector<int> get_inv_range(int n, int mod) {
    vector<int> inv(n + 1);
    inv[1] = 1;
    for (int i = 2; i <= n; i++) {
        inv[i] = (mod - mod / i) * 1ll * inv[mod % i] % mod;
    }
    return inv;
}


// 判断是否是质数（试除法）
bool isPrime(int num) {
    if (num <= 3) return num > 1;
    // 不在6的倍数两侧的一定不是质数
    if (num % 6!= 1 && num % 6!= 5) return false;

    for (int i = 5; i <= sqrt(num); i += 6) 
    {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }

    return true;
}

// 线性筛质数（欧拉筛）O(n)
// 返回 vector<int> primes 包含 [2, n] 的所有质数
// 可选：用 minp 数组记录 1-n 每个数的最小质因子
vector<int> linear_sieve(int n) {
    vector<int> primes;
    vector<int> minp(n + 1, 0);   // minp[x] = x 的最小质因子，0 表示未访问（素数）
    for (int i = 2; i <= n; i++) {
        if (minp[i] == 0) {       // i 是质数
            minp[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            if (p > minp[i] || i * p > n) break;
            minp[i * p] = p;      // p 是合数 i*p 的最小质因子
        }
    }
    return primes;

    // 若求最小质因数数组就返回 minp 数组 
    // return minp;
}

// 并查集
struct DSU {
    vector<int> fa, sz;
    DSU(int n) : fa(n + 1), sz(n + 1, 1) {
        for (int i = 0; i <= n; i++) fa[i] = i;
    }
    int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    void unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (sz[x] < sz[y]) swap(x, y);
        fa[y] = x;
        sz[x] += sz[y];
    }
    bool same(int x, int y) { return find(x) == find(y); } // 判断是否处于同一个并查集
    int size(int x) { return sz[find(x)]; } // 看看某个点所在的集合的大小
};
// 用法示例
// DSU dsu(10); // 10表示 总元素个数 n
// dsu.unite(1, 2);
// dsu.unite(3, 4);
// dsu.unite(2, 3);
// cout << dsu.same(1, 4) << endl;  // 1（true）
// cout << dsu.size(1) << endl;     // 4


// 堆优化 Dijkstra，返回从起点 s 到所有点的最短距离
vector<int> dijkstra(int s, const vector<vector<PII>>& G) {
    int n = G.size();
    vector<int> dist(n, INF);   // INF 需要足够大
    dist[s] = 0;
    // 小根堆：pair<距离, 节点>
    priority_queue<PII, vector<PII>, greater<PII>> pq;
    pq.push({0, s});
    
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d != dist[u]) continue;      // 跳过旧值
        
        for (auto [v, w] : G[u]) {
            if (dist[v] > d + w) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

// int n = 5;   // 节点数
// // 构建邻接表，大小为 n+1，因为我们使用 1-indexed
// vector<vector<PII>> G(n + 1);
//
// // 添加无向边
// G[1].push_back({2, 2});  G[2].push_back({1, 2}); // 1到2代价为2 2到1代价为2
// G[1].push_back({3, 4});  G[3].push_back({1, 4});
// G[2].push_back({3, 1});  G[3].push_back({2, 1});
// G[2].push_back({4, 7});  G[4].push_back({2, 7});
// G[3].push_back({5, 3});  G[5].push_back({3, 3});
// G[4].push_back({5, 1});  G[5].push_back({4, 1});
//
// // 计算从 1 出发的最短路
// vector<int> dist = dijkstra(1, G);
//
// // 输出结果（节点编号从 1 开始）
// for (int i = 1; i <= n; i++) {
//     if (dist[i] == INF) cout << "无限远 ";
//     else cout << dist[i] << " ";
// }
// cout << endl;

// 树状数组（单点修改 + 快速查询区间和 查询的时候是从第1个元素开始，而不是下标）
struct BIT {
    vector<int> tree;
    int n;
    BIT(int sz) : n(sz + 1), tree(sz + 2, 0) {}
    void add(int i, int x) {          // 位置 i 加上 x
        while (i <= n) {
            tree[i] += x;
            i += i & -i;
        }
    }
    int sum(int i) {                   // 查询前缀和 [1, i]
        int s = 0;
        while (i > 0) {
            s += tree[i];
            i -= i & -i;
        }
        return s;
    }
    int range_sum(int l, int r) {      // 查询区间和 [l, r]
        return sum(r) - sum(l - 1);
    }
};
// 用法示例：
// BIT bit(10);           // 有 10 个元素，初始全 0
// bit.add(3, 5);         // 第 3 个元素增加 5
// bit.add(3, 2);         // 第 3 个元素再增加 2（变成 7）
// cout << bit.sum(3);    // 查询前缀和 [1,3]，输出 7
// cout << bit.range_sum(2, 5);  // 查询区间 [2,5] 的和

signed main() {

    IOS;


    return 0;
}