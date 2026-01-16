#include <iostream>
#include <vector>
using namespace std;

int maxOnes(vector<string>& matrix, int n, int m) {
    // 用于记录每列不同状态的数量
    vector<vector<int>> colStates(2, vector<int>(m, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            // 统计每列0和1的数量
            colStates[matrix[i][j] - '0'][j]++;
        }
    }

    int maxCount = 0;
    for (int j = 0; j < m; ++j) {
        // 对于每一列，取原状态和反置状态下1的数量的较大值
        maxCount += max(colStates[0][j], colStates[1][j]);
    }
    return maxCount;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<string> matrix(n);
    for (int i = 0; i < n; ++i) {
        cin >> matrix[i];
    }

    int result = maxOnes(matrix, n, m);
    cout << result << endl;

    return 0;
}