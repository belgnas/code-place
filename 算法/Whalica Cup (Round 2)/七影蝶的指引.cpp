/*

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
    q.push(1); // 从根节点1开始遍历
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
        
        
        
    }
    

    return 0;
}

*/

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm> // 用于二分查找
using namespace std;

#define int long long

const int N = 2e5 + 10;
// 邻接表相关（你的原有实现）
int h[N], e[2 * N], ne[2 * N], idx;
// 修正变量名：depth存储节点深度（原down被占用，避免冲突）
int depth[N], fa[N]; // fa存储父节点，用于遍历避免回走
// down[u]：u到子树叶节点的最大蝴蝶数；up[u]：u到根节点的蝴蝶总数
int down[N], up[N];
// 存储每个节点的所有蝴蝶消失时间（一个节点可能有多个蝴蝶）
vector<int> ti_list[N];
// 各深度的max_down和max_up
int max_down[N], max_up[N];
// 所有叶子节点的统一深度
int leaf_depth;

// 初始化函数（扩展，覆盖所有需要重置的变量）
void init(int n) {
    for (int i = 0; i <= n; i++) {
        h[i] = -1;
        ti_list[i].clear();
        depth[i] = 0;
        fa[i] = -1;
        down[i] = 0;
        up[i] = 0;
        max_down[i] = -1e18; // 初始化为极小值
        max_up[i] = -1e18;
    }
    idx = 0;
    leaf_depth = 0;
}

// 加边函数（你的原有实现，无修改）
void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

// BFS：计算节点深度、父节点，确定叶子节点的统一深度
void bfs_depth(int n) {
    queue<int> q;
    q.push(1);
    depth[1] = 0;
    fa[1] = -1; // 根节点父节点标记为-1

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = h[u]; i != -1; i = ne[i]) {
            int j = e[i];
            if (fa[j] == -1 && j != fa[u]) { // 未访问过且不是父节点
                fa[j] = u;
                depth[j] = depth[u] + 1;
                q.push(j);
            }
        }
    }

    // 找到叶子节点的统一深度（叶子：度数1且非根）
    for (int u = 1; u <= n; ++u) {
        int cnt = 0;
        for (int i = h[u]; i != -1; i = ne[i]) cnt++;
        if (cnt == 1 && u != 1) {
            leaf_depth = depth[u];
            break;
        }
    }
}

// 后序DFS：计算down数组（u到子树叶节点的最大蝴蝶数）
void dfs_down(int u) {
    // 判断是否为叶子节点（度数1且非根）
    int cnt = 0;
    for (int i = h[u]; i != -1; i = ne[i]) cnt++;
    bool is_leaf = (cnt == 1 && u != 1);

    if (is_leaf) {
        // 叶子节点的到达时间 = 0（从叶子出发）
        int arrive_time = 0;
        // 统计能收集的蝴蝶数：t_i >= arrive_time的数量
        int num = ti_list[u].end() - lower_bound(ti_list[u].begin(), ti_list[u].end(), arrive_time);
        down[u] = num;
        return;
    }

    // 非叶子节点：取子节点down的最大值 + 当前节点能收集的蝴蝶数
    int max_child = 0;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j != fa[u]) { // 只遍历子节点
            dfs_down(j);
            max_child = max(max_child, down[j]);
        }
    }

    // 当前节点的到达时间 = 叶子深度 - 当前节点深度
    int arrive_time = leaf_depth - depth[u];
    int num = ti_list[u].end() - lower_bound(ti_list[u].begin(), ti_list[u].end(), arrive_time);
    down[u] = num + max_child;
}

// 先序DFS：计算up数组（u到根节点的蝴蝶总数）
void dfs_up(int u) {
    // 当前节点的到达时间
    int arrive_time = leaf_depth - depth[u];
    // 统计当前节点能收集的蝴蝶数
    int num = ti_list[u].end() - lower_bound(ti_list[u].begin(), ti_list[u].end(), arrive_time);

    if (fa[u] == -1) {
        up[u] = num; // 根节点无父节点，直接取当前数
    } else {
        up[u] = up[fa[u]] + num; // 累加父节点的up值
    }

    // 遍历子节点
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j != fa[u]) {
            dfs_up(j);
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0); // 加速cin输入

    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;

        // 初始化当前测试用例的所有变量
        init(n);

        // 读入树的边（你的原有逻辑）
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            add(u, v);
            add(v, u);
        }

        // 读入蝴蝶数据（修正：一个节点可能有多个蝴蝶，需存入vector）
        for (int i = 0; i < m; i++) {
            int a, t;
            cin >> a >> t;
            ti_list[a].push_back(t);
        }

        // 对每个节点的蝴蝶消失时间排序（用于二分查找）
        for (int i = 1; i <= n; ++i) {
            sort(ti_list[i].begin(), ti_list[i].end());
        }

        // 步骤1：BFS计算深度、父节点、叶子深度
        bfs_depth(n);

        // 步骤2：DFS计算down数组
        dfs_down(1);

        // 步骤3：DFS计算up数组
        dfs_up(1);

        // 步骤4：统计各深度的max_down和max_up
        for (int u = 1; u <= n; ++u) {
            int d = depth[u];
            max_down[d] = max(max_down[d], down[u]);
            max_up[d] = max(max_up[d], up[u]);
        }

        // 步骤5：计算最终答案
        int ans = down[1]; // 不使用特殊能力的最大值
        // 遍历所有可能的跳跃深度（使用特殊能力）
        for (int d = 1; d <= leaf_depth; ++d) {
            int prev_d = d - 1;
            // 跳过无节点的深度
            if (max_down[d] == -1e18 || max_up[prev_d] == -1e18) continue;
            ans = max(ans, max_down[d] + max_up[prev_d]);
        }

        // 输出答案
        cout << ans << endl;
    }

    return 0;
}