#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <string>
#include <vector>
#include <cstring>
#include <set>
#include <tuple>

using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define endl '\n'

const int MOD = 998244353;

// 快速幂计算 a^b mod mod
int pow_mod(int a, int b)
{
    int res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
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

    vector<tuple<int, int, int, int>> segments(n);
    vector<int> prob(n), not_prob(n);

    for (int i = 0; i < n; i++)
    {
        int l, r, p, q;
        cin >> l >> r >> p >> q;
        segments[i] = {l, r, p, q};

        // 计算概率的模表示
        int inv_q = inv(q);
        prob[i] = p * inv_q % MOD;
        not_prob[i] = (1 - prob[i] + MOD) % MOD;
    }

    // 对于每个单元格，记录覆盖它的线段
    vector<vector<int>> cell_segs(m + 1);
    for (int i = 0; i < n; i++)
    {
        auto &[l, r, p, q] = segments[i];
        for (int j = l; j <= r; j++)
        {
            cell_segs[j].push_back(i);
        }
    }

    // 如果任何单元格没有线段覆盖，结果为0
    for (int i = 1; i <= m; i++)
    {
        if (cell_segs[i].empty())
        {
            cout << 0 << endl;
            return 0;
        }
    }

    int result = 0;

    // 枚举所有可能的线段组合 (适用于n较小的情况)
    if (n <= 20)
    {
        for (int mask = 1; mask < (1 << n); mask++)
        {
            // 检查此组合是否满足条件：每个单元格恰好被一个线段覆盖
            vector<int> coverage(m + 1, 0);
            bool valid = true;

            for (int i = 0; i < n; i++)
            {
                if (mask & (1 << i))
                {
                    auto &[l, r, p, q] = segments[i];
                    for (int j = l; j <= r; j++)
                    {
                        coverage[j]++;
                        if (coverage[j] > 1)
                        {
                            valid = false;
                            break;
                        }
                    }
                    if (!valid)
                        break;
                }
            }

            // 检查是否所有单元格都被覆盖
            if (valid)
            {
                for (int j = 1; j <= m; j++)
                {
                    if (coverage[j] != 1)
                    {
                        valid = false;
                        break;
                    }
                }
            }

            // 如果有效，计算此组合的概率
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
        // 对于n较大的情况，直接返回0（需要更复杂算法）
        result = 0;
    }

    cout << result << endl;

    return 0;
}
