#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define endl '\n'

const int MAX_VAL = 5000;  // 元素的最大值
const int MAX_SUM = 10000; // 最大可能的和（5000+5000）

signed main()
{
    IOS;

    int n;
    cin >> n;
    vector<int> count(MAX_VAL + 1, 0); // 统计每个元素的频率

    for (int i = 0; i < n; ++i)
    {
        int x;
        cin >> x;
        count[x]++;
    }

    int max_pairs = 0;
    // 遍历所有可能的和s
    for (int s = 2; s <= MAX_SUM; ++s)
    {
        int current_pairs = 0;
        // 遍历x从1到s/2，避免重复计算
        for (int x = 1; x <= s / 2; ++x)
        {
            int y = s - x;
            // 确保y在有效范围内（1到MAX_VAL）
            if (y < 1 || y > MAX_VAL)
            {
                continue;
            }
            if (x == y)
            {
                // 元素相同，数对数量为频率的一半
                current_pairs += count[x] / 2;
            }
            else
            {
                // 元素不同，数对数量为两者频率的最小值
                current_pairs += min(count[x], count[y]);
            }
        }
        // 更新最大数对数量
        if (current_pairs > max_pairs)
        {
            max_pairs = current_pairs;
        }
    }

    // 最大长度为最大数对数量乘以2
    cout << max_pairs * 2 << endl;

    return 0;
}