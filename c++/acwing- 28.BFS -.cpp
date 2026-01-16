// 深度优先搜索(DFS) && 广度优先搜索(BFS)

// 广度优先搜索

// 深搜是没有模板的，但是宽搜有
// 不是所有的最短路问题都可以用BFS来做。只有所有边的权重都一样时才可以，有专门的最短路算法
// BFS（宽搜），可以看成一种特殊的DP

// acwing——844. 走迷宫
// 给定一个n*m的二维整数数组，用来表示一个迷宫，数组中只包含0或1，其中0表示可以走的路，1表示不可通过的墙壁。
// 最初，有一个人位于左上角(1, 1)处，已知该人每次可以向上、下、左、右任意一个方向移动一个位置。
// 请问，该人从左上角移动至右下角(n, m)处，至少需要移动多少次。
// 数据保证(1, 1)处和(n, m)处的数字为0，且一定至少存在一条通路。

// 输入格式
// 第一行包含两个整数n和m。
// 接下来n行，每行包含m个整数（0或1），表示完整的二维数组迷宫。

// 输出格式
// 输出一个整数，表示从左上角移动至右下角的最少移动次数。

// 数据范围
// 1 ≤ n, m ≤ 100

// 输入样例：
// 5 5
// 0 1 0 0 0
// 0 1 0 1 0
// 0 0 0 0 0
// 0 1 1 1 0
// 0 0 0 1 0

// 输出样例：
// 8

#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

typedef pair<int, int> PII;

const int N = 110;

int n, m;
int g[N][N]; // g数组存的是这个地图
int d[N][N]; // d数组存的是每个点到起点的距离
PII q[N * N], Prev[N][N]; // Prev数组是用来记录路径的

int bfs()
{
    int hh = 0, tt = 0; // hh是队头，tt是队尾
    q[0] = {0, 0};

    memset(d, -1, sizeof d); // 先将d数组初始化为-1

    d[0][0] = 0; // 表示起点走过了（起点到起点的距离为0）

    int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1}; // x 方向的向量和 y 方向的向量组成的上、右、下、左

    while(hh <= tt)
    {
        auto t = q[hh ++];

        for(int i = 0; i < 4; i++)
        {
            int x = t.first + dx[i]; // x表示沿着此方向走会走到哪个点
            int y = t.second + dy[i]; // y表示沿着此方向走会走到哪个点

            if(x >= 0 && x < n && y >= 0 && y < m && g[x][y] == 0 && d[x][y] == -1) // 在边界内 并且是空地可以走 且之前没有走过
            {
                d[x][y] = d[t.first][t.second] + 1;
                Prev[x][y] = t; // 记录每个点是从哪个点走来的
                q[++ tt] = {x, y};
            }
        }
    }

    // 这下面这几行是输出路径（是从终点回溯到起点，所以输出的路径是逆序的）
    int x = n - 1, y = m - 1;
    while(x || y)
    {
        cout << x << " " << y << endl;
        auto t = Prev[x][y];
        x = t.first, y = t.second;
    }

    return d[n - 1][m - 1];
}

int main()
{
    cin >> n >> m;

    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> g[i][j];

    cout << bfs() << endl;

    return 0;
}