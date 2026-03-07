#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

typedef pair<int, int> PII;

const int N = 510;

int n, m;
int g[N][N];
int dist[N];
bool st[N];

int dijkstra()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;

    for(int i = 0; i < n - 1; i++)// 为什么是n - 1次？
    // 因为我们是要找到1号点到n号点的最短距离，所以我们要找n - 1次
    {
        int t = -1;
        cout << "int t = -1;" << endl;

        for(int k = 1; k <= n; k++)
        {
            cout << "dist[" << k << "] = " << dist[k] << endl;
        }

        // 下面这个 for 的意思就是：在不在s中的点中（距离还没有确定距离，即st[j]为false的第一个点），找到距离最近的点t
        for(int j = 1; j <= n; j++)
        {


            if(!st[j] && (t == -1 || dist[t] > dist[j]))
            // 一共有3个条件
            // 1. j不在s中，即st[j]为false，意味着j是第一次被选出来
            // 2. t是第一个点，即t == -1
            // 3. dist[t] > dist[j]，即t的距离大于j的距离
            // 这3个条件都满足，就把j赋值给t
            {
                cout << "if(!st[j] && (t == -1 || dist[t] > dist[j]))" << endl;
                t = j;
            }
            else
            {
                cout << "else" << endl;
            }
        }

        // 可以选加的优化
        // if(t == n) break; 


        st[t] = true;
        cout << "st[t] = true;" << endl;

        for(int j = 1; j <= n; j++)
        {
            dist[j] = min(dist[j], dist[t] + g[t][j]);
            cout << "dist[j] = min(dist[j], dist[t] + g[t][j]);" << endl;
        }
    }

    // 这时已经得到了1号点（起点）到每个点的最短距离

    if(dist[n] == 0x3f3f3f3f) return -1;

    for(int k = 1; k <= n; k++)
    {
        cout << "dist[" << k << "] = " << dist[k] << endl;
    }

    cout << "return dist[n];" << endl;
    return dist[n];
}

int main()
{
    scanf("%d%d", &n, &m);

    memset(g, 0x3f, sizeof g);

    while (m--)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        g[a][b] = min(g[a][b], c);
    }

    int t = dijkstra();

    printf("%d\n", t);

    return 0;
}