#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define int long long

void solve() {
    int n;
    cin >> n;
    vector<int> v_x(n), v_y(n);
    for (int i = 0; i < n; i++) {
        cin >> v_x[i] >> v_y[i];
    }

    sort(v_x.begin(), v_x.end());
    sort(v_y.begin(), v_y.end());

    int mid_x = v_x[n / 2];
    int mid_y = v_y[n / 2];

    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += abs(v_x[i] - mid_x);
        ans += abs(v_y[i] - mid_y);
    }

    cout << ans << endl;
}

signed main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}