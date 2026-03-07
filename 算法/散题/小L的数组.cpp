#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
#define int long long
signed main() {
    
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    
    vector<bool> dp(2048, false);
    dp[0] = true;
    
    for (int i = 0; i < n; i++) {
        vector<bool> now(2048, false);
        int a1 = a[i];
        int b1 = b[i];
        for (int j = 0; j < 2048; j++) {
            if (dp[j] == true) {
                int idx = max(0LL, j - a1);
                now[idx] = true;
                int idx2 = j ^ b1;
                now[idx2] = true;
            }
        }
        dp = now;
    }
    
    int mx = 0;
    for (int i = 2047; i >= 0; i--) {
        if (dp[i] == true) {
            mx = i;
            break;
        }
    }
    
    cout << mx << endl;
    
    return 0;
}