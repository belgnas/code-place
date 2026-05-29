// #include <iostream>
// #include <vector>
// #include <string>
// #include <set>
// using namespace std;

// #define IOS ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

// #define int long long

// int count_blk(vector<int>& a) {
//     int highBlk = a.back();
//     int blk = 0;
//     int bottomBlk = 0;
//     for (int i = a.size() - 1; i >= 0; i--) {
//         highBlk = min(highBlk, a[i]);
//         if (highBlk == 0) {
//             break;
//         }
//         bottomBlk ++;
//         blk += highBlk;
//     }
//     // cout << "sum: " << sum << endl;
//     // cout << "blk: " << blk << endl;
//     // cout << "bottomBlk: " << bottomBlk << endl;
//     return blk;
// }

// signed main() {

//     IOS;

//     int t;
//     cin >> t;
//     while(t--) {
//         int n;
//         cin >> n;
//         vector<int> a(n, 0);
//         int sum = 0;
//         for (int i = 0; i < n; i++) {
//             cin >> a[i];
//             sum += a[i];
//         }

//         int blk1 = count_blk(a);
//         int ans1 = sum - blk1;

//         int blk2 = LLONG_MAX;
//         for (int i = n - 1; i >= 0; i--) {
//             if (i == n - 1) {
//                 continue;
//             }

//             if (a[i] >= a[i + 1] && a[i + 1] > 0) {
//                 a[i + 1] --;
//                 blk2 = min(blk2, count_blk(a));
//                 a[i + 1] ++;
//             }
//         }
//         // int blk2 = LLONG_MAX;
//         // for (int i = 0; i < n; i++) {
//         //     if (a[i] > 0) {
//         //         a[i] --;
//         //         blk2 = min(blk2, count_blk(a));
//         //         a[i] ++;
//         //     }
//         // }
//         int ans2 = sum - 1 - blk2;

//         cout << max(ans1, ans2) << endl;
//     }


//     return 0;
// }


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define IOS ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define int long long

signed main() {
    IOS;

    int t;
    cin >> t;
    while (t--) {
        // int n;
        // cin >> n;
        // vector<int> a(n);
        // int sum = 0;
        // for (int i = 0; i < n; i++) {
        //     cin >> a[i];
        //     sum += a[i];
        // }
        int n;
        cin >> n;
        vector<int> a(n);
        int sum = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            sum += a[i];
        }

        // // 1. 计算后缀最小值 s[i] = min(a[i]..a[n-1])
        // vector<int> s(n);
        // s[n - 1] = a[n - 1];
        // for (int i = n - 2; i >= 0; i--) {
        //     s[i] = min(a[i], s[i + 1]);
        // }
        vector<int> s(n);
        s.back() = a.back();
        for (int i = n - 1; i >= 1; i--) {
            s[i - 1] = min(a[i - 1], s[i]);
        }

        // // 2. 求 sum(s) 和 最长连续相等块的长度
        // int sum_s = 0;
        // int max_block = 1, cur_block = 1;
        // sum_s += s[0];
        // for (int i = 1; i < n; i++) {
        //     sum_s += s[i];
        //     if (s[i] == s[i - 1]) {
        //         cur_block++;
        //         max_block = max(max_block, cur_block);
        //     }
        //     else {
        //         cur_block = 1;
        //     }
        // }
        // // 如果整个 s 数组都相等，上面循环中 cur_block 会一直累加并更新 max_block
        // // 但若 n==1，max_block 初值1 已正确。
        int sum_s = 0; // 固定不动的
        int max_block = 1, cur_block = 1; // 初始化为1，因为至少有一个元素
        sum_s += s[0];
        for (int i = 1; i < n; i++) {
            sum_s += s[i];
            if (s[i] == s[i - 1]) {
                cur_block++;
                max_block = max(max_block, cur_block);
            }
            else {
                cur_block = 1;
            }
        }


        // int ans = sum - sum_s + max_block - 1;
        // cout << ans << endl;

        cout << "sum = " << sum << endl;
        cout << "sum_s = " << sum_s << endl;
        cout << "max_block = " << max_block << endl;
        cout << "cur_block = " << cur_block << endl;

        int ans = sum - sum_s + max_block - 1; // 总数 - 固定不动的 + 最长连续相等块的长度 - 1，就是被移动的方块数
        cout << ans << endl;
    }
    return 0;
}