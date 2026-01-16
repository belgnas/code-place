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
    
    int n;
    cin >> n;
    vector<pair<pair<int,int>, pair<int, int>>> arr(n);
    for(int i = 0; i < n; i++)
    {
        int a, b, c, d; // 左上角坐标(a, b) 长度c 宽度d
        cin >> a >> b >> c >> d;
        arr[i] = {{a, b}, {a + c, b + d}};
    }

    int x, y;
    cin >> x >> y;
    int ans = -1;
    for(int i = n - 1; i >= 0; i--)
    {
        auto [left_top, right_bottom] = arr[i];
        if (x >= left_top.first && x <= right_bottom.first && y >= left_top.second && y <= right_bottom.second)
        {
            ans = i + 1; // 记录第几个矩形包含点(x, y)
            break; // 找到第一个包含点的矩形就可以退出循环
        }
    }

    cout << ans << endl;
    
    return 0;
}