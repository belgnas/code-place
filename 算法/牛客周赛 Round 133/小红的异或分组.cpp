#include <iostream>
#include <cmath>
#include <vector>
#include <map>
using namespace std;
#define int long long

signed main() {

    int n;
    cin >> n;
    
    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    vector<int> prev(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        prev[i] = prev[i - 1] ^ a[i];
    }
    vector<int> suff(n + 1 + 1, 0);
    for (int i = n; i >= 1; --i) {
        suff[i] = suff[i + 1] ^ a[i];
    }
    int total = prev[n];

    int ans = 0;
//     for (int i = 1; i <= n - 2; ++i) {
//         int num1 = prev[i];
//         for (int j = i + 2; j <= n; ++j) {
//             int num3 = suff[j];
//             if (num1 == num3) {
//                 int num2 = final ^ num1 ^ num3;
//                 if (num2 == num1) {
//                     ans++;
//                 }
//             }
//         }
//     }
    // 重要发现:如果三部分的异或和相等，则这3部分的异或和都等于整个该数组的异或和
    // 所以只需要找到哪些地方异或和等于total就可以，也就是说，只要前后两个部分都等于整体，中间这部分自然就等于了。
    
    vector<int> suff2(n + 2, 0);
    int num = 0;
    for (int i = n; i >= 1; i--) {
        // 这里先赋值再做判断，意味着记录的是当前位置后（不包括当前位置）的等于total的异或和数
        suff2[i] = num;
        if (suff[i] == total) {
            num ++;
        }
    }
    
//     for (int i = 0; i < suff2.size(); i++) {
//         cout << suff2[i] << ' ';
//     }
//     cout << endl;
    
    for (int i = 1; i <= n - 2; i++) {
        if (prev[i] == total) {
            // 这里需要找的是后一个位置后的suff2，避免中间部分为空
            ans += suff2[i + 1];
        }
    }

    cout << ans << endl;

    return 0;
}