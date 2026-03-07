// 牛客竞赛 1001【模板】整数域二分

// 知识点：二分

// https://ac.nowcoder.com/acm/contest/22353/1001

#include <iostream>
#include <vector>
#include <algorithm>

// 使用 using namespace std 简化后续对标准库中标识符的使用
using namespace std;

// 二分查找第一个大于等于 target 的元素的索引
// 参数 arr 是已排序的数组，target 是要查找的目标值
int lowerBound(const vector<int>& arr, int target)
{
    // 初始化左边界为数组的起始位置
    int left = 0;
    // 初始化右边界为数组的末尾位置之后一位
    int right = arr.size();

    // 二分查找的循环条件，当左边界小于右边界时继续查找
    while (left < right)
    {
        // 计算中间位置
        int mid = left + (right - left) / 2; // 使用 left + (right - left) / 2 而不是 (left + right) / 2 是为了避免整数溢出的问题，特别是当 left 和 right 都很大时。

        // 如果中间元素小于目标值，说明目标值在右半部分
        if (arr[mid] < target)
        {
            // 更新左边界为中间位置的下一个位置
            left = mid + 1;
        }
        else
        {
            // 否则，目标值在左半部分或者就是中间元素，更新右边界为中间位置
            right = mid;
        }
    }
    // 最终 left 即为第一个大于等于 target 的元素的索引
    return left;
}

// 二分查找最后一个小于等于 target 的元素的索引
// 参数 arr 是已排序的数组，target 是要查找的目标值
int upperBound(const vector<int>& arr, int target)
{
    // 初始化左边界为数组的起始位置
    int left = 0;
    // 初始化右边界为数组的末尾位置之后一位
    int right = arr.size();

    // 二分查找的循环条件，当左边界小于右边界时继续查找
    while (left < right)
    {
        // 计算中间位置
        int mid = left + (right - left) / 2;

        // 如果中间元素小于等于目标值，说明目标值可能在右半部分
        if (arr[mid] <= target)
        {
            // 更新左边界为中间位置的下一个位置
            left = mid + 1;
        }
        else
        {
            // 否则，目标值在左半部分，更新右边界为中间位置
            right = mid;
        }
    }
    // 最终 left - 1 即为最后一个小于等于 target 的元素的索引
    return left - 1;
}

// 处理区间元素个数查询的函数
// 参数 arr 是已排序的数组，l 是区间左边界，r 是区间右边界
int query(const vector<int>& arr, int l, int r)
{
    // 调用 lowerBound 函数找到第一个大于等于 l 的元素的索引
    int leftIndex = lowerBound(arr, l);
    // 调用 upperBound 函数找到最后一个小于等于 r 的元素的索引
    int rightIndex = upperBound(arr, r);

    // 如果左边界索引大于右边界索引，说明区间内没有满足条件的元素
    if (leftIndex > rightIndex)
    {
        return 0;
    }
    // 计算满足条件的元素个数，即右边界索引减去左边界索引再加 1
    return rightIndex - leftIndex + 1;
}

int main()
{
    int n, q;
    // 读取数组的长度 n 和查询的次数 q
    cin >> n >> q;

    // 定义一个长度为 n 的整数向量 arr 用于存储数组元素
    vector<int> arr(n);
    // 循环读取数组的 n 个元素
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    // 对数组进行排序，以便后续使用二分查找
    sort(arr.begin(), arr.end());

    // 循环处理 q 次查询操作
    for (int i = 0; i < q; i++)
    {
        int l, r;
        // 读取每次查询的区间左边界 l 和右边界 r
        cin >> l >> r;
        // 调用 query 函数进行查询，得到满足条件的元素个数
        int result = query(arr, l, r);
        // 输出查询结果
        cout << result << endl;
    }

    return 0;
}