#include <bits/stdc++.h>
using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)

int main()
{
    IOS;
    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;
        int a[n];
        for (int i = 0; i < n; i++)
            cin >> a[i];

        int res = 0;
        multiset<int> s;

        for (int x : a)
        {
            auto p = s.upper_bound(x);

            if (p != s.end())
            {
                res = max(res, x + *prev(s.end()));
            }

            s.insert(x);
        }

        cout << res << endl;
    }
    return 0;
}