// 二分图

// 学算法 -> 遵循实用主义

// 二分图
//  1.**染色法(本质上就是一个简单的dfs)        O(n + m)
//      注：可以用来判断一个图是否是二分图
//  2.匈牙利算法                            一般是O(m)，最坏是O(nm)

//  二分图的性质：
//      1.二分图不存在奇数环

//  染色法个人理解：相邻的点被染色成不同的颜色，若是存在矛盾，就证明不是二分图
//      1.首先我们要明确一点：二分图是一个图，其中的点可以被分为两个集合，使得所有的边都只出现在集合之间。
//      2.我们可以用一个数组来存储每个点的颜色，用0表示未染色，1表示染成了红色，2表示染成了蓝色。
//      3.我们可以用一个dfs来遍历整个图，对于每个点，如果它没有被染色，我们就将它染成红色，然后将它的所有邻接点染成蓝色。
//      4.如果某个点已经被染色了，我们就判断它的颜色是否和它的邻接点的颜色相同，如果相同，就说明这个图不是二分图。
//      5.如果某个点没有被染色，我们就将它染成红色，然后将它的所有邻接点染成蓝色。
//      6.如果某个点已经被染色了，我们就判断它的颜色是否和它的邻接点的颜色相同，如果相同，就说明这个图不是二分图。

// ACwing 860 - 染色法判断二分图（染色法）
// 题目描述
// 给定一个n个点m条边的无向图，图中可能存在重边和自环。
// 请你判断这个图是否是二分图。

// 输入格式
// 第一行包含两个整数n和m。
// 接下来m行，每行包含两个整数u和v，表示点u和点v之间存在一条边。

// 输出格式
// 如果给定图是二分图，则输出“Yes”，否则输出“No”。

// 数据范围
// 1 ≤ n, m ≤ 10^5

// 输入样例：
// 4 4
// 1 3
// 1 4
// 2 3
// 2 4

// 输出样例：
// Yes

// 题目大意：
// 输入n m 表示n 个顶点 m 条边，可能有重边和自环。判断该图是不是一个二分图。

#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

const int N = 100010, M = 200010; // 这个图是无向图，边数 * 2

int n, m;
int h[N], e[M], ne[M], idx;
int color[N];

void add(int a, int b)
{
    e[idx] = b;
    ne[idx] = h[a]; 
    h[a] = idx;
    idx++;
}

bool dfs(int u, int c)
{
    color[u] = c;

    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(!color[j])
        {
            if(!dfs(j, 3 - c)) return false;
        }
        else if(color[j] == c) return false;
    }

    return true;
}

int main()
{
    scanf("%d%d", &n, &m);

    memset(h, -1, sizeof h);

    while(m--)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b), add(b, a);
    }

    bool flag = true;
    for(int i = 1; i <= n; i++)
    {
        if(color[i] == 0)
        {
            color[i] = 1;
            if(!dfs(i, 1))
            {
                flag = false;
                return 0;
            }
        }
    }

    if(flag) puts("Yes");
    else puts("No");

    return 0;
}
