#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
using namespace std;

// 极简版质因数分解（只返回不同的质因子）
vector<long long> get_primes(long long x) {
    vector<long long> res;
    if (x == 1) return res;
    // 处理2
    if (x % 2 == 0) {
        res.push_back(2);
        while (x % 2 == 0) x /= 2;
    }
    // 处理奇数
    for (long long i = 3; i * i <= x; i += 2) {
        if (x % i == 0) {
            res.push_back(i);
            while (x % i == 0) x /= i;
        }
    }
    if (x > 1) res.push_back(x);
    return res;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<long long> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        
        if (n < 2) { // 不足两个数直接输出-1
            cout << -1 << '\n';
            continue;
        }
        
        unordered_map<long long, long long> mp; // 质因子 -> 对应的数
        bool ok = false;
        for (auto num : a) {
            if (num == 1) continue; // 1和任何数gcd都是1，跳过
            auto primes = get_primes(num);
            for (auto p : primes) {
                if (mp.count(p)) { // 找到共同质因子
                    cout << mp[p] << ' ' << num << '\n';
                    ok = true;
                    goto end_loop; // 直接跳出所有循环，简化逻辑
                }
                mp[p] = num; // 记录质因子第一次出现的数
            }
        }
    end_loop:
        if (!ok) cout << -1 << '\n';
    }
    return 0;
}