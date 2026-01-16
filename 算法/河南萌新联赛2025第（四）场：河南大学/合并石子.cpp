#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <string>
#include <vector>
#include <cstring>
#include <set>
#include <tuple>
#include <bitset>
#include <utility>
#include <queue> // 队列
#include <deque> // 双端队列

using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define endl '\n'

const int INF = 9e18;

signed main()
{
    IOS;

    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1, 0);
    for(int i = 1; i <= n; i++) cin >> a[i];

    vector<int> prefix_sum(n + 2, 0); // 前缀
    vector<int> suffix_sum(n + 2, 0); // 后缀

    for(int i = 2; i <= n; i++)
    {
        prefix_sum[i] = prefix_sum[i - 1] + a[i - 1];
    }
    for(int i = n - 1; i >= 1; i--)
    {
        suffix_sum[i] = suffix_sum[i + 1] + a[i + 1];
    }
    // // 测试
    // for(int i = 1; i <= n + 1; i++) cout << prefix_sum[i] << " ";
    // cout << endl;
    // for(int i = 1; i <= n + 1; i++) cout << suffix_sum[i] << " ";
    // cout << endl;


    vector<int> prefix_ans(n + 2, 0);
    vector<int> suffix_ans(n + 2, 0);
    for(int i = 2; i <= n; i++)
    {
        prefix_ans[i] = prefix_ans[i - 1] + (prefix_sum[i] + k - 1) / k; // +(k-1)是为了向上取整
    }
    for(int i = n - 1; i >= 1; i--)
    {
        suffix_ans[i] = suffix_ans[i + 1] + (suffix_sum[i] + k - 1) / k;
    }
    // // 测试
    // for(int i = 1; i <= n + 1; i++) cout << prefix_ans[i] << " ";
    // cout << endl;
    // for(int i = 1; i <= n + 1; i++) cout << suffix_ans[i] << " ";
    // cout << endl;


    int ans = INF;
    for(int i = 1; i <= n; i++)
    {
        ans = min(ans, prefix_ans[i] + suffix_ans[i]);
    }

    cout << ans << endl;
    
    return 0;
}

// #include <iostream>
// #include <cmath>
// #include <algorithm>
// #include <vector>

// using namespace std;

// #define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
// #define int long long
// #define endl '\n'

// const int INF = 9e18; // Use a larger INF for long long

// signed main()
// {
//     IOS;

//     int n, k;
//     cin >> n >> k;
//     vector<int> a(n + 1);
//     for(int i = 1; i <= n; i++) cin >> a[i];

//     // left_cost[i] = cost to move all stones from 1...i-1 into pile i
//     vector<int> left_cost(n + 2, 0);
//     // stones_moved_left[i] = sum of stones from 1 to i
//     vector<int> stones_moved_left(n + 2, 0);

//     for(int i = 2; i <= n; i++)
//     {
//         stones_moved_left[i] = stones_moved_left[i - 1] + a[i - 1];
//         left_cost[i] = left_cost[i - 1] + (stones_moved_left[i] + k - 1) / k;
//     }

//     // right_cost[i] = cost to move all stones from i+1...n into pile i
//     vector<int> right_cost(n + 2, 0);
//     // stones_moved_right[i] = sum of stones from i to n
//     vector<int> stones_moved_right(n + 2, 0);

//     for(int i = n - 1; i >= 1; i--)
//     {
//         stones_moved_right[i] = stones_moved_right[i + 1] + a[i + 1];
//         right_cost[i] = right_cost[i + 1] + (stones_moved_right[i] + k - 1) / k;
//     }

//     int ans = INF;
//     for(int i = 1; i <= n; i++)
//     {
//         ans = min(ans, left_cost[i] + right_cost[i]);
//     }

//     cout << ans << endl;

//     return 0;
// }