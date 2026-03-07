#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)

typedef pair<int, int> PII;

const int N = 100010;
const int INF = 0x3f3f3f3f;  // [新增] 定义无穷大常量

int n, m, q;
int h[N], e[N << 1], ne[N << 1], w[N << 1], idx;  // [修改] 边数组大小翻倍（无向边需要双倍空间）
int dist[N];
bool st[N];

// [修改] 合并双向边的添加，确保每条边同时添加 a->b 和 b->a
void add(int a, int b, int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
    e[idx] = a;
    w[idx] = c;
    ne[idx] = h[b];
    h[b] = idx++;
}

void dijkstra() {
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.push({0, 1});
    
    while (heap.size()) {
        auto t = heap.top();
        heap.pop();
        int ver = t.second, distance = t.first;
        if (st[ver]) continue;
        st[ver] = true;
        for (int i = h[ver]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dist[j] > distance + w[i]) {
                dist[j] = distance + w[i];
                heap.push({dist[j], j});
            }
        }
    }
}

int main() {
    IOS;
    cin >> n >> m >> q;
    memset(h, -1, sizeof h);
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);  // [修改] 直接调用合并后的add函数，不再重复添加反向边
    }
    dijkstra();
    long long ans = 0;  // [修改] 使用long long防止累加溢出
    while (q--) {
        int school;
        cin >> school;
        ans += dist[school] * 2;  // [修改] 累加结果到long long类型
    }
    cout << ans << endl;
    return 0;
}