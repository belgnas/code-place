#include <iostream>
#include <string>
using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define endl '\n'
typedef pair<int, int> PII;

signed main()
{
    IOS;
    int n, m;
    cin >> n >> m;

    string base = "0011";
    // 偏移 s 下，长度为 r 的片段中 '1' 的个数（r = m % 4）
    int ones[4][4] = {
        {0,0,0,1}, // s=0
        {0,0,1,2}, // s=1
        {0,1,2,2}, // s=2
        {0,1,1,1}  // s=3
    };
    int k = m / 4, r = m % 4;
    int target = (n * m + 1) / 2;   // 黑子数量要求（奇数格黑多1）

    for (int flip = 0; flip < 2; ++flip) {
        for (int isAFirst = 0; isAFirst < 2; ++isAFirst) {
            int odd = isAFirst ? (n + 1) / 2 : n / 2;   // A 行出现的次数
            int even = n - odd;
            for (int s = 0; s < 4; ++s) {
                int A1 = 2 * k + ones[s][r];             // A 行中 1 的个数
                int B1 = m - A1;                         // B 行中 1 的个数
                int total1 = odd * A1 + even * B1;       // 总黑子数
                if (total1 == target) {                  // 找到合法方案
                    for (int i = 0; i < n; ++i) {
                        bool rowA = (i % 2 == 0) ? isAFirst : !isAFirst;
                        string row;
                        row.reserve(m);
                        for (int j = 0; j < m; ++j) {
                            char c = base[(j + s) & 3];
                            if (!rowA) c = (c == '0' ? '1' : '0');
                            if (flip)  c = (c == '0' ? '1' : '0');
                            row += c;
                        }
                        cout << row << endl;
                    }
                    return 0;
                }
            }
        }
    }
    cout << -1 << endl;
    return 0;
}