#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<int> a(n);
        vector<int> b(m);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < m; i++) cin >> b[i];
        if (b.size() > a.size()) {
            cout << "NO" << endl;
            continue;
        }
        bool flat = true;
        int idx1 = 0;
        int idx2 = 0;
        while (idx2 < m) {
            if (idx1 >= n) {
                flat = false;
                break;
            }
            if (a[idx1] >= b[idx2]) {
                idx1++;
                idx2++;
            }
            while (a[idx1] < b[idx2] && idx1 < n) {
                idx1++;
            }
        }
        if (flat) {
            cout << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
        }
    }
    
    return 0;
}