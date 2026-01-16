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
//          **(b).SPFA算法                O(m)  可以用来判断是否有复环图
//              一般 O(m), 最坏 O(nm)
//  2.多源汇最短路（求的是任意两点之间的最短距离）
//      (1).Floyd算法                   O(n^3)


// 题目来源：AcWing 852. spfa判断负环

// 一、题目描述
// 给定一个 n 个点 m 条边的有向图，图中可能存在重边和自环，边权可能为负数。
// 请你判断图中是否存在负权回路。

// 输入格式
// 第一行包含整数 n 和 m。

// 接下来 m 行每行包含三个整数 x,y,z，表示存在一条从点 x 到点 y 的有向边，边长为 z。

// 输出格式
// 如果图中存在负权回路，则输出 Yes，否则输出 No。

// 数据范围
// 1 ≤ n ≤ 2000, 1 ≤ m ≤ 10000
// 图中涉及边长绝对值均不超过 10000。

// 输入样例：
// 3 3
// 1 2 -1
// 2 3 4
// 3 1 -4

// 输出样例：
// Yes

#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

const int N = 100010;

int n, m;
int h[N], e[N], ne[N], w[N], idx;
int dist[N], cnt[N];
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

bool spfa()
{
    queue<int> q;
    for(int i = 1; i <= n; i++) // 我们一开始需要把所有点都加入队列中，然后从每个点开始判断是否有负环
    {
        q.push(i);
        st[i] = true;
    }

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
                cnt[j] = cnt[t] + 1; // 更新j号点的入队次数

                if(cnt[j] >= n) return true; // 如果j号点的入队次数大于等于n，则说明存在负环

                if(!st[j]) // 如果j号点不在队列中
                {
                    q.push(j); // 把j号点加入队列中
                    st[j] = true; // 表示j号点在队列中
                }
            }
        }
    }

    return false;
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

    if(spfa()) puts("Yes");
    else puts("No");

    return 0;
}