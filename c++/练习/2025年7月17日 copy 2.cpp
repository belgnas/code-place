#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
    {
        int n, k;
        cin >> n >> k;

        vector<int> h(n + 1);
        int max_h = 0;
        for (int i = 1; i <= n; ++i)
        {
            cin >> h[i];
            max_h = max(max_h, h[i]);
        }

        if (h[k] == max_h)
        {
            cout << "YES" << endl;
            continue;
        }

        int current_tower = k;
        int current_time = 1;
        bool found = false;

        while (true)
        {
            // 检查当前塔是否是最高塔
            if (h[current_tower] == max_h)
            {
                found = true;
                break;
            }

            // 寻找可达的最高塔
            int next_tower = -1;
            int max_next_height = 0;

            for (int j = 1; j <= n; ++j)
            {
                if (j == current_tower)
                    continue;

                // 检查是否可达：高度 >= 当前时间 且 <= 初始塔高度
                if (h[j] >= current_time && h[j] <= h[k])
                {
                    if (h[j] > max_next_height)
                    {
                        max_next_height = h[j];
                        next_tower = j;
                    }
                }
            }

            // 没有可达的塔，失败
            if (next_tower == -1)
                break;

            // 计算传送到下一塔的新时间
            int time = abs(h[current_tower] - h[next_tower]);
            current_time += time;
            current_tower = next_tower;

            // 如果新时间超过当前塔高度，失败
            if (current_time > h[current_tower])
                break;
        }

        cout << (found ? "YES" : "NO") << endl;
    }

    return 0;
}