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
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
         
        vector<int> dp(n + 2, 0);
        int max_len = 0;
         
        for (int num : a) {
            dp[num] = max(dp[num - 1], dp[num + 1]) + 1;
            max_len = max(max_len, dp[num]);
        }
         
        cout << max_len << endl;
    }
    return 0;
}