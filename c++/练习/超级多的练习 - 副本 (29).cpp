#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)

typedef pair<int, int> PII;

const int N = 100010;
const int INF = 0x3f3f3f3f; // 定义无穷大常量

int n, m, q;                      // n个点 m条边 送q次外卖
int h[N], e[N], ne[N], w[N], idx; // h是邻接表的头结点，e是边的终点，ne是下一条边的编号，w是边的权重，idx是边的编号
int dist[N];                      // 存储1号点到每个点的最短距离
bool st[N];                       // 存储每个点是否已经确定了距离

void add(int a, int b, int c) // 添加一条边a->b，权重为c
{
    // e和w相当于idx这条边对应的2个属性，或者说特征
    e[idx] = b;
    w[idx] = c;

    ne[idx] = h[a];
    h[a] = idx;
    idx++;
}

void dijkstra()
{
    memset(dist, 0x3f, sizeof dist); // 初始化1号节点到每个位置的距离为 无穷大
    dist[1] = 0;                     // 到自己的距离为0

    priority_queue<PII, vector<PII>, greater<PII>> heap; // 定义一个小根堆，存储距离和点的编号
    heap.push({0, 1});                                   // 把距离为0的1号点加入堆中

    while (heap.size()) // while堆不为空
    {
        auto t = heap.top(); // 每次找到距离最小的点，也就是堆顶元素
        heap.pop();          // 弹出堆顶元素

        int ver = t.second, distance = t.first; // ver是点的编号，distance是距离

        if (st[ver])
            continue; // 如果这个点已经被确定了距离，就跳过
        // 比如有2条路被记录到堆中，一条是{4, 3}，{5, 3}，前者是{ 距离为4 , 起点到点3 }，后者是{ 距离为5 , 起点到点3}
        // 由于小根堆的特性，{4, 3}会被先取出，这是一切正常运行，st[3]会从false标记成true，然后堆里剩下的那个{5, 3}就没有了意义，等到{5, 4}时就会直接continue
        st[ver] = true; // 如果这个点之前没有被确定距离，那么现在就确定距离

        for (int i = h[ver]; i != -1; i = ne[i])
        {
            int j = e[i]; // j是ver的出边的终点
            if (dist[j] > distance + w[i])
            {
                dist[j] = distance + w[i]; // 更新j的距离
                heap.push({dist[j], j});   // 把j加入到堆中
            }
        }
    }
}

int main()
{
    IOS;

    cin >> n >> m >> q;

    memset(h, -1, sizeof h); // 初始化邻接表

    while (m--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
        add(b, a, c);
    }

    int ans = 0;
    dijkstra();

    while (q--)
    {
        int school;
        cin >> school;
        int t = dist[school];
        // if (t == INF)
        // {                       // 显式使用INF检查不可达性
        //     cout << -1 << endl; // 或其他错误处理，根据题目要求调整
        //     return 0;
        // }
        ans += (t * 2);
    }

    cout << ans << endl;

    return 0;
}