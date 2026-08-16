// #include <bits/stdc++.h>
#include <iostream> // cin, cout, cerr - 标准输入输出流
#include <vector>   // vector - 动态数组（向量）

using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define endl '\n'

// 2x2 矩阵结构
struct Matrix
{
    int a[2][2];
    int mod;

    Matrix(int m = 1) : mod(m)
    {
        a[0][0] = a[0][1] = a[1][0] = a[1][1] = 0;
    }

    // 矩阵乘法
    // 注意：m 最大 1e18，两数相乘会爆 long long，必须用 __int128 中转
    Matrix operator*(const Matrix &other) const
    {
        Matrix res(mod);
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                __int128 sum = 0;
                for (int k = 0; k < 2; k++)
                {
                    sum += (__int128)a[i][k] * other.a[k][j] % mod;
                }
                res.a[i][j] = (int)(sum % mod);
            }
        }
        return res;
    }
};

// 矩阵快速幂
Matrix matrix_pow(Matrix base, int n)
{
    Matrix res(base.mod);
    // 初始化为单位矩阵
    res.a[0][0] = res.a[1][1] = 1;

    while (n > 0)
    {
        if (n & 1)
        {
            res = res * base;
        }
        base = base * base;
        n >>= 1;
    }

    return res;
}

signed main()
{
    IOS;

    int m, a, c, x0, n, g;
    cin >> m >> a >> c >> x0 >> n >> g;

    // 构造转移矩阵
    // [X_{n+1}]   [a c] [X_n]
    // [   1   ] = [0 1] [ 1 ]
    Matrix trans(m);
    trans.a[0][0] = a % m;
    trans.a[0][1] = c % m;
    trans.a[1][0] = 0;
    trans.a[1][1] = 1;

    // 计算转移矩阵的 n 次幂
    Matrix result = matrix_pow(trans, n);

    // 计算 X_n
    // [X_n]   [result.a[0][0]  result.a[0][1]] [X_0]
    // [ 1 ] = [result.a[1][0]  result.a[1][1]] [ 1 ]
    // 同样要用 __int128 防止溢出
    int xn = (int)(((__int128)result.a[0][0] * (x0 % m) + result.a[0][1]) % m);

    // 输出 X_n mod g
    cout << xn % g << endl;

    return 0;
}
