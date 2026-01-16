// acwing- 32.最小生成树2-堆优化Prim算法

// 最小生成树
//  1.普利姆算法(Prim)
//      (1).朴素版Prim算法       O(n^2)   ---------- 适合稠密图
//      (2).堆优化版Prim算法     O(mlogn)  ---------- 适合稀疏图
//  2.**克鲁斯卡尔算法(Kruskal)    O(mlogm)  ---------- 适合稀疏图

// (稀疏图一般用Kruskal，因为相较于 堆优化版Prim ，代码更简单，思路更清晰）

// Kruskal算法
// 1.将所有边按权重从小到大排序  O(mlogm) 
//      这一步是Kruskal算法的瓶颈，决定了Kruskal算法的时间复杂度
// 2.枚举每条边 a, b, w   O(m)
//      如果 a, b 不连通，将这条边加入到集合中
//   为什么呢？
//      因为如果 a, b 连通，那么将 a, b 连起来，会形成一个环，那么环中一定存在一条边的权重大于等于 a, b 之间的边的权重。


// 题目来源：AcWing 859. Kruskal算法求最小生成树

// 一、题目描述
// 给定一个 n 个点 m 条边的无向图，图中可能存在重边和自环，边权可能为负数。
// 求最小生成树的树边权重之和，如果最小生成树不存在则输出 impossible。
// 给定一张边带权的无向图 G = ( V , E ) G=(V,E)G=(V,E)，其中 V 表示图中点的集合，E 表示图中边的集合，n=|V|, m=|E|。
// 由 V 中的全部 n 个顶点和 E 中 n-1 条边构成的无向连通子图被称为 G 的一棵生成树，其中边的权值之和最小的生成树被称为无向图 G 的最小生成树。

// 输入格式
// 第一行包含两个整数 n 和 m。
// 接下来 m 行，每行包含三个整数 u,v,w ，表示点 u 和点 v 之间存在一条权值为 w 的边。

// 输出格式
// 共一行，若存在最小生成树，则输出一个整数，表示最小生成树的树边权重之和，如果最小生成树不存在则输出 impossible。

// 数据范围
// 1 ≤ n ≤ 10^5, 1 ≤ m ≤ 2*10^5
// 图中涉及边的边权的绝对值均不超过 1000。

// 输入样例：
// 4 5
// 1 2 1
// 1 3 2
// 1 4 3
// 2 3 2
// 3 4 4

// 输出样例：
// 6

// 二、最小生成树 Kruskal算法
// Kruskal算法非常简单：
// 将所有边按权重从小到大排序           (这也是该算法时间复杂度瓶颈：O(mlogm) )
// 枚举每条边 a→b ，权重是 c 。如果当前 a, b 不在一个集合中，则将该边加入集合中（并查集）。


#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 200010;

int n, m;
int p[N];

struct Edge
{
    int a, b, w;

    bool operator< (const Edge &W) const
    {
        return w < W.w; // 从小到大排序
    }

}edges[N];

int find(int x)
{
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int main()
{
    scanf("%d%d", &n, &m);

    for(int i = 0; i < m; i++)
    {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        edges[i] = {a, b, w};
    }

    sort(edges, edges + m);

    for(int i = 1; i <= n; i++)
    {
        p[i] = i;
    }

    int res = 0, cnt = 0; // res 是最小生成树的树边权重之和，cnt 是最小生成树的边数
    // 因为最小生成树的边数是 n - 1，所以当 cnt == n - 1 时，最小生成树就已经构造完毕了。

    // 枚举每条边
    for(int i = 0; i < m; i++)
    {
        int a = edges[i].a;
        int b = edges[i].b;
        int w = edges[i].w;

        a = find(a); // 找到 a 的祖宗节点
        b = find(b); // 找到 b 的祖宗节点

        if(a != b) // 如果 a, b 不在一个集合中
        {
            res += w;
            cnt++;
            p[a] = b; // 将 a 的祖宗节点指向 b 的祖宗节点
        }
    }

    if(cnt < n - 1) puts("impossible"); // 如果加的边数小于 n-1 的话，说明这个连通图是不连通的
    else printf("%d\n", res); // 否则输出最小生成树的树边权重之和

    return 0;
}