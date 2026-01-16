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
//          (b).SPFA算法                O(m)
//              一般 O(m), 最坏 O(nm)
//  2.多源汇最短路（求的是任意两点之间的最短距离）
//      **(1).Floyd算法                  O(n^3)

// 题目来源：AcWing 854. Floyd算法求最短路
// 题目描述：
// 给定一个 n 个点 m 条边的有向图，图中可能存在重边和自环，边权可能为负数。
// 再给定 k 个询问，每个询问包含两个整数 x 和 y，表示查询从点 x 到点 y 的最短距离，
// 如果路径不存在，则输出 impossible。
// 数据保证图中不存在负权回路。

// 输入输出格式：

// 输入
// 第一行包含三个整数 n,m,k。
// 接下来 m 行，每行包含三个整数 x,y,z，表示存在一条从点 x 到点 y 的有向边，边长为 z。
// 接下来 k 行，每行包含两个整数 x,y，表示询问点 x 到点 y 的最短距离。

// 输出
// 共 k 行，每行输出一个整数，表示询问的结果，若询问两点间不存在路径，则输出 impossible。

// 数据范围
// 1 ≤ n ≤ 200
// 1 ≤ k ≤ n^2
// 1 ≤ m ≤ 20000
// 图中涉及边长绝对值均不超过10000。

// 输入输出样例：

// 输入
// 3 3 2
// 1 2 1
// 2 3 2
// 1 3 1
// 2 1
// 1 3

// 输出
// impossible
// 1

#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

const int N = 210, INF = 1e9;

int n, m, Q; // n个点，m条边，Q个询问
int d[N][N]; // d是邻接矩阵，d[i][j]表示从i到j的最短距离

void floyd()
{
    for(int k = 1; k <= n; k++) // 枚举中间点
        for(int i = 1; i <= n; i++) // 枚举起点
            for(int j = 1; j <= n; j++) // 枚举终点
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]); // 松弛操作
}

int main()
{
    scanf("%d%d%d", &n, &m, &Q);

    // 初始化邻接矩阵，将所有点到自己的距离初始化为0，其他点到自己的距离初始化为无穷大
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            if(i == j) d[i][j] = 0;
            else d[i][j] = INF;

    while(m--)
    {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);

        d[a][b] = min(d[a][b], w); // 有重边，只保留最短的边
    }

    floyd();

    // 处理询问
    while(Q--)
    {
        int a, b;
        scanf("%d%d", &a, &b);

        if(d[a][b] > INF / 2) puts("impossible"); // 如果距离大于INF/2，说明没有路径
        else printf("%d\n", d[a][b]);
    }

    return 0;
}