#include <iostream>
#include <vector>
using namespace std;

#define int long long

const int mod = 676767677;

int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}



signed main() {

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> p(n);
        for (int i = 0; i < n; i++) {
            cin >> p[i];
        }
        
        int ans = 0;
        for (int i = 0; i < n - 1; i++) {
            int x = p[i];
            int y = p[i + 1];
            int diff = abs(x - y);
            if (diff == gcd(x, y)) {
                ans++;
            }
        }
        cout << ans << '\n';
    }


    return 0;
}