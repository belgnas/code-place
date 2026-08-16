// #include <bits/stdc++.h>
#include <iostream> // cin, cout, cerr - 标准输入输出流
#include <vector>   // vector - 动态数组（向量）

using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'

const int N = 2e5 + 10;

// 并查集
int fa[N];  // fa[i] 表示 i 的父节点
int rnk[N]; // rnk[i] 表示以 i 为根的树的秩（深度的上界）

// 初始化并查集
void init(int n)
{
    for (int i = 1; i <= n; i++)
    {
        fa[i] = i;   // 每个元素的父节点是自己
        rnk[i] = 0;  // 初始秩为 0
    }
}

// 查找根节点（带路径压缩）
int find(int x)
{
    if (fa[x] != x)
    {
        fa[x] = find(fa[x]); // 路径压缩：将路径上所有节点直接连到根节点
    }
    return fa[x];
}

// 合并两个集合（按秩合并）
void unite(int x, int y)
{
    int fx = find(x);
    int fy = find(y);

    if (fx == fy) return; // 已经在同一集合中

    // 按秩合并：将秩小的树连到秩大的树下
    if (rnk[fx] < rnk[fy])
    {
        fa[fx] = fy;
    }
    else if (rnk[fx] > rnk[fy])
    {
        fa[fy] = fx;
    }
    else
    {
        fa[fy] = fx;
        rnk[fx]++; // 秩相同时，秩加 1
    }
}

// 判断是否在同一集合
bool same(int x, int y)
{
    return find(x) == find(y);
}

signed main()
{
    IOS;

    int n, m;
    cin >> n >> m;

    init(n);

    for (int i = 0; i < m; i++)
    {
        int z, x, y;
        cin >> z >> x >> y;

        if (z == 1)
        {
            unite(x, y);
        }
        else
        {
            if (same(x, y))
            {
                cout << "Y" << endl;
            }
            else
            {
                cout << "N" << endl;
            }
        }
    }

    return 0;
}
