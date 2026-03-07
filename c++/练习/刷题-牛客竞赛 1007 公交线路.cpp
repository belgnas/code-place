// 刷题-牛客竞赛 1007 公交线路

// 知识点：spfa算法

// 难度：简单

// https://ac.nowcoder.com/acm/contest/26077/1007

#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

const int N = 100010;

int n, m;
int h[N], e[N], ne[N], w[N], idx;
int dist[N];
bool st[N];
int from, to;

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

int spfa()
{
    memset(dist, 0x3f, sizeof dist);
    dist[from] = 0;

    queue<int> q;
    q.push(from); // 把距离为0的1号点加入队列中
    st[from] = true; // 表示1号点在队列中

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
                if(!st[j]) // 如果j号点不在队列中
                {
                    q.push(j); // 把j号点加入队列中
                    st[j] = true; // 表示j号点在队列中
                }
            }
        }
    }

    if(dist[to] == 0x3f3f3f3f) return -1;
    return dist[to];
}

int main()
{
    cin >> n >> m;
    cin >> from >> to;

    memset(h, -1, sizeof h);

    while(m--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);;
    }

    int t = spfa();

    if(t == -1) cout << "-1" << endl;
    else cout << t << endl;

    return 0;
}