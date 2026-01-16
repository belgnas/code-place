// P1025 [NOIP 2001 提高组] 数的划分

// 知识点：dfs、递归、减枝

// 难度：普及/提高?

// https://www.luogu.com.cn/problem/P1025


// #include <iostream>

// // 深度优先搜索函数
// int dfs(int num, int part, int now)
// {
//     if (part == 1)
//     {
//         return 1;
//     }
//     int sum = 0;
//     for (int i = now; i <= num / part; i++)
//     {
//         sum += dfs(num - i, part - 1, i);
//     }
//     return sum;
// }

// int main()
// {
//     int n, k;
//     using namespace std;
//     cout << "请输入n和k：" << endl;
//     cin >> n >> k;
//     cout << dfs(n, k, 1) << endl;
//     return 0;
// }

#include <iostream>

// 深度优先搜索函数，用于计算将整数 num 分成 part 个正整数的不同分法数量
// num: 剩余待分的整数
// part: 还需要将剩余的数分成的份数
// now: 当前可以选择的最小的数，用于保证分法的顺序性，避免重复计算
int dfs(int num, int part, int now)
{
    // 当只剩下一份需要分时，意味着剩余的 num 作为最后一份，此时只有一种分法
    if (part == 1)
    {
        return 1;
    }
    // 用于累加所有可能的分法数量
    int sum = 0;
    // 从 now 开始枚举当前可以分出的数 i
    // 上限设为 num / part 是一种剪枝操作，若 i 大于 num / part，剩下的数无法再分成 part - 1 份正整数
    for (int i = now; i <= num / part; i++)
    {
        // 递归调用 dfs 函数，计算剩余待分的数（num - i）分成 part - 1 份，且下一次选择的数不小于 i 的分法数量
        // 并将其累加到 sum 中
        sum += dfs(num - i, part - 1, i);
    }
    // 返回总的分法数量
    return sum;
}

int main()
{
    // 定义两个整数 n 和 k，n 表示要被拆分的整数，k 表示要拆分成的份数
    int n, k;
    // 使用标准库中的命名空间，这样可以直接使用 cout 和 cin 等标识符
    using namespace std;
    // 提示用户输入要拆分的整数 n 和要拆分成的份数 k
    cout << "请输入n和k：" << endl;
    // 从标准输入读取用户输入的 n 和 k 的值
    cin >> n >> k;
    // 调用 dfs 函数，从 n 开始拆分成 k 份，且首次选择的数最小为 1
    // 并将结果输出到标准输出
    cout << dfs(n, k, 1) << endl;
    // 程序正常结束，返回 0
    return 0;
}