#include <bits/stdc++.h>
using namespace std;

#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)

int n, k, ans, hang[5], lie[5];

void dfs(int x, int y)
{
    if (x == n && y > n)
    {
        for (int i = 1; i <= n; i++)
            if (hang[i] != k)
                return;
        for (int i = 1; i <= n; i++)
            if (lie[i] != k)
                return;
        ans++;
        return;
    }
    if (y > n)
        x++, y = 1;
    for (int i = 0; hang[x] + i <= k && lie[y] + i <= k; i++)
    {
        // 剪枝1 
        // 行/列和不超过k
        // 剪枝2
        // 可以达到k
        if (hang[x] + i + k * (n - y) < k || lie[y] + i + k * (n - x) < k)
            continue;
        hang[x] += i;
        lie[y] += i;
        dfs(x, y + 1);
        hang[x] -= i;
        lie[y] -= i;
    }
}

int main()
{
    IOS;

    cin >> k >> n;

    dfs(1, 1);

    cout << ans << "\n";

    return 0;
}