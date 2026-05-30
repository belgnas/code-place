#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<int> b(n), val(n);
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
        cin >> val[i];
    }

    // dp[i][j]表示前i只猪，在第j天的最小花费
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, INT_MAX));
    for (int j = 0; j <= m; ++j) {
        dp[0][j] = 0;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            // 不陪第i只猪
            dp[i][j] = min(dp[i][j], dp[i - 1][j] + val[i - 1]);
            // 如果第i只猪要求在第j天陪，并且j在要求范围内
            if (j >= a[i - 1] && j < a[i - 1] + m) {
                // 陪第i只猪
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + b[i - 1]);
            }
        }
    }

    int minCost = INT_MAX;
    for (int j = 1; j <= m; ++j) {
        minCost = min(minCost, dp[n][j]);
    }

    cout << minCost << endl;
    return 0;
}