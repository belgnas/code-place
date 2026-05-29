#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

// bool test01(int i, int j, int k, vector<int>& a, vector<int>& b, vector<int>& c) {
//     int n = a.size();
//     for (int idx = 0; idx < n; idx++) {
//         int idx1 = (idx + i) % n;
//         int idx2 = (idx + j) % n;
//         int idx3 = (idx + k) % n;
//         if (a[idx1] < b[idx2] && b[idx2] < c[idx3]) {
//             continue;
//         }
//         else {
//             return false;
//         }
//     }
//     return true;
// }

signed main()
{
    IOS;

    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<int> a(n), b(n), c(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < n; i++) cin >> b[i];
        for (int i = 0; i < n; i++) cin >> c[i];
        int ans = 0;

        // for (int i = 0; i < n; i++) {
        //     for (int j = 0; j < n; j++) {
        //         for (int k = 0; k < n; k++) {
        //             // 起点为(i, j, k)
        //             if (test01(i, j, k, a, b, c)) {
        //                 ans++;
        //             }
        //         }
        //     }
        // }

        // for (int i = 0; i < n; i++) {
        //     for (int j = 0; j < n; j++) {
        //         if (a[i] < b[j]) {
        //             bool flat = true;
        //             for (int k = 0; k < n; k++) {
        //                 if (b[j] < c[k]) {
        //                     cout << "a[i] : " << a[i] << ", b[j] : " << b[j] << ", c[k] : " << c[k] << endl;
        //                     continue;
        //                 }
        //                 else {
        //                     flat = false;
        //                     break;
        //                 }
        //             }
        //             if (flat) {
        //                 ans++;
        //             }
        //         }
        //     }
        // }

        int cnt_ab = 0;
        // 统计a < b的次数
        for (int i = 0; i < n; i++) {
            bool flat = true;
            for (int j = 0; j < n; j++) {
                int idx1 = j;
                int idx2 = (i + j) % n;
                // 如果满足要求，就继续
                if (a[idx1] < b[idx2]) {
                    continue;
                }
                else {
                    flat = false;
                    break;
                }
            }
            if (flat) {
                cnt_ab++;
            }
        }

        int cnt_bc = 0;
        // 统计b < c的次数
        for (int i = 0; i < n; i++) {
            bool flat = true;
            for (int j = 0; j < n; j++) {
                int idx1 = j;
                int idx2 = (i + j) % n;
                // 如果满足要求，就继续
                if (b[idx1] < c[idx2]) {
                    continue;
                }
                else {
                    flat = false;
                    break;
                }
            }
            if (flat) {
                cnt_bc++;
            }
        }

        ans = n * cnt_ab * cnt_bc;

        cout << ans << endl;
    }

    return 0;
}