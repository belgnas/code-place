#include <iostream>
#include <vector>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)

struct Casino
{
    long long l, r, real;
};

int main()
{
    IOS;

    int t;
    cin >> t;
    while (t--)
    {
        int n;
        long long k;
        cin >> n >> k;

        vector<Casino> casinos;
        for (int i = 0; i < n; ++i)
        {
            long long l, r, real;
            cin >> l >> r >> real;
            // 初始筛选：保留未来可能访问的赌场（r >= 当前硬币数k）
            if (r >= k)
            {
                casinos.push_back({l, r, real});
            }
        }

        long long current = k; // 当前硬币数
        bool can_improve = true;

        while (can_improve)
        {
            can_improve = false;
            long long best_real = current; // 记录最优的reali
            int best_idx = -1;

            // 寻找当前可访问的、能提升硬币数的赌场
            for (int i = 0; i < casinos.size(); ++i)
            {
                const auto &c = casinos[i];
                // 检查是否可访问：当前硬币数在[li, ri]范围内
                if (c.l <= current && current <= c.r)
                {
                    // 优先选择能让硬币数增加最多的赌场
                    if (c.real > best_real)
                    {
                        best_real = c.real;
                        best_idx = i;
                        can_improve = true;
                    }
                }
            }

            if (can_improve)
            {
                current = best_real; // 更新当前硬币数
                // 过滤掉未来不可能访问的赌场（ri < 当前硬币数）
                vector<Casino> new_casinos;
                for (const auto &c : casinos)
                {
                    if (c.r >= current)
                    {
                        new_casinos.push_back(c);
                    }
                }
                casinos.swap(new_casinos);
            }
        }

        cout << current << '\n';
    }

    return 0;
}