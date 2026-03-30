#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n, 0);
        for (int i = 0; i < n; i++) cin >> a[i];

        // 1 - 6
        // 2 - 5
        // 3 - 4

        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (i == 0) continue;
            
            if (a[i] == 7 - a[i - 1] || a[i] == a[i - 1]) {
                // cout << "i = " << i << endl;
                ans++;
                i++;
            }
        }

        cout << ans << endl;
    }


    return 0;
}