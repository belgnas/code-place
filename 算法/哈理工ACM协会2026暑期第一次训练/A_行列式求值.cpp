// #include <bits/stdc++.h>
#include <iostream> // cin, cout, cerr - 标准输入输出流
#include <vector>   // vector - 动态数组（向量）
#include <algorithm>// sort, min, max, reverse - 常用算法

using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define endl '\n'

int p; // 模数

// 扩展欧几里得算法求逆元（支持 p 不是质数的情况）
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

// 求 a 在模 p 下的逆元（支持 p 不是质数）
int inv(int a)
{
    a = ((a % p) + p) % p;

    // 先尝试用费马小定理（如果 p 是质数，会快很多）
    // 但如果 p 不是质数，我们用扩展欧几里得
    int x, y;
    int d = exgcd(a, p, x, y);

    if (d != 1)
    {
        return -1; // 不存在逆元
    }

    return ((x % p) + p) % p;
}

// 高斯消元求行列式
int determinant(vector<vector<int>> &a, int n)
{
    int det = 1;

    for (int i = 0; i < n; i++)
    {
        // 找到第 i 列非零元素（从第 i 行开始找）
        // 选择绝对值最大的作为主元，提高数值稳定性
        int pivot = -1;
        for (int j = i; j < n; j++)
        {
            if (a[j][i] != 0)
            {
                if (pivot == -1)
                {
                    pivot = j;
                }
                else if (a[j][i] > a[pivot][i])
                {
                    pivot = j;
                }
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
            det = (p - det) % p; // 交换行，行列式变号
        }

        // 累乘对角线元素
        det = det * a[i][i] % p;

        // 计算主元的逆元
        int pivot_inv = inv(a[i][i]);

        // 如果逆元不存在，说明 gcd(a[i][i], p) != 1，行列式在模 p 意义下为 0
        if (pivot_inv == -1)
        {
            return 0;
        }

        // 消元：将第 i 列下方的元素都变成 0
        for (int j = i + 1; j < n; j++)
        {
            if (a[j][i] == 0) continue;

            int factor = a[j][i] * pivot_inv % p;
            for (int k = i; k < n; k++)
            {
                a[j][k] = ((a[j][k] - factor * a[i][k]) % p + p) % p;
            }
        }
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
            a[i][j] = ((a[i][j] % p) + p) % p; // 读入时就取模，处理负数
        }
    }

    int result = determinant(a, n);
    cout << result << endl;

    return 0;
}
