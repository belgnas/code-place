#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 自定义比较函数，用于比较二维数组的两行
bool compareRows(const vector<int>& row1, const vector<int>& row2) {
    int sum1 = 0, sum2 = 0;
    int n = row1.size();

    // 计算两行的元素和
    for (int i = 0; i < n; ++i) {
        sum1 += row1[i];
        sum2 += row2[i];
    }

    // 优先比较行元素和
    if (sum1 != sum2) {
        return sum1 > sum2;
    }

    // 若和相同，逐位比较元素
    for (int i = 0; i < n; ++i) {
        if (row1[i] != row2[i]) {
            return row1[i] > row2[i];
        }
    }

    // 如果所有元素都相同，可简单返回 false，因为元素完全相同不存在严格大于关系
    return false;
}

// 对二维数组进行排序的函数
void sort2DArray(vector<vector<int>>& arr) {
    sort(arr.begin(), arr.end(), compareRows);
}

int main() {
    vector<vector<int>> arr = {
        {1, 2, 3},
        {4, 5, 6},
        {1, 2, 3}
    };

    // 调用排序函数
    sort2DArray(arr);

    // 输出排序后的二维数组
    for (const auto& row : arr) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }

    return 0;
}