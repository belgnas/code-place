// 爱...你...喵...

// 小红的陡峭值（四）

// 知识点：深度优先遍历、邻接表

// https://ac.nowcoder.com/acm/contest/103152/E
#include<iostream>
#include<cstring>
#include<cmath>

using namespace std;

const int N = 100010, M = N * 2; // 因为是无向图，所以 M = 2 * N

int n;
long long ans = 1e18;
int h[N], e[M], ne[M], idx; // h：头结点 e：当前节点所指向的终点（是用来跳转到其他链表开头的） ne：下个节点的所对应的idx编号（是用来跳转到当前链表的下一个结点的） idx：保证节点地址唯一
long long sub[N]; // sub 数组表示以u为根的子树的陡峭值

void add(int a, int b)
{
    // e就是当前节点的一个数据，可以用它跳转到下一个链表的开头，
    e[idx] = b; // 当前idx编号对应的指向的终点是b(相邻的！！)
    ne[idx] = h[a]; // 当前idx编号对应的指向的终点的编号是原先h[a]指向的编号
    h[a] = idx; // 更新当前头结点h[a]的指向的idx编号
    idx++; // 保证idx编号唯一
}

void dfs1(int u, int f)  
{
    // u 代表当前正在访问的节点编号
    // f 代表当前节点 u 的父节点编号

    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == f)
        {
            continue;
        }
        dfs1(v, u);
        
        sub[u] += sub[v] + abs(v - u);
    }
}

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

    memset(h, -1, sizeof h);
    memset(sub, 0, sizeof sub); // 初始化为 0 是为了方便后续通过累加手段来更新陡峭值

    // 读取 n-1 条边，构建邻接表
    for(int i = 0; i < n - 1; i++)
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