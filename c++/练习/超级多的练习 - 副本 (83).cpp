#include <bits/stdc++.h>
using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
typedef long long ll;
const ll MOD = 998244353;

ll qpow(ll a, ll b)
{
    ll res = 1;
    while (b)
    {
        if (b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

int main()
{
    IOS;

    int T;
    cin >> T;
    vector<ll> ns(T), res(T);

    for (int i = 0; i < T; ++i)
        cin >> ns[i];

    for (int i = 0; i < T; ++i)
    {
        ll n = ns[i], c2 = 0;
        while (n)
        {
            n /= 2;
            c2 += n;
        }
        res[i] = qpow(c2 + 1, MOD - 2);
    }

    for (int i = 0; i < T; ++i)
    {
        cout << res[i];
        if (i != T - 1)
            cout << ' ';
    }
    cout << endl;

    return 0;
}