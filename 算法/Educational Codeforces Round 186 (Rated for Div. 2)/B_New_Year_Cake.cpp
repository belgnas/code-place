#include <iostream>
#include <string>
using namespace std;

#define int long long

signed main()
{
    int t;
    cin >> t;
    while(t--) {
        int a, b;
        cin >> a >> b;

        int res1 = 0;
        int a1 = a, b1 = b;
        int temp1 = 1;
        while (true) {
            // 奇数轮，a1减去temp1
            if (res1 % 2 == 0) {
                a1 -= temp1;
                if (a1 >= 0) {
                    res1++;
                }
                else {
                    break;
                }
            }
            // 偶数轮，b1减去temp1
            else {
                b1 -= temp1;
                if (b1 >= 0) {
                    res1++;
                }
                else {
                    break;
                }
            }
            temp1 = temp1 * 2;
        }

        // cout << "res1 : " << res1 << endl;

        int res2 = 0;
        int a2 = a, b2 = b;
        int temp2 = 1;
        while (true) {
            // 奇数轮，b2减去temp2
            if (res2 % 2 == 0) {
                b2 -= temp2;
                if (b2 >= 0) {
                    res2++;
                }
                else {
                    break;
                }
            }
            // 偶数轮，a2减去temp2
            else {
                a2 -= temp2;
                if (a2 >= 0) {
                    res2++;
                }
                else {
                    break;
                }
            }
            temp2 = temp2 * 2;
        }

        // cout << "res2 : " << res2 << endl;
        
        cout << max(res1, res2) << endl;
    }

    return 0;
}