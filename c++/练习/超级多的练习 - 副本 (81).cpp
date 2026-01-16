#include <bits/stdc++.h>
using namespace std;

#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

int main()
{
    IOS;
    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;
        int arr[n];
        for (int i = 0; i < n; i++)
            cin >> arr[i];

        int ans = -1;                // 初始化 ans 为 -1，表示无逆序对时输出 -1
        multiset<int> left_elements; // 维护左侧已遍历的元素（自动升序排序）

        for (int j = 0; j < n; j++)
        {
            int current = arr[j];
            // 查找左侧比 current 大的元素的最小值（第一个大于的位置）
            auto it = left_elements.upper_bound(current);

            if (it != left_elements.end())
            {
                // 存在大于 current 的元素，最大的大于元素是 multiset 的最后一个元素
                int max_left = *prev(left_elements.end());
                ans = max(ans, current + max_left);
            }

            left_elements.insert(current); // 将当前元素加入左侧集合，供后续元素使用
        }

        cout << ans << endl;
    }
    return 0;
}