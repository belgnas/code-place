#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
#define int long long
#define endl '\n'

const int MOD = 676767677;

signed main() {
    IOS;

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<int> b(n, 0);
        for(int i = 0; i < n; i++){
            cin >> b[i];
        }
        vector<int> cnt(n + 1, 0);
        for(int i = 0; i < n; i++){
            cnt[b[i]]++;
        }

        int ans = 1;

        vector<int> sit(n + 1 + 1, 0);
        for (int i = 0; i <= n; i++){
            sit[i + 1] = cnt[i] + sit[i];
        }

        bool flat = true;
        for(int i = 0; i < n; i++){
            if (b[i] == 0) {
                continue;
            }

            int time = LLONG_MAX;
            if (i > 0) {
                time = min(time, b[i - 1] + 1);
            }
            if (i < n - 1) {
                time = min(time, b[i + 1] + 1);
            }

            if (time > b[i]) {
                flat = false;
                break;
            }
            if (time == b[i]) {
                ans = (ans * sit[b[i]]) % MOD;
            }
            if (time < b[i]) {
                ans = (ans * cnt[b[i] - 1]) % MOD;
            }
        }

        if (!flat) {
            ans = 0;
        }

        cout << ans << endl;
    }

    return 0;
}