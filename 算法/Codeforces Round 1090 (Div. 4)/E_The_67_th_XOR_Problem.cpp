#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
#define int long long
#define endl '\n'

signed main() {
    IOS;

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n, 0);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }

        int mx = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                mx = max(mx, a[i] ^ a[j]);
            }
        }

        cout << mx << endl;
    }

    return 0;
}