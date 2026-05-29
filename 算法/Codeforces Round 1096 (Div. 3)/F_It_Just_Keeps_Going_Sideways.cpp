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
        int n;
        cin >> n;
        vector<int> a(n);
        vector<int> nums(n + 1); // 记录每个数字出现的次数
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            nums[a[i]] ++;
        }

        vector<int> level(n + 1); // 记录每层的方块数
        level[n] = nums[n];
        for (int i = n - 1; i >= 1; i--) { // 最底层肯定有方块：1 <= a[i] <= n
            level[i] = level[i + 1] + nums[i];
        }

        // init：假设每个方块都放在最左列，移到初始位置的总移动距离
        int init = 0;
        for (int i = 0; i < n; i++) {
            init += i * a[i];
        }
        // cout << "init: " << init << endl;

        // after：假设每个方块都放在最左列，移到最终位置的总移动距离
        int after = 0;
        for (int i = 1; i <= n; i++) {
            // 从 n 加到 n - level[i]
            // 求和公式
            int temp = (n - (n - level[i])) * (n + n - level[i] - 1) / 2;
            // int temp = level[i] * (2 * n - level[i] - 1) / 2;
            after += temp;
        }
        // cout << "after: " << after << endl;

        int cur = after - init; // 实际移动距离
        // 每层移动减少一个方块看看会不会变化
        int mx_delta = 0; // 可能会多移动的距离
        for (int i = 0; i < n; i++) {
            // 多了一个 最终阶段的最左端的方块移回其重力改变前的初始位置所得的距离
            // 从 i 移动到 n - level[a[i]]，末位置 - 初始位置
            // 这里是反向抵消之前的移动，所以是 i - (n - level[a[i]])
            mx_delta = max(mx_delta, i - (n - level[a[i]]));
        }

        cout << cur + mx_delta << endl;

    }
    return 0;
}