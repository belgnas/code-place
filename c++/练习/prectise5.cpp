#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <string>
#include <vector>
#include <cstring>
#include <set>

using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define endl '\n'

const int MOD = 998244353; // 修复：添加分号

struct Segment
{
    int l, r, p, q;
};

// 快速幂
int pow_mod(int a, int b)
{
    int res = 1;
    while (b > 0) // 修复：条件应为b > 0
    {
        if (b & 1)
        {
            res = res * a % MOD;
        }
        a = a * a % MOD;
        b >>= 1;
    }
    return res; // 修复：添加返回值
}

// 计算逆元
int inv(int x)
{
    return pow_mod(x, MOD - 2);
}

signed main()
{
    IOS;

    int n, m;
    cin >> n >> m;

    vector<Segment> segments(n);
    vector<int> prob(n), not_prob(n);

    for (int i = 0; i < n; i++)
    {
        int l, r, p, q;
        cin >> l >> r >> p >> q;
        segments[i] = {l, r, p, q};

        int inv_q = inv(q);
        prob[i] = p * inv_q % MOD;
        not_prob[i] = (1 - prob[i] + MOD) % MOD;
    }

    vector<vector<int>> cell_segs(m + 1);
    for (int i = 0; i < n; i++)
    {
        int l = segments[i].l;
        int r = segments[i].r;
        // 修复：循环应该从l开始，而不是1
        for (int j = l; j <= r; j++)
        {
            if (j <= m) // 确保不超出范围
                cell_segs[j].push_back(i);
        }
    }

    for (int i = 1; i <= m; i++)
    {
        if (cell_segs[i].empty())
        {
            cout << '0' << endl;
            return 0;
        }
    }

    int result = 0; // 修复：变量名拼写错误

    if (n <= 20)
    {
        for (int mask = 1; mask < (1 << n); mask++)
        {
            vector<int> cover(m + 1, 0); // 修复：语法错误，分号改为逗号并添加分号
            bool valid = true;

            for (int i = 0; i < n; i++)
            {
                if (mask & (1 << i))
                {
                    int l = segments[i].l;
                    int r = segments[i].r;
                    for (int j = l; j <= r; j++)
                    {
                        if (j > m)
                            continue; // 防止越界
                        cover[j]++;
                        if (cover[j] > 1)
                        {
                            valid = false;
                            break;
                        }
                    }
                    if (!valid)
                        break;
                }
            }

            if (valid)
            {
                for (int j = 1; j <= m; j++)
                {
                    if (cover[j] != 1)
                    {
                        valid = false;
                        break;
                    }
                }
            }

            if (valid)
            {
                int p = 1;
                for (int i = 0; i < n; i++)
                {
                    if (mask & (1 << i))
                    {
                        p = p * prob[i] % MOD;
                    }
                    else
                    {
                        p = p * not_prob[i] % MOD;
                    }
                }
                result = (result + p) % MOD;
            }
        }
    }
    else
    {
        result = 0;
    }

    cout << result << endl;

    return 0;
}
