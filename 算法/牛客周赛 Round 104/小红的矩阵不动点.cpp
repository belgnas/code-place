// #include <iostream>
// #include <cmath>
// #include <algorithm>
// #include <iomanip>
// #include <string>
// #include <vector>
// #include <cstring>
// #include <set>
// #include <tuple>
// #include <bitset>
// #include <utility>
// #include <queue> // 队列
// #include <deque> // 双端队列

// using namespace std;

// #define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
// #define int long long
// #define endl '\n'

// const int INF = 0x3f3f3f3f;

// signed main()
// {
//     IOS;

//     int n, m;
//     cin >> n >> m;
//     // 初始化一个 n * m 的二维数组
//     vector<vector<pair<int, int>>> arr(n + 1, vector<pair<int, int>>(m + 1, {0, -1}));

//     vector<int> num(510, 0);

//     int ans = 0;
//     for(int i = 1; i <= n; i++)
//     {
//         for(int j = 1; j <= m; j++)
//         {
//             cin >> arr[i][j].first;
//             if(arr[i][j].first == min(i, j))
//             {
//                 arr[i][j].second = -1;
//                 ans++;
//             }
//             else
//             {
//                 arr[i][j].second = min(i, j);
//                 num[arr[i][j].first]++;
//             }
//         }
//     }

//     int flat_add_one = false;
//     for(int i = 1; i <= n; i++)
//     {
//         for(int j = 1; j <= m; j++)
//         {
//             // if(arr[i][j].second == false && num[min(i, j)] != 0)
//             // {
//             //     ans++;
//             //     goto that;
//             // }

//             if(arr[i][j].second != -1 && num[min(i, j)] != 0)
//             {
//                 for(int k = i + 1; k <= n; k++)
//                 {
//                     for(int h = j + 1; h <= m; h++)
//                     {
//                         if(arr[k][h].second != -1)
//                         {
//                             int flat1 = (min(i, j) == arr[k][h].first);
//                             int flat2 = (min(k, h) == arr[i][j].first);

//                             if(flat1 && flat2)
//                             {
//                                 // cout << "喵" << endl;
//                                 ans += 2;
//                                 goto that;
//                             }
//                             if(flat1 || flat2)
//                             {
//                                 flat_add_one = true;
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//     }

//     if(flat_add_one)
//     {
//         ans += 1;
//     }

//     that:

//     cout << ans << endl;

//     return 0;
// }

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)

int main()
{
    IOS;
    int n, m;
    cin >> n >> m;
    vector<vector<int>> arr(n + 1, vector<int>(m + 1));
    vector<pair<int, int>> wrong; // 错误位置(i,j)
    int initial = 0;              // 初始正确数量

    // 统计初始正确值和错误位置
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            cin >> arr[i][j];
            int t = min(i, j);
            if (arr[i][j] == t)
                initial++;
            else
                wrong.emplace_back(i, j);
        }
    }

    // 哈希表：key=当前值，value=该值所在错误位置的目标值列表
    unordered_map<int, vector<int>> val_to_targets;
    // 错误值映射一个正确值
    for (auto [i, j] : wrong)
    {
        val_to_targets[arr[i][j]].push_back(min(i, j));
    }

    int max_add = 0;
    // 优先找+2的交换
    for (auto [i, j] : wrong)
    {
        int need = min(i, j); // 当前位置需要的值
        int have = arr[i][j]; // 当前位置拥有的值

        // 检查是否存在其他位置：值为need，且需要have
        if (val_to_targets.count(need))
        {
            for (int t : val_to_targets[need])
            {
                if (t == have)
                {
                    // 确保不是同一个位置（避免自己和自己交换）
                    bool same = false;
                    if (val_to_targets[have].size() == 1)
                    {
                        // 特殊情况：当前值在错误位置中只出现一次
                        same = (arr[i][j] == need && min(i, j) == have);
                    }
                    if (!same)
                    {
                        max_add = 2;
                        goto end; // 找到最优解直接退出
                    }
                }
            }
        }
    }
end:

    // 找+1的交换
    if (max_add < 2)
    {
        for (auto [i, j] : wrong)
        {
            int need = min(i, j);
            // 只要存在其他位置的值等于need，就能+1
            if (val_to_targets.count(need) &&
                (val_to_targets[need].size() > 1 ||
                 val_to_targets[need][0] != min(i, j) ||
                 arr[i][j] != need))
            {
                max_add = 1;
                break;
            }
        }
    }

    cout << initial + max_add << endl;
    return 0;
}