#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

#define int long long

int gcd(int a, int b)
{
    if(b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

// 检查a和b是否互质
bool check_gcd(int a, int b) {
    return gcd(a, b) == 1;
}



signed main()
{
    IOS;
    
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        vector<int> a(n);
        bool has_odd = false;
        bool has_even = false;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            if(a[i] % 2 == 0) {
                has_even = true;
            }else {
                has_odd = true;
            }
        }

        if (has_odd && has_even) {
            cout << "YES" << endl;
            continue;
        }
        if (has_odd || !has_even) {
            bool found = false;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (check_gcd(a[i], a[j])) {
                        cout << "YES" << endl;
                        found = true;
                        break;
                    }
                }
                if (found) {
                    break;
                }
            }
            if (!found) {
                cout << "NO" << endl;
            }
            continue;
        }
        if (!has_odd && has_even) {
            cout << "NO" << endl;
            continue;
        }


        
    }


    
    return 0;
}