#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <climits>
using namespace std;
#define int long long
#define endl '\n'

#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)

signed main() {

    IOS;
    
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<string> s(n);
        for (int i = 0; i < n; i++) {
            cin >> s[i];
        }
        vector<vector<int>> a(n, vector<int>(m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                a[i][j] = (s[i][j] == '1');
            }
        }

        vector<int> col_1(m), col_0(m); // 记录每一列的1的数量和0的数量
        for (int j = 0; j < m; j++) {
            for (int i = 0; i < n; i++) {
                col_1[j] += a[i][j];
                col_0[j] += (1 - a[i][j]);
            }
        }

        for (int i = 0; i < n; i++) {
            int res = 0;
            // 求未修改的位置的贡献 col_1 或者 col_0 (记录为c)
            // 加上修改后那段长度的贡献 n - c - 1
            // res 等于 未修改部分的贡献 + 修改后部分的贡献
            // c部分 + ((n - c - 1) 部分
            // 对于修改后的部分，可以理解成 c + (n - c - 1) - c;
            // 等效于 先假设全部都未修改, 算出来全部的c后
            // 再加上 (n - c - 1) - c 的最小子段和
            // 最后算出的结果就是 答案
            for (int j = 0; j < m; j++) {
                int c = a[i][j] == 0 ? col_1[j] : col_0[j];
                res += c;
            }
            // 计算 数组(n - c) - c
            vector<int> temp(m);
            for (int j = 0; j < m; j++) {
                int c = a[i][j] == 0 ? col_1[j] : col_0[j];
                temp[j] = (n - c - 1) - c;
            }
            // 计算 数组(n - c - 1) - c 的最小连续子段和
            int min_len = LLONG_MAX;
            int cur_len = 0;
            for (int j = 0; j < m; j++) {
                cur_len = min(cur_len + temp[j], temp[j]);
                min_len = min(min_len, cur_len);
            }
            res += min(min_len, 0LL);

            cout << res << endl;
        }

    }

    return 0;
}