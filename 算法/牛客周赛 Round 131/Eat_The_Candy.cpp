#include <iostream>
#include <algorithm>
#include <vector>
 
using namespace std;
 
#define int long long
 
signed main() {
     
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n + 2);
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        vector<int> qian(n + 2);
        vector<int> hou(n + 2);
         
        vector<int> temp = a;
         
        for (int i = 2; i <= n; i++) {
            int num = min(temp[i - 1], temp[i]);
            qian[i] = qian[i - 1] + num;
             
            temp[i - 1] -= num;
            temp[i] -= num;
        }
         
        temp = a;
        for (int i = n-1; i >= 1; i--) {
            int num = min(temp[i + 1], temp[i]);
            hou[i] = hou[i + 1] + num;
             
            temp[i + 1] -= num;
            temp[i] -= num;
        }
         
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            ans = max(ans, qian[i - 1] + hou[i + 1] + a[i]);
        }
         
        cout << ans << endl;
    }
     
    return 0;
}