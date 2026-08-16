// #include <bits/stdc++.h>
#include <iostream> // cin, cout, cerr - 标准输入输出流
#include <vector>   // vector - 动态数组（向量）

using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define endl '\n'

const int MOD = 1e9 + 7;

// 矩阵结构
struct Matrix
{
    int n;
    vector<vector<int>> a;

    Matrix(int size) : n(size)
    {
        a.assign(n, vector<int>(n, 0));
    }

    // 矩阵乘法
    Matrix operator*(const Matrix &other) const
    {
        Matrix res(n);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                for (int k = 0; k < n; k++)
                {
                    res.a[i][j] = (res.a[i][j] + a[i][k] * other.a[k][j]) % MOD;
                }
            }
        }
        return res;
    }

    // 单位矩阵
    static Matrix identity(int size)
    {
        Matrix res(size);
        for (int i = 0; i < size; i++)
        {
            res.a[i][i] = 1;
        }
        return res;
    }
};

// 矩阵快速幂
Matrix matrix_pow(Matrix base, int k)
{
    Matrix res = Matrix::identity(base.n);

    while (k > 0)
    {
        if (k & 1)
        {
            res = res * base;
        }
        base = base * base;
        k >>= 1;
    }

    return res;
}

signed main()
{
    IOS;

    int n, k;
    cin >> n >> k;

    Matrix mat(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> mat.a[i][j];
            mat.a[i][j] = ((mat.a[i][j] % MOD) + MOD) % MOD; // 处理负数
        }
    }

    Matrix result = matrix_pow(mat, k);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << result.a[i][j];
            if (j < n - 1) cout << " ";
        }
        cout << endl;
    }

    return 0;
}
