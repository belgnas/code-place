#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

#define int long long
#define endl '\n'

#define IOS ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
// #define a first
// #define b second
#define PII pair<int, int>

const int N = 1e6 + 10; // 节点数
const int M = N * 2; // 边数

bool compare(PII a, PII b) {
    if (a.first != b.first) {
        return a.first < b.first;
    }
    return a.second < b.second;
}

// int idx; // 边的索引
// int ne[M]; // 下一个节点
// int val[M]; // 边的权值
// int head[N]; // 头节点

// void init() {
//     idx = 0;
//     memset(ne, -1, sizeof ne); // 初始化全部点的下一个节点为-1
// }

// void add_edge(int a, int b, int v = -1) {
//     ne[idx] = head[a]; // 新的边指向a的下一个节点
//     head[idx] = idx; // 新的边成为a的头节点
//     val[idx] = v; // 新的边的权值为v // 用不到的时候就默认为-1
//     idx++; // 边的索引增加
// }

int p[N], sz[N];

void init() {
    for (int i = 1; i <= N; i++) {
        p[i] = i; // 初始化每个点的父节点为本身
        sz[i] = 1; // 初始化每个点的大小为1
    }
}

int find(int x) {
    return p[x] == x ? x : p[x] = find(p[x]);
}

void merge(int a, int b) {
    int pa = find(a);
    int pb = find(b);
    if (pa == pb) {
        return;
    }
    if (sz[a] < sz[b]) {
        swap(a, b);
    }
    p[pa] = pb; // 合并pb到pa
    sz[pb] += sz[pa]; // 更新pb的大小
}

signed main()
{
    IOS;

    int n;
    cin >> n;

    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
    }

    vector<PII> AB;
    for (int i = 1; i <= n; i++) {
        AB.push_back({a[i] - i, -(b[i] - i)});
    }
    sort(AB.begin(), AB.end(), compare);

    // for (auto &ab : AB) {
    //     cout << ab.first << " " << ab.second << endl;
    // }

    vector<PII> stk;  // first = minY, second = maxY

    for (int i = 0; i < n; ) {
        int curL = AB[i].second;
        int curR = AB[i].second;
        int j = i;
        // 聚合同 x 的点
        while (j < n && AB[j].first == AB[i].first) {
            curL = min(curL, AB[j].second);
            curR = max(curR, AB[j].second);
            j++;
        }
        // 注意：此时 j 已经指向下一批次的第一个点
        // 开始合并栈顶区间
        while (!stk.empty() && curR >= stk.back().first) {
            curL = min(curL, stk.back().first);
            curR = max(curR, stk.back().second);
            stk.pop_back();
        }
        stk.push_back({curL, curR});
        i = j;  // 跳过已处理的点
    }

    cout << stk.size() << endl;
    

    // int cnt = 0;
    // vector<int> sk;
    // // int mn = LLONG_MAX;
    // for (auto &ab : AB) {
    //     // if (ab.second < mn) {
    //     //     mn = ab.second;
    //     //     cnt++;
    //     // }

    //     // if (sk.empty()) {
    //     //     sk.push_back(ab.first);
    //     //     cnt++;
    //     //     continue;
    //     // }

    //     // if (ab.second >= sk.front()) {
    //     //     continue;
    //     // }
    //     // else {
    //     //     sk.clear();
    //     //     cnt++;
    //     //     sk.push_back(ab.first);
    //     // }
    // }

    // // if (!sk.empty()) {
    // //     cnt++;
    // // }

    // cout << cnt << endl;

    // cout << "-----------------" << endl;


    // 满足
    // a[i] - i <= a[j] - j && b[i] - i >= b[j] - j
    // 或
    // a[i] - i >= a[j] - j && b[i] - i <= b[j] - j
    // 点之间有一条无向道路相连

    // vector<PII> edges;
    // vector<bool> used(n + 1, false);
    // for (int i = 1; i <= n; i++) {
    //     for (int j = i + 1; j <= n; j++) {
    //         int x1 = a[i] - i;
    //         int y1 = b[i] - i;
    //         int x2 = a[j] - j;
    //         int y2 = b[j] - j;

    //         if( (x1 <= x2 && y1 >= y2) || (x1 >= x2 && y1 <= y2) ) {
    //             used[i] = true;
    //             used[j] = true;

    //             edges.push_back({i, j});
    //             // bool found = false;
    //             // for (auto &edge : edges) {
    //             //     if (i == edge.second) {
    //             //         found = true;
    //             //         edge.second = j;
    //             //         break;
    //             //     }
    //             //     else if (j == edge.first) {
    //             //         found = true;
    //             //         edge.first = i;
    //             //         break;
    //             //     }
    //             // }
    //             // if (!found) {
    //             //     edges.push_back({i, j});
    //             // }
    //         }
    //     }
    // }
    
    // for (int i = 1; i <= n; i++) {
    //     if (!used[i]) {
    //         edges.push_back({i, i});
    //     }
    // }

    // sort(edges.begin(), edges.end(), compare);

    // cout << edges.size() << endl;

    // for (auto edge : edges) {
    //     cout << edge.first << " " << edge.second << endl;
    // }

    // // init();
    // // for (auto edge : edges) {
    // //     add_edge(edge.first, edge.second);
    // //     add_edge(edge.second, edge.first);
    // // }

    // // // 求连通块的数量
    // // int cnt = 0;

    // // init();

    // // for (int i = 1; i <= n; i++) {
    // //     for (int j = i + 1; j <= n; j++) {
    // //         int x1 = a[i] - i;
    // //         int y1 = b[i] - i;
    // //         int x2 = a[j] - j;
    // //         int y2 = b[j] - j;

    // //         if( (x1 <= x2 && y1 >= y2) || (x1 >= x2 && y1 <= y2) ) {
    // //             merge(i, j);
    // //         }
    // //     }
    // // }

    // // // for (auto edge : edges) {
    // // //     merge(edge.first, edge.second);
    // // // }
    // // // 统计连通块的数量
    // // for (int i = 1; i <= n; i++) {
    // //     if (p[i] == i) {
    // //         cnt++;
    // //     }
    // // }
    
    // // cout << cnt << endl;

    return 0;
}