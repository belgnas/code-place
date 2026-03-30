#include <iostream>
#include <vector>
using namespace std;

// dfs 搜索全排列，使 ∑ num[pos] * val == sum
vector<int> dfs(vector<int>& path, vector<bool>& used, const vector<int>& num, long long sum, long long now) {
    int n = num.size();
    // 剪枝：当前和已经大于目标，不可能达到
    if (now > sum) return {};
    if (path.size() == n) {
        if (now == sum) return path;
        else return {};
    }
    
    for (int i = 1; i <= n; ++i) {
        if (!used[i]) {
            long long new_now = now + 1LL * num[path.size()] * i;
            // 剪枝：加上当前数字后已超过目标，跳过
            if (new_now > sum) continue;
            used[i] = true;
            path.push_back(i);
            vector<int> res = dfs(path, used, num, sum, new_now);
            if (!res.empty()) return res;
            path.pop_back();
            used[i] = false;
        }
    }
    return {};
}

int main() {
    int n, sum;
    cin >> n >> sum;
    vector<vector<int>> f(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        f[i][0] = 1;
        f[i][i] = 1;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < i; j++) {
            f[i][j] = f[i - 1][j - 1] + f[i - 1][j];
        }
    }
    
    vector<int> num = f[n - 1];  // 杨辉三角第 n 行（索引 0~n-1）
    vector<bool> used(n + 1, false);
    vector<int> path;
    vector<int> ans = dfs(path, used, num, sum, 0);
    
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
    
    return 0;
}