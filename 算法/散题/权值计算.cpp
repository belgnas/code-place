#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
using namespace std;

#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define endl '\n'
#define int long long

signed main() {
    IOS;
    
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }

        // 只有当a[i]是子数组 l~r 中首次出现时，才会产生贡献

        unordered_map<int, int> pw;
        int ans = 0;
        for (int i = 0; i <= n; i++) {
            int x = a[i];

            int pre = 0;
            if (pw.count(x) > 0) {
                pre = pw[x];
            }
            else {
                pre = 0;
            }

            int l_num = i - pre;
            // int r_num = 
            
            int k = n - i + 1;
            int r_sum = k * (k + 1) / 2;

            ans += (l_num * r_sum);
            pw[x] = i;
        }

        cout << ans << endl;
        
    }

    return 0;
}