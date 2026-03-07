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
//          **(a).Bellman-Ford算法        O(nm)  // ps：如果能求出来最短路，那么这个图里是没有负权回路的 所以会限制循环的次数，也就是最多走多少次
//              比较适合 存在负权边 的图
//          (b).SPFA算法                O(m)
//              一般 O(m), 最坏 O(nm)
//  2.多源汇最短路（求的是任意两点之间的最短距离）
//      (1).Floyd算法                   O(n^3)

// 一些名词：
//  dist[b] = min(dist[b], dist[a] + w); // 松弛操作
//  dist[b] <= dist[a] + w; // 三角不等式

// Bellman-Ford算法
// 模板：
// int n, m;       // n表示点数，m表示边数
// int dist[N];        // dist[x]存储1到x的最短路距离

// struct Edge     // 边，a表示出点，b表示入点，w表示边的权重
// {
//     int a, b, w;
// }edges[M];

// // 求1到n的最短路距离，如果无法从1走到n，则返回-1。
// int bellman_ford()
// {
//     memset(dist, 0x3f, sizeof dist);
//     dist[1] = 0;

//     // 如果第n次迭代仍然会松弛三角不等式，就说明存在一条长度是n+1的最短路径，由抽屉原理，路径中至少存在两个相同的点，说明图中存在负权回路。
//     for (int i = 0; i < n; i ++ )
//     {
//         for (int j = 0; j < m; j ++ )
//         {
//             int a = edges[j].a, b = edges[j].b, w = edges[j].w;
//             if (dist[b] > dist[a] + w)
//                 dist[b] = dist[a] + w;
//         }
//     }

//     if (dist[n] > 0x3f3f3f3f / 2) return -1;
//     return dist[n];
// }


// 题目描述
// 给定一个 n 个点 m 条边的有向图，图中可能存在重边和自环， 边权可能为负数。

// 请你求出从 1 号点到 n 号点的最多经过 k 条边的最短距离，如果无法从 1 号点走到 n 号点，输出 impossible。
// 注意：图中可能 存在负权回路 。

// 输入格式
// 第一行包含三个整数 n,m,k。
// 接下来 m 行，每行包含三个整数 x,y,z，表示存在一条从点 x 到点 y 的有向边，边长为 z ，点的编号为 1?n。

// 输出格式
// 输出一个整数，表示从 1号点到 n 号点的最多经过 k 条边的最短距离。
// 如果不存在满足条件的路径，则输出 impossible。

// 数据范围
// 1≤n,k≤500, 1≤m≤10000,1≤x,y≤n
// 任意边长的绝对值不超过 10000

// 输入样例：
// 3 3 1
// 1 2 1
// 2 3 1
// 1 3 3

// 输出样例：
// 3

#include<iostream>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

const int N = 510, M = 10010;

int n, m, k;
int dist[N], backup[N];

struct Edge
{
    int a, b, w;
}edges[N]; // 这里edges[N]是一个数组，数组的元素是Edge类型的结构体

int bellman_ford()
{
    memset(dist, 0x3f, sizeof dist); // 初始化dist数组
    dist[1] = 0; // 1号点到1号点的距离为0

    for(int i = 0; i < k; i++)
    {
        memcpy(backup, dist, sizeof dist); // 备份dist数组
        // 为什么要备份dist数组？
        // 因为我们要更新dist数组，但是我们要保证更新dist数组的时候，dist数组中的值是上一次迭代的结果，而不是本次迭代的结果
        for(int j = 0; j < m; j++)
        {
            int a  = edges[j].a, b = edges[j].b, w = edges[j].w;
            dist[b] = min(dist[b], backup[a] + w); // 更新dist数组
        }
    }

    if(dist[n] > 0x3f3f3f3f / 2) return -1; // 如果dist[n]大于(一个量级很大的数) 0x3f3f3f3f / 2，说明最短路不存在
    return dist[n]; // 否则，返回dist[n]
    
}

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    
    for(int i = 0; i < m; i++)
    {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        edges[i] = {a, b, w};
    }

    int t = bellman_ford();

    if(t == -1) puts("impossible"); // 如果最短路不存在，输出impossible
    else printf("%d\n", t); // 否则，输出最短距离

    return 0;
}