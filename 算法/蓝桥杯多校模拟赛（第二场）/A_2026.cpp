#include <iostream>
#include <map>
using namespace std;

#define int long long

signed main() {

    // int ans = 287926;
    // cout << ans << endl;

    int ans = 0;
    for (int i = 1; i <= 20262026; i++) {
        int num = i;
        int num2 = 0, num0 = 0, num6 = 0;
        while (num > 0) {
            int temp = num % 10;
            num /= 10;
            if (temp == 2) {
                num2++;
            }
            if (temp == 0) {
                num0++;
            }
            if (temp == 6) {
                num6++;
            }
        }
        if (num2 == 2 && num0 == 1 && num6 == 1) {
            ans++;
        }
    }

    cout << ans << endl;


    return 0;
}