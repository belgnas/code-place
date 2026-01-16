#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
void solve(int task)
{
    int n, cnt = 0;
    string s;
    cin >> n;
    cin >> s;
    for (int i = 0; i + 1 < n; i++)
    {
        cnt += (s[i] != s[i + 1]);
    }
    if (cnt >= 3)
    {
        cout << "0\n";
    }
    else if (cnt == 2)
    {
        if (s == "1001" || s == "0110")
            cout << 2 << "\n";
        else
            cout << 1 << "\n";
    }
    else if (cnt == 1)
    {
        if (s == "1100" || s == "0011")
            cout << 2 << "\n";
        else
            cout << "1\n";
    }
    else if (cnt == 0)
    {
        cout << 2 << "\n";
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++)
    {
        solve(i);
    }
    return 0;
}
