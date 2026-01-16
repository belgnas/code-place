// #include <bits/stdc++.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <string>
#include <vector>
#include <cstring>
#include <set>
#include <tuple>
#include <bitset>
#include <utility>
#include <queue> // 队列
#include <deque> // 双端队列
#include <stack>

using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define endl '\n'
typedef pair<int, int> PII;

const int INF = 0x3f3f3f3f;
// &: 只有当两个相应的位都为 1 时,结果位才为 1,否则为 0
// |: 只要两个相应的位中有一个为 1,结果位就为 1,否则为 0
// ^: 如果两个相应的位不同(一个为 1，另一个为 0),则结果位为 1,如果相同则结果位为 0

signed main()
{
    IOS;

    // ()()(()())
    IOS;
    string s;
    cin >> s;

    int max_len = 0;

    // 第一次遍历：从左到右，处理 ) 多于 ( 的情况
    int left = 0, right = 0;
    for (char c : s)
    {
        if (c == '(')
            left++;
        else
            right++;

        if (right > left)
        { // 无效，重置
            left = right = 0;
        }
        else if (left == right)
        { // 有效匹配
            max_len = max(max_len, 2 * left);
        }
    }

    // 第二次遍历：从右到左，处理 ( 多于 ) 的情况
    left = right = 0;
    for (int i = s.size() - 1; i >= 0; i--)
    {
        char c = s[i];
        if (c == '(')
            left++;
        else
            right++;

        if (left > right)
        { // 无效，重置
            left = right = 0;
        }
        else if (left == right)
        { // 有效匹配
            max_len = max(max_len, 2 * left);
        }
    }

    cout << max_len << endl;

    return 0;
}