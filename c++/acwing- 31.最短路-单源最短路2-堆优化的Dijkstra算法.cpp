// 最短路


// 我们学编程不会让我们去数学证明，我们只需要知道结论，然后用代码去“实现”就好了，实际上就比的是记忆能力。

//（在每种情况下，都有各自的最优抉择）
// 分类：
//  1.单源最短路（求的是一个点到其他所有点的最短距离）
//      (1).所有边的权重都是正数
//          (a).朴素Dijkstra算法        O(n^2)
//              比较适合 稠密图
//          **(b).堆优化版的Dijkstra算法  O(mlogn)
//              比较适合 稀疏图
//      (2).存在负权边
//          (a).Bellman-Ford算法        O(nm)
//              比较适合 存在负权边 的图
//          (b).SPFA算法                O(m)
//              一般 O(m), 最坏 O(nm)
//  2.多源汇最短路（求的是任意两点之间的最短距离）
//      (1).Floyd算法                   O(n^3)

// 我们在讲最短路算法的时候，都是针对有向图的
// 如果遇到无向图，我们一般会把无向图转化成有向图来处理
// 例如：把 a - b 无向边 转化成 a -> b 和 b -> a 两条有向边


// 如果想优化时间复杂度，可以使用堆优化
// 用堆优化的方式有2种：
//  1.手写堆
//  2.使用STL中的priority_queue（优先队列）

// 因为优先队列比手写堆要简单，所以我们一般使用优先队列来优化

// 题目描述 ：
// 给定一个 n 个点 m 条边的有向图，图中可能存在重边和自环，所有边权均为非负值。
// 请你求出 1 号点到 n 号点的最短距离，如果无法从 1 号点走到 n 号点，则输出 -1。

// 输入输出格式 ：
// 输入
// 第一行包含整数 n 和 m。
// 接下来 m 行每行包含三个整数 x,y,z，表示存在一条从点 x 到点 y 的有向边，边长为 z。

// 输出
// 输出一个整数，表示 1 号点到 n 号点的最短距离。
// 如果路径不存在，则输出 -1。

// 样例：
// 输入
// 3 3
// 1 2 2
// 2 3 1
// 1 3 4

// 输出
// 3

#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

typedef pair<int, int> PII; // 定义一个pair类型，第一个元素是距离，第二个元素是点的编号

const int N = 100010;

int n, m; // n个点，m条边
int h[N], e[N], ne[N], w[N], idx; // h是邻接表的头结点，e是边的终点，ne是下一条边的编号，w是边的权重，idx是边的编号
int dist[N]; // 存储1号点到每个点的最短距离
bool st[N]; // 存储每个点是否已经确定了距离

void add(int a, int b, int c) // 添加一条边a->b，权重为c
{
    
    // 这样子想：h[a]是一个链表，链表的头结点是h[a]，头结点的下一个是起点结点是ne[idx]，即ne[h[a]]，头结点的下一个的下一个结点是ne[ne[h[a]]]，以此类推
    // 其中e[idx]是起点对应的终点，w[idx]是权重，可以看成起点的2个内容元素。
    e[idx] = b;
    // cout << "e[" << idx << "] = " << b << endl;
    w[idx] = c;
    // cout << "w[" << idx << "] = " << c << endl;
    ne[idx] = h[a];
    // cout << "ne[" << idx << "] = " << h[a] << endl;
    h[a] = idx;
    // cout << "h[" << a << "] = " << idx << endl;
    idx++;
    // cout << "idx = " << idx << endl;
}

int dijkstra()
{
    memset(dist, 0x3f, sizeof dist); 
    dist[1] = 0;

    priority_queue<PII, vector<PII>, greater<PII>> heap; // 定义一个小根堆，存储距离和点的编号
    heap.push({0, 1}); // 把距离为0的1号点加入堆中

    while (heap.size())// while堆不为空
    {
        auto t = heap.top(); // 每次找到距离最小的点，也就是堆顶元素
        heap.pop(); // 弹出堆顶元素

        int ver = t.second, distance = t.first; // ver是点的编号，distance是距离
        
        if (st[ver]) continue; // 如果这个点已经被确定了距离，就跳过
        // 比如有2条路被记录到堆中，一条是{4, 3}，{5, 3}，前者是{ 距离为4 , 起点到点3 }，后者是{ 距离为5 , 起点到点3}
        // 由于小根堆的特性，{4, 3}会被先取出，这是一切正常运行，st[3]会从false标记成true，然后堆里剩下的那个{5, 3}就没有了意义，等到{5, 4}时就会直接continue
        st[ver] = true;

        for (int i = h[ver]; i != -1; i = ne[i]) // 遍历ver的所有出边
        {
            int j = e[i]; // j是ver的出边的终点
            if (dist[j] > distance + w[i]) // 如果j的距离大于ver的距离加上ver到j的权重
            {
                dist[j] = distance + w[i]; // 更新j的距离
                heap.push({dist[j], j}); // 把j加入堆中
            }
        }
    }


    if (dist[n] == 0x3f3f3f3f) return -1;  // 如果dist[n] == 0x3f3f3f3f，说明1号点到n号点没有路径，返回-1
        
    return dist[n]; // 返回1号点到n号点的最短距离
}

int main()
{
    scanf("%d%d", &n, &m);

    memset(h, -1, sizeof h); // 初始化邻接表

    while (m--)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c); // 添加一条边a->b，权重为c
    }

    int t = dijkstra();

    printf("%d\n", t);

    return 0;
}