#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define int long long

const int mod = 998244353;

signed main()
{

    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        string s;
        cin >> s;
        int num = 0;
        int t = 0;
        for (int i = 0; i < n; i++)
        {
            if (s[i] == '(')
            {
                num++;
            }
            else
            {
                num--;
            }
            if (num == 0)
            {
                t++;
            }
        }
        int ans = 1;
        for (int i = 1; i <= t; i++)
        {
            ans *= 2;
            ans %= mod;
        }
        cout << ans << endl;
    }

    return 0;
}