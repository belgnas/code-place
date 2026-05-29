#include <iostream>
#include <vector>
using namespace std;

#define int long long

const int mod = 676767677;

signed main() {

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        bool full_of_1 = true;
        int last_not_1 = -1;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (a[i] != 1) {
                full_of_1 = false;
                last_not_1 = i;
            }
        }

        int ans = 0;
        if (full_of_1) {
            ans = 1;
        }
        else {
            for (int i = 0; i < n; i++) {
                if (a[i] != 1) {
                    ans += a[i];
                    ans %= mod;
                }
            }

            bool has_tail_one = false;
            for (int i = last_not_1 + 1; i < n; i++) {
                if (a[i] == 1) {
                    has_tail_one = true;
                    break;
                }
            }
            if (has_tail_one) {
                ans = (ans + 1) % mod;
            }
        }

        cout << ans << endl;
    }


    return 0;
}