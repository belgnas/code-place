#include <iostream>
#include <string>
using namespace std;

#define int long long

const int mod = 998244353;

// 难道要快速幂？
int fast_pow(int a, int b, int mod) // a ^ b % mod
{
    int res = 1 % mod;
    while (b)
    {
        if (b & 1)
        {
            res = res * 1ll * a % mod;
        }
        a = a * 1ll * a % mod;
        b >>= 1;
    }
    return res;
}


signed main() {

    int t;
    cin >> t;
    while (t-- > 0) {
        string s;
        cin >> s;
        int len = s.size();
        
        // 首尾字符
        char first = s[0];
        char last = s[len - 1]; 
        
        // 特判长度1
        if (len == 1) {
            if (first == '?') {
                cout << '2' << endl;
            }
            else {
                cout << '1' << endl;
            }
            continue;
        }

        // cout << "len = " << len << endl;
        // cout << "first = " << first << endl;
        // cout << "last = " << last << endl;

        if (len % 2 == 0) {
            if ((first == '0' && last == '0') || (first == '1' && last == '1')) {
                cout << '0' << endl;
                continue;
            }
        }
        else {
            if ((first == '0' && last == '1') || (first == '1' && last == '0')) {
                cout << '0' << endl;
                continue;
            }
        }

        // 除开首尾外'?'的数量
        int num = 0;
        for (int i = 0; i < len; i++) {
            if (i == 0 || i == len - 1) {
                continue;
            }
            else {
                if (s[i] == '?') {
                    num ++;
                }
            }
        }
        
        // 首尾相同 && 长度为奇数 -> 平衡
        // 首尾不相同 && 长度为偶数 -> 平衡

        // 0...0 奇数 1...1 奇数
        // 0...1 偶数 1...0 偶数
        // 0...?  ?...0  1...?  ?...1
        // ?...?

        // cout << "len = " << len << endl;
        // cout << "first = " << first << endl;
        // cout << "last = " << last << endl;

        int temp = 1;
//         for (int i = 0; i < num; i++) {
//             temp *= 2;
//             temp %= mod;
//             // cout << "temp = " << temp << endl;
//         }
        temp = fast_pow(2, num, mod);

        int ans = temp;
        if (first == '?' && last == '?') {
            ans *= 2;
            ans %= mod;
        }

        cout << ans << endl;
        
    }

    return 0;
}