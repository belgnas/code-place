#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

const int mod = 998244353;

// 组合数
int comb_mod(int n, int m, int mod) {
    if (m == 0 || n == m) return 1;
    
    m = min(m, n - m);
    int res = 1;

    for (int i = 1; i <= m; i++) {
        res = res * (n - i + 1) / i;
    }
    res %= mod;

    return res;
}






signed main()
{
    IOS;

    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<int> a(n + 1);
        for (int i = 0; i <= n; i++) cin >> a[i];
        sort(a.begin() + 1, a.end(), greater<int>());

        // for (int i = 1; i <= n; i++) {
        //     a[i] -= a[n];
        // }

        // 必须是这样的
        // ***
        // ********
        // ********

        // 先统计能变成多少个mx - 1，统计记录下花费多少a[0]，如果a[0] < 0，就直接返回false
        // 然后再统计能变成多少个mx，统计记录下花费多少a[0]，如果a[0] < 0，就直接中断。
        bool flat1 = true;
        int mx = a[1];
        for (int i = 1; i <= n; i++) {
            if (a[i] >= mx - 1) {
                continue;
            }
            else {
                int num = mx - 1 - a[i];
                a[i] += num;
                a[0] -= num;
                if (a[0] < 0) {
                    flat1 = false;
                    break;
                }
            }
        }

        if (!flat1) {
            cout << 0 << endl;
            continue;
        }

        // cout << "a[0] = " << a[0] << endl;

        int num1 = 0, num2 = n;
        int need = n;
        for (int i = 1; i <= n; i++) {
            int num = mx - a[i];

            // 记录最后一轮有多少人需要花费a[0]，
            if (num <= 0) {
                need--;
            }

            if (a[0] >= num) {
                num1++;
                num2--;
                a[0] -= num;
            }
            else {
                break;
            }
        }
        // cout << "num1 = " << num1 << " num2 = " << num2 << endl;
        // cout << "need = " << need << endl;

        // 从need里面选num2个人
        int choose = comb_mod(need, num2, mod);
        // cout << "choose = " << choose << endl;

        int res1 = 1;
        for (int i = 1; i <= num1; i++) {
            res1 = res1 * i % mod;
        }

        int res2 = 1;
        for (int i = 1; i <= num2; i++) {
            res2 = res2 * i % mod;
        }

        // cout << "res1 = " << res1 << " res2 = " << res2 << endl;

        int ans = res1 * res2 % mod;
        ans = ans * choose % mod;

        cout << ans << endl;
    }

    return 0;
}