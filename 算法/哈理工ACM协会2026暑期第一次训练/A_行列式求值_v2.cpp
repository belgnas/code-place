// #include <bits/stdc++.h>
#include <iostream> // cin, cout, cerr - 标准输入输出流
#include <vector>   // vector - 动态数组（向量）
#include <algorithm>// sort, min, max, reverse - 常用算法

using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define endl '\n'

int p; // 模数

// 扩展欧几里得算法
int exgcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}

// 求 a 在模 p 下的逆元
int inv(int a)
{
    int x, y;
    int d = exgcd(a, p, x, y);
    if (d != 1) return -1;
    return ((x % p) + p) % p;
}

// 高斯消元求行列式（辗转相除法，不使用逆元）
int determinant(vector<vector<int>> &a, int n)
{
    int det = 1;

    for (int i = 0; i < n; i++)
    {
        // 找到第 i 列非零元素
        int pivot = -1;
        for (int j = i; j < n; j++)
        {
            if (a[j][i] != 0)
            {
                pivot = j;
                break;
            }
        }

        // 如果找不到非零元素，行列式为 0
        if (pivot == -1)
        {
            return 0;
        }

        // 交换行
        if (pivot != i)
        {
            swap(a[i], a[pivot]);
            det = (p - det) % p;
        }

        // 使用辗转相除法消元，不需要逆元
        for (int j = i + 1; j < n; j++)
        {
            // 使用辗转相除，使 a[j][i] = 0
            while (a[j][i] != 0)
            {
                // 计算倍数：使得 a[j][i] - mult * a[i][i] 的绝对值减小
                int mult = a[j][i] / a[i][i];

                for (int k = i; k < n; k++)
                {
                    a[j][k] = ((a[j][k] - mult * a[i][k]) % p + p) % p;
                }

                // 如果第 j 行第 i 列还不是 0，交换第 i 行和第 j 行
                if (a[j][i] != 0)
                {
                    swap(a[i], a[j]);
                    det = (p - det) % p;
                }
            }
        }

        // 累乘对角线元素
        det = det * a[i][i] % p;
    }

    return (det % p + p) % p;
}

signed main()
{
    IOS;

    int n;
    cin >> n >> p;

    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> a[i][j];
            a[i][j] = ((a[i][j] % p) + p) % p;
        }
    }

    int result = determinant(a, n);
    cout << result << endl;

    return 0;
}
