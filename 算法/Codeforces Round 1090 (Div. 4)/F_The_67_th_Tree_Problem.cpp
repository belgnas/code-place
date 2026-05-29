#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
#define int long long
#define endl '\n'

signed main() {
    IOS;

    int t;
    cin >> t;
    while (t--) {
        int x, y;
        cin >> x >> y;
        int n = x + y;

        if (y < x || (n % 2 == 0 && x == 0) || (n % 2 != 0 && y == 0)) {
            cout << "NO" << endl;
            continue;
        }
        else {
            cout << "YES" << endl;
        }
        
        if (n % 2 == 0) {
            for (int i = 1; i < x; i++){
                cout << i << " " << i + 1 << endl;
            }
            for (int i = 1; i <= x; i++){
                cout << i << " " << x + i << endl;
            }
            for (int i = 2 * x + 1; i <= n; i++){
                cout << x << " " << i << endl;
            }
        }
        else {
            if (x == 0) {
                for (int i = 2; i <= n; i++){
                    cout << 1 << " " << i << endl;
                }
            }
            else {
                cout << 1 << " " << 2 << endl;
                for (int i = 2; i < x + 1; i++){
                    cout << i << " " << i + 1 << endl;
                }
                for (int i = 2; i <= x + 1; i++){
                    cout << i << " " << x + i << endl;
                }
                for (int i = 2 * x + 2; i <= n; i++){
                    cout << x + 1 << " " << i << endl;
                }
            }
        }
    }

    return 0;
}