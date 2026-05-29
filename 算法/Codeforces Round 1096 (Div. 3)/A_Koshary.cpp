#include <iostream>
#include <vector>

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
        int x, y;
        cin >> x >> y;
        
        if(x % 2 == 0 || y % 2 == 0) {
            cout << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
        }
        
    }


    return 0;
}