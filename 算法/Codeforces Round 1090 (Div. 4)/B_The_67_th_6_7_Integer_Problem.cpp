#include <iostream>
#include <vector>
using namespace std;

#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

#define int long long

signed main(){

    IOS;

    int t;
    cin >> t;
    while(t--){
        int n = 7;
        vector<int> vec(n, 0);
        int sum = 0;
        for(int i = 0; i < n; i++){
            cin >> vec[i];
            sum -= vec[i];
        }

        // cout << sum << endl;

        int ans = LLONG_MIN;
        for (int i = 0; i < n; i++){
            ans = max(ans, sum + 2 * vec[i]);
        }

        cout << ans << endl;
    }

    return 0;
}