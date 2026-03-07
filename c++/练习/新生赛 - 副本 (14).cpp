#include <iostream>
#include <string>
using namespace std;

int main() 
{
    int T;
    cin>>T;

    for (int t = 0; t < T; t++) 
    {
        string grid[4];
        // 创建一个字符串数组 grid，用于存储每个测试用例中的 4x4 矩形的每一行。

        for (int i = 0; i < 4; i++) 
        {
            cin >> grid[i];
            // 逐行读取 4x4 矩形的内容，将每一行存储到 grid 数组中。
        }

        bool answer = false;
        // answer 变量用于标记是否找到了满足条件的 2x2 子矩形。

        // 检查水平方向的 2x2 子矩形
        for (int i = 0; i < 3; i++) 
        {
            // i 用于控制行的索引，最多到第 2 行（因为从第 2 行开始才能完整地构成一个 2x2 的水平子矩形）。
            for (int j = 0; j < 3; j++) 
            {
                // j 用于控制列的索引，最多到第 2 列（同理）。
                if ((grid[i][j] == grid[i][j + 1]) && (grid[i][j] == grid[i + 1][j]) && (grid[i][j] == grid[i + 1][j + 1])) 
                {
                    // 判断当前位置（i,j）与其右边（i,j+1）、下边（i+1,j）、右下角（i+1,j+1）的字符是否相同。
                    answer = true;
                    break;
                    // 如果找到了满足条件的子矩形，将 answer 设为 true，并跳出当前内层循环。
                }
            }
            if (answer) break;
            // 如果已经找到了满足条件的子矩形，跳出当前外层循环。
        }

        // 如果水平方向未找到满足条件的子矩形，检查垂直方向的 2x2 子矩形
        if (!answer) 
        {
            for (int i = 0; i < 3; i++) 
            {
                // i 现在用于控制列的索引，最多到第 2 列。
                for (int j = 0; j < 3; j++) 
                {
                    // j 用于控制行的索引，最多到第 2 行。
                    if ((grid[j][i] == grid[j][i + 1]) && (grid[j][i] == grid[j + 1][i]) && (grid[j][i] == grid[j + 1][i + 1])) 
                    {
                        // 判断当前位置（j,i）与其下边（j+1,i）、右边（j,i+1）、右下角（j+1,i+1）的字符是否相同（这里是垂直方向判断）。
                        answer = true;
                        break;
                        // 如果找到了满足条件的子矩形，将 answer 设为 true，并跳出当前内层循环。
                    }
                }
                if (answer) break;
                // 如果已经找到了满足条件的子矩形，跳出当前外层循环。
            }
        }

        if (answer) 
        {
            cout << "Yes" << endl;
            // 如果找到了满足条件的子矩形，输出"Yes"。
        } else {
            cout << "No" << endl;
            // 如果没有找到满足条件的子矩形，输出"No"。
        }
    }

    return 0;
}