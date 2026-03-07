#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

typedef pair<int, int> PII;

const int N = 100010;

int n, m;
int h[N], e[N], ne[N], w[N], idx;
int dist[N];
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

int dijkstra()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.push({0, 1}); // 把距离为0的1号点加入堆中

    while(heap.size())
    {
        auto t = heap.top();
        heap.pop();

        int ver = t.second, distance = t.first;
        
        if(st[ver]) continue; // 
        st[ver] = true;

        for(int i = h[ver]; i != -1; i = ne[i])
        {
            int j = e[i];
            if(dist[j] > distance + w[i])
            {
                dist[j] = distance + w[i];
                heap.push({dist[j], j});
            }
        }
    }

    if(dist[n] == 0x3f3f3f3f) return -1;

    return dist[n];
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

    int t = dijkstra();

    cout << t << endl;

    return 0;
}