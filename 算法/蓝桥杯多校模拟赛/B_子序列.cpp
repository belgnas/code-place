#include <iostream>
using namespace std;
const long long mod = 1e9 + 7;

int main() {
    long long ans = 0;
    ans = (4052LL * 4051 * 4050 / 6) % mod;                // C(4052,3)
    ans = (ans + 2 * (2026LL * 2025 * 2024 / 6)) % mod;   // 2 * C(2026,3)
    ans = (ans + 2026LL * 2026 * 2025) % mod;              // 2 * C(2026,2) * 2026
    cout << ans << endl;
    return 0;
}