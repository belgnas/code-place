#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

#define int long long

// N：节点数
// 2 * N：单向边数（双向边等效于2条单向边）
const int N = 2e5 + 10;
// h[i]表示节点i的所有邻接节点的下标
// e[idx]表示下标为idx的邻接节点
// ne[idx]表示下标为idx的邻接节点的下一个邻接节点的下标
// idx表示当前邻接节点的下标
// d[i]表示当前节点存储的值
int h[N], e[2 * N], ne[2 * N], idx, d[N];
int down[N], up[N];


void init() {
    for (int i = 0; i < N; i++) h[i] = -1;
    idx = 0;
    memset(d, 0, sizeof d);
    memset(down, 0, sizeof down);
    memset(up, 0, sizeof up);
}

void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

// bfs_down：从根节点开始，从上往下遍历所有节点，记录每个节点的深度
void bfs_down() {
    queue<int> q;
    q.push(1);
    while (q.size()) {
        int u = q.front(); // u表示当前节点 front()返回队列的第一个元素
        q.pop();
        for (int i = h[u]; i != -1; i = ne[i]) {
            int j = e[i]; // j表示当前节点的邻接节点
            if (down[j]) continue; // 如果j已经被遍历过，跳过
            down[j] = down[u] + 1; // 记录j的深度为u的深度加1
            q.push(j); // 将j加入队列，继续遍历j的邻接节点
        }
    }
}

// bfs_up：从叶子节点开始，从下往上遍历所有节点，记录每个节点的深度
void bfs_up(int n) {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (down[i] == n - 1) {
            q.push(i);
            up[i] = 1;
        }
    }
    while (q.size()) {
        int u = q.front(); // u表示当前节点 front()返回队列的第一个元素
        q.pop();
        for (int i = h[u]; i != -1; i = ne[i]) {
            int j = e[i]; // j表示当前节点的邻接节点
            if (up[j]) continue; // 如果j已经被遍历过，跳过
            up[j] = up[u] + 1; // 记录j的深度为u的深度加1
            q.push(j); // 将j加入队列，继续遍历j的邻接节点
        }
    }
}



signed main()
{
    int T;
    cin >> T;
    while (T--) {
        int n, m; // n个节点，m只蝴蝶
        cin >> n >> m;

        init();
        
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            add(u, v);
            add(v, u);
        }
        for (int i = 0; i < m; i++) {
            int a, t;
            cin >> a >> t;
            d[a] = t;
        }

        // 题目要求可以等效于：
        // 从上往下所能遍历的蝴蝶数 + 从下往上所能遍历的蝴蝶数

        // 预处理从上往下的节点深度
        bfs_down();

        // 预处理从下往上的节点深度
        bfs_up(n);

        // 统计每一层深度的蝴蝶数
        
        
        
    }
    

    return 0;
}
