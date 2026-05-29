#include <iostream>
#include <vector>
using namespace std;

#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
#define int long long

const int MAX_P = 200000; // 足够容纳前 10000 个质数
vector<int> prime;
bool is_prime[MAX_P + 1];

void sieve() {
    fill(is_prime + 2, is_prime + MAX_P + 1, true);
    for (int p = 2; p <= MAX_P; p++) {
        if (is_prime[p]) {
            prime.push_back(p);
            if (prime.size() > 10005) break;
            for (int i = p * p; i <= MAX_P; i += p) {
                is_prime[i] = false;
            }
        }
    }
}

signed main() {
    IOS;
    
    sieve();

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> a(n, 0);
        // 构造序列
        // a[0] = p[0]
        // a[1] = p[0]*p[1], a[2] = p[1]*p[2] ... a[n-2] = p[n-3]*p[n-2]
        // a[n-1] = p[n-2]
        
        a[0] = prime[0];
        for (int i = 1; i < n - 1; i++) {
            a[i] = prime[i - 1] * prime[i];
        }
        a[n - 1] = prime[n - 2];

        // 输出结果
        for (int i = 0; i < n; i++) {
            cout << a[i] << " ";
        }
        cout << endl;
    }

    return 0;
}