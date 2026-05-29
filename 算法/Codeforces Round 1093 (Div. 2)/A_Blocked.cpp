#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define int long long

signed main() {

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n, 0);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        sort(a.begin(), a.end(), greater<int>());

        bool flag = true;
        for (int i = 1; i < n; i++) {
            if (a[i] == a[i-1]) {
                flag = false;
                break;
            }
        }

        if (!flag) {
            cout << "-1" << endl;
        }
        else {
            for (int i = 0; i < n; i++) {
                cout << a[i] << " ";
            }
            cout << endl;
        }

        
    }


    return 0;
}