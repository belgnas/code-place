/*
 * LeetCode 85. 最大矩形 (Maximal Rectangle)
 *
 * 给定一个仅包含 0 和 1 、大小为 rows x cols 的二维二进制矩阵，
 * 找出只包含 1 的最大矩形，并返回其面积。
 *
 * 示例 1：
 *   输入：matrix = [["1","0","1","0","0"],
 *                   ["1","0","1","1","1"],
 *                   ["1","1","1","1","1"],
 *                   ["1","0","0","1","0"]]
 *   输出：6
 *
 * 示例 2：
 *   输入：matrix = [["0"]]
 *   输出：0
 *
 * 示例 3：
 *   输入：matrix = [["1"]]
 *   输出：1
 *
 * 提示：
 *   rows == matrix.length
 *   cols == matrix[i].length
 *   1 <= rows, cols <= 200
 *   matrix[i][j] 为 '0' 或 '1'
 */

#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        // 边界判断：空矩阵直接返回 0
        if (matrix.empty() || matrix[0].empty()) return 0;
        int n = matrix.size();    // 行数
        int m = matrix[0].size(); // 列数

        // height[j]: 当前行第 j 列向上连续 '1' 的个数（柱状图高度）
        vector<int> height(m, 0);
        // left[j]: 当前行第 j 列的悬线能向左延伸到的最远列下标（初始为 0）
        vector<int> left(m, 0);
        // right[j]: 当前行第 j 列的悬线能向右延伸到的最远列下标（初始为最右列 m-1）
        vector<int> right(m, m - 1);

        int maxArea = 0; // 记录全局最大矩形面积

        // 逐行遍历矩阵，更新 height, left, right
        for (int i = 0; i < n; i++) {
            // ---------- 从左到右，更新 height 和 left ----------
            int curLeft = 0; // 当前行最近遇到的 '0' 的右边第一个位置
            for (int j = 0; j < m; j++) {
                if (matrix[i][j] == '1') {
                    // 高度直接在上一次的基础上 +1
                    height[j]++;
                    // 左边界受两个条件约束：
                    // 1. 当前行左边最近 0 的边界 curLeft
                    // 2. 上一行同一列的左边界 left[j]（因为高度是累积的，矩形必须对齐）
                    // 取最大值（更靠右的那个限制）
                    left[j] = max(left[j], curLeft);
                } else {
                    // 遇到 '0'，高度清零
                    height[j] = 0;
                    // 左边界重置为 0，这样下一行如果出现 '1'，max(0, curLeft) 就会从 curLeft 开始
                    left[j] = 0;
                    // 更新当前行的 '0' 边界到下一个位置
                    curLeft = j + 1;
                }
            }

            // ---------- 从右到左，更新 right 并计算面积 ----------
            int curRight = m - 1; // 当前行从右往左遇到的最近 '0' 的左边第一个位置
            for (int j = m - 1; j >= 0; j--) {
                if (matrix[i][j] == '1') {
                    // 右边界受两个条件约束：
                    // 1. 当前行右边最近 0 的边界 curRight
                    // 2. 上一行同一列的右边界 right[j]
                    // 取最小值（更靠左的那个限制）
                    right[j] = min(right[j], curRight);

                    // 计算以当前悬线高度为高，左右边界确定的矩形的面积
                    int area = height[j] * (right[j] - left[j] + 1);
                    // 更新全局最大面积
                    maxArea = max(maxArea, area);
                } else {
                    // 遇到 '0'，右边界重置为最右列，让下一行重新开始
                    right[j] = m - 1;
                    // 更新当前行的 '0' 边界到左边一个位置
                    curRight = j - 1;
                }
            }
            
            cout << "i = " << i << endl;
            cout << "height : " << endl;
            for (int i = 0; i < m; i++) {
                cout << height[i] << " ";
            }
            cout << endl;
            cout << "left : " << endl;
            for (int i = 0; i < m; i++) {
                cout << left[i] << " ";
            }
            cout << endl;
            cout << "right : " << endl;
            for (int i = 0; i < m; i++) {
                cout << right[i] << " ";
            }
            cout << endl;
            cout << endl;
        }


        // 返回找到的最大矩形面积
        return maxArea;
    }
};

int main() {
    vector<vector<char>> matrix = {
        {'1','0','1','0','0'},
        {'1','0','1','1','1'},
        {'1','1','1','1','1'},
        {'1','0','0','1','0'}
    };

    cout << "matrix : " << endl;
    for (auto &row : matrix) {
        for (auto &c : row) {
            cout << c << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    cout << Solution().maximalRectangle(matrix) << endl;
    
}
