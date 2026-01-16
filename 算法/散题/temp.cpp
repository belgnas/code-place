#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <map>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define endl '\n'
#define int long long

signed main() {
    IOS;
    
    int t;
    cin >> t;
    while (t-- > 0) {
        int n, x;
        cin >> n >> x;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        
        bool flat = true;
        int num = 0;
        for (int i = 0; i < n; i++) {
            int total = num + a[i];
            if (total < x) {
                flat = false;
                break;
            }
            int lastday = max(0LL, x - num);
            num = a[i] - lastday;
        }
        
        if (flat) {
            cout << "Yes" << endl;
        }
        else {
            cout << "No" << endl;
        }
    }
    
    return 0;
}