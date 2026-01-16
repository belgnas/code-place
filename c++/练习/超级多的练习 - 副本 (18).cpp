#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0) // 加速输入输出

/*
 * 函数功能：判断给定排列是否可能是题中算法遍历完全二叉树的输出序列
 * 参数说明：
 *   arr: 输入的排列数组
 *   n: 完全二叉树的节点数量
 * 返回值：
 *   true: 可能是合法输出序列
 *   false: 不可能是合法输出序列
 */
bool test(vector<int> arr, int n)
{
    // 处理边界情况：空树（虽然题目中n≥1，但防御性编程）
    if (n == 0)
        return true;

    // 规则1：根节点（编号1）必须是序列的第一个元素
    // 因为题中算法从根节点开始遍历，深度0的节点只有1个（节点1）
    if (arr[0] != 1)
        return false;

    // 计算每个节点的深度（深度定义：根节点深度为0）
    // 节点i的深度 = log2(i) 的整数部分，例如：
    // i=1 → log2(1)=0 → 深度0
    // i=2/3 → log2(2)=1, log2(3)≈1.58→深度1
    // i=4-7 → log2(i)∈[2,3)→深度2
    unordered_map<int, int> depthMap;
    for (int i = 1; i <= n; i++)
    {
        depthMap[i] = log2(i); // 自动向下取整（转换为int时舍弃小数部分）
    }

    // 按深度分组：将序列中的节点按深度归类
    // 例如：深度0的节点存入depthNodes[0]，深度1的节点存入depthNodes[1]
    unordered_map<int, vector<int>> depthNodes;
    for (int num : arr)
    {
        depthNodes[depthMap[num]].push_back(num);
    }

    // 检查深度是否连续递增（从0开始无跳跃）
    // 合法的深度序列必须是0,1,2,...,k（k为最大深度）
    vector<int> depths;
    for (auto &[depth, nodes] : depthNodes)
    {
        depths.push_back(depth);
    }
    sort(depths.begin(), depths.end()); // 排序后检查连续性
    for (int i = 0; i < depths.size(); i++)
    {
        if (depths[i] != i) // 深度i的位置必须是深度值i
            return false;
    }

    // 检查同深度节点是否在序列中连续出现（顺序可任意，但必须连续）
    int idx = 0; // 当前检查的序列起始位置
    for (int d = 0; d < depths.size(); d++)
    {                                         // 按深度0,1,2...依次检查
        int depthSize = depthNodes[d].size(); // 该深度的节点数量
        // 提取序列中当前深度的子数组
        vector<int> currentNodes(arr.begin() + idx, arr.begin() + idx + depthSize);
        // 提取该深度所有应有的节点（排序后便于比较）
        vector<int> expectedNodes = depthNodes[d];

        // 排序后比较：若元素相同则说明连续出现（顺序无关）
        sort(currentNodes.begin(), currentNodes.end());
        sort(expectedNodes.begin(), expectedNodes.end());
        if (currentNodes != expectedNodes)
        {
            return false;
        }

        idx += depthSize; // 移动到下一个深度的起始位置
    }

    return true;
}

int main()
{
    IOS; // 启用输入输出加速

    int t;
    cin >> t;
    while (t--)
    { // 处理多个测试用例
        int n;
        cin >> n;
        vector<int> arr(n);
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i]; // 读取排列序列
        }
        // 输出判断结果：YES（合法）或NO（不合法）
        cout << (test(arr, n) ? "YES" : "NO") << endl;
    }

    return 0;
}