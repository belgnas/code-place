#include <iostream>
#include <vector>
#include <unordered_set>
#include <cstring>
#include <algorithm>
using namespace std;

// 全局变量（方便回溯，小n下无副作用）
int n;          // 矩阵阶数
vector<vector<int>> mat; // 当前生成的01矩阵
int cnt_valid;  // 符合条件的矩阵数量
// 四连通方向（上下左右）
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

// 验证条件1：行和是0~n-1的排列（无重复、仅含0~n-1、共n个）
bool checkRow() {
    unordered_set<int> s;
    vector<int> row_sum(n, 0);
    for (int i = 0; i < n; ++i) {
        int sum = 0;
        for (int j = 0; j < n; ++j) sum += mat[i][j];
        row_sum[i] = sum;
        if (sum < 0 || sum >= n) return false; // 行和超出0~n-1，直接无效
        s.insert(sum);
    }
    return s.size() == n; // 无重复则是排列
}

// 验证条件2：列和是0~n-1的排列（无重复、仅含0~n-1、共n个）
bool checkCol() {
    unordered_set<int> s;
    vector<int> col_sum(n, 0);
    for (int j = 0; j < n; ++j) {
        int sum = 0;
        for (int i = 0; i < n; ++i) sum += mat[i][j];
        col_sum[j] = sum;
        if (sum < 0 || sum >= n) return false; // 列和超出0~n-1，直接无效
        s.insert(sum);
    }
    return s.size() == n; // 无重复则是排列
}

// DFS统计连通块：遍历val的连通区域，标记访问
void dfs(int x, int y, int val, vector<vector<bool>>& vis) {
    vis[x][y] = true;
    for (int d = 0; d < 4; ++d) {
        int nx = x + dx[d];
        int ny = y + dy[d];
        if (nx >= 0 && nx < n && ny >=0 && ny < n) {
            if (!vis[nx][ny] && mat[nx][ny] == val) {
                dfs(nx, ny, val, vis);
            }
        }
    }
}

// 验证条件3：0的连通块数 + 1的连通块数 == n
bool checkConn() {
    vector<vector<bool>> vis(n, vector<bool>(n, false));
    int cnt0 = 0, cnt1 = 0;
    // 统计0的连通块
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!vis[i][j] && mat[i][j] == 0) {
                cnt0++;
                dfs(i, j, 0, vis);
            }
        }
    }
    // 重置访问标记，统计1的连通块
    fill(vis.begin(), vis.end(), vector<bool>(n, false));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!vis[i][j] && mat[i][j] == 1) {
                cnt1++;
                dfs(i, j, 1, vis);
            }
        }
    }
    // 输出连通块数量（方便打表观察）
    // cout << "  连通块：0的块数=" << cnt0 << "，1的块数=" << cnt1 << "，总和=" << cnt0+cnt1 << endl;
    return (cnt0 + cnt1) == n;
}

// 输出当前符合条件的矩阵（带格式，方便观察）
void printMat() {
    cnt_valid++;
    cout << "===== 符合条件的好矩阵 No." << cnt_valid << " =====" << endl;
    // // 验证并输出行和
    // cout << "  行和：";
    // for (int i = 0; i < n; ++i) {
    //     int sum = 0;
    //     for (int j = 0; j < n; ++j) sum += mat[i][j];
    //     cout << sum << " ";
    // }
    // cout << endl;
    // // 验证并输出列和
    // cout << "  列和：";
    // for (int j = 0; j < n; ++j) {
    //     int sum = 0;
    //     for (int i = 0; i < n; ++i) sum += mat[i][j];
    //     cout << sum << " ";
    // }
    // cout << endl;
    // 输出矩阵本身（01之间加空格，对齐）
    cout << "  矩阵：" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "    ";
        for (int j = 0; j < n; ++j) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << "-------------------------" << endl;
}

// 回溯生成所有01矩阵：pos = i*n + j 表示当前填充第pos个位置（按行优先）
void backtrack(int pos) {
    // 填充完所有位置，验证三个条件
    if (pos == n * n) {
        if (checkRow() && checkCol() && checkConn()) {
            printMat(); // 符合条件则输出
        }
        return;
    }
    int i = pos / n; // 当前行
    int j = pos % n; // 当前列
    
    // 剪枝：先计算当前行已填充的和，若加1后超过n-1，则不填1
    int cur_row_sum = 0;
    for (int k = 0; k < j; ++k) cur_row_sum += mat[i][k];
    // 尝试填0
    mat[i][j] = 0;
    backtrack(pos + 1);
    // 尝试填1（剪枝：行和不超过n-1才填）
    if (cur_row_sum + 1 < n) {
        mat[i][j] = 1;
        backtrack(pos + 1);
    }
}

// 初始化并启动暴力打表
void bruteForce() {
    mat.assign(n, vector<int>(n, 0));
    cnt_valid = 0;
    cout << "========== 开始暴力枚举 " << n << " 阶01矩阵 ==========" << endl;
    backtrack(0);
    cout << "========== 枚举结束，共找到 " << cnt_valid << " 个好矩阵 ==========" << endl;
}

int main() {
    // 输入n（建议1、2、3，n=4可跑，n≥5勿试！）
    cout << "请输入矩阵阶数n（建议1/2/3）：";
    cin >> n;
    bruteForce();
    return 0;
}