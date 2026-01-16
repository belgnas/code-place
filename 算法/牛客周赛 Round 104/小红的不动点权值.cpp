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
typedef pair<int, int> PII;

const int INF = 0x3f3f3f3f;
// &: 只有当两个相应的位都为 1 时,结果位才为 1,否则为 0
// |: 只要两个相应的位中有一个为 1,结果位就为 1,否则为 0
// ^: 如果两个相应的位不同(一个为 1，另一个为 0),则结果位为 1,如果相同则结果位为 0

const int MAX = 3e6 + 5;

vector<int> prep(MAX); // prep 数组用来记录排列中每个数值对应的原始下标位置（因为是一一对应，所以用记录值所在的位置）

signed main()
{
    IOS;
    
    int n;
    cin >> n;
    vector<int> arr(n + 1);
    for(int i = 1; i <= n; i++)
        cin >> arr[i];
    
    // 1 4 2 3
    // 1   1 4 2   1 4   1 4 2 3
    // 1  +  2   +  1   +   4    ==   8

    for(int i = 1; i <= n; i++)
    {
        prep[arr[i]] = i;
    }

    int min_num = INF, max_num = 0;
    int ans = 0;
    
    for(int i = 1; i <= n; i++)
    {
        min_num = min(min_num, prep[i]);
        max_num = max(max_num, prep[i]);
        ans += min_num * (n - max_num + 1);
    }
    //  min_num = min(min_num, prep[i]); max_num = max(max_num, prep[i]); ：随着 i 递增，不断更新当前已经处理过的数值（1 到 i ）在原始排列中的最小下标和最大下标。比如，处理到 i 时，要保证子数组必须包含 1 到 i 这些数值，那么这些数值在原始排列里的位置的最小和最大下标就决定了子数组的边界范围。
    //  ans += min_num * (n - max_num + 1); ：这一步是关键。当确定了包含 1 到 i 这些数值的原始排列中的最小下标 min_num 和最大下标 max_num 后，min_num 可以看作是子数组左边界的一种限制（左边界至少要到 min_num 才能包含这些数值的最小位置 ），n - max_num + 1 表示右边界的可选数量。相乘的结果就是当前包含 1 到 i 这些数值的所有符合条件的子数组对最终权值和的贡献。
    //  举个例子，假设处理到 i 时，min_num 是 L，max_num 是 R 。那么左边界选在 [1, L] 区间，右边界选在 [R, n] 区间，这样的子数组必然包含 1 到 i 所有数值（因为这些数值的位置都在 [L, R] 里 ），每个这样的子数组对应的排序后计算不动点时，会对权值有贡献，而这里通过数学推导，直接用 L * (n - R + 1) 来累加这种贡献到总结果 ans 里

    cout << ans << endl;
    
    return 0;
}