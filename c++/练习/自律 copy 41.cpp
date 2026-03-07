#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int test01(const string &s)
{
    int count = 0;
    int n = s.length();

    // 暴力了，没时间了
    for (int i = 0; i < n; ++i)
    {
        if (s[i] != 'o') continue;

        for (int j = i + 1; j < n; ++j)
        {
            if (s[j] != 'v') continue;

            for (int k = j + 1; k < n; ++k)
            {
                if (s[k] == 'o') count++;
            }
        }
    }
    return count;
}

int ans_num(const string &s)
{
    vector<int> str;

    for (int i = 0; i < s.length(); ++i)
    {
        if (s[i] == '?')
        {
            str.push_back(i);
        }
    }

    int max_num = 0;
    int q_count = str.size();

    for (int mask = 0; mask < (1 << q_count); ++mask)
    {
        string temp = s;

        for (int i = 0; i < q_count; ++i)
        {
            if (mask & (1 << i))
            {
                temp[str[i]] = 'v';
            }
            else
            {
                temp[str[i]] = 'o';
            }
        }

        // 计算当前方案的ovo数量
        int n1 = test01(temp);

        // 更新最大值
        if (n1 > max_num)
        {
            max_num = n1;
        }
    }

    return max_num;
}

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        string s;
        cin >> s;

        cout << ans_num(s) << endl;
    }

    return 0;
}