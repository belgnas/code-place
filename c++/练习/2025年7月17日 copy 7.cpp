#include <iostream>
#include <vector>
#include <queue>
#include <bitset>
#include <cstring>
#include <algorithm>

using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define endl '\n'

const int N = 55;  // 城市数量不超过50
const int M = 1005; // 边的最大数量
const int INF = 0x3f3f3f3f;

// 邻接表存储相关
int h[N], e[M], ne[M], w[M], idx;
int n, m, k, a, b;

// 定义路径结构体，用于优先队列存储和排序
struct Path
{
    long long len;      // 路径总长度
    vector<int> nodes;  // 路径上的城市序列
    bitset<N> visited;  // 已访问的城市

    // 优先队列排序规则：先按长度升序，长度相同按字典序升序
    bool operator<(const Path &other) const
    {
        if (len != other.len)
        {
            return len > other.len; // 长度小的优先（小根堆）
        }
        else
        {
            int min_len = min(nodes.size(), other.nodes.size());
            for (int i = 0; i < min_len; ++i)
            {
                if (nodes[i] != other.nodes[i])
                {
                    return nodes[i] > other.nodes[i];
                }
            }
            return nodes.size() > other.nodes.size();
        }
    }
};

// 添加边
void add(int u, int v, int l)
{
    e[idx] = v;
    w[idx] = l;
    ne[idx] = h[u];
    h[u] = idx++;
}

signed main()
{
    IOS;
    memset(h, -1, sizeof h);  // 初始化邻接表头节点
    idx = 0;                  // 边索引从0开始

    cin >> n >> m >> k >> a >> b;

    // 读取边信息
    for (int i = 0; i < m; ++i)
    {
        int u, v, l;
        cin >> u >> v >> l;
        add(u, v, l);
    }

    // 对每个节点的邻接边按终点v升序排序，保证字典序
    for (int u = 1; u <= n; ++u)
    {
        vector<pair<int, int>> temp;  // 临时存储(v, w)
        for (int i = h[u]; i != -1; i = ne[i])
        {
            temp.emplace_back(e[i], w[i]);
        }
        sort(temp.begin(), temp.end());  // 按v升序排序
        
        // 重新构建邻接表
        h[u] = -1;  // 清空原邻接表
        for (auto &p : temp)
        {
            add(u, p.first, p.second);
        }
    }

    // 优先队列（小根堆）
    priority_queue<Path> pq;

    // 初始化起点路径
    Path start;
    start.len = 0;
    start.nodes.push_back(a);
    start.visited.set(a);
    pq.push(start);

    int count = 0;
    vector<int> result;

    while (!pq.empty())
    {
        Path current = pq.top();
        pq.pop();

        int last = current.nodes.back();
        if (last == b)
        {
            count++;
            if (count == k)
            {
                result = current.nodes;
                break;
            }
            continue;
        }

        // 扩展路径
        for (int i = h[last]; i != -1; i = ne[i])
        {
            int v = e[i];
            int l = w[i];
            if (!current.visited.test(v))
            {
                Path next = current;
                next.len += l;
                next.nodes.push_back(v);
                next.visited.set(v);
                pq.push(next);
            }
        }
    }

    // 输出结果
    if (count == k)
    {
        for (int i = 0; i < result.size(); ++i)
        {
            if (i > 0) cout << "-";
            cout << result[i];
        }
        cout << endl;
    }
    else
    {
        cout << "No" << endl;
    }

    return 0;
}
