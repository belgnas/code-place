#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <string>
#include <vector>
#include <cstring>
#include <set>
#include <tuple>
#include <bitset>
#include <utility>
#include <queue> // 队列
#include <deque> // 双端队列

using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define endl '\n'

const int INF = 0x3f3f3f3f;

signed main()
{
    IOS;
    
    int t;
    cin >> t;
    while(t--)
    {
        // 转换成计算操作结束后在坐标轴中每个区间的长度总和的尽可能小的值（求绝对值之和转化成求长度之和）
        // 前者的操作为选择2个索引
        // 后者的操作为将2个索引的2对数字所能组成的最小绝对值之和的排列
        // （后者的操作可以理解成：将4个数字看成数轴上的4个点组成的2个线段，这2个线段原本的长度和就是绝对值之和，而后者的会让2个线段出现重叠的部分，让这4个点组成的2个线段的长度和最大）
        // （当然，很关键的一点是，前者会选择在原本就存在重叠部分的4个点的索引，好让后者的操作无效化）（若是没有存在重叠部分的4个点，也会选择重叠区域尽可能小的索引）
        int n, k;
        cin >> n >> k;
        // 将每组ai和bi存进pair数组里
        vector<pair<int, int>> arr(n);
        for(int i = 0; i < n; i++)
            cin >> arr[i].first;
        for(int i = 0; i < n; i++)
            cin >> arr[i].second;

        // 测试
        // for(int i = 0; i < n; i++)
        // {
        //     cout << arr[i].first << " " << arr[i].second << endl;
        // }
        // cout << endl;

        // 计算绝对值的总和
        int ans = 0;
        for(int i = 0; i < n; i++)
        {
            if(arr[i].first > arr[i].second) swap(arr[i].first, arr[i].second); // 保证arr[i].first对应在坐标轴中的每个小区间的左端点，arr[i].second对应在坐标轴中的每个小区间的右端点
            ans += abs(arr[i].first - arr[i].second);
        }

        // 排序（按照arr[i].first的大小从小到大排序）
        // （目的是为了判断是否存在重叠区间（让后者无法增加差值），并计算相邻区间的真实间隙（用于确定最大可能的差值增量））
        sort(arr.begin(), arr.end());

        // 如果出现了能够重叠的4个点的索引（意味着前者可以每次都选择这4个点，让后者的操作无效化，所以可以直接输出ans了）
        int flat = false;
        for(int i = 1; i < n; i++)
        {
            if(arr[i].first <= arr[i - 1].second)
            {
                cout << ans << endl;
                flat = true;
                break;
            }
        }
        if(flat) continue;

        // 但是如果没有出现重叠的4个点，前者就会选择尽可能小的间隙的4个点，后者会将这些点改成重叠的线段，但然后接下来每次都选择这4个点让后者第二次及以后的操作无效化
        int mn = INF; // 初始化间隙为一个很大的值，方便找到最小的间隙
        for(int i = 1; i < n; i++)
        {
            mn = min(mn, arr[i].first - arr[i - 1].second);
        }

        // ans要加2倍的间隙是因为间隙变成了重叠的部分，所以需要2倍
        ans = ans + mn * 2;

        cout << ans << endl;

    }
    
    return 0;
}