#include <bits/stdc++.h>
// #include <iostream>
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

        for (int i = 1; i <= n; i++) {
            if (c[i][j] == num) {
                cnt++;
            }
            else {
                break;
            }
        }
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





    // unordered_map<int, int> ump;
    // vector<int> c_cnt (m + 1, 0);
    // for (int j = 1; j <= m; j++) {
    //     int num = c[1][j];
    //     int cnt = 0;

    //     for (int i = 1; i <= n; i++) {
    //         if (c[i][j] == num) {
    //             cnt++;
    //         }
    //         else {
    //             break;
    //         }
    //     }

    //     ump[num] = max(ump[num], cnt);
    // }
    // int ans = 0;
    // for (auto it : ump) {
    //     ans += (n - it.second);
    // }
    // ans += ((m - ump.size()) * n);
    // cout << ans << endl;