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
#include <stack>
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
    
    int m, n;
    cin >> m >> n;
    deque<int> q;
    int x;
    int ans = 0;
    for (int i = 0; i < n; ++i)
    {
        cin >> x;
        if (q.size() < m && find(q.begin(), q.end(), x) == q.end()) // 检查队列中是否已存在该元素
        {
            ans++;
            q.push_back(x); // 队列未满且元素不在队列中时入队
        }
        if (q.size() == m && find(q.begin(), q.end(), x) == q.end()) // 队列已满
        {
            ans++;
            q.pop_front(); // 出队最早入队的元素
            q.push_back(x); // 新元素入队
        }
        if (find(q.begin(), q.end(), x) != q.end()) // 元素已在队列中
        {
            continue; // 元素已在队列中，不做处理
        }
    }

    cout << ans << endl;

    
    return 0;
}