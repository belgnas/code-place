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
    while (t--)
    {
        int n, x;
        cin >> n >> x;
        string s;
        cin >> s;
        if (x == 1 || x == n)
        {
            cout << "1" << endl;
            continue;
        }
        x--;
        int inf = 1e9;
        int lf = -inf, rg = inf;
        for (int i = x - 1; i >= 0; i--)
        {
            if (s[i] == '#')
            {
                lf = i;
                break;
            }
        }
        for (int i = x + 1; i < n; i++)
        {
            if (s[i] == '#')
            {
                rg = i;
                break;
            }
        }

        if (lf == -inf && rg == inf)
        {
            cout << "1" << endl;
            continue;
        }

        cout << max(min(x + 1, n - rg + 1), min(lf + 2, n - x)) << endl;
    }

    return 0;
}