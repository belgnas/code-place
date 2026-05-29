#include <iostream>
#include <vector>
using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr)

#define int long long

signed main() {
    
    IOS;

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<int> a(n, 0);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            ans += (((a[i] + m - 1) / m) + 1);
        }

        cout << ans << endl;
    }


    return 0;
}