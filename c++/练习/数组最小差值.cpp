#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

const int N = 100010, M = N * 2;
long long ans = 1e18;       // 记录最小差值，初始化为极大值
int n;                      // 节点总数
int h[N], e[M], ne[M], idx; // 邻接表相关数组
long long sub[N];           // sub[u] 表示以u为根的子树的陡峭值

// 添加边到邻接表
void add(int a, int b)
{
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

// 第一次DFS：计算以每个节点为根的子树的陡峭值
void dfs1(int u, int f)
{
    for (int i = h[u]; i != -1; i = ne[i])
    { // 遍历u的所有邻接节点
        int v = e[i];
        if (v == f)
            continue; // 跳过父节点，避免重复访问

        dfs1(v, u); // 递归计算子节点v的子树陡峭值

        // 当前边的陡峭值贡献是abs(v - u)
        // 加上子节点v的子树陡峭值，累加到父节点u的子树陡峭值中
        sub[u] += sub[v] + abs(v - u);
    }
}

// 第二次DFS：枚举断开每条边，计算两棵树陡峭值之差的绝对值
void dfs2(int u, int f)
{
    for (int i = h[u]; i != -1; i = ne[i])
    { // 遍历u的所有邻接节点
        int v = e[i];
        if (v == f)
            continue; // 跳过父节点

        // 断开边u-v后，以v为根的子树的陡峭值（不包含边u-v）
        long long childSteepness = sub[v];

        // 另一棵树的陡峭值 = 总陡峭值 - 子树v的陡峭值 - 边u-v的贡献
        long long parentSteepness = sub[1] - childSteepness - abs(u - v);

        // 计算两棵树陡峭值之差的绝对值
        long long diff = abs(childSteepness - parentSteepness);

        // 更新全局最小差值
        ans = min(ans, diff);

        dfs2(v, u); // 递归处理子节点v的邻接边
    }
}

int main()
{
    cin >> n;

    // 初始化邻接表
    memset(h, -1, sizeof h);
    memset(sub, 0, sizeof sub);

    // 读取n-1条边，构建邻接表
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        add(a, b); // 添加双向边
        add(b, a);
    }

    // 第一次DFS：计算所有子树的陡峭值（根节点为1）
    dfs1(1, -1);

    // 第二次DFS：枚举所有边，计算最小差值
    dfs2(1, -1);

    cout << ans << endl;
    return 0;
}