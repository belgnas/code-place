#include <iostream>
#include <string>
using namespace std;

#define int long long

signed main()
{
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;

        bool flat2025 = false, flat2026 = false;
        for (int i = 0; i + 3 < n; i++) {
            string sub = s.substr(i, 4);
            // cout << "sub : " << sub << endl;
            if (sub == "2026") {
                flat2026 = true;
            }
            if (sub == "2025") {
                flat2025 = true;
            }
        }

        // if (flat2025) {
        //     cout << "flat2025 : true" << endl;
        // }
        // else {
        //     cout << "flat2025 : false" << endl;
        // }

        // if (flat2026) {
        //     cout << "flat2026 : true" << endl;
        // }
        // else {
        //     cout << "flat2026 : false" << endl;  
        // }

        int ans = 0;
        // !flat2025 && !flat2026 0
        // flat2025 && !flat2026 0
        // !flat2025 && flat2026 1
        // flat2025 && flat2026 0
        if (flat2025 && !flat2026) {
            // 有2025，没有2026，改一个2025就可以
            ans = 1;
        }

        cout << ans << endl;
    }

    return 0;
}