// 一道动态规划题（简单题）

#include<bits/stdc++.h>

using namespace std;

#define IOS ios::sync_with_stdio(false), cout.tie(0), cin.tie(0);

const int N = 500010;

int arr[N];
int dp[N][2];
// 定义一个二维数组 dp，dp[i][0] 和 dp[i][1] 用于记录状态
// dp[i][0] 表示考虑前 i 个元素且不选择第 i 个元素时能得到的最大结果
// dp[i][1] 表示考虑前 i 个元素且选择第 i 个元素时能得到的最大结果

int main()
{
    IOS;

    int n;
    cin >> n;

    // 初始化边界条件
    dp[0][0] = 0;
    dp[0][1] = 0;
    // 当没有元素时，不选元素和选元素的最大结果都为 0

    for(int i = 1; i <= n; i++)
        cin >> arr[i];
    // 循环读取 n 个整数，存储到数组 arr 中，数组下标从 1 开始

    for(int i = 1; i <= n; i++)
    {
        // 状态转移：不选择第 i 个元素
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);
        // dp[i][0] 的值取前 i - 1 个元素中不选第 i - 1 个元素（dp[i - 1][0]）
        // 和选第 i - 1 个元素（dp[i - 1][1]）这两种情况中的最大值

        // 状态转移：选择第 i 个元素
        dp[i][1] = dp[i - 1][0] + arr[i];
        // 如果选择第 i 个元素，那么它的最大值是在前 i - 1 个元素不选第 i - 1 个元素的基础上
        // 加上当前第 i 个元素的值 arr[i]
    }

    cout << max(dp[n][0], dp[n][1]) << endl;
    // 输出考虑前 n 个元素时，不选第 n 个元素（dp[n][0]）和选第 n 个元素（dp[n][1]）
    // 这两种情况中的最大值


    return 0;
}