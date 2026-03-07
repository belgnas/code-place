#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;

const int maxn = 5e4 + 10;

// 全局变量定义
int n, t, x;           // n:数组长度, t:测试用例数, x:临时变量(未使用)
int ans, best_pos;     // ans:最大贡献值, best_pos:最优删除位置(输出时需+1)
int a[maxn];           // 存储输入数组
int left_pairs[maxn];  // left_pairs[j]:前j个元素形成的有效对数量
int right_pairs[maxn]; // right_pairs[j]:从j到末尾元素形成的有效对数量
stack<int> s;          // 单调栈,用于维护递减序列

/**
 * 初始化函数：重置计数器和数组
 * 每次处理新测试用例前调用,避免数据残留
 */
inline void init()
{
    ans = 0;
    best_pos = 0;
    memset(left_pairs, 0, sizeof(left_pairs));   // 清零左侧贡献数组
    memset(right_pairs, 0, sizeof(right_pairs)); // 清零右侧贡献数组
}

/**
 * 主函数：处理多组测试用例
 * 核心算法：
 * 1. 预处理left_pairs数组：计算每个前缀的有效对数量
 * 2. 预处理right_pairs数组：计算每个后缀的有效对数量
 * 3. 枚举删除位置,快速计算删除后的总贡献
 */
int main()
{
    // 关闭输入输出流的同步,提高IO效率(约10倍)
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> t;
    for (int i = 1; i <= t; i++)
    { // 处理每组测试用例
        cin >> n;

        init(); // 初始化全局变量

        // 读取输入数组
        for (int j = 1; j <= n; j++)
            cin >> a[j];

        // ===== 预处理左侧贡献数组 left_pairs =====
        // left_pairs[j]表示前j个元素中,以每个元素为右端点的有效对数量之和
        // 有效对定义：对于i<j,不存在k(i<k<j)使得a[k]同时大于a[i]和a[j]
        while (!s.empty())
            s.pop(); // 清空栈
        for (int j = 1; j <= n; j++)
        {
            left_pairs[j] = left_pairs[j - 1]; // 继承前j-1个元素的贡献
            int popped_count = 0;

            // 弹出所有小于当前元素的值：维护单调递减栈
            while (!s.empty() && s.top() < a[j])
            {
                popped_count++;
                s.pop();
            }

            // 计算当前元素加入后的新增贡献（这里的popped_count表示的是以当前arr[j]为右端点，弹出的元素为左端点的内部对（2端点之间同样可以有其他比端点小的（内部对）元素），“+1”表示的是以当前元素arr[j]为右端点，左边第一个比arr[j]大的元素为左端点的边界对（2端点之间同样可以有其他比端点小的（内部对）元素））
            if (!s.empty())
                left_pairs[j] += popped_count + 1; // 栈顶元素作为左端点,新增popped_count + 1个有效对
            else
                left_pairs[j] += popped_count; // 栈为空时,新增popped_count个有效对

            s.push(a[j]); // 当前元素入栈
        }

        // ===== 预处理右侧贡献数组 right_pairs =====
        // 与left_pairs对称,从右向左扫描
        while (!s.empty())
            s.pop(); // 清空栈
        for (int j = n; j >= 1; j--)
        {
            right_pairs[j] = right_pairs[j + 1]; // 继承后j+1到n的贡献
            int popped_count = 0;

            // 弹出所有小于当前元素的值
            while (!s.empty() && s.top() < a[j])
            {
                popped_count++;
                s.pop();
            }

            // 计算当前元素加入后的新增贡献
            if (!s.empty())
                right_pairs[j] += popped_count + 1; // 栈顶元素作为右端点
            else
                right_pairs[j] += popped_count; // 栈为空时

            s.push(a[j]); // 当前元素入栈
        }

        // ===== 计算最优删除位置 =====
        // 枚举每个删除位置j,计算删除后的总贡献
        for (int j = 1; j <= n; j++)
        {
            // 删除位置j后的总贡献 = 原始总贡献 - 位置j的左侧贡献 - 位置j+1的右侧贡献
            // 这里的"左侧贡献"和"右侧贡献"指包含位置j的贡献,删除后这些贡献消失
            int current_contribution = left_pairs[n] - left_pairs[j] - right_pairs[j + 1];

            if (current_contribution > ans)
            {
                ans = current_contribution; // 更新最大贡献
                best_pos = j + 1;           // 记录最优删除位置(注意题目要求输出j+1)
            }
        }

        // 输出结果：测试用例编号、最优删除位置、最大贡献值
        cout << "Case #" << i << ": " << best_pos << " " << ans << "\n";
    }
    return 0;
}