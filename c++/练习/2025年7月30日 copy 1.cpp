#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <string>
#include <vector>
#include <cstring>
#include <set>
#include <tuple>
#include <queue>
#include <bitset>
#include <utility>

using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define endl '\n'

const int INF = 0x3f3f3f3f;

signed main()
{
    IOS;

    int T;
    cin >> T;
    while(T--)
    {
        int n;
        cin >> n;
        vector<int> arr(n);
        int ans = 0;
        for(int i = 0; i < n; i++)
        {
            cin >> arr[i];
            ans += arr[i]; 
        }

        sort(arr.begin(), arr.end());
        
        int idx = 0;
        while(arr[idx] == 0)
        {
            idx++;
            ans++;
        }

        cout << ans << endl;
    }
    
    

    
    return 0;
}