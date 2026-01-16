#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main()
{
    // 读取测试用例的数量
    int t;
    cin >> t;

    // 循环处理每个测试用例
    while (t--)
    {
        // 读取字符串的长度 n 和参数 k
        int n, k;
        cin >> n >> k;
        // 读取字符串 s
        string s;
        cin >> s;

        // 如果 k 大于等于字符串的长度 n，无法进行任何操作，直接输出 0
        if (k >= n)
        {
            cout << 0 << endl;
            // 跳过本次循环，处理下一个测试用例
            continue;
        }

        // 创建一个长度为 k 的向量 counts，用于存储每个等价类中字符的出现次数
        // 每个元素是一个 unordered_map，键为字符，值为该字符在当前等价类中的出现次数
        vector<unordered_map<char, int>> counts(k);

        // 遍历每个等价类的起始位置
        for (int i = 0; i < k; ++i)
        {
            // 遍历当前等价类中的所有位置
            for (int j = i; j < n; j += k)
            {
                // 统计当前字符在当前等价类中的出现次数
                counts[i][s[j]]++;
            }
        }

        // 初始化总操作次数为 0
        int total = 0;
        // 遍历每个等价类的字符统计结果
        for (const auto &cnt : counts)
        {
            // 如果当前等价类为空，跳过本次循环
            if (cnt.empty())
                continue;
            // 初始化当前等价类中出现次数最多的字符的出现次数为 0
            int max_freq = 0;
            // 初始化当前等价类中字符的总出现次数为 0
            int m = 0;
            // 遍历当前等价类中每个字符及其出现次数
            for (const auto &[_, freq] : cnt)
            {
                // 更新出现次数最多的字符的出现次数
                max_freq = max(max_freq, freq);
                // 累加当前等价类中字符的总出现次数
                m += freq;
            }
            // 计算将当前等价类中其他字符统一为出现次数最多的字符所需的操作次数，并累加到总操作次数中
            total += (m - max_freq);
        }

        // 输出当前测试用例的最少操作次数
        cout << total << endl;
    }

    return 0;
}