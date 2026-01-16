#include <bits/stdc++.h>
using namespace std;

vector<int> intNum;

void gen()
{
    auto back = [&](auto self, string &cur, int n, int len) -> void
    {
        if (len == n)
        {
            intNum.push_back(stoi(cur));
            return;
        }
        for (int i = 1; i <= n; ++i)
        {
            if (cur.find('0' + i) == string::npos)
            {
                cur.push_back('0' + i);
                self(self, cur, n, len + 1);
                cur.pop_back();
            }
        }
    };
    for (int i = 1; i <= 9; ++i)
    {
        string s;
        back(back, s, i, 0);
    }
    sort(intNum.begin(), intNum.end()); // 排序以便二分查找
}

int main()
{
    gen(); // 预处理生成所有有趣数字
    int T;
    cin >> T;
    while (T--)
    {
        int l, r;
        cin >> l >> r;
        // 二分查找第一个大于等于l的有趣数字
        auto it = lower_bound(intNum.begin(), intNum.end(), l);
        if (it != intNum.end() && *it <= r)
        {
            cout << *it << endl;
        }
        else
        {
            cout << -1 << endl;
        }
    }
    return 0;
}