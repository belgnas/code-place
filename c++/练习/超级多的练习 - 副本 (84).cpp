#include <bits/stdc++.h>
using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)

// 检查矩阵是否全为 0
bool quanshi0(vector<string> &mat, int n, int m)
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (mat[i][j] != '0')
                return false;
    return true;
}

// 检查是否能通过选两行不同的行使矩阵变全 0
bool jiancha2hang(vector<string> &mat, int n, int m)
{
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
        {
            bool ok = true;
            // 检查所选两行是否全为 1
            for (int k = 0; k < m; ++k)
                if (mat[i][k] != '1' || mat[j][k] != '1')
                {
                    ok = false;
                    break;
                }
            if (!ok)
                continue;
            // 检查其他行是否全为 0
            for (int p = 0; p < n; ++p)
            {
                if (p == i || p == j)
                    continue;
                for (int k = 0; k < m; ++k)
                    if (mat[p][k] != '0')
                    {
                        ok = false;
                        break;
                    }
                if (!ok)
                    break;
            }
            if (ok)
                return true;
        }
    return false;
}

// 检查是否能通过选两列不同的列使矩阵变全 0
bool jiancha2lie(vector<string> &mat, int n, int m)
{
    for (int i = 0; i < m; ++i)
        for (int j = i + 1; j < m; ++j)
        {
            bool ok = true;
            // 检查所选两列是否全为 1
            for (int k = 0; k < n; ++k)
                if (mat[k][i] != '1' || mat[k][j] != '1')
                {
                    ok = false;
                    break;
                }
            if (!ok)
                continue;
            // 检查其他列是否全为 0
            for (int p = 0; p < m; ++p)
            {
                if (p == i || p == j)
                    continue;
                for (int k = 0; k < n; ++k)
                    if (mat[k][p] != '0')
                    {
                        ok = false;
                        break;
                    }
                if (!ok)
                    break;
            }
            if (ok)
                return true;
        }
    return false;
}

// 检查是否能通过选一行一列使矩阵变全 0
bool jiancha1hang1lie(vector<string> &mat, int n, int m)
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
        {
            bool ok = true;
            // 检查非交叉区域是否全为 0
            for (int x = 0; x < n; ++x)
                for (int y = 0; y < m; ++y)
                    if (x != i && y != j && mat[x][y] != '0')
                    {
                        ok = false;
                        goto END;
                    }
            // 检查行 i 的非 j 列是否全为 1
            for (int y = 0; y < m; ++y)
                if (y != j && mat[i][y] != '1')
                {
                    ok = false;
                    goto END;
                }
            // 检查列 j 的非 i 行是否全为 1
            for (int x = 0; x < n; ++x)
                if (x != i && mat[x][j] != '1')
                {
                    ok = false;
                    goto END;
                }
            // 检查交叉点是否为 0
            if (mat[i][j] != '0')
                ok = false;
        END:
            if (ok)
                return true;
        }
    return false;
}

int main()
{
    IOS;
    int T;
    cin >> T;
    while (T--)
    {
        int n, m;
        cin >> n >> m;
        vector<string> mat(n);
        for (int i = 0; i < n; ++i)
            cin >> mat[i];

        bool can = false;
        // 情况 1：矩阵本身全为 0
        if (quanshi0(mat, n, m))
            can = true;
        else
        {
            // 情况 2：选两行不同的行
            if (jiancha2hang(mat, n, m))
                can = true;
            // 情况 3：选两列不同的列
            else if (jiancha2lie(mat, n, m))
                can = true;
            // 情况 4：选一行一列
            else if (jiancha1hang1lie(mat, n, m))
                can = true;
        }
        cout << (can ? "YES" : "NO") << endl;
    }
    return 0;
}