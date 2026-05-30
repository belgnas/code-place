// 牛客竞赛 小红的字符串同构（A组，B组）

// 知识点：组合数学

// 难度：易

// https://ac.nowcoder.com/acm/contest/72647/D

// 思路：我们可以先计算出满足第一个条件的字符串数量：用乘法原理计算，答案为25^n然后我们需要减去和原字符串同构的情况，答案为最大的字符减去最小的字符这么多。

#include <iostream>
#include <string>
using namespace std;

const int mod = 1e9 + 7;

int main()
{
    string s;
    cin >> s;

    // 避免使用与标准库函数同名的变量名
    char maxChar = s[0];
    char minChar = s[0];

    // 遍历字符串，找出字符的最大值和最小值
    for (int i = 0; i < static_cast<int>(s.length()); i++)
    {
        if (maxChar < s[i])
        {
            maxChar = s[i];
        }
        if (minChar > s[i])
        {
            minChar = s[i];
        }
    }

    // 计算差值
    int num = ('z' - maxChar) + (minChar - 'a');

    // 计算 25 的字符串长度次幂并在过程中取模
    long long power = 1;
    for (int i = 0; i < static_cast<int>(s.length()); i++)
    {
        power = (power * 25) % mod;
    }

    // 计算最终结果并处理可能的负数情况
    long long ans = (power - num + mod) % mod;

    cout << ans << endl;

    return 0;
}