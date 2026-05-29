#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define IOS ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

#define int long long

signed main()
{
    IOS;

    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        string s;
        cin >> s;
        int num_1 = 0;
        int num_2 = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') {
                num_1++;
            }
            else {
                num_2++;
            }
        }

        if (num_1 == num_2) {
            cout << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
        }
    }


    return 0;
}