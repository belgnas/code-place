// 最短路


// 我们学编程不会让我们去数学证明，我们只需要知道结论，然后用代码去“实现”就好了，实际上就比的是记忆能力。

//（在每种情况下，都有各自的最优抉择）
// 分类：
//  1.单源最短路（求的是一个点到其他所有点的最短距离）
//      (1).所有边的权重都是正数
//          (a).朴素Dijkstra算法        O(n^2)
//              比较适合 稠密图
//          (b).堆优化版的Dijkstra算法  O(mlogn)
//              比较适合 稀疏图
//      (2).存在负权边
//          (a).Bellman-Ford算法        O(nm)
//              比较适合 存在负权边 的图
//          **(b).SPFA算法                O(m)  // ps：如果能求出来最短路，那么这个图里是没有负权回路的
//              一般 O(m), 最坏 O(nm)
//  2.多源汇最短路（求的是任意两点之间的最短距离）
//      (1).Floyd算法                   O(n^3)

// 一些名词：
//  dist[b] = min(dist[b], dist[a] + w); // 松弛操作
//  dist[b] <= dist[a] + w; // 三角不等式

// spfa 算法（队列优化的Bellman-Ford算法） —— 模板题 
// AcWing 851. spfa求最短路
// 时间复杂度是O(m)，一般情况下比Dijkstra算法要快，最坏情况下是O(nm)。 // 大部分情况下，正权图也可以用spfa算法。
// 注意：spfa算法不能处理负权回路，因为负权回路是没有最短路的。
// 模板：
// int n;      // 总点数
// int h[N], w[N], e[N], ne[N], idx;       // 邻接表存储所有边
// int dist[N];        // 存储每个点到1号点的最短距离
// bool st[N];     // 存储每个点是否在队列中

// // 求1号点到n号点的最短路距离，如果从1号点无法走到n号点则返回-1
// int spfa()
// {
//     memset(dist, 0x3f, sizeof dist);
//     dist[1] = 0;

//     queue<int> q;
//     q.push(1);
//     st[1] = true;

//     while (q.size())
//     {
//         auto t = q.front();
//         q.pop();

//         st[t] = false;

//         for (int i = h[t]; i != -1; i = ne[i])
//         {
//             int j = e[i];
//             if (dist[j] > dist[t] + w[i])
//             {
//                 dist[j] = dist[t] + w[i];
//                 if (!st[j])     // 如果队列中已存在j，则不需要将j重复插入
//                 {
//                     q.push(j);
//                     st[j] = true;
//                 }
//             }
//         }
//     }

//     if (dist[n] == 0x3f3f3f3f) return -1;
//     return dist[n];
// }

// 题目来源：AcWing 851. spfa求最短路

// 一、题目描述
// 给定一个 n 个点 m 条边的有向图，图中可能存在重边和自环， 边权可能为负数。
// 请你求出 1 号点到 n 号点的最短距离，如果无法从 1 号点走到 n 号点，则输出 impossible。
// 数据保证不存在负权回路。

// 输入格式
// 第一行包含整数 n 和 m。
// 接下来 m 行每行包含三个整数 x, y, z，表示存在一条从点 x  到点 y 的有向边，边长为 z。

// 输出格式
// 输出一个整数，表示 1 号点到 n 号点的最短距离。
// 如果路径不存在，则输出 impossible。

// 数据范围
// 1 ≤ n, m ≤ 10^5,图中涉及边长绝对值均不超过 10000。

// 输入样例：
// 3 3
// 1 2 5
// 2 3 -3
// 1 3 4

// 输出样例：
// 2

#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

const int N = 100010;

int n, m;
int h[N], e[N], ne[N], w[N], idx;
int dist[N];
bool st[N];

void add(int a, int b, int c)
{
    w[idx] = c;
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx;
    // 这样子想：h[a]是一个链表，链表的头结点是h[a]，头结点的下一个是起点结点是ne[idx]，即ne[h[a]]，头结点的下一个的下一个是起点结点是ne[ne[h[a]]]，以此类推
    // 其中e[idx]是起点对应的终点，w[idx]是权重，可以看成起点的2个内容元素。
    idx ++;
}

int spfa()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;

    queue<int> q;
    q.push(1); // 把距离为0的1号点加入队列中
    st[1] = true; // 表示1号点在队列中

    while(q.size())
    {
        int t = q.front();
        q.pop();

        st[t] = false; // 表示t号点不在队列中

        for(int i = h[t]; i != -1; i = ne[i]) // 更新t号点的所有出边
        {
            int j = e[i];
            if(dist[j] > dist[t] + w[i]) // 如果j号点的距离大于t号点的距离加上边权
            {
                dist[j] = dist[t] + w[i]; // 更新j号点的距离
                if(!st[j]) // 如果j号点不在队列中
                {
                    q.push(j); // 把j号点加入队列中
                    st[j] = true; // 表示j号点在队列中
                }
            }
        }
    }

    if(dist[n] == 0x3f3f3f3f) return -1;
    return dist[n];
}

int main()
{
    cin >> n >> m;

    memset(h, -1, sizeof h);

    while(m--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
    }

    int t = spfa();

    if(t == -1) cout << "impossible" << endl;
    else cout << t << endl;

    return 0;
}