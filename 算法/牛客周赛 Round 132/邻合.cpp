#include <iostream>
#include <vector>
using namespace std;
#define int long long
#define endl '\n'

#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

// // 检查两个数是否互质
// bool gcd(int a, int b) {
//     // 如果第二个数为0，代表第一个数为1，1与任何数互质
//     if (b == 0) {
//         return a == 1;
//     }
//     // 递归计算两个数的最大公约数
//     return gcd(b, a % b);
// }

bool gcd(int a, int b) {
    while(b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a == 1;
}

signed main() {
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
        for (int i = 0; i < n; i++) {
            if (a[i] == 1) {
                ans++;
            }
        }
        for (int i = 0; i < n - 1;) {
            // 如果互质，代表后面数字需要更改，可以跳过第二个数字与第三个数字的互质判断
            if (gcd(a[i], a[i + 1]) && a[i] > 1 && a[i + 1] > 1) {
                ans++;
                i += 2;
            }
            else {
                i++;
            }
        }

        cout << ans << endl;

    }

    return 0;
}