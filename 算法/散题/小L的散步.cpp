#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
#define int long long

bool test01(int where, int l, vector<int> &fx, int len) {
    if (where >= len) {
        return false;
    }
    
    auto it = lower_bound(fx.begin(), fx.end(), where);
    
    // 有缝隙
    bool flat1 = false;
    if(it != fx.end()) {
        flat1 = true;
    }
    // 能踩到
    bool flat2 = false; 
    if (*it > l && *it < where + l) {
        flat2 = true;
    }
    
    return (flat1 && flat2);
}

signed main() {
    
    int n, m, l;
    cin >> n >> m >> l;
    vector<int> fx(n);
    int len = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        len += x;
        fx[i] = len;
    }
    
    bool flat = false;
    int where = 0;
    
    flat = test01(where, l, fx, len);
    
    if (!flat) {
        for (int i = 0; i < m; i++) {
            int y = 0;
            cin >> y;
            where += y;
            if (test01(where, l, fx, len)) {
                flat = true;
                break;
            }
            
            if (where >= len) {
                break;
            }
            
        }
    }
    
    if (flat) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }
    
    
    
    return 0;
}