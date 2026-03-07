#include <iostream>
#include <string>
using namespace std;

#define int long long

signed main()
{

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        if (n == 1) {
            cout << "YES" << endl;
            cout << 1 << endl;
            continue;
        }
        // 麻了，打表题
        // 5 1 6 2 7 3 8 4 9
        int num1 = 1;
        int num2 = n / 2 + 1;
        cout << "YES" << endl;
        for(int i = 0; i < n; i++) {
            if (i % 2 == 0) {
                cout << num2 ++ << " ";
            }
            else {
                cout << num1 ++ << " ";
            }
        }
        cout << endl;
    }
    

    return 0;
}
