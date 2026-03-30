#include <iostream>
#include <vector>
using namespace std;
int main() {
    
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> d(n, 0);
        for (int i = 0; i < n; i++) cin >> d[i];
        int ans = 0;
        int num = 0x3f3f3f3f;
        for (int i = 0; i < n; i++) {
            // 能减1就减1
            if (d[i] >= num) {
                num --;
                ans ++;
            }
            // 不能减1就变成d[i]
            if (d[i] < num) {
                num = d[i];
                ans ++;
            }
            
            if (num == 0) {
                break;
            }
        }
        
        
        cout << ans << endl;
    }
    
    
    return 0;
}