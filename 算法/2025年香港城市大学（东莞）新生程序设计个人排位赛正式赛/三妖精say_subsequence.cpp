#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <map>
#include <string>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define endl '\n'
#define int long long

const int mod = 998244353;

// 从字符串中选出 3 个字符，组成一个新的长度为 3 的字符串，要求如下：
// 选出的三个字符两两不同。
// 新串中字符出现的顺序不要求与原字符串顺序一致。
// 两种选法被认为不同，当且仅当存在某一位所选择的字符在原字符串中的位置不同。

signed main() {
    IOS;
    
    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<int> cnt(26, 0);
    for (int i = 0; i < n; ++i) {
        cnt[s[i] - 'a']++;
    }
    
    int ans = 0;
    for (int i = 0; i < 26; ++i) {
        for (int j = i + 1; j < 26; ++j) {
            for (int k = j + 1; k < 26; ++k) {
                ans += cnt[i] * cnt[j] * cnt[k];
            }
        }
    }
    
    ans = (ans * 6) % mod;
    cout << ans << endl;
    
    return 0;
}

