#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace std;

#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define int long long

// 当前节点x深度
int test01(int x) {
    int d = 0;
    int temp = 1;
    while (temp * 2 <= x) {
        temp *= 2;
        d++;
    }
    return d;
}

// 当前深度d的节点数
int test02(int d) {
    int num = 1;
    for (int i = 0; i < d; i++) {
        num *= 2;
    }
    return num;
}

signed main() {
    IOS;
    
    int t;
    cin >> t;
    while (t-- > 0) {
        int n, q;
        cin >> n >> q;
        int d0 = test01(n);
        int num0 = test01(d0);
        while (q--) {
            int x;
            cin >> x;
            
            int d = test01(x);
            int num = test02(d);
            
            int ans = 0;
            if (d < d0) {
                ans = num0;
            }
            else {
                ans = n - (num0 - 1);
            }
            cout << ans << endl;
        }
    }
    
    return 0;
}