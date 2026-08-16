// #include <bits/stdc++.h>
#include <iostream> // cin, cout, cerr - 标准输入输出流
#include <vector>   // vector - 动态数组（向量）
#include <cstring>  // strcpy, strcmp, strlen - C风格字符串函数

using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define endl '\n'

const int N = 2010;

int C[N][N];    // C[i][j] 表示组合数 C(i, j) % k
int sum[N][N];  // sum[i][j] 表示第 i 行中，[0, j] 列有多少个满足 k|C(i,y) 且 y<=i 的
int f[N][N];    // f[i][j] 表示 (x,y) 满足 0<=x<=i, 0<=y<=min(x,j) 且 k|C(x,y) 的对数
int k;

// 预处理组合数
void init()
{
    // 杨辉三角递推组合数（模 k）
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            if (j == 0)
            {
                C[i][j] = 1 % k;
            }
            else
            {
                C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % k;
            }
        }
    }

    // 预处理一维前缀和 sum[i][j]
    for (int i = 0; i < N; i++)
    {
        sum[i][0] = (C[i][0] == 0) ? 1 : 0;
        for (int j = 1; j < N; j++)
        {
            sum[i][j] = sum[i][j - 1];
            if (j <= i && C[i][j] == 0)
            {
                sum[i][j]++;
            }
        }
    }

    // 预处理 f[i][j]
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            f[i][j] = (i > 0) ? f[i - 1][j] : 0;
            // 加上第 i 行的贡献：[0, min(i, j)]
            int max_y = min((long long)i, (long long)j);
            f[i][j] += sum[i][max_y];
        }
    }
}

signed main()
{
    IOS;

    int t;
    cin >> t >> k;

    init();

    while (t--)
    {
        int n, m;
        cin >> n >> m;

        cout << f[n][m] << endl;
    }

    return 0;
}
