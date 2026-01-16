#include <iostream>
#include <vector>
using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'

// 定义各组合的除数（LCM）
vector<long long> d1 = {2, 3, 5, 7};            // 单个除数
vector<long long> d2 = {6, 10, 14, 15, 21, 35}; // 两两组合的LCM
vector<long long> d3 = {30, 42, 70, 105};       // 三三组合的LCM
vector<long long> d4 = {210};                   // 四个数的LCM

// 计算[l, r]中能被x整除的数的数量
long long count_div(long long l, long long r, long long x)
{
    return (r / x) - ((l - 1) / x);
}

int main()
{
    IOS;
    int t;
    cin >> t;
    while (t--)
    {
        long long l, r;
        cin >> l >> r;
        long long total = r - l + 1; // 总数量

        // 计算各集合的数量和
        long long sum_single = 0;
        for (long long x : d1)
            sum_single += count_div(l, r, x);

        long long sum_pair = 0;
        for (long long x : d2)
            sum_pair += count_div(l, r, x);

        long long sum_triple = 0;
        for (long long x : d3)
            sum_triple += count_div(l, r, x);

        long long sum_quadruple = 0;
        for (long long x : d4)
            sum_quadruple += count_div(l, r, x);

        // 应用容斥原理计算好数数量
        long long good = total - sum_single + sum_pair - sum_triple + sum_quadruple;
        cout << good << endl;
    }
    return 0;
}