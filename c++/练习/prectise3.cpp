/*
OR:|
XOR:^
AND:&
*/

// 核心思想是利用位运算的独立性，将问题分解为 31 个独立位的选择问题

#include <iostream>
#include <vector>
using namespace std;

#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)

const int N = 100010; // 修正分号

int main()
{
    IOS;

    int n, m;
    cin >> n >> m;

    // 存储操作和参数
    vector<string> op(n); // 修正定义方式
    vector<int> t(n);     // 修正定义方式

    for (int i = 0; i < n; i++)
        cin >> op[i] >> t[i];

    // 预处理：计算每一位初始为0和1时的最终结果
    int zero = 0, one = 0xFFFFFFFF; // zero初始全0，one初始全1

    for (int i = 0; i < n; i++)
    {
        if (op[i] == "AND")
        {
            zero &= t[i];
            one &= t[i];
        }
        else if (op[i] == "OR")
        {
            zero |= t[i];
            one |= t[i];
        }
        else if (op[i] == "XOR")
        {
            zero ^= t[i];
            one ^= t[i];
        }
    }

    // 贪心构造初始攻击力x，使得最终结果最大且x ≤ m
    int x = 0;
    int res = 0;

    for (int k = 30; k >= 0; k--)
    { // 从最高位到最低位
        int mask = 1 << k;

        // 优先选择初始位为0（不消耗x）
        if ((zero & mask) != 0)
        {
            res |= mask; // 结果的第k位置1
        }
        // 否则尝试初始位为1（消耗x）
        else if ((one & mask) != 0 && (x + mask <= m))
        {
            x += mask;   // x的第k位置1
            res |= mask; // 结果的第k位置1
        }
    }

    cout << res << endl;
    return 0;
}