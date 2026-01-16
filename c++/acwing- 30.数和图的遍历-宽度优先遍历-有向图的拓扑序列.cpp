// 树和图的遍历-宽度优先搜索

// AcWing 848. 有向图的拓扑序列 ：拓扑序列就是从前指向后的边的序列（不是所有边都有拓扑序列的）（可以证明一个有向无环图是一定存在一个拓扑序列的，所以有向无环图也被称为拓扑图）

// 题目描述
// 给定一个 n 个点 m 条边的有向图，点的编号是 1 到 n，图中可能存在重边和自环。
// 请输出任意一个该有向图的拓扑序列，如果拓扑序列不存在，则输出 ?1。
// 若一个由图中所有点构成的序列 A 满足：对于图中的每条边 (x,y)，x 在 A 中都出现在 y 之前，则称 A 是该图的一个拓扑序列。

// 输入格式
// 第一行包含两个整数 n 和 m。
// 接下来 m 行，每行包含两个整数 x 和 y，表示存在一条从点 x 到点 y 的有向边 (x,y)。

// 输出格式
// 共一行，如果存在拓扑序列，则输出任意一个合法的拓扑序列即可。
// 否则输出-1。

// 数据范围
// 1 ≤ n, m ≤ 10^5

// 输入样例：
// 3 3
// 1 2
// 2 3
// 1 3

// 输出样例：
// 1 2 3

// 思路：将入度为0的点入列，再删去该点指向的所有边，再将入度为0的点入列，直到所有点都入列，若所有点都入列，则该序列是一个拓扑序列，否则该序列不存在拓扑序列。

// 入度：是指指向该点的边的数量（所以所有入度为0的点都可以排在最前面的位置）
// 出度：是指从该点出发的边的数量

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 100010;

int n, m;
int h[N], e[N], ne[N], idx;
int q[N], d[N];

void add(int a, int b)
{
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx;
    idx++;
}

bool topsort()
{
    int hh = 0, tt = -1;

    for (int i = 1; i <= n; i++)
        if (!d[i])
            q[++tt] = i;

    while (hh <= tt)
    {
        int t = q[hh++];

        for (int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            d[j]--;
            if (d[j] == 0)
            {
                q[++tt] = j;
            }
        }
    }

    return tt == n - 1;
}

int main()
{
    cin >> n >> m;

    memset(h, -1, sizeof h);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        add(a, b);
        d[b]++;
    }

    if (topsort())
    {
        for (int i = 0; i < n; i++)
            cout << q[i] << ' ';
    }
    else
        puts("-1");

    return 0;
}