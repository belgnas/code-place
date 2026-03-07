#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
typedef long long ll;

// 龟速乘（防止乘法溢出）
ll mulmod(ll a, ll b, ll mod)
{
    return (a * b - (ll)((long double)a / mod * b) * mod + mod) % mod;
}

// 快速幂取模
ll powmod(ll a, ll b, ll mod)
{
    ll res = 1;
    a %= mod;
    while (b > 0)
    {
        if (b & 1)
            res = mulmod(res, a, mod);
        a = mulmod(a, a, mod);
        b >>= 1;
    }
    return res;
}

// 米勒-拉宾素性测试（确定性版本，适用于n<2^64）
bool is_prime(ll n)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0)
        return false;
    ll d = n - 1, s = 0;
    while (d % 2 == 0)
        d /= 2, s++;
    static const ll a[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}; // 测试基
    for (ll base : a)
    {
        if (base >= n)
            continue;
        ll x = powmod(base, d, n);
        if (x == 1 || x == n - 1)
            continue;
        for (int _ = 0; _ < s - 1; _++)
        {
            x = powmod(x, 2, n);
            if (x == n - 1)
                break;
        }
        if (x != n - 1)
            return false;
    }
    return true;
}

// Pollard's Rho算法找因子
ll pollards_rho(ll n)
{
    if (n % 2 == 0)
        return 2;
    if (n % 3 == 0)
        return 3;
    if (n % 5 == 0)
        return 5;
    while (true)
    {
        ll c = rand() % (n - 1) + 1;
        ll x = 2, y = 2, d = 1;
        while (d == 1)
        {
            x = (mulmod(x, x, n) + c) % n;
            y = (mulmod(y, y, n) + c) % n;
            y = (mulmod(y, y, n) + c) % n;
            d = __gcd(abs(x - y), n);
        }
        if (d != n)
            return d;
    }
}

// 统计质因数分解次数的奇偶性
int count_prime_factors(ll n)
{
    int res = 0;
    function<void(ll)> dfs = [&](ll x)
    {
        if (x == 1)
            return;
        if (is_prime(x))
        {
            res++;
            return;
        }
        ll p = pollards_rho(x);
        dfs(p);
        dfs(x / p);
    };
    dfs(n);
    return res;
}

int main()
{
    IOS;
    srand(time(0)); // 初始化随机数种子
    int t;
    cin >> t;
    while (t--)
    {
        ll x;
        cin >> x;
        if (x == 1)
        { // 特殊情况：1没有质因数
            cout << "yukari" << endl;
            continue;
        }
        int cnt = count_prime_factors(x);
        cout << (cnt % 2 ? "kou" : "yukari") << endl;
    }
    return 0;
}