#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define int long long

signed main() {

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<int> a(n, 0);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        bool flat = true;
        int num = m - 1;
        // cout << "num : " << num << endl;
        for (int i = 1; i < n; i++) {
            if (a[i - 1] != a[i]) {
                num = m - 1;
            }
            else {
                num--;
            }

            // cout << "num : " << num << endl;

            if (num <= 0) {
                flat = false;
                break;
            }
        }

        if (flat) {
            cout << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
        }
        
    }


    return 0;
}