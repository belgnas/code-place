#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;
#define int long long
const int mod = 998244353;
vector<int> f(1e6 + 10);
vector<int> inv_f(1e6 + 10);

void init() {
    f[0] = 1;
    for (int i = 1; i <= f.size(); i++) {
        f[i] = f[i - 1] * i % mod;
    }
    // 逆元
    
}

int test01(int n, int num) {
    int res = 1;
    if (n < 0 || num < 0 || n < num) {
        res = 0;
    }
    else {
        res = res * f[n] % mod;
        res = res * inv_f[num] % mod;
        res = res * inv_f[n - num] % mod;
    }
    
    return res;
}

signed main() {
    
    int T;
    cin >> T;
    while (T--) {
        int n, x1, t;
        cin >> n >> x1 >> t;
        int x2 = n - x1;
        int ans = 0;
        if (t == 0) {
            if (x1 == 0 || x2 == 0) {
                ans = 1;
            }
            else {
                ans = 0;
            }
        }
        else {
            if (x1 == 0 || x2 == 0) {
                ans = 0;
            }
            else {
                int num = t + 1;
                int zuo1 = (num + 1) / 2;
                int you1 = num - zuo1;
                int num1 = test01(x1 - 1, zuo1 - 1) * test01(x2 - 1, you1 - 1) % mod;
                int zuo2 = num / 2;
                int you2 = num - zuo2;
                int num2 = test01(x1 - 1, zuo2 - 1) * test01(x2 - 1, you2 - 1) % mod;
                ans = (num1 + num2) % mod;
            }
        }
        
        cout << ans << endl;
    }
    
    
    
    return 0;
}