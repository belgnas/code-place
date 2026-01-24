#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

#define int long long
const int mod = 998244353;

signed main() {
    int t;
    cin >> t;
    while (t--) {
        vector<int> num(1e5 + 10, 0);

        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (a[i] <= 1e5) {
                num[a[i]] ++;
            }
        }

        // for (int i = 1; i <= 5; i++) {
        //     cout << num[i] << " ";
        // }
        // cout << endl;

        if (num[1] < 2) {
            cout << 0 << endl;
            return 0;
        }

        int ans = 0;
        int temp = 1;
        for (int i = 1; i <= num.size(); i++) {
            if (num[i] >= 2) {
                // temp *= C 2 num[i]
                temp *= num[i];
                temp *= num[i] - 1;
                temp /= 2;
                temp %= mod;
                ans = (ans + temp) % mod;
            }
            else {
                break;
            }
        }

        cout << ans << endl;
    }
    
    return 0;
}