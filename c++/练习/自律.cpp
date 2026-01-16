#include <iostream>
#include <set>
#include <cmath>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

int main()
{
    IOS;

    int n;
    cin >> n;
    if (n == 0)
    {
        cout << 0 << endl;
        return 0;
    }

    set<int> s;
    int first;
    cin >> first;
    s.insert(first);
    int total = first; // 第1天的波动值是自身

    for (int i = 1; i < n; ++i)
    { // 从第2天开始处理
        int a;
        cin >> a;

        auto it = s.lower_bound(a); // 找到第一个>=a的元素
        int min_diff = 2e9;         // 初始化一个较大值

        // 比较当前元素（若存在）
        if (it != s.end())
        {
            min_diff = min(min_diff, *it - a);
        }

        // 比较前一个元素（若存在）
        if (it != s.begin())
        {
            --it;
            min_diff = min(min_diff, a - *it);
        }

        total += min_diff; // 累加当天的最小波动值
        s.insert(a);       // 将当前值加入集合，供后续天数比较
    }

    cout << total << endl;
    return 0;
}