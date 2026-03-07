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
        int A, B, n;
        cin >> A >> B >> n;
        vector<int> a(A), b(B); // 使用vector动态数组
        for (int i = 0; i < A; i++)
            cin >> a[i];
        for (int i = 0; i < B; i++)
            cin >> b[i];

        // 边界条件：总人数不足
        if (A + B < n)
        {
            cout << "-1" << endl;
            continue;
        }

        sort(a.begin(), a.end(), greater<int>()); // 降序排序
        sort(b.begin(), b.end(), greater<int>());

        int max_sum = 0;
        int min_y = (n + 1) / 2; // 最小安静人数（y ≥ min_y）
        int max_y = min(A, n);   // 最大安静人数（不超过可用安静数和n）

        // 枚举安静人数y从min_y到max_y，对应的闹腾人数x = n - y
        for (int y = min_y; y <= max_y; y++)
        {
            int x = n - y;
            if (x < 0 || x > B)
                continue; // 闹腾人数不能为负，且不超过可用闹腾数
            if (x > y)
                continue; // 必须满足x ≤ y（闹腾不相邻）

            // 取前y大的安静和前x大的闹腾
            int sum = 0;
            for (int i = 0; i < y; i++)
                sum += a[i]; // 前y个安静
            for (int i = 0; i < x; i++)
                sum += b[i]; // 前x个闹腾
            max_sum = max(max_sum, sum);
        }

        // 特殊情况：当min_y > A时（安静人数不足，例如A=2, n=5, min_y=3 > A=2）
        if (min_y > A)
        {
            cout << "-1" << endl;
        }
        else
        {
            cout << max_sum << endl;
        }
    }
    return 0;
}