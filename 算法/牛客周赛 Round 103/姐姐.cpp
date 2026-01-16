// #include <bits/stdc++.h>
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
typedef pair<int, int> PII;

const int INF = 0x3f3f3f3f;
// &: 只有当两个相应的位都为 1 时,结果位才为 1,否则为 0
// |: 只要两个相应的位中有一个为 1,结果位就为 1,否则为 0
// ^: 如果两个相应的位不同(一个为 1，另一个为 0),则结果位为 1,如果相同则结果位为 0

signed main()
{
    IOS;

    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> a[i];
        }

        int cnt = 0;
        for (int i = 0; i < n; ++i)
        {
            // 处理环形：i=0 时，前一个元素是 a[n-1]
            int prev = (i == 0) ? a[n - 1] : a[i - 1];
            if (prev == 0 && a[i] == 1)
            {
                cnt++;
            }
        }

        // 因为是环形数组，最多只能有一次 0->1 的变化
        cout << (cnt <= 1 ? "YES" : "NO") << endl;
    }

    return 0;
}