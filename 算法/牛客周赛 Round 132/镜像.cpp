#include <iostream>
#include <vector>
#include <queue>
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
        int a, b, k;
        cin >> a >> b >> k;
        vector<int> arr(1e6 + 1, -1);
        queue<pair<int, int>> q;
        q.push({a, 0});
        while (!q.empty()) {
            int x = q.front().first;
            int step = q.front().second;
            q.pop();
            if (arr[x] != -1) {
                continue;
            }
            arr[x] = step;
            if (x == b) {
                break;
            }
            int y = x + k;
            if (y <= 1e6) {
                q.push({y, step + 1});
            }
            if (x % 10 != 0) {
                // 翻转
                int z = 0;
                while (x != 0) {
                    z = z * 10 + x % 10;
                    x /= 10;
                }
                q.push({z, step + 1});
            }
        }
        cout << arr[b] << endl;
    }

    return 0;
}