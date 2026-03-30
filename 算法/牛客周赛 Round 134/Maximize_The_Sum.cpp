#include <iostream>
#include <vector>
#include <unordered_map> 
#include <string>
using namespace std;

// string test01(string& s, int idx) {
//     int x = s[idx] - '0', y = s[idx + 1] - '0', z = s[idx + 2] - '0';
//     int x2 = x ^ y, y2 = y ^ z, z2 = z ^ x;
//     s[idx] = char(x2 + '0');
//     s[idx + 1] = char(y2 + '0');
//     s[idx + 2] = char(z2 + '0');
//     return s;
// }

int main() {
    
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string a;
        cin >> a;
        
        bool has_1 = false;
        bool has_0 = false;
        for (int i = 0; i < n; i++) {
            if (a[i] == '1') {
                has_1 = true;
            }
            else {
                has_0 = true;
            }
        }
        
        int ans = 0;
        if (has_0 && has_1) {
            ans = n - 1;
        }
        if (has_0 && !has_1) {
            ans = 0;
        }
        if (!has_0 && has_1) {
            ans = n;
        }
        
        cout << ans << endl;
        // 000 -> 000 
        // 001 -> 011 // +1
        // 010 -> 110
        // 100 -> 101
        // 110 -> 011 // 更改位置
        // 011 -> 101
        // 101 -> 110
        // 111 -> 000  // 不会用到
    }
    
    return 0;
}