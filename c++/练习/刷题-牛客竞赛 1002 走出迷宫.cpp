// 牛客竞赛 1002 走出迷宫

//  知识点：图论、搜索、深度优先搜索、广度优先搜索

// 难度：简单

// https://ac.nowcoder.com/acm/contest/23156/1002

// 这下面的这段题目描述是ai生成的（反正意思差不多）
// 题目描述：
// 给定一个 n 行 m 列的地图，其中 '.' 表示空地，'#' 表示障碍物，'S' 表示起点，'E' 表示终点。
// 你可以在地图上移动，每次只能向上、下、左、右四个方向移动一格，并且不能移动到障碍物上。
// 请你判断是否存在一条从起点到终点的路径。
// 如果存在，请输出 "Yes"，否则输出 "No"。

// 输入输出格式：
// 输入
// 第一行包含两个整数 n 和 m，表示地图的行数和列数。
// 接下来 n 行，每行包含 m 个字符，表示地图的具体情况。
// 输出
// 输出一行，包含一个字符串，如果存在一条从起点到终点的路径，则输出 "Yes"，否则输出 "No"。

// 样例：
// 输入
// 3 4
// S...
// ....
// ...E
// 输出
// Yes
// 样例解释：
// 从起点 (1, 1) 开始，向右移动一步，向下移动一步，向右移动一步，到达终点 (3, 4)。




#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

const int N = 510, M = 510;

int n, m;
char arr[N][M];
bool flat[N][M];
int from_x, from_y, to_x, to_y;

bool dfs(int x, int y)
{
    if(flat[x][y] || x < 1 || x > n || y < 1 || y > m || arr[x][y] == '#')
    {
        return false;
    }
    if(x == to_x && y == to_y)
    {
        return true;
    }
    flat[x][y] = true;

    if(dfs(x + 1, y))
    {
        return true; // 如果在右方找到了终点，返回 true
    }
    if(dfs(x - 1, y))
    {
        return true; // 如果在左方找到了终点，返回 true
    }
    if(dfs(x, y + 1))
    {
        return true; // 如果在上方找到了终点，返回 true
    }
    if(dfs(x, y - 1))
    {
        return true; // 如果在下方找到了终点，返回 true
    }

    flat[x][y] = true;
    return false;
}

int main()
{
    while(cin >> n >> m)
    {
        memset(flat, false, sizeof(flat));
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= m; j++)
            {
                cin >> arr[i][j];
                if(arr[i][j] == 'S')
                {
                    from_x = i;
                    from_y = j;
                }
                if(arr[i][j] == 'E')
                {
                    to_x = i;
                    to_y = j;
                    arr[i][j] = '.';
                }
            }
        }

        bool ans = dfs(from_x, from_y);
        if(ans) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    
    return 0;
}