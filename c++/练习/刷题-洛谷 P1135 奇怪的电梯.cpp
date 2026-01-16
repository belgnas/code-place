// 题目名称:字符串的展开

// 时间:2025年4月19日

// 知识点:dfs、diikstra..(应该有好多种解法)

// 网址:洛谷 P1135 奇怪的电梯 

// 来源:散题

// 个人感想:一道很好写，但是超超超难优化的，dfs题喵(应该还有其他的解法的说)

// 思路:
// 刚开始写的时候花了不到20分钟就写了一个简单的dfs，果不其然STL了，于是开始想方设法优化减枝，先是尝试了能不能通过判。断当前楼层到达的次数是否大于2来判断，发现完全没用，并且因为我的回湖出了问题导致反而通过的数据减少了，后来，我突然发现这题完全可以看成dikstra来写，于是参考了dikstra(记录一个点到其他所有点的最短距离)的思路，经过一番调试才写出来了，总用时大概1h。

// 收获:(有的话就写)
// 没有语法上的收获

// 埋坑:要不我们再写个bfs和dijkstra的版本?

#include <bits/stdc++.h>
using namespace std;

#define IOS ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

#define INF 0x3f3f3f3f

const int N = 210;

int nex[N], floor_min[N]; // nex数组存储每层可移动的层数，floor_min数组存储起点到每一层的最短步数
int n, st, ed;

void dfs(int floor, int step)
{
    floor_min[floor] = step; // 记录当前路径到达该楼层的步数（一定是更优的才会进入）

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

    cout << (floor_min[ed] == INF ? -1 : floor_min[ed]) << endl; // 看了题解后果断放弃了自己单纯的if-else判断

    return 0;
}
