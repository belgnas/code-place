#include <iostream>
#include <string>
using namespace std;

int main() 
{
    int T;
    cin>>T;
    // T 表示测试用例的数量，接下来会进行 T 次独立的检查。

    for (int t = 0; t < T; t++) 
    {
        string str1[4];
        // 创建一个字符串数组 str1，用于存储每个测试用例中的 4x4 矩形的每一行。

        for (int i = 0; i < 4; i++) 
        {
            cin >> str1[i];
            // 逐行读取 4x4 矩形的内容，将每一行存储到 str1 数组中。
        }

        bool answer = false;
        // answer 变量用于标记在当前测试用例中是否找到了满足条件的 2x2 子矩形。

        // 检查水平方向的 2x2 子矩形
        for (int i = 0; i < 3; i++) 
        {
            // i 用于控制行的索引，最多到第 2 行（因为从第 2 行开始才能完整地构成一个 2x2 的水平子矩形）。
            for (int j = 0; j < 3; j++) 
            {
                // j 用于控制列的索引，最多到第 2 列（同理）。
                if ((str1[i][j] == str1[i][j + 1]) && (str1[i][j] == str1[i + 1][j]) && (str1[i][j] == str1[i + 1][j + 1])) 
                {
                    // 判断当前位置（i,j）与其右边（i,j+1）、下边（i+1,j）、右下角（i+1,j+1）的字符是否相同。
                    answer = true;
                    break;
                    // 如果找到了满足条件的子矩形，将 answer 设为 true，并跳出当前内层循环，不再继续检查这一行的其他位置。
                }
            }
            if (answer) break;
            // 如果已经找到了满足条件的子矩形，跳出当前外层循环，不再继续检查其他行。
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
                    if ((str1[j][i] == str1[j][i + 1]) && (str1[j][i] == str1[j + 1][i]) && (str1[j][i] == str1[j + 1][i + 1])) 
                    {
                        // 判断当前位置（j,i）与其下边（j+1,i）、右边（j,i+1）、右下角（j+1,i+1）的字符是否相同（这里是垂直方向判断）。
                        answer = true;
                        break;
                        // 如果找到了满足条件的子矩形，将 answer 设为 true，并跳出当前内层循环，不再继续检查这一列的其他位置。
                    }
                }
                if (answer) break;
                // 如果已经找到了满足条件的子矩形，跳出当前外层循环，不再继续检查其他列。
            }
        }

        if (answer) {
            cout << "Yes" << endl;
            // 如果找到了满足条件的子矩形，输出"Yes"，表示当前测试用例中会感到开心。
        } else {
            cout << "No" << endl;
            // 如果没有找到满足条件的子矩形，输出"No"，表示当前测试用例中不会感到开心。
        }
    }

    return 0;
}