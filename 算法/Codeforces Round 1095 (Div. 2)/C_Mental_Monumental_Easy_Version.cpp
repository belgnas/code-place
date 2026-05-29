#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <map>
using namespace std;

#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0); cout.tie(0);

const int mod = 676767677;

int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

bool check(int mid, int n, map<int, int>& mp) {
    if (mid == 0) {
        return true;
    }

    vector<int> miss;
    vector<int> done;

    for (int i = 0; i < mid; i++) {
        if (mp.count(i) && mp[i] > 0) {
            // 如果这个数有富余，多出来的都是“供体”
            for (int j = 0; j < mp[i] - 1; j++) {
                done.push_back(i);
            }
        }
        else {
            // 否则它是“缺失值”
            miss.push_back(i);
        }
    }

    for (auto it : mp) {
        if (it.first >= mid) {
            for (int j = 0; j < it.second; j++) {
                done.push_back(it.first);
            }
        }
    }

    if (miss.empty()) {
        return true;
    }
    if (done.size() < miss.size()) {
        return false;
    }

    sort(miss.begin(), miss.end(), greater<int>());
    sort(done.begin(), done.end(), greater<int>());

    for (int i = 0; i < miss.size(); i++) {
        if (done[i] < 2 * miss[i] + 1) {
            return false;
        }
    }

    return true;
}



signed main() {

    IOS;

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        map<int, int> mp;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            mp[x]++;
        }

        int l = 1, r = n;
        int ans = 0;

        while (l <= r) {
            int mid = (l + r) / 2;
            if (check(mid, n, mp)) {
                ans = mid;
                l = mid + 1;
            }
            else {
                r = mid - 1;
            }
        }

        cout << ans << endl;
    }

    return 0;
}

// #include <iostream>
// #include <vector>
// #include <set>
// #include <algorithm>

// using namespace std;

// void solve() {
//     int n;
//     cin >> n;
//     multiset<int> ms;
//     for (int i = 0; i < n; i++) {
//         int x;
//         cin >> x;
//         ms.insert(x);
//     }

//     int ans = 0;
//     while (!ms.empty()) {
//         // 1. 如果当前的 ans 已经在集合里，直接用掉它
//         auto it = ms.find(ans);
//         if (it != ms.end()) {
//             ms.erase(it);
//             ans++;
//         } 
//         // 2. 如果不在，就拿集合里最大的那个数来尝试变成 ans
//         else {
//             int biggest = *ms.rbegin(); // 获取最大值
//             // 判断最大值是否能通过取模变成 ans
//             // 根据公式，必须满足 biggest >= 2 * ans + 1
//             if (biggest >= 2 * ans + 1) {
//                 ms.erase(prev(ms.end())); // 删掉最大的那个
//                 ans++;
//             } else {
//                 // 最大值都变不出来了，那 MEX 只能到此为止
//                 break;
//             }
//         }
//     }
//     cout << ans << endl;
// }

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(0);
//     int t;
//     cin >> t;
//     while (t--) {
//         solve();
//     }
//     return 0;
// }


// #include <iostream>
// #include <vector>
// #include <set>
// #include <unordered_set>
// #include <algorithm>
// using namespace std;

// #define int long long

// const int mod = 676767677;

// int gcd(int a, int b)
// {
//     while (b != 0)
//     {
//         int temp = b;
//         b = a % b;
//         a = temp;
//     }
//     return a;
// }



// signed main() {

//     int t;
//     cin >> t;
//     while (t--) {
//         int n;
//         cin >> n;
//         // mex 
//         multiset<int> ms;
//         for (int i = 0; i < n; i++) {
//             int x;
//             cin >> x;
//             ms.insert(x);
//         }

//         int ans = 0;
//         while (!ms.empty()) {
//             auto it = ms.find(ans); // it 是指向 ans 的迭代器
//             if (it != ms.end()) {
//                 ms.erase(it);
//             }
//             else {
//                 // it = ms.lower_bound(2 * ans); // 
//                 // if (it != ms.end()) {
//                 //     ms.erase(it);
//                 // }
//                 // else {
//                 //     break;
//                 // }
                
//                 int big = *ms.rbegin();
//                 if (big >= 2 * ans + 1) {
//                     ms.erase(prev(ms.end()));
//                 }
//                 else {
//                     break;
//                 }
//             }
//             ans++;
//         }
//         cout << ans << endl;
//     }
//     return 0;


//     return 0;
// }