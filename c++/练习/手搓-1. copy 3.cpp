#include <bits/stdc++.h>
using namespace std;

#define IOS ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

#define INF 0x3f3f3f3f

const int N = 210;

int nex[N], floor_min[N]; // k数组存储每层可移动步数，floor_min数组存储最短步数
int n, st, ed;

void dfs(int floor, int step)
{
    floor_min[floor] = step; // 记录当前路径到达该节点的步数（一定是更优的才会进入）

    // 向下移动
    if (floor - nex[floor] >= 1 && step + 1 < floor_min[floor - nex[floor]]) // 若向下移动合法且步数更优
    {
        dfs(floor - nex[floor], step + 1);
    }

    // 向上移动
    if (floor + nex[floor] <= n && step + 1 < floor_min[floor + nex[floor]]) // 若向上移动合法且步数更优
    {
        dfs(floor + nex[floor], step + 1);
    }
}

int main()
{
    IOS;
    memset(floor_min, INF, sizeof(floor_min)); // 初始化最短步数为无穷大

    cin >> n >> st >> ed; // 输入总楼层数、起点、终点
    for (int i = 1; i <= n; i++)
        cin >> nex[i];

    floor_min[st] = 0; // 起点步数为0（初始位置无需移动）
    dfs(st, 0);  // 从起点开始搜索

    cout << (floor_min[ed] == INF ? -1 : floor_min[ed]) << endl;

    return 0;
}