#include <iostream>
#include <cmath>
#include <map>
using namespace std;
#define int long long

map<int, int> factorize(int x) {
    map<int, int> res;
    for (int i = 2; i * i <= x; ++i) {
        while (x % i == 0) {
            res[i]++;
            x /= i;
        }
    }
    if (x > 1) res[x]++;
    return res;
}

signed main() {
    int x, l, r;
    cin >> x >> l >> r;

    int ans = -1;
    map<int, int> cnt = factorize(x);
    int temp = 1;
    
    for (auto [k, v] : cnt) {
        if (v % 2 == 1) {
            temp *= k;
        }
    }
    
    if (temp > r) {
        cout << -1 << endl;
        return 0;
    }
    
    for (int i = 1; temp * i * i <= r; ++i) {
        int t = temp * i * i;
        if (t >= l) {
            ans = t;
            break;
        }
    }
    
    cout << ans << endl;
    return 0;
}