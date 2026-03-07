#include <iostream>
#include <vector>
using namespace std;

#define int long long
signed main() {

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += a[i];
        }
        sum *= (n - 1);
        int jishu = 0;
        int oushu = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] % 2 == 1) {
                jishu++;
            } else {
                oushu++;
            }
        }
        sum -= jishu * oushu;
        sum /= 2;
        cout << sum << endl;
    }

    return 0;
}