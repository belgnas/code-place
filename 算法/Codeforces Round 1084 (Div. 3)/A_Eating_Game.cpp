#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

#define int long long

signed main()
{
    IOS;

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        int ans = 0;
        int mx = -1;
        for (int i = 0; i < n; i++) {
            if (a[i] > mx) {
                mx = a[i];
                ans = 1;
            }
            else if (a[i] == mx) {
                ans++;
            }
        }

        cout << ans << endl;
    }



    return 0;
}
