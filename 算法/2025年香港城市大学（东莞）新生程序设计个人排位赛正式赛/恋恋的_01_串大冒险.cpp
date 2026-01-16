#include <bits/stdc++.h>
using namespace std;

#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)

int main() {
    IOS;

    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;

    vector<int> ans(n + 1, 0);

    int ops = 0; // 当前操作数
    int lianxu_0 = 0;

    
    ans[0] = 0;

    for (int i = 1; i <= n; i++) {
        char c = s[i - 1];
        if (c == '1') {
            lianxu_0 = 0;
        }
        else {
            if (lianxu_0 == k - 1) {
                ops++;
                lianxu_0 = 0;
            } else {
                lianxu_0++;
            }
        }

        
        if (ops <= n) {
            ans[ops] = i;
        }
    }

    int max_len = 0;
    for (int i = 0; i <= n; i++) {
        max_len = max(max_len, ans[i]);
        ans[i] = max_len;
    }

    for (int i = 0; i <= n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;

    return 0;
}
