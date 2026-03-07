#include <iostream>
#include <math.h>
#include <string.h>
#include <algorithm>
#include <iomanip>
#include <iostream>
using namespace std;

int cnt[291]; // 记录每个分数出现的次数

int main()
{
    int n, k, s;
    cin >> n >> k >> s;

    int ans = 0;
    while (n--)
    {
        int tt, pat;
        cin >> tt >> pat;

        if (tt >= 175)
            if (pat >= s) // 根据题目的最多推荐，同时满足 天梯赛 和 PAT 分数要求的人不计入数组
                ans++;
            else if (cnt[tt] < k) // 防止人数超过k的批次
            {
                ans++;
                cnt[tt]++;
            }
    }

    cout << ans;
    return 0;
}