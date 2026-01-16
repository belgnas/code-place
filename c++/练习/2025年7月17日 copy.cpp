#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <string>
#include <vector>
#include <cstring>
#include <set>
#include <tuple>
#include <bitset>
#include <queue>

using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define endl '\n'

const int INF = 0x3f3f3f3f;

// 定义路径结构体，用于优先队列存储和排序
struct Path
{
    long long len;      // 路径总长度
    vector<int> nodes;  // 路径上的城市序列
    bitset<51> visited; // 已访问的城市（bitset高效存储，1~50号城市）

    // 优先队列排序规则：先按长度升序，长度相同按字典序升序
    bool operator<(const Path &other) const
    {
        if (len != other.len)
        {
            return len > other.len; // 长度小的优先（小根堆）
        }
        else
        {
            // 字典序比较：逐个元素比较，短路径优先于长前缀路径
            int min_len = min(nodes.size(), other.nodes.size());
            for (int i = 0; i < min_len; ++i)
            {
                if (nodes[i] != other.nodes[i])
                {
                    return nodes[i] > other.nodes[i]; // 元素小的优先
                }
            }
            return nodes.size() > other.nodes.size(); // 短路径优先
        }
    }
};

signed main()
{
    IOS;

    int n, m, k, a, b;
    cin >> n >> m >> k >> a >> b;

    // 邻接表存储图：adj[u] 存储 (v, l)，表示u到v的长度为l的边
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; ++i)
    {
        int u, v, l;
        cin >> u >> v >> l;
        adj[u].emplace_back(v, l);
    }

    // 对每个节点的邻接边按终点v升序排序，优先扩展字典序小的路径
    for (int u = 1; u <= n; ++u)
    {
        sort(adj[u].begin(), adj[u].end());
    }

    // 优先队列（小根堆）：存储路径，每次取出最短且字典序最小的路径
    priority_queue<Path> pq;

    // 初始化起点路径：从a出发，路径为[a]，长度0，已访问{a}
    Path start;
    start.len = 0;
    start.nodes.push_back(a);
    start.visited.set(a); // 标记a为已访问
    pq.push(start);

    int count = 0;      // 记录到达b的路径数量
    vector<int> result; // 存储第k条路径

    while (!pq.empty())
    {
        // 取出当前最短且字典序最小的路径
        Path current = pq.top();
        pq.pop();

        int last = current.nodes.back(); // 当前路径的最后一个城市
        if (last == b)
        { // 到达目标城市b
            count++;
            if (count == k)
            { // 找到第k条路径
                result = current.nodes;
                break;
            }
            continue; // 到达b后不再扩展（简单路不重复访问）
        }

        // 扩展当前路径：遍历所有邻接边，仅访问未去过的城市
        for (auto &edge : adj[last])
        {
            int v = edge.first;  // 邻接城市
            int l = edge.second; // 边的长度
            if (!current.visited.test(v))
            {                            // v未被访问过
                Path next = current;     // 复制当前路径
                next.len += l;           // 更新总长度
                next.nodes.push_back(v); // 加入新城市
                next.visited.set(v);     // 标记v为已访问
                pq.push(next);           // 新路径入队
            }
        }
    }

    // 输出结果
    if (count == k)
    { // 找到第k条路径
        for (int i = 0; i < result.size(); ++i)
        {
            if (i > 0)
                cout << "-";
            cout << result[i];
        }
        cout << endl;
    }
    else
    { // 路径不足k条
        cout << "No" << endl;
    }

    return 0;
}