#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define endl "\n";
// #define int long long

int main()
{
    IOS;

    int T;
    cin >> T;
    while (T--)
    {
        int n, k;
        cin >> n >> k;
        vector<int> h(n + 1); // 存储塔的高度（索引1~n，与题目编号一致）
        for (int i = 1; i <= n; ++i)
        {
            cin >> h[i];
        }

        int max_height = *max_element(h.begin() + 1, h.end()); // 最高塔的高度

        // 若初始塔已是最高塔，直接返回YES
        if (h[k] == max_height)
        {
            cout << "YES\n";
            continue;
        }

        int current_time = 1;  // 初始时间（水位从1开始）
        int current_tower = k; // 当前所在塔
        set<int> visited;      // 记录已访问的塔，避免循环

        bool can_reach = false;
        while (true)
        {
            // 若当前塔是最高塔，成功
            if (h[current_tower] == max_height)
            {
                can_reach = true;
                break;
            }

            // 标记当前塔为已访问
            if (visited.count(current_tower))
            {
                break; // 循环访问，无法前进
            }
            visited.insert(current_tower);

            // 寻找所有可达的塔中最优的下一个塔
            int next_tower = -1;
            int best_h = -1; // 记录可达塔中的最高高度

            for (int j = 1; j <= n; ++j)
            {
                if (j == current_tower)
                    continue; // 不能传送到自身

                int transfer_time = abs(h[current_tower] - h[j]); // 传送时间
                // 传送期间的最大水位（传送结束前一刻）：current_time + transfer_time - 1
                // 需满足：传送期间不超过当前塔高度，且到达时不超过目标塔高度
                bool safe_transfer = (current_time + transfer_time - 1 <= h[current_tower]);
                bool safe_arrive = (current_time + transfer_time <= h[j]);

                if (safe_transfer && safe_arrive)
                {
                    // 优先选择高度更高的塔（更接近最高塔）
                    if (h[j] > best_h)
                    {
                        best_h = h[j];
                        next_tower = j;
                    }
                }
            }

            // 没有可达的塔，失败
            if (next_tower == -1)
            {
                break;
            }

            // 更新当前状态，准备下一次传送
            current_time += abs(h[current_tower] - h[next_tower]);
            current_tower = next_tower;
        }

        cout << (can_reach ? "YES" : "NO") << "\n";
    }

    return 0;
}