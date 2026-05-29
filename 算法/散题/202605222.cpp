#include <bits/stdc++.h>
using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long

signed main() {
    IOS;

    int n, m;
    cin >> n >> m;
    vector<vector<int>> c(n + 1, vector<int> (m + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> c[i][j];
        }
    }

    vector<int> c_cnt (m + 1, 0);
    for (int j = 1; j <= m; j++) {
        int num = c[1][j];
        int cnt = 0;

        // 【修改处】删除了原先错误的 if (c_cnt[num] >= (n + 1) / 2) 判断

        for (int i = 1; i <= n; i++) {
            if (c[i][j] == num) {
                cnt++;
            }
            else {
                break;
            }
        }
        // 始终保持 c_cnt[num] 记录的是该颜色能达到的最大前缀长度
        if (c_cnt[num] < cnt) {
            c_cnt[num] = cnt;
        }
    }

    int ans = 0;
    for (int i = 1; i <= m; i++) {
        ans += (n - c_cnt[i]);
    }

    cout << ans << endl;
    return 0;
}