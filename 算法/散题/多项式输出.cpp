#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define endl '\n'

const int INF = 0x3f3f3f3f;

signed main()
{
    IOS;

    int n; // n 是多项式的最高次数，系数个数是 n+1
    cin >> n;
    vector<int> coeffs(n + 1); // 系数个数 = 次数 + 1（次数从 n 到 0）
    for (int i = 0; i <= n; ++i)
    {
        cin >> coeffs[i];
    }

    string poly;
    bool is_first = true; // 标记是否是第一个非零项

    for (int i = 0; i <= n; ++i)
    {
        int coeff = coeffs[i];
        if (coeff == 0)
            continue; // 跳过零系数

        int degree = n - i; // 第 i 个系数对应 degree 次（核心修正）

        // 处理符号
        if (is_first)
        {
            is_first = false;
            if (coeff < 0)
            {
                poly += "-"; // 首项为负时直接加负号
            }
        }
        else
        {
            if (coeff > 0)
            {
                poly += "+"; // 非首项正系数加 "+"
            }
            else
            {
                poly += "-"; // 非首项负系数加 "-"
            }
        }

        int abs_coeff = abs(coeff); // 取绝对值处理系数

        // 处理系数部分（非常数项的 1/-1 省略）
        if (degree == 0)
        {
            // 常数项必须显示系数（包括 1/-1）
            poly += to_string(abs_coeff);
        }
        else
        {
            // 非常数项：系数为 1 或 -1 时省略系数
            if (abs_coeff != 1)
            {
                poly += to_string(abs_coeff);
            }
        }

        // 处理变量和次数
        if (degree > 0)
        {
            poly += "x"; // 显示 x
            if (degree > 1)
            {
                poly += "^" + to_string(degree); // 次数 >1 时显示 ^degree
            }
        }
    }

    // 全零多项式处理
    if (poly.empty())
    {
        poly = "0";
    }

    cout << poly << endl;

    return 0;
}